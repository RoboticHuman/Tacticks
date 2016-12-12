#pragma once
#include <map>
#include <memory>
#include <GL/glew.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <Tacticks/DebugFactory.h>
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class DebugMeshRenderer {

    struct DebugMeshRenderData{
        DebugMeshRenderData(std::vector<DebugMesh::Vertex>& vertices,std::vector<GLuint>& indices);
        ~DebugMeshRenderData();
        DebugMeshRenderData(DebugMeshRenderData&& oldData);
        DebugMeshRenderData& operator=(DebugMeshRenderData&& oldData);
        bool moved;
        GLuint VAO, VBO, EBO;
        int sizeOfIndices;
        void draw(glm::mat4& globalTransform);
        void setupBuffers(std::vector<DebugMesh::Vertex>& vertices,std::vector<GLuint>& indices);
    };

private:
    static std::vector<std::weak_ptr<DebugMesh> > debugMeshPtrs;
    static std::vector<DebugMeshRenderData> debugMeshData;
public:
    static std::vector<bool> bDrawDebugMeshes;
    static const std::vector<std::weak_ptr<DebugMesh> >& getDebugMeshCache();
    
    DebugMeshRenderer()=default;
    static void draw();
    static void update();

};
