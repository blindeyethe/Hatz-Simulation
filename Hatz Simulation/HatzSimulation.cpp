#include "HatzSimulation.h"

HatzSim::HatzSim()
{
    sAppName = "Hatz Simulation";
}

void HatzSim::Camera_Move()
{
    if (GetKey(olc::Key::A).bHeld) cameraPosX += cameraSpeed * GetElapsedTime();
    if (GetKey(olc::Key::D).bHeld) cameraPosX -= cameraSpeed * GetElapsedTime();
    if (GetKey(olc::Key::W).bHeld) cameraPosY += cameraSpeed * GetElapsedTime();
    if (GetKey(olc::Key::S).bHeld) cameraPosY -= cameraSpeed * GetElapsedTime();
}
