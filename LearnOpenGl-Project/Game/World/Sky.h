#pragma once

#include <glad/glad.h>

#include "Utils/CubeTextureMap.h"

#include "Utils/Defs.h"

#include "OpenGL/Shader.h"
#include "OpenGL/Camera.hpp"

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

class Sky
{
private:
	GLuint* mChunk[16][16][200] = { nullptr };
	Camera* mCamera;
	Shader mShader;
	GLuint mTexture;
	glm::vec3 mPosition;
	VertexArray vao;
	VertexBuffer vbo;
	std::vector<float> mAllVertices;
	CubeTextureMap m_CubeMap;
public:
	Sky(Camera* cam, glm::vec3 pos);
	~Sky();
	void Draw();
};

