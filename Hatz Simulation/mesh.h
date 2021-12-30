#pragma once
#include "vec2d.h"
#include "plane.h"
#include <vector>

class HatzSim;

struct point
{
    vec2d position;
    vec2d velocity;
    vec2d force;
    float mass;
};

struct spring
{
    point point[2];
};

struct mesh
{
    float pointMass;

    std::vector<spring> springs;
    float Ks; //Stiffness
    float L0; //Rest Length
    float Kd; //Damping Factor

    int numberCubesX;
    int numberCubesY;

    mesh(int cubesX, int cubesY, float stiffness, float length, float dumpingFactor, float mass) :
        numberCubesX(cubesX), numberCubesY(cubesY), Ks(stiffness), L0(length), Kd(dumpingFactor), pointMass(mass) {}
};

bool Mesh_Collide(mesh& m, plane& p);
void Mesh_Move(mesh& m, HatzSim& hatzSim);
void Mesh_Draw(mesh& m, HatzSim& hatzSim);
void Mesh_Create(mesh& m);