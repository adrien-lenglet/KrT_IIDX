
class Swapchain
{
public:
	Swapchain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	Swapchain(Vk &vk);
	~Swapchain(void);

	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;

	VkSwapchainKHR swapchain;
	VkExtent2D extent;
	VkSurfaceFormatKHR format;
	VkPresentModeKHR presentMode;
	std::vector<VkImage> images;

	bool isValid(void);

private:
	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;
	Vk *vk;

	void updateCapabilities(void);

	VkExtent2D getExtent2D(void);
	VkSurfaceFormatKHR getSurfaceFormat(void);
	VkPresentModeKHR getPresentMode(void);
	uint32_t getMinImageCount(void);
	VkSwapchainKHR createSwapchain(void);
};
