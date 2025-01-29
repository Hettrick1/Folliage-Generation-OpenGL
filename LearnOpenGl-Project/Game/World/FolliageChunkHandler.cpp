#include "FolliageChunkHandler.h"

FolliageChunkHandler::FolliageChunkHandler(Camera* camera)
	: mCamera(camera)
{
	LoadChunks(RENDER_DISTANCE, RENDER_DISTANCE);
}

FolliageChunkHandler::~FolliageChunkHandler()
{
}

void FolliageChunkHandler::LoadChunks(unsigned int sizeX, unsigned int sizeY)
{
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			mActiveChunks.emplace_back(mCamera, glm::vec3(i, j, 0.0f));
		}
	}
}

void FolliageChunkHandler::UpdateChunks()
{
}

void FolliageChunkHandler::DrawChunks()
{
	for (FolliageChunk& chunk : mActiveChunks) {
		chunk.Draw();
	}
}
