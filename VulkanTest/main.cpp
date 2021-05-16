#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <string>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	GLFWwindow* mWindow; //pointer points to the actual window
	VkInstance mInstance; //it holds the handle to the vulkan instance

	

	void initWindow()
	{
		glfwInit(); //initializes the GLFW library
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //tell GLFW to not create an OenGL context
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable resized window
		mWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan()
	{
		createInstance();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(mWindow))
		{
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		vkDestroyInstance(mInstance, nullptr);
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void createInstance()
	{
		//********************VkApplicationInfo*******************//
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//*******************VkInstanceCreationInfo**************//
		//VkInstanceCreateInfo is not optional
		//It tells the Vulkan driver which global extensions and validation layers we want to use
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		//Retrieve a list of supported Vulkan extensions
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		std::unordered_set<std::string> supportedExtensionList;
		std::cout << "available extensions:\n";
		for (const auto& extension : extensions)
		{
			std::cout << '\t' << extension.extensionName << '\n';
			supportedExtensionList.insert(std::string(extension.extensionName));
		}

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		//Check if the required extensions are included in the support extension lists
		for (int i = 0; i < glfwExtensionCount; i++)
		{
			const char* glfwRequiredExtension = glfwExtensions[i];
			if (supportedExtensionList.find(std::string(glfwRequiredExtension)) == supportedExtensionList.end())
			{
				std::cout << "required vulkan extension " << glfwRequiredExtension << " is not supported" << std::endl;
				throw std::runtime_error("required vulkan extension is not supported");
			}
		}

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		//*****************Create a Vulkan Instance**********************//
		if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
	}
};

int main()
{
	HelloTriangleApplication app;

	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}