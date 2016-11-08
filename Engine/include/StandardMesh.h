#include "Mesh.h"

#pragma once


/**
 * @brief      A vertex structure that holds per vertex info.
 */
struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};
/**
 * @brief      A texture vertex to reference the Texture id and its type.
 */
struct Texture{
    GLuint id;
    string type;
    string path;
};


class StandardMesh : public Mesh
{

    std::vector<Texture> textures;

    StandardMesh() = delete;
    virtual void setupBuffers() override;

public:
    virtual void draw(Shader *shader) override;
    // $$$$$$$$$$$$$$
    // TESTING PUT BACK IN PRIVATE
    std::vector<Vertex> vertices;
    /**
     * @brief      Mesh contsructor to initialize per mesh components
     *
     * @param[in]  vertices  The vertices
     * @param[in]  indices   The indices
     * @param[in]  textures  The textures
     */
    StandardMesh(vector<Vertex> &vertices, vector<GLuint> &indices, vector<Texture> &textures, glm::mat4& parentTransform);
    /**
     * @brief      Raycasts a ray with all triangles in a mesh
     *
     * @param[in]  start of the ray
     * @param[in]  end of the ray
     * @param      the scaling factor based on the distance of the hit point along the ray direction from the start of the ray.
     *
     * @return     Whether a hit was captured or not.
     */
    bool raycast(const glm::vec3&, const glm::vec3&, float&);
};
