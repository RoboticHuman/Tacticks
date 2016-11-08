#include "Mesh.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#pragma once


class DebugMesh : public Mesh
{
    /**
     * @brief      A vertex structure that holds per vertex info.
     */
    struct Vertex{
        glm::vec3 position;
        glm::vec4 color;
    };

    std::vector<Vertex> vertices;

    virtual void setupBuffers() override;
    int getVertex(float x, float y, float z, short r, short g, short b, short a);

public:
    virtual void draw(Shader *shader) override;
    DebugMesh(glm::mat4& parentTransform);

    // Drawing Functions
    //////////////////////////////////////////
    void drawCuboid(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,
            unsigned char r=255, unsigned char g=255, unsigned char b=255, unsigned char a=255);

    void drawConvexPolygon(vector<glm::vec3>& coord,
            unsigned char r=255, unsigned char g=255, unsigned char b=255, unsigned char a=255);
    //////////////////////////////////////////
};
