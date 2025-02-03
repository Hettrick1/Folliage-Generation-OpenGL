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

#include <unordered_map>
#include <algorithm>

struct ChunkHash {
	size_t operator()(const std::pair<int, int>& pos) const {
		return std::hash<int>()(pos.first) ^ (std::hash<int>()(pos.second) << 1);
	}
};

struct ChunkEqual {
	bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
		return a.first == b.first && a.second == b.second;
	}
};

class FolliageChunkHandler
{
public:
	FolliageChunkHandler(Camera* camera);
	~FolliageChunkHandler();
	void LoadChunks(int sizeX, int sizeY);
	void UpdateChunks();
	bool IsChunkInFrustum(const glm::vec3& chunkPosition);
	void DrawChunks();
private:
	Camera* mCamera;
	glm::vec3 mPrevCameraPos;
	glm::vec3 mPrevCameraRot;
	glm::vec2 mPrevViewportSize;
	std::unordered_map<std::pair<int, int>, FolliageChunk*, ChunkHash, ChunkEqual> mActiveChunks;
	std::unordered_map<std::pair<int, int>, FolliageChunk*, ChunkHash, ChunkEqual> mUnactiveChunks;
};
