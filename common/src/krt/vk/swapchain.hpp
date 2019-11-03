
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

	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;

	VkSwapchainKHR swapchain;
	VkExtent2D extent;
	VkSurfaceFormatKHR format;
	VkPresentModeKHR presentMode;
	std::vector<Image> images;

	bool isValid(void);

private:
	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;

	void updateCapabilities(void);

	VkExtent2D getExtent2D(void);
	VkSurfaceFormatKHR getSurfaceFormat(void);
	VkPresentModeKHR getPresentMode(void);
	uint32_t getMinImageCount(void);
	VkSwapchainKHR createSwapchain(void);
	std::vector<Image> fetchImages(void);
};
