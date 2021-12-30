#include "HatzSimulation.h"

#include <iostream> //temp

bool HatzSim::OnUserCreate() 
{
    Mesh_Create(hatzMesh);

    //temp
    obstacles.push_back({ 0,30, 50,30,  50,30, 50,50,  50,50,0,50,  0,50,0,30 });

    //obstacles.push_back({ 0,0, 50,0,  50,0, 50,20,  50,20,0,20,  0,20,0,0 });

    return true;
}

bool HatzSim::OnUserUpdate(float fElapsedTime) 
{
    Camera_Move();

    Mesh_Move(hatzMesh, *this);

    for (plane p : obstacles) //temp
    {
        //if (Mesh_Collide(hatzMesh, p))
            //std::cout << "Collided!";
    }

    if (GetKey(olc::Key::I).bPressed) //temp
    {
        for (spring s : hatzMesh.springs)
        {
            std::cout << "x: " << s.point[0].position.x << " y: " << s.point[0].position.y << std::endl;
        }
    }

    //Clear
    FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

    for (plane p : obstacles) //temp
    {
        for (line l : p.line)
        {
            DrawLine(l.point[0].x + (int)cameraPosX, l.point[0].y + (int)cameraPosY,
                l.point[1].x + (int)cameraPosX, l.point[1].y + (int)cameraPosY);
        }
    }

    Mesh_Draw(hatzMesh, *this);

    return true;
}

int main()
{
    HatzSim hatzSim;
    if (hatzSim.Construct(256, 240, 3, 3))
        hatzSim.Start();

    return 0;
}