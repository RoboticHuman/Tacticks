#include <vector>
#include <limits>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "DebugMesh.h"

using namespace std;

DebugMesh::DebugMesh(glm::mat4& parentTransform):globalTransform(parentTransform)
{

}

int DebugMesh::getVertex(float x, float y, float z, float r, float g, float b, float a)
{
    /*
    TODO: FIND A WAY TO MAKE MORE EFFICIENT CHECKS
    for (int i=0; i<vertices.size(); i++) {
        if (std::abs(x - vertices[i].position.x) > numeric_limits<float>::epsilon()) continue;
        if (std::abs(y - vertices[i].position.y) > numeric_limits<float>::epsilon()) continue;
        if (std::abs(z - vertices[i].position.z) > numeric_limits<float>::epsilon()) continue;
        // FIX THE BELLOW CHECKS TO WORK FOR FLOATS
        if (r - vertices[i].color.x != 0) continue;
        if (g - vertices[i].color.y != 0) continue;
        if (b - vertices[i].color.z != 0) continue;
        if (a - vertices[i].color.w != 0) continue;
        return i;
    }
*/
    Vertex t;
    t.position = glm::vec3(x,y,z);
    t.color = glm::vec4(r,g,b,a);
    vertices.push_back(t);

    return vertices.size()-1;
}

void DebugMesh::drawCuboid(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,
                float r, float g, float b, float a)
{
    /*
     2-----6
     |\    |\
     | 3-----7
     0-|---4 |
      \|    \|
       1-----5
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
    indices.push_back(inds[0]);
    indices.push_back(inds[1]);

    indices.push_back(inds[1]);
    indices.push_back(inds[3]);
    indices.push_back(inds[2]);

    // Up face
    indices.push_back(inds[6]);
    indices.push_back(inds[2]);
    indices.push_back(inds[3]);

    indices.push_back(inds[6]);
    indices.push_back(inds[3]);
    indices.push_back(inds[7]);

    // Back face
    indices.push_back(inds[3]);
    indices.push_back(inds[1]);
    indices.push_back(inds[5]);

    indices.push_back(inds[3]);
    indices.push_back(inds[5]);
    indices.push_back(inds[7]);

    // Right face
    indices.push_back(inds[7]);
    indices.push_back(inds[5]);
    indices.push_back(inds[4]);

    indices.push_back(inds[7]);
    indices.push_back(inds[4]);
    indices.push_back(inds[6]);

    // Forward face
    indices.push_back(inds[6]);
    indices.push_back(inds[4]);
    indices.push_back(inds[0]);

    indices.push_back(inds[6]);
    indices.push_back(inds[0]);
    indices.push_back(inds[2]);

    // Down face
    indices.push_back(inds[4]);
    indices.push_back(inds[5]);
    indices.push_back(inds[1]);

    indices.push_back(inds[4]);
    indices.push_back(inds[1]);
    indices.push_back(inds[0]);
}


void DebugMesh::drawConvexPolygon(vector<glm::vec3>& coord,
                float r, float g, float b, float a)
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
