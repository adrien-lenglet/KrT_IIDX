
#include "Swapchain.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "Pipeline.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

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
		Fence inFlight;
		VkFence imageInFlight;

	private:
		VkCommandBuffer createCommandBuffer(void);
	};

	Renderer(Swapchain &swapchain, Queue &presentationQueue);
	~Renderer(void);

	void render(void);

private:
	Swapchain &swapchain;
	Queue &presentationQueue;
	Pipeline pipeline;
	std::vector<Renderer::Image> images;
	size_t currentImage;

	uint32_t nextImage(void);
	std::vector<Renderer::Image> createImages(void);
};

}
}
}