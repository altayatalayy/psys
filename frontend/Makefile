CFLAGS = -std=c++17 -I. -I$(VULKAN_SDK)/include
LDFLAGS = -L$(VULKAN_SDK)/lib `pkg-config --static --libs glfw3` -lvulkan
IMGUIDIR = imgui
IMGUIFILES = $(shell find $(IMGUIDIR) -name '*.cpp')
IMGUIOBJS = $(shell find $(IMGUIDIR) -name '*.o')

a.out: *.cpp
		g++ $(CFLAGS) -o a.out main.cpp $(LDFLAGS) $(IMGUIOBJS)

imgui:
	g++ -c $(IMGUIFILES) $(CFLAGS) $(LDFLAGS)
	mv imgui*.o $(IMGUIDIR)
	g++ $(CFLAGS) -o imgui.out imgui_test.cpp $(LDFLAGS) $(IMGUIOBJS)

%.o:%.cpp
	g++ -c (%%).cpp -o (%%).o

tv.out: tv.c
	gcc  -I$(VULKAN_SDK)/include -o tv.out tv.c $(LDFLAGS) -std=c17

.PHONY: test clean imgui

test: a.out
		./a.out

clean:
		rm -f a.out
