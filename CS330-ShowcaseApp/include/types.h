#pragma once
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f};
    glm::vec4 Color {1.f, 1.f, 1.f, 1.f};
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};
