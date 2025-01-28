#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

#include <OpenGL/imageLoader/stb_image.h>
#include "OpenGL/Shader.h"
#include "OpenGL/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

class Plane
{
public:
	Plane() = delete;
	Plane(Camera* camera, glm::vec3 position, glm::vec2 size);
	~Plane();
	void Draw();
private:
	glm::vec3 mPosition;
	glm::vec2 mSize;
	Shader mShader;
	Camera* mCamera;
	VertexArray mVao;
	VertexBuffer mVbo;
	std::vector<float> mVertices;
};

