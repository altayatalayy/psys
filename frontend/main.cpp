
#include "first_app.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "imgui/imgui.h"

void keyCallBack(GLFWwindow *win, int key, int scancode, int action, int mods);
bool s = false;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
	glfwSetKeyCallback(window, keyCallBack);

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported\n";

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui::Begin("Hello");
		ImGui::End();
	}

	glfwDestroyWindow(window);
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
