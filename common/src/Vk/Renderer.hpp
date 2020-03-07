
#include "Swapchain.hpp"
#include "Semaphore.hpp"
#include "Pipeline.hpp"

namespace Vk {

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
		VkCommandPool commandPool;
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

	Renderer(Swapchain &swapchain);

	Pipeline pipeline;
	Images images;
};

}