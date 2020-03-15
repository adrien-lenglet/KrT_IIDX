#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "Device.hpp"
#include "Dep/VulkanDevice.hpp"
#include "Queue.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class Swapchain : public Dep::VulkanDevice
{
public:
	class Image : public Dep::VulkanDevice
	{
	public:
		Image(Swapchain &swapchain, VkImage image);
		Image(Swapchain::Image &&other);
		~Image(void);

		Swapchain &swapchain;

		VkImage image;
		VkImageView view;
		VkFramebuffer framebuffer;

	private:
		VkImageView createImageView(void);
		VkFramebuffer createFramebuffer(void);
	};

	Swapchain(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice);
	Swapchain(VkSurfaceKHR surface, Device &dev, Queue &queue);
	~Swapchain(void);

	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;

	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	std::vector<VkPresentModeKHR> presentModes;

	VkExtent2D extent;
	VkSurfaceFormatKHR surfaceFormat;
	VkPresentModeKHR presentMode;
	VkSwapchainKHR swapchain;
	VkRenderPass renderPass;
	std::vector<Image> images;

	bool isValid(void);
	Queue& getQueue(void) const;

private:
	Queue *m_queue;

	VkSurfaceCapabilitiesKHR getCapabilities(void);

	VkExtent2D getExtent2D(void);
	VkSurfaceFormatKHR getSurfaceFormat(void);
	VkPresentModeKHR getPresentMode(void);
	uint32_t getMinImageCount(void);
	VkSwapchainKHR createSwapchain(Device &device);
	VkRenderPass createRenderPass(void);
	std::vector<Image> fetchImages(void);
};

}
}
}