CFLAGS = -std=c++17 -I. -I$(VULKAN_SDK)/include
LDFLAGS = -L$(VULKAN_SDK)/lib `pkg-config --static --libs glfw3` -lvulkan
IMGUIFILES = $(shell find $(IMGUIDIR) -name '*.cpp')
IMGUIOBJS = $(shell find $(IMGUIDIR) -name '*.o')

# create list of all spv files and set as dependency
vertSources = $(shell find ./shaders -type f -name "*.vert")
vertObjFiles = $(patsubst %.vert, %.vert.spv, $(vertSources))
fragSources = $(shell find ./shaders -type f -name "*.frag")
fragObjFiles = $(patsubst %.frag, %.frag.spv, $(fragSources))

TARGET = a.out
$(TARGET): $(vertObjFiles) $(fragObjFiles)
$(TARGET): *.cpp *.hpp
	g++ $(CFLAGS) -o $(TARGET) *.cpp $(LDFLAGS) 

# make shader targets
%.spv: %
	${GLSLC} $< -o $@

imgui:
	g++ -c $(IMGUIFILES) $(CFLAGS) $(LDFLAGS)
	mv imgui*.o $(IMGUIDIR)
	g++ $(CFLAGS) -o imgui.out imgui_test.cpp $(LDFLAGS) $(IMGUIOBJS)

tv.out: tv.c
	gcc  -I$(VULKAN_SDK)/include -o tv.out tv.c $(LDFLAGS) -std=c17

.PHONY: test clean imgui

test: a.out
	./a.out

clean:
	rm -f a.out
	rm -f *.spv
