#ifndef IMAGE_CONTAINER_H
#define IMAGE_CONTAINER_H

//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>
#include <vector>

//Thitrd-party includes

//Own includes
#include "utils/drawing/Rectangle.h"
#include "sdl_utils/config/ImageContainerCfg.h"

//Forward Declarations
struct SDL_Texture;


using Frames = std::vector<Rectangle>;
class ImageContainer 
{
public:
	SDL_Texture* getImageTexture(int32_t rsrcId) const;
	const Frames& getImageFrame(int32_t rsrcId) const;

protected:
	int32_t init(const ImageContainerCfg& imageContCfg);
	void deInit();

private:
	int32_t loadSingleResource(const ImageCfg& resCfg, const int32_t rsrcId);

	//the textures we'll be drawing
	std::unordered_map<int32_t, SDL_Texture*> _textures;
	std::unordered_map<int32_t, Frames> _textureFrames;
};


#endif // !IMAGE_CONTAINER_H

