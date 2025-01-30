#include "Plane.h"

Plane::Plane(Camera* camera, glm::vec3 position, glm::vec2 size)
    : mVbo(GL_ARRAY_BUFFER), mPosition(position), mCamera(camera), mShader("Core/OpenGL/Shaders/vertexShader.glsl", "Core/OpenGL/Shaders/fragmentShader.glsl"), mSize(size)
{
	mVertices = {
        0.0f * mSize.x, 0.0f * mSize.y, 0.0f,
        1.0f * mSize.x, 0.0f * mSize.y, 0.0f,
        1.0f * mSize.x, 1.0f * mSize.y, 0.0f,
        1.0f * mSize.x, 1.0f * mSize.y, 0.0f,
        0.0f * mSize.x, 1.0f * mSize.y, 0.0f,
        0.0f * mSize.x, 0.0f * mSize.y, 0.0f,
	};
    mVao.Bind();
    mVbo.BufferData(mVertices.size() * sizeof(float), mVertices.data(), GL_STATIC_DRAW);
    mVbo.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    mVao.Unbind();
}

Plane::~Plane()
{
}

void Plane::Draw()
{
    if (mVertices.size() > 0) {
        mShader.Use();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), mPosition); 
        glm::mat4 view = mCamera->GetViewMatrix(); 
        glm::mat4 projection = mCamera->GetProjectionMatrix(); 
        glm::mat4 mvp = projection * view * model; 

        mShader.SetMat4("u_MVP", mvp);
        mVao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
        mVao.Unbind();
    }
}
