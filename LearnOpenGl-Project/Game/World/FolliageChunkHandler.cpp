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
	int count = 0;
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			glm::vec3 chunkPosition = glm::vec3(i * CHUNK_SIZE, j * CHUNK_SIZE, 0.0);
			FolliageChunk* newChunk = new FolliageChunk(mCamera, chunkPosition);
			mActiveChunks.push_back(newChunk);
			//mActiveChunks.emplace_back(mCamera, chunkPosition);
			count++;
		}
	}
	std::cout << "chunks : " << count << std::endl;
}

void FolliageChunkHandler::UpdateChunks()
{
}

void FolliageChunkHandler::DrawChunks()
{
	for (FolliageChunk* chunk : mActiveChunks) {
		chunk->Draw();
	}
}
