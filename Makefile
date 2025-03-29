# Compilator și opțiuni
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -Iinclude

# Directoare
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = lib
GLAD_DIR = $(LIB_DIR)/glad

# Output final
TARGET = $(BUILD_DIR)/coffee_invaders

# Liste de fișiere sursă (C++)
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
GLAD_OBJ = $(BUILD_DIR)/glad.o

# Librării necesare
LIBS = -lglfw -lGL -ldl -lm -lstdc++
INCLUDES = -I$(GLAD_DIR)/include -I/usr/include -I$(LIB_DIR) -Iinclude

# Regula principală
all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(GLAD_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Reguli pentru compilarea fișierelor
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilarea separată a glad.c
$(GLAD_OBJ): $(GLAD_DIR)/src/glad.c | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creare director build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Curățare
clean:
	rm -rf $(BUILD_DIR)

# Rulare joc
run: $(TARGET)
	./$(TARGET)
