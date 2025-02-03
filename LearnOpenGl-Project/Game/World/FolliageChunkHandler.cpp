#include "FolliageChunkHandler.h"

FolliageChunkHandler::FolliageChunkHandler(Camera* camera)
    : mCamera(camera)
{
    LoadChunks(RENDER_DISTANCE, RENDER_DISTANCE);
}

FolliageChunkHandler::~FolliageChunkHandler()
{
    for (auto& pair : mActiveChunks) delete pair.second;
    for (auto& pair : mUnactiveChunks) delete pair.second;
    mActiveChunks.clear();
    mUnactiveChunks.clear();
}

void FolliageChunkHandler::LoadChunks(int sizeX, int sizeY)
{
    int count = 0;
    for (int i = -sizeX; i < sizeX; i++) {
        for (int j = -sizeY; j < sizeY; j++) {
            glm::vec3 chunkPosition = glm::vec3(i * CHUNK_SIZE, j * CHUNK_SIZE, 0.0);
            FolliageChunk* newChunk = new FolliageChunk(mCamera, chunkPosition);

            bool isInFrustum = IsChunkInFrustum(chunkPosition);
            if (isInFrustum) {
                mActiveChunks[{i, j}] = newChunk;
            }
            else {
                mUnactiveChunks[{i, j}] = newChunk;
            }

            count++;
        }
    }
    std::cout << "Chunks loaded: " << count << std::endl;
}

void FolliageChunkHandler::UpdateChunks()
{
    glm::vec3 cameraPos = mCamera->GetPosition();
    glm::vec3 cameraRot = mCamera->GetForwardVector();
    glm::vec2 viewportSize = mCamera->GetCameraSize();

    if (cameraPos != mPrevCameraPos || cameraRot != mPrevCameraRot || viewportSize != mPrevViewportSize)
    {
        int camChunkX = static_cast<int>(cameraPos.x / CHUNK_SIZE);
        int camChunkY = static_cast<int>(cameraPos.y / CHUNK_SIZE);

        for (auto it = mActiveChunks.begin(); it != mActiveChunks.end(); )
        {
            FolliageChunk* chunk = it->second;
            glm::vec3 chunkPos = chunk->GetPosition();
            int chunkX = static_cast<int>(chunkPos.x / CHUNK_SIZE);
            int chunkY = static_cast<int>(chunkPos.y / CHUNK_SIZE);

            if (!IsChunkInFrustum(chunkPos))
            {
                mUnactiveChunks[{chunkX, chunkY}] = chunk;
                it = mActiveChunks.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = mUnactiveChunks.begin(); it != mUnactiveChunks.end(); )
        {
            FolliageChunk* chunk = it->second;
            glm::vec3 chunkPos = chunk->GetPosition();
            int chunkX = static_cast<int>(chunkPos.x / CHUNK_SIZE);
            int chunkY = static_cast<int>(chunkPos.y / CHUNK_SIZE);

            if (IsChunkInFrustum(chunkPos))
            {
                mActiveChunks[{chunkX, chunkY}] = chunk;
                it = mUnactiveChunks.erase(it);
            }
            else
            {
                ++it;
            }
        }

        mPrevCameraPos = cameraPos;
        mPrevCameraRot = cameraRot;
        mPrevViewportSize = viewportSize;
    }
}

bool FolliageChunkHandler::IsChunkInFrustum(const glm::vec3& chunkPosition)
{
    Frustum frustumPlanes = mCamera->GetFrustum();
    glm::vec3 chunkSize = glm::vec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

    for (const FrustumPlane& plane : frustumPlanes.planes) {
        int outsideCount = 0;
        for (int x = -1; x <= 1; x += 2) {
            for (int y = -1; y <= 1; y += 2) {
                for (int z = -1; z <= 1; z += 2) {
                    glm::vec3 corner = chunkPosition + glm::vec3(x, y, z) * chunkSize;
                    if (glm::dot(plane.normal, corner) + plane.d < 0) {
                        outsideCount++;
                    }
                }
            }
        }
        if (outsideCount == 8) {
            return false;
        }
    }
    return true;
}

void FolliageChunkHandler::DrawChunks()
{
    for (auto& pair : mActiveChunks) {
        pair.second->Draw();
    }
}
