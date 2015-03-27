#ifndef _OPENGL_MESH
#define _OPENGL_MESH

// Include GLEW
#include <GL/glew.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLFramework/common/shader.hpp>
#include <OpenGLFramework/common/texture.hpp>

class OpenGLContent{
	static unsigned int idSeed;
	unsigned int objectID;
protected:
	glm::mat4 M;
	glm::mat4 localM;
public:
	OpenGLContent();
	virtual bool loadResourcesToMainMemory()=0;
	virtual bool allocateOpenGLResources()=0;
	virtual bool render(glm::mat4 P, glm::mat4 V)=0;
	virtual bool unallocateAllResources()=0;
	inline OpenGLContent& setModelMatrix(glm::mat4 M){
		this->M=M; // model matrix used as the absolute one
		this->localM=M; //local model matrix
		return *this;
	}
	inline OpenGLContent& setAbsoluteModelMatrix(glm::mat4 M){
			this->M=M;
			return *this;
	}
	inline glm::mat4 getModelMatrix(){
		return localM; //return local model matrix
	}
	inline unsigned int getID(){return objectID;}
};

#endif
