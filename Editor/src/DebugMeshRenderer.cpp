#include "DebugMeshRenderer.h"

DebugMeshRenderer::DebugMeshRenderData::DebugMeshRenderData(std::vector<DebugMesh::Vertex>& vertices,std::vector<GLuint>& indices){
	sizeOfIndices=indices.size();
	setupBuffers(vertices,indices);
	moved = false;
}
DebugMeshRenderer::DebugMeshRenderData::DebugMeshRenderData(DebugMeshRenderer::DebugMeshRenderData&& oldData):VAO(oldData.VAO),VBO(oldData.VBO),EBO(oldData.EBO)
{
	VAO=oldData.VAO;
	VBO=oldData.VBO;
	EBO=oldData.EBO;
	sizeOfIndices = oldData.sizeOfIndices;
	moved = false;
	oldData.moved = true;
}
DebugMeshRenderer::DebugMeshRenderData::~DebugMeshRenderData(){
	if(moved) return;
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
}
DebugMeshRenderer::DebugMeshRenderData& DebugMeshRenderer::DebugMeshRenderData::operator=(DebugMeshRenderer::DebugMeshRenderData&& oldData){
	VAO=oldData.VAO;
	VBO=oldData.VBO;
	EBO=oldData.EBO;
	sizeOfIndices = oldData.sizeOfIndices;
	moved = false;
	oldData.moved = true;
	return *this;
}
void DebugMeshRenderer::DebugMeshRenderData::draw(glm::mat4& globalTransform){
	GLuint transformLocation = ResourceManager::getShader("debugMeshShader")->getUniformLocation("meshTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(globalTransform));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sizeOfIndices, GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}
void DebugMeshRenderer::DebugMeshRenderData::setupBuffers(std::vector<DebugMesh::Vertex>& vertices,std::vector<GLuint>& indices){
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

void DebugMeshRenderer::update()
{
    DebugFactory::update();
    const std::vector<std::weak_ptr<DebugMesh> >& debugMeshes=DebugFactory::getDebugMeshCacheReference();

    for (int i=0; i<debugMeshPtrs.size();) {
        if (debugMeshPtrs[i].expired()) {
            debugMeshPtrs.erase(debugMeshPtrs.begin()+i);
            debugMeshData.erase(debugMeshData.begin()+i);
            bDrawDebugMeshes.erase(bDrawDebugMeshes.begin()+i);
        }
        else {
            i++;
        }
    }

    for(int i=debugMeshPtrs.size() ; i<debugMeshes.size(); i++){
        debugMeshPtrs.push_back(debugMeshes[i]);

        debugMeshData.push_back(DebugMeshRenderData(debugMeshPtrs.back().lock()->vertices,debugMeshPtrs.back().lock()->indices));
        bDrawDebugMeshes.push_back(false);
    }
}

void DebugMeshRenderer::draw()
{
    for(int i=0;i<bDrawDebugMeshes.size();i++)
    {
        if(bDrawDebugMeshes[i])
            debugMeshData[i].draw(debugMeshPtrs[i].lock()->getGlobalTransform());
    }
}

const std::vector<std::weak_ptr<DebugMesh> >& DebugMeshRenderer::getDebugMeshCache() 
{
	return debugMeshPtrs;
}
