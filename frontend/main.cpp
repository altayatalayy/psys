
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vulkan/vulkan.h>

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

	glfwTerminate();

	return 0;
}

void keyCallBack(GLFWwindow *win, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		std::cout << "Pressed space key" << std::endl;
	}
}
