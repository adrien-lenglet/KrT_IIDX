
class Swapchain
{
public:
	class Image
	{
	public:
		Image(Swapchain &swapchain, VkImage image);
		~Image(void);

		Swapchain &swapchain;

		VkImage image;
		VkImageView view;

	private:
	};

	Swapchain(Vk &vk, VkPhysicalDevice physicalDevice);
	Swapchain(Vk &vk);
	~Swapchain(void);

	Vk &vk;

	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;

	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	std::vector<VkPresentModeKHR> presentModes;

	VkExtent2D extent;
	VkSurfaceFormatKHR surfaceFormat;
	VkPresentModeKHR presentMode;
	VkSwapchainKHR swapchain;
	std::vector<Image> images;
	VkRenderPass renderPass;

	bool isValid(void);

private:

	VkSurfaceCapabilitiesKHR getCapabilities(void);
	std::vector<VkSurfaceFormatKHR> getSurfaceFormats(void);
	std::vector<VkPresentModeKHR> getPresentModes(void);

	VkExtent2D getExtent2D(void);
	VkSurfaceFormatKHR getSurfaceFormat(void);
	VkPresentModeKHR getPresentMode(void);
	uint32_t getMinImageCount(void);
	VkSwapchainKHR createSwapchain(void);
	std::vector<Image> fetchImages(void);
	VkRenderPass createRenderPass(void);
};
