CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
BUILD_DIR = build

$(BUILD_DIR)/var_reader: $(BUILD_DIR)/scanner.yy.cpp src/var_type.cpp src/var_reader.cpp include/var_type.hpp include/scanner.hpp include/tokens.hpp
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/scanner.yy.cpp src/var_type.cpp src/var_reader.cpp -o $(BUILD_DIR)/var_reader

$(BUILD_DIR)/scanner.yy.cpp: src/scanner.ll include/scanner.hpp include/tokens.hpp | $(BUILD_DIR)
	flex -o $(BUILD_DIR)/scanner.yy.cpp src/scanner.ll

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(BUILD_DIR)/var_reader
	./$(BUILD_DIR)/var_reader

clean:
	rm -rf $(BUILD_DIR)
