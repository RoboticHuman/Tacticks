#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "../../Editor/include/Shader.h"


#pragma once

class DebugMesh
{
    /**
     * @brief      A vertex structure that holds per vertex info.
     */
    struct Vertex{
        glm::vec3 position;
        glm::vec4 color;
    };

    GLuint VAO, VBO, EBO;
    glm::mat4& globalTransform;


    int getVertex(float x, float y, float z, float r, float g, float b, float a);

public:
	// $$$$$$$$$$$$$$
	// TESTING PUT BACK IN PRIVATE
    void setupBuffers();
	std::vector<GLuint> indices;
    std::vector<Vertex> vertices;





    void draw(Shader* shader);
    DebugMesh(glm::mat4& parentTransform);

    // Drawing Functions
    //////////////////////////////////////////
    void drawCuboid(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,
             float r=1,  float g=1,  float b=1,  float a=1);

    void drawConvexPolygon(std::vector<glm::vec3>& coord,
             float r=1,  float g=1,  float b=1,  float a=1);
    //////////////////////////////////////////
};
