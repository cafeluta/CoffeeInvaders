CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -Ilib/glad/include
LDFLAGS := -lGL -lglfw -ldl

SRC_DIR := src
OBJ_DIR := build
LIB_DIR := lib/glad/src

SOURCES := $(wildcard $(SRC_DIR)/Engine/*.cpp) \
           $(wildcard $(SRC_DIR)/Game/*.cpp) \
           $(SRC_DIR)/stb_image.cpp \
           $(LIB_DIR)/glad.c \
           cfi.cpp

OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES)))

TARGET := game

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean