#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

struct GrassInstanceData {
    glm::vec3 position;
    float rotation;
    float windStrengh;
    float bend;
};