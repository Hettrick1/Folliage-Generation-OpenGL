#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

#include <OpenGL/imageLoader/stb_image.h>
#include "OpenGL/Shader.h"
#include "OpenGL/Camera.hpp"
#include "FolliageChunk.h"
#include "Utils/Defs.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class FolliageChunkHandler
{
public:
	FolliageChunkHandler(Camera* camera);
	~FolliageChunkHandler();
	void LoadChunks(int sizeX, int sizeY);
	void UpdateChunks();
	void DrawChunks();
private:
	Camera* mCamera;
	std::vector<FolliageChunk*> mActiveChunks; // here it's pointers because not all my chuks are the same size
	std::vector<FolliageChunk*> mUnActiveChunks;
};
