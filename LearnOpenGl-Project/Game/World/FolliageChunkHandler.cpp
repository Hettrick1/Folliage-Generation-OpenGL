#include "FolliageChunkHandler.h"

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

std::unordered_map<std::pair<int, int>, FolliageChunk*, ChunkHash, ChunkEqual> activeChunks;
std::unordered_map<std::pair<int, int>, FolliageChunk*, ChunkHash, ChunkEqual> unactiveChunks;

FolliageChunkHandler::FolliageChunkHandler(Camera* camera)
    : mCamera(camera)
{
    LoadChunks(RENDER_DISTANCE, RENDER_DISTANCE);
}

FolliageChunkHandler::~FolliageChunkHandler()
{
    for (auto& pair : activeChunks) delete pair.second;
    for (auto& pair : unactiveChunks) delete pair.second;
    activeChunks.clear();
    unactiveChunks.clear();
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
                activeChunks[{i, j}] = newChunk;
            }
            else {
                unactiveChunks[{i, j}] = newChunk;
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

        for (auto it = activeChunks.begin(); it != activeChunks.end(); )
        {
            FolliageChunk* chunk = it->second;
            glm::vec3 chunkPos = chunk->GetPosition();
            int chunkX = static_cast<int>(chunkPos.x / CHUNK_SIZE);
            int chunkY = static_cast<int>(chunkPos.y / CHUNK_SIZE);

            if (!IsChunkInFrustum(chunkPos))
            {
                unactiveChunks[{chunkX, chunkY}] = chunk;
                it = activeChunks.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = unactiveChunks.begin(); it != unactiveChunks.end(); )
        {
            FolliageChunk* chunk = it->second;
            glm::vec3 chunkPos = chunk->GetPosition();
            int chunkX = static_cast<int>(chunkPos.x / CHUNK_SIZE);
            int chunkY = static_cast<int>(chunkPos.y / CHUNK_SIZE);

            if (IsChunkInFrustum(chunkPos))
            {
                activeChunks[{chunkX, chunkY}] = chunk;
                it = unactiveChunks.erase(it);
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
    for (auto& pair : activeChunks) {
        pair.second->Draw();
    }
}
