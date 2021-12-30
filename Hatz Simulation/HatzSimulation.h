#pragma once
#include "olcPixelGameEngine.h"
#include "mesh.h"

class HatzSim : public olc::PixelGameEngine
{
public:
	HatzSim();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	float cameraPosX = 0.0f;
	float cameraPosY = 0.0f;
	float cameraSpeed = 400.0f;

private:
	mesh hatzMesh{ 3, 2, 5, 10, 5, 2 };

	std::vector<plane> obstacles;

	void Camera_Move();
};