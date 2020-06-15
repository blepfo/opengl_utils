BIN=./bin
BUILD=./build
SRC=./src
LIB=./lib

OPENGL_ARGS=-framework Opengl -I/usr/local/include -lGLFW -lglew

# Dear ImGui assumed to be in IMGUI
IMGUI=/usr/local/include/imgui
IMGUI_EXAMPLES=$(IMGUI)/examples

MAKEFILE_DIR=$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
GL_UTILS=$(MAKEFILE_DIR)GlUtils

# Assumes that stb_image.h is located in this directory
# Used for texture loading
STB_IMAGE_DIR=$(MAKEFILE_DIR)

CC=g++ --std=c++17
CPP_ARGS=-Wall

all: directories $(LIB)/GlUtils.a $(LIB)/imgui.a


# Vicsek TwoTrianglesRenderer demo
demo_vicsek: $(BIN)/demo_vicsek.o

$(BIN)/demo_vicsek.o: demo_vicsek/main.cpp demo_vicsek/vicsek.fs $(LIB)/imgui.a $(LIB)/GlUtils.a
	$(info $@)
	$(CC) $(CPP_ARGS) \
		-I$(IMGUI) \
		-I$(GL_UTILS) \
		-I$(STB_IMAGE_DIR) \
		$(OPENGL_ARGS) \
		-o $@ \
		$(filter %.cpp %.a, $^)

# GlUtils - Uses 
$(LIB)/GlUtils.a: $(wildcard $(GL_UTILS)/src/*.cpp) $(wildcard $(GL_UTILS)/*.hpp)
	$(info $@)
	cd $(BUILD)/GlUtils \
	&& $(CC) -c \
		-I$(IMGUI) \
		-I$(MAKEFILE_DIR) \
		-I$(STB_IMAGE_DIR) \
		$(filter %.cpp, $^)
	ar rvs $@ $(BUILD)/GlUtils/*.o

$(LIB)/imgui.a: $(wildcard $(IMGUI)/*.cpp) $(wildcard $(IMGUI)/*.h) $(IMGUI_EXAMPLES)/imgui_impl_opengl3.cpp $(IMGUI_EXAMPLES)/imgui_impl_glfw.cpp
	$(info $@)
	cd $(BUILD)/imgui \
	&& $(CC) -c \
		-I$(IMGUI) \
		-I$(IMGUI_EXAMPLES) \
		$(filter %.cpp, $^) 
	ar rvs $@ $(BUILD)/imgui/*.o

directories: $(BIN) $(LIB) $(BUILD)/imgui/ $(BUILD)/GlUtils/

$(BUILD)/%/: 
	mkdir -p $@

$(LIB):
	mkdir -p $@

$(BIN):
	mkdir -p $@



.PHONY: clean
clean:
	rm -rf $(BUILD) $(LIB) $(BIN)

