#include "FolliageChunk.h"

FolliageChunk::FolliageChunk(Camera* camera, glm::vec3 position)
	: mCamera(camera), mPosition(position), mVbo(GL_ARRAY_BUFFER), mInstanceVbo(GL_ARRAY_BUFFER), mShader("Core/OpenGL/Shaders/grassVertexShader.glsl", "Core/OpenGL/Shaders/grassFragmentShader.glsl")
{
    std::vector<float> mGrassBladeVertices = {    
        // Triangle 1
        0.0f, 0.0f, 0.0f,  // Bas gauche
        0.05f, 0.0f, 0.0f,  // Bas droite
        0.05f, 0.0f, 0.3f,  // Haut droite
    
        // Triangle 2
        0.05f, 0.0f, 0.3f,  // Haut droite
        0.0f, 0.0f, 0.3f,  // Haut gauche
        0.0f, 0.0f, 0.0f,   // Bas gauche

        // Triangle 3
        0.0f, 0.0f, 0.3f,  // Bas gauche
        0.05f, 0.0f, 0.3f,  // Bas droite
        0.05f, 0.0f, 0.5f,  // Haut droite

        // Triangle 4
        0.05f, 0.0f, 0.5f,  // Haut droite
        0.0f, 0.0f, 0.5f,  // Haut gauche
        0.0f, 0.0f, 0.3f,   // Bas gauche

        // Triangle 5
        0.05f, 0.0f, 0.5f,  // Haut droite
        0.025f, 0.0f, 0.7f,  // Haut gauche
        0.0f, 0.0f, 0.5f   // Bas gauche
    };
    for (int i = 0; i < 1000; ++i) {
        float x = (rand() % 100) / 100.0f;
        float y = (rand() % 100) / 100.0f;
        mGrassPositions.push_back(glm::vec3(x, y, 0.0f));
    }
    mVao.Bind();

    mVbo.BufferData(mGrassBladeVertices.size() * sizeof(float), mGrassBladeVertices.data(), GL_STATIC_DRAW);
    mVbo.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Positions
    glEnableVertexAttribArray(0);

    mInstanceVbo.BufferData(mGrassPositions.size() * sizeof(glm::vec3), mGrassPositions.data(), GL_STATIC_DRAW);
    mInstanceVbo.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    mVao.Unbind();
}

FolliageChunk::~FolliageChunk()
{
}

void FolliageChunk::Draw()
{
    mShader.Use();

    // Calculer la matrice MVP
    glm::mat4 model = glm::translate(glm::mat4(1.0f), mPosition);
    glm::mat4 view = mCamera->GetViewMatrix();
    glm::mat4 projection = mCamera->GetProjectionMatrix();
    glm::mat4 mvp = projection * view * model;

    mShader.SetMat4("u_MVP", mvp);

    // Dessiner les brins d'herbe avec instancing
    mVao.Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 30, 1000);
    mVao.Unbind();
}
