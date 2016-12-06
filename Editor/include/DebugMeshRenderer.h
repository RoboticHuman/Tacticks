#pragma once
#include <map>
#include <memory>
#include <GL/glew.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "Tacticks/DebugFactory.h"
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>
class DebugMeshRenderer {

    struct DebugMeshRenderData{
        DebugMeshRenderData(std::vector<DebugMesh::Vertex>& vertices,std::vector<GLuint>& indices){
            sizeOfIndices=indices.size();
            setupBuffers(vertices,indices);
            moved = false;
        }
        ~DebugMeshRenderData(){
            if(moved) return;
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDeleteVertexArrays(1,&VAO);
            glDeleteBuffers(1,&VBO);
            glDeleteBuffers(1,&EBO);
        }
        DebugMeshRenderData(DebugMeshRenderData&& oldData):VAO(std::move(oldData.VAO)),VBO(std::move(oldData.VBO)),EBO(std::move(oldData.EBO))
        {
            moved = false;
            oldData.moved = true;
        }
        DebugMeshRenderData& operator =(DebugMeshRenderData&& oldData){
            VAO=std::move(oldData.VAO),VBO=std::move(oldData.VBO),EBO=std::move(oldData.EBO);
            moved = false;
            oldData.moved = true;
        }
        bool moved;
        GLuint VAO, VBO, EBO;
        int sizeOfIndices;
        void draw(glm::mat4& globalTransform){
            GLuint transformLocation = ResourceManager::getShader("debugMeshShader")->getUniformLocation("meshTransform");
            glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(globalTransform));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, sizeOfIndices, GL_UNSIGNED_INT,0);
            glBindVertexArray(0);
        }
        void setupBuffers(std::vector<DebugMesh::Vertex>& vertices,std::vector<GLuint>& indices){
            //generate vertex array
            glGenVertexArrays(1, &VAO);
            //generate vertex buffer object to store vertex data
            glGenBuffers(1, &VBO);
            //generate element buffer object to allow for indexed drawing
            glGenBuffers(1, &EBO);

            //let OpenGL bind to the vertex array we generated above
            glBindVertexArray(VAO);
            //let OpenGL bind to the vertex buffer object before we can copy vertex data
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            //copy vertex data into vertex buffer object
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (DebugMesh::Vertex), &vertices[0], GL_STATIC_DRAW);
            //let OpenGL bind to the element buffer so that we copy the vertex indices to it.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

            //enable vertex attribute "position" in vertex shader at layout location 0.
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DebugMesh::Vertex),(GLvoid*)0);

            //enable vertex attribute "normals" in vertex shader at layout location 1.
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(DebugMesh::Vertex), (GLvoid*)offsetof(DebugMesh::Vertex, color));

            glBindVertexArray(0);
        }
    };

private:
    std::vector<std::weak_ptr<DebugMesh> > debugMeshPtrs;
    std::vector<DebugMeshRenderData> debugMeshData;
public:
    std::vector<bool> bDrawDebugMeshes;
    DebugMeshRenderer ()=default;
    void draw();
    void update();

};
