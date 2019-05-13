/**
 * @file Texture_Cube.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_TEXTURE_CUBE_H_
#define OPENGL_SCENE_TEXTURE_CUBE_H_

#include "Texture.hpp"

namespace prz
{
	
	class Texture_Cube : public Texture
	{
	private:

		static const GLenum textureTarget_[];
		
		Texture_Cube(PBuffer<PImage&> cubeImages) :
			Texture(GL_TEXTURE_CUBE_MAP, cubeImages)
		{}
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_TEXTURE_CUBE_H_
