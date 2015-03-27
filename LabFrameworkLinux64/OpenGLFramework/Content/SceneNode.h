#ifndef _SCENE_NODE
#define _SCENE_NODE
#include <OpenGLFramework/Content/OpenGLContent.h>
#include <map>

class SceneNode:public OpenGLContent{
	std::map<unsigned int, OpenGLContent*> children;
public:
	virtual bool loadResourcesToMainMemory(){
		bool result=true;
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			result&=it->second->loadResourcesToMainMemory();
		return result;
	}
	virtual bool allocateOpenGLResources(){
		bool result=true;
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			result&=it->second->allocateOpenGLResources();
		return result;
	}
	virtual bool render(glm::mat4 P, glm::mat4 V){
		bool result=true;
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		//We set the absolute model matrix of the children by accumulating with ours
		for(;it!=children.end();it++) {
			it->second->setAbsoluteModelMatrix(this->M*it->second->getModelMatrix());
			result&=it->second->render(P,V);
		}
		return result;
	}
	virtual bool unallocateAllResources(){
		bool result=true;
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			result&=it->second->unallocateAllResources();
		return result;
	}
	
	/**Add an object to the node.*/
	inline void addChild(OpenGLContent* child){
		children[child->getID()]=child;
	}

	/**Retrieve a child from the node. The child is still stored in the node*/
	inline OpenGLContent* getChild(unsigned int id){
		if(children.find(id)!=children.end())
			return children[id];
		return NULL;
	}

	/**Retrieve a child from the node. The child is removed from the node*/
	inline OpenGLContent* removeChild(unsigned int id){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.find(id);
		if(it!=children.end()){
			OpenGLContent* result=it->second;
			children.erase(it);
			return result;
		}
		return NULL;
	}
	~SceneNode(){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			delete(it->second);	
	}
};

#endif
