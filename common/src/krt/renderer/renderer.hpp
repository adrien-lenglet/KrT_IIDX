
#include "pipeline/pipeline.hpp"

class Renderer
{
public:
	class Image
	{
	public:
		Image(Swapchain::Image &swapchainImage);
		Image(Image &&that);
		~Image(void);

		Swapchain::Image &swapchainImage;
		VkCommandBuffer commandBuffer;
		Semaphore imageAvailable;
		Semaphore renderFinished;

	private:
		VkCommandBuffer createCommandBuffer(void);
	};

	class Images
	{
	public:
		Images(Swapchain &swapchain);
		~Images(void);

		Image& nextImage(void);

	private:
		Swapchain &swapchain;

		std::vector<Image> images;

		std::vector<Image> createImages(void);
	};

	Renderer(Vk &vk);

	Pipeline pipeline;
	Images images;
};
