#ifndef RENDERER_H
#define RENDERER_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes

//Forward Declarations
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;


class Renderer 
{
public:
	Renderer() = default;
	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&& other) = delete;

	Renderer& operator=(const Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) = delete;

	int32_t init(SDL_Window* window);
	void deInit();
	void clearScreen();
	void finishFrame();
	void renderTexture(SDL_Texture* texture);

private:
	SDL_Renderer* _sdlRenderer = nullptr;
};


#endif // !RENDERER_H
