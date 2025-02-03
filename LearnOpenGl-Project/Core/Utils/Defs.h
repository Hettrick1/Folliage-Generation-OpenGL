#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define RENDER_DISTANCE 20
#define CHUNK_SIZE 5
#define PI 3.14159265358979323846264338327950288419716939937510582

#define DEFAULT_WINDOW_X 1280
#define DEFAULT_WINDOW_Y 800
#define GL_VERSION_MAJOR 3
#define GL_VERSION_MINOR 2

struct FrustumPlane {
    glm::vec3 normal;
    float d;
};

struct Frustum {
    FrustumPlane planes[6]; // Left, Right, Bottom, Top, Near, Far
};
