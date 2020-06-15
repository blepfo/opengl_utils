BIN=./bin
BUILD=./build
SRC=./src
LIB=./lib

OPENGL_ARGS=-framework Opengl -I/usr/local/include -lGLFW -lglew

# Dear ImGui assumed to be in IMGUI
IMGUI=/usr/local/include/imgui
IMGUI_EXAMPLES=$(IMGUI)/examples

MAKEFILE_DIR=$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
STB_IMAGE_DIR=$(MAKEFILE_DIR)

GL_UTILS=$(MAKEFILE_DIR)GlUtils

CC=g++ --std=c++17

all: $(LIB)/GlUtils.a $(LIB)/imgui.a

$(LIB)/GlUtils.a: $(LIB) $(BUILD)/GlUtils/ $(wildcard $(GL_UTILS)/src/*.cpp) $(wildcard $(GL_UTILS)/*.hpp)
	$(info $@)
	cd $(BUILD)/GlUtils \
	&& $(CC) -c \
		-I$(IMGUI) \
		-I$(MAKEFILE_DIR) \
		-I$(STB_IMAGE_DIR) \
		$(filter %.cpp, $^)
	ar rvs $@ $(BUILD)/GlUtils/*.o

$(LIB)/imgui.a: $(LIB) $(BUILD)/imgui/ $(wildcard $(IMGUI)/*.cpp) $(wildcard $(IMGUI)/*.h) $(IMGUI_EXAMPLES)/imgui_impl_opengl3.cpp $(IMGUI_EXAMPLES)/imgui_impl_glfw.cpp
	$(info $@)
	cd $(BUILD)/imgui \
	&& $(CC) -c \
		-I$(IMGUI) \
		-I$(IMGUI_EXAMPLES) \
		$(filter %.cpp, $^) 
	ar rvs $@ $(BUILD)/imgui/*.o

$(BUILD)/%/: 
	mkdir -p $@

$(LIB):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD) $(LIB) $(BIN)

