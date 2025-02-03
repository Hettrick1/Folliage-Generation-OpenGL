#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

#include <OpenGL/imageLoader/stb_image.h>
#include "OpenGL/Shader.h"
#include "OpenGL/Camera.hpp"
#include "Utils/Defs.h"
#include "Utils/GrassInstanceData.h"
#include "Utils/FastNoiseLite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

class FolliageChunk
{
public:
	FolliageChunk() = delete;
	FolliageChunk(Camera* camera, glm::vec3 position);
	~FolliageChunk();
	void Draw();
	glm::vec3 GetPosition();
private:
	glm::vec3 mPosition;
	Shader mShader;
	Camera* mCamera;
	VertexArray mVao;
	VertexBuffer mVbo, mInstanceVbo;
	std::vector<float> mGrassBladeVertices;
	std::vector<GrassInstanceData> mGrassInstances;
	FastNoiseLite mWindStrenghNoise;
	glm::vec3 mLightDir;
	glm::vec3 mLightColor;
	glm::vec3 mAmbientColor;
};

