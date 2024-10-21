CC=g++
BUILD_DIR=build
TARGET=$(BUILD_DIR)/graph
SOURCE=graph.cpp main.cpp
OBJECTS=$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCE))

.PHONY: $(BUILD_DIR) clean

all: $(BUILD_DIR) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
