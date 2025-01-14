# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wunused-variable -Wunused-function -g

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Google Test (installed via apt)
GTEST_INCLUDE_DIR = /usr/include/gtest
GTEST_LIB_DIR = /usr/lib/x86_64-linux-gnu

# Files
SRC_FILES = $(SRC_DIR)/Vehicle.cpp $(SRC_DIR)/Charger.cpp $(SRC_DIR)/Simulation.cpp
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/simulator

# Google Test files for unit tests
TEST_SRC_FILES = $(TEST_DIR)/test_main.cpp
TEST_OBJ_FILES = $(TEST_SRC_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_TARGET = $(BIN_DIR)/test_simulator

# Default target
all: $(TARGET)

# Rule to build target
$(TARGET): $(OBJ_FILES) $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) $(OBJ_DIR)/main.o -o $(TARGET)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build object files for the main application
$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the test target (excluding main.cpp)
$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) $(TEST_OBJ_FILES) -o $(TEST_TARGET) -I$(GTEST_INCLUDE_DIR) -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -pthread

# Rule to build object files for tests
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE_DIR) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything
rebuild: clean all

# Run tests and then run the main application
run_tests: $(TEST_TARGET)
	$(TEST_TARGET) # Run the tests
	$(TARGET) # Run the main application after tests

.PHONY: all clean rebuild run_tests
