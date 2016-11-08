#include <vector>
#include <limits>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "DebugMesh.h"
#include "ResourceManager.h"
#include "Shader.h"

using namespace std;

DebugMesh::DebugMesh(glm::mat4& parentTransform):Mesh(parentTransform)
{
}

int DebugMesh::getVertex(float x, float y, float z, short r, short g, short b, short a)
{
    for (int i=0; i<vertices.size(); i++) {
        if (std::abs(x - vertices[i].position.x) > numeric_limits<float>::epsilon()) continue;
        if (std::abs(y - vertices[i].position.y) > numeric_limits<float>::epsilon()) continue;
        if (std::abs(z - vertices[i].position.z) > numeric_limits<float>::epsilon()) continue;
        if (r - vertices[i].color.x != 0) continue;
        if (g - vertices[i].color.y != 0) continue;
        if (b - vertices[i].color.z != 0) continue;
        if (a - vertices[i].color.w != 0) continue;
        return i;
    }
    
    Vertex t;
    t.position = glm::vec3(x,y,z);
    t.color = glm::vec4(r,g,b,a);
    vertices.push_back(t);
    
    return vertices.size()-1;
}

void DebugMesh::drawCuboid(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,
                unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    /*
     
     3-----7
     |\    |\
     | 2-----6
     1-|---5 |
      \|    \|
       0-----4
     
     */
    vector<int> inds(8);
    float xDiff = maxX - minX;
    float yDiff = maxY - minY;
    float zDiff = maxZ - minZ;
    
    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++)
            for (int k=0; k<2; k++)
                inds[4*i+2*j+k] = getVertex(minX+i*xDiff, minY+j*yDiff, minZ+k*zDiff, r,g,b,a);
    
    
    // Left face
    indices.push_back(inds[2]);
    indices.push_back(inds[1]);
    indices.push_back(inds[0]);
    
    indices.push_back(inds[2]);
    indices.push_back(inds[3]);
    indices.push_back(inds[1]);
    
    // Up face
    indices.push_back(inds[6]);
    indices.push_back(inds[3]);
    indices.push_back(inds[2]);
    
    indices.push_back(inds[6]);
    indices.push_back(inds[7]);
    indices.push_back(inds[3]);
    
    // Back face
    indices.push_back(inds[3]);
    indices.push_back(inds[5]);
    indices.push_back(inds[1]);
    
    indices.push_back(inds[3]);
    indices.push_back(inds[7]);
    indices.push_back(inds[5]);
    
    // Right face
    indices.push_back(inds[7]);
    indices.push_back(inds[4]);
    indices.push_back(inds[5]);
    
    indices.push_back(inds[7]);
    indices.push_back(inds[6]);
    indices.push_back(inds[4]);
    
    // Forward face
    indices.push_back(inds[6]);
    indices.push_back(inds[0]);
    indices.push_back(inds[4]);
    
    indices.push_back(inds[6]);
    indices.push_back(inds[2]);
    indices.push_back(inds[4]);
    
    // Down face
    indices.push_back(inds[4]);
    indices.push_back(inds[1]);
    indices.push_back(inds[5]);
    
    indices.push_back(inds[4]);
    indices.push_back(inds[0]);
    indices.push_back(inds[1]);
}

                          
void DebugMesh::drawConvexPolygon(vector<glm::vec3>& coord,
                unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    vector<int> inds;
    inds.reserve(coord.size());
    
    for (int i=0; i<coord.size(); i++)
        inds.push_back(getVertex(coord[i].x,coord[i].y,coord[i].z,r,g,b,a));
    
    // Draw in a polygon strip sort of manner
    for (int i=1; i<inds.size()-1; i++) {
        indices.push_back(inds[0]);
        indices.push_back(inds[i]);
        indices.push_back(inds[i+1]);
    }
    
}

void DebugMesh::draw(Shader *shader)
{
    GLuint transformLocation = ResourceManager::getShader("meshShader")->getUniformLocation("meshTransform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(globalTransform));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}


void DebugMesh::setupBuffers()
{
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (Vertex), &vertices[0], GL_STATIC_DRAW);
    //let OpenGL bind to the element buffer so that we copy the vertex indices to it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    
    // $$$$$$$$$$$$$$$$$$$$$$$
    // TODO BING ATTRIBUTES WHEN SHADER IS READY
    /*
    
    //enable vertex attribute "position" in vertex shader at layout location 0.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)0);
    
    //enable vertex attribute "normals" in vertex shader at layout location 1.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    
    //enable vertex attribute "texCoords" in vertex shader at layout location 2.
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
     
     */
    
    glBindVertexArray(0);
}












