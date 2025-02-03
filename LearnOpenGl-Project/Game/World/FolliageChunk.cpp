#include "FolliageChunk.h"

FolliageChunk::FolliageChunk(Camera* camera, glm::vec3 position)
	: mCamera(camera), mPosition(position), mVbo(GL_ARRAY_BUFFER), mInstanceVbo(GL_ARRAY_BUFFER), mShader("Core/OpenGL/Shaders/grassVertexShader.glsl", "Core/OpenGL/Shaders/grassFragmentShader.glsl")
{
    mGrassBladeVertices = {    
        // Triangle 1
        0.0f, 0.0f, 0.0f,  // Bas gauche
        0.1f, 0.0f, 0.0f,  // Bas droite
        0.1f, 0.0f, 0.3f,  // Haut droite
    
        // Triangle 2
        0.1f, 0.0f, 0.3f,  // Haut droite
        0.0f, 0.0f, 0.3f,  // Haut gauche
        0.0f, 0.0f, 0.0f,   // Bas gauche

        // Triangle 3
        0.0f, 0.0f, 0.3f,  // Bas gauche
        0.1f, 0.0f, 0.3f,  // Bas droite
        0.075f, 0.0f, 0.5f,  // Haut droite

        // Triangle 4
        0.075f, 0.0f, 0.5f,  // Haut droite
        0.025f, 0.0f, 0.5f,  // Haut gauche
        0.0f, 0.0f, 0.3f,   // Bas gauche

        // Triangle 5
        0.075f, 0.0f, 0.5f,  // Haut droite
        0.05f, 0.0f, 0.7f,  // Haut gauche
        0.025f, 0.0f, 0.5f   // Bas gauche
    };

    mLightDir = glm::normalize(glm::vec3(-1.0f, -1.0f, -0.5f));
    mLightColor = glm::vec3(1.2f, 1.0f, 0.8f);
    mAmbientColor = glm::vec3(0.2f, 0.3f, 0.2f);

    mWindStrenghNoise.SetSeed(1234);
    mWindStrenghNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 4000 ; ++i) {
        float x = (rand() % 100) / 50.0f * CHUNK_SIZE;
        float y = (rand() % 100) / 50.0f * CHUNK_SIZE;
        float rotation = -(rand() % 90) * (PI / 180);
        float bend = (rand() % 360) * (PI / 180.0f);
        float strengh = mWindStrenghNoise.GetNoise(mPosition.x + x, mPosition.y + y);
        mGrassInstances.push_back({ glm::vec3(x, y, 0.0f), rotation, strengh * 5, bend});
    }
    mVao.Bind();

    mVbo.BufferData(mGrassBladeVertices.size() * sizeof(float), mGrassBladeVertices.data(), GL_STATIC_DRAW);
    mVbo.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    mInstanceVbo.BufferData(mGrassInstances.size() * sizeof(GrassInstanceData), mGrassInstances.data(), GL_STATIC_DRAW);
    mInstanceVbo.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GrassInstanceData), (void*)offsetof(GrassInstanceData, position));
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    mInstanceVbo.VertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(GrassInstanceData), (void*)offsetof(GrassInstanceData, rotation));
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    mInstanceVbo.VertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GrassInstanceData), (void*)offsetof(GrassInstanceData, windStrengh));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    mInstanceVbo.VertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(GrassInstanceData), (void*)offsetof(GrassInstanceData, bend));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);
    mVao.Unbind();
}

FolliageChunk::~FolliageChunk()
{

}

void FolliageChunk::Draw()
{
    mShader.Use();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), mPosition);
    glm::mat4 view = mCamera->GetViewMatrix();
    glm::mat4 projection = mCamera->GetProjectionMatrix();
    glm::mat4 mvp = projection * view * model;

    mShader.SetMat4("u_MVP", mvp);
    mShader.SetFloat("u_timer", glfwGetTime());

    mShader.SetVec3("u_LightDirection", mLightDir);
    mShader.SetVec3("u_LightColor", mLightColor);
    mShader.SetVec3("u_AmbientColor", mAmbientColor);

    mVao.Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, mGrassBladeVertices.size() / 3, mGrassInstances.size()); 
    mVao.Unbind();
}

glm::vec3 FolliageChunk::GetPosition()
{
    return mPosition;
}
