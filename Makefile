BIN=./bin
BUILD=./build
SRC=./src
LIB=./lib

GL_UTILS_BUILD=$(BUILD)/GlUtils
SCENE_RENDERER_BUILD=$(BUILD)/SceneRenderer

SYS_INCLUDE=/usr/local/include
OPENGL_ARGS=-framework Opengl -I/usr/local/include -lGLFW -lglew

# Dear ImGui assumed to be in IMGUI
IMGUI=/usr/local/include/imgui
IMGUI_EXAMPLES=$(IMGUI)/examples

MAKEFILE_DIR=$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
GL_UTILS=$(MAKEFILE_DIR)GlUtils
GL_UTILS_SRC=$(GL_UTILS)/src
SCENE_RENDERER=$(MAKEFILE_DIR)/SceneRenderer
SCENE_RENDERER_SRC=$(SCENE_RENDERER)/src

# Assumes that stb_image.h is located in this directory
# Used for texture loading
STB_IMAGE_DIR=$(MAKEFILE_DIR)

# Location of FreeImage install
FREEIMAGE_DIST=/usr/local/include/FreeImage/Dist

CC=g++ --std=c++17
CPP_ARGS=-Wall

all: directories $(LIB)/GlUtils.a $(LIB)/imgui.a


demo: directories demo_vicsek


# VICSEK TWOTRIANGLES DEMO
demo_vicsek: directories $(BIN)/demo_vicsek.o

VICSEK_DEPS = demo_vicsek/main.cpp demo_vicsek/vicsek.fs
# Libs
VICSEK_DEPS += $(addprefix $(LIB)/, GlUtils.a imgui.a)
# GlUtil headers
VICSEK_DEPS += $(addprefix $(GL_UTILS)/, SaveUtils.hpp Shader.hpp TwoTrianglesRenderer.hpp) 
# FreeImage for Png saving
VICSEK_DEPS += $(FREEIMAGE_DIST)

$(BIN)/demo_vicsek.o: $(VICSEK_DEPS)
	$(info $@)
	$(info $^)
	$(CC) $(CPP_ARGS) \
		-I$(GL_UTILS) \
		-I$(STB_IMAGE_DIR) \
		-I$(FREEIMAGE_DIST) \
		$(LIB)/GlUtils.a \
		$(LIB)/imgui.a \
		$(OPENGL_ARGS) \
		$(FREEIMAGE_DIST)/libfreeimage.a \
		-o $@ \
		$(filter %.cpp %.a, $^)


# SCENE RENDERER

$(LIB)/SceneRenderer.a: $(addprefix $(SCENE_RENDERER_BUILD)/, Objects.o Scene.o)
	$(info $@)
	ar rvs $@ $(filter %.o, $^)

$(SCENE_RENDERER_BUILD)/Objects.o: $(SCENE_RENDERER_SRC)/Objects.cpp $(SCENE_RENDERER)/Objects.hpp $(GL_UTILS)/Camera.hpp
	$(info $@)
	$(CC) -c \
		-I$(SYS_INCLUDE) \
		-I$(MAKEFILE_DIR) \
		-o $@ \
		$<

$(SCENE_RENDERER_BUILD)/Scene.o: $(SCENE_RENDERER_SRC)/Scene.cpp $(addprefix $(SCENE_RENDERER)/, Scene.hpp Objects.hpp Lights.hpp)
	$(info $@)
	$(CC) -c \
		-I$(SYS_INCLUDE) \
		-I$(MAKEFILE_DIR) \
		-o $@ \
		$<


# GL UTILS

# Object archive
$(LIB)/GlUtils.a: $(addprefix $(GL_UTILS_BUILD)/, Camera.o Init.o SaveUtils.o Shader.o SimpleRenderer.o TextureUtils.o TwoTrianglesRenderer.o)
	$(info $@)
	ar rvs $@ $(filter %.o, $^)


$(GL_UTILS_BUILD)/TwoTrianglesRenderer.o: $(GL_UTILS_SRC)/TwoTrianglesRenderer.cpp $(GL_UTILS)/TwoTrianglesRenderer.hpp $(GL_UTILS)/SimpleRenderer.hpp
	$(info $@)
	$(CC) -c \
		-I$(SYS_INCLUDE) \
		-I$(MAKEFILE_DIR) \
		-o $@ \
		$<

# GlUtils default - single cpp file with single hpp
$(GL_UTILS_BUILD)/%.o: $(GL_UTILS_SRC)/%.cpp $(GL_UTILS)/%.hpp
	$(info $@)
	$(CC) -c \
		-I$(SYS_INCLUDE) \
		-I$(MAKEFILE_DIR) \
		-I$(IMGUI) \
		-I$(STB_IMAGE_DIR) \
		-I$(FREEIMAGE_DIST) \
		-o $@ \
		$<


# Imgui object archive for OpenGL3 + GLFW 
$(LIB)/imgui.a: $(wildcard $(IMGUI)/*.cpp) $(addprefix $(IMGUI_EXAMPLES)/, imgui_impl_opengl3.cpp imgui_impl_glfw.cpp)
	$(info $@)
	cd $(BUILD)/imgui \
	&& $(CC) -c \
		-I$(IMGUI) \
		-I$(IMGUI_EXAMPLES) \
		$(filter %.cpp, $^) 
	ar rvs $@ $(BUILD)/imgui/*.o


# DIRECTORIES

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

