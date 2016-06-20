#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>
#include <GL/glew.h>

//GLM
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/version.h>

using namespace std;
using namespace glm;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char* readAllFile(const char* fpath){
	unsigned long long fsz;
	char* buf;

	FILE* file = fopen(fpath, "r");
	if(file == nullptr){
		printf("Error:: Unable to load shader file: %s\n", fpath);
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	fsz = ftell(file);
	rewind(file);

	buf = new char[fsz+1]();
	if(fread(buf, 1, fsz, file) != fsz){
		printf("Unexpected error while reading file: %s\n", fpath);
		fclose(file);
		delete [] buf;
		return nullptr;
	}
	fclose(file);
	return buf;
}

bool GL_Destroy(SDL_Window* &mainwindow, SDL_GLContext &maincontext){
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();
	return true;
}
bool GL_init(SDL_Window* &mainwindow, SDL_GLContext &maincontext){
	SDL_version SDL_cVer; //SDL version during compilation (Header version)
	SDL_version SDL_rVer; //SDL version during in runtime (Dll version)
	SDL_VERSION(&SDL_cVer);
	SDL_GetVersion(&SDL_rVer);

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Error:: Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	string SDL_err;
	mainwindow = SDL_CreateWindow("SDLTutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);
	if(mainwindow == nullptr){
		printf("Error:: Unable to create SDL window: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}
	if((SDL_err = SDL_GetError()) != ""){
		printf("Error:: SDL Error: %s\n", SDL_err.c_str());
		SDL_ClearError();
	}
    maincontext = SDL_GL_CreateContext(mainwindow);
	if((SDL_err = SDL_GetError()) != ""){
		printf("Error:: SDL Error: %s\n", SDL_err.c_str());
		SDL_ClearError();
	}

	SDL_GL_SetSwapInterval(1);

	if(SDL_cVer.major != SDL_rVer.major || SDL_cVer.minor != SDL_rVer.minor || SDL_cVer.patch != SDL_rVer.patch){
		printf("Warning:: SDL compiled version is different from the DLL.\n");
		printf("\tSDL compiled version: %d.%d.%d\n", SDL_cVer.major, SDL_cVer.minor, SDL_cVer.patch);
		printf("\tSDL runtime version:  %d.%d.%d\n", SDL_rVer.major, SDL_rVer.minor, SDL_rVer.patch);
	}
	else printf("SDL Okay... Using SDL %d.%d.%d\n", SDL_rVer.major, SDL_rVer.minor, SDL_rVer.patch);

	GLenum glew_init = glewInit();
	if(glew_init != GLEW_OK){
		printf("Error:: Glew Init failed: %d: %s\n", glew_init, glewGetErrorString(glew_init));
		GL_Destroy(mainwindow, maincontext);
		return false;
	}
	printf("GLEW Okay... Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("OpenGL Okay... Using OpenGL %s\n", glGetString(GL_VERSION));
	printf("GLM Okay... Using GLM %d.%d.%d\n", GLM_VERSION_MAJOR, GLM_VERSION_MINOR, GLM_VERSION_PATCH);
	glClearColor(0, 0, 0, 1.0);
	return true;
}

mat4 transform(vec2 const &Orientation, vec3 const &Translate, vec3 const &Up){
	mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	mat4 ViewTranslate = translate(mat4(1.0f), Translate);
	mat4 ViewRotateX = rotate(ViewTranslate, Orientation.y, Up);
	mat4 View = rotate(ViewRotateX, Orientation.x, Up);
	mat4 Model = mat4(1.0f);
	return Projection * View * Model;
}

bool Read_Mesh(GLuint &vao, GLuint &vbo, GLuint &veo, const char* fpath){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fpath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

	if(scene == nullptr){
		printf("Error:: Assimp is unable to load Obj File: %s\n", importer.GetErrorString());
		return false;
	}
	else printf("Assimp Okay ... Using Assimp %d.%d.%d\n", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());

	assert(scene->mNumMeshes == 1);
	aiMesh* mesh = scene->mMeshes[0];

	vector<float> Vertices(3 * mesh->mNumVertices);
	vector<unsigned int> Faces(3 * mesh->mNumFaces);

	for(int i = 0; i < mesh->mNumVertices; i++){
		Vertices[3*i+0] = mesh->mVertices[i].x;
		Vertices[3*i+1] = mesh->mVertices[i].y;
		Vertices[3*i+2] = mesh->mVertices[i].z;
	}
	for(int i = 0; i < mesh->mNumFaces; i++){
		assert(mesh->mFaces[i].mNumIndices == 3);
		Faces[3*i+0] = mesh->mFaces[i].mIndices[0];
		Faces[3*i+1] = mesh->mFaces[i].mIndices[1];
		Faces[3*i+2] = mesh->mFaces[i].mIndices[2];
	}

	/*vector<float> Vertices(3*4);
	Vertices[ 0] = -1.0f; Vertices[ 1] = -1.0f; Vertices[ 2] = 0.0f;
	Vertices[ 3] =  0.0f; Vertices[ 4] = -1.0f; Vertices[ 5] = 1.0f;
	Vertices[ 6] =  1.0f; Vertices[ 7] = -1.0f; Vertices[ 8] = 0.0f;
	Vertices[ 9] =  0.0f; Vertices[10] =  1.0f; Vertices[12] = 0.0f;

	vector<unsigned int> Faces(3*4);
	Faces[ 0] = 0; Faces[ 1] = 3; Faces[ 2] = 1;
	Faces[ 3] = 1; Faces[ 4] = 3; Faces[ 5] = 2;
	Faces[ 6] = 2; Faces[ 7] = 3; Faces[ 8] = 0;
	Faces[ 9] = 0; Faces[10] = 1; Faces[12] = 2;
*/
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &veo);

    glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Faces.size(), &Faces[0], GL_STATIC_DRAW);

	return true;
}

bool Read_Shader(GLuint &shaderProgram, const char* vsfpath, const char* fsfpath){
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLchar* vertexSource = readAllFile("shaders/envCheck/VSTest.vs");
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar* fragmentSource = readAllFile("shaders/envCheck/FSTest.fs");
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	delete []vertexSource;
	delete []fragmentSource;
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
	return true;
}

int main(int argc, char* argv[]){
	SDL_Window *mainwindow; SDL_GLContext maincontext;
	SDL_Event event;

	GLuint vao, vbo, veo;
	GLuint shaderProgram;
	GLint posAttrib;

	if(!GL_init(mainwindow, maincontext)) return -1;
	if(!Read_Shader(shaderProgram, "shaders/envCheck/VSTest.vs", "shaders/envCheck/FSTest.fs")) return -1;
	if(!Read_Mesh(vao, vbo, veo, "models/envCheck/pyramid.obj")) return -1;

	glBindFragDataLocation(shaderProgram, 0, "outColor");
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glUseProgram(shaderProgram);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	bool Exit_Flag = false;
	while(!Exit_Flag){
		while(SDL_PollEvent(&event)){	//Handeling events
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_q:
						case SDLK_ESCAPE:
							Exit_Flag = true;
						break;
					}
				break;
				case SDL_QUIT:
					Exit_Flag = true;
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(mainwindow);
	}

	glDisableVertexAttribArray(posAttrib);
	glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

	GL_Destroy(mainwindow, maincontext);
	return 0;
}
