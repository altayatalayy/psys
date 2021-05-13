
#include "first_app.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "imgui/imgui.h"

void keyCallBack(GLFWwindow *win, int key, int scancode, int action, int mods);
bool s = false;

int main() {
	//glfwSetKeyCallback(window, keyCallBack);
  lve::FirstApp app{};

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
	return EXIT_SUCCESS;
}

void keyCallBack(GLFWwindow *win, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		std::cout << "Pressed space key" << std::endl;
	}
}
