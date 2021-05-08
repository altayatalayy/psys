CFLAGS = -std=c++17 -I. -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK)/lib `pkg-config --static --libs glfw3` -lvulkan

a.out: *.cpp
		g++ $(CFLAGS) -o a.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: a.out
		./a.out

clean:
		rm -f a.out
