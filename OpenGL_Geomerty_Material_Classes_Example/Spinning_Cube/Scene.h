#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"

class Scene
{
private:
	Camera& camera;

public:
	Scene(Camera& camera) : camera(camera) {};
	~Scene() {};
};

#endif // SCENE_H
