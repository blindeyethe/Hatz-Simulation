#include "mesh.h"
#include "HatzSimulation.h"

bool Mesh_Collide(mesh& m, plane& p)
{
    line springLine;
    for (spring& spring : m.springs)
    {
        springLine.point[0] = spring.point[0].position;
        springLine.point[1] = spring.point[1].position;

        bool allOut = true;
        for (line& line : p.line)
        {
            for (vec2d& point : line.point)
            {
                if (Line_DistanceTo(springLine, point) < 0.0f)
                {
                    allOut = false;
                    break;
                }
            }
        }

        if (allOut)
            return false;
    }

    for (line& line : p.line)
    {
        bool allOut = true;
        for (spring& spring : m.springs)
        {
            for (point& point : spring.point)
            {
                if (Line_DistanceTo(line, point.position) < 0.0f)
                {
                    allOut = false;
                    break;
                }
            }
        }

        if (allOut)
            return false;
    }

    return true;
}

void Mesh_Move(mesh& m, HatzSim& hatzSim)
{
    for (spring& s : m.springs)
    {
        for (point& p : s.point)
        {
            p.force = { 0, 0 };

            //Gravity
            p.force.y += 9.8 * p.mass;

            //Euler Integration
            vec2d Vt, Pt;
            Vt = ToVector_Multiply(p.force, hatzSim.GetElapsedTime());
            Vt = ToVector_Divide(Vt, p.mass);
            p.velocity = Vector_Add(p.velocity, Vt);

            Pt = ToVector_Multiply(p.velocity, hatzSim.GetElapsedTime());
            p.position = Vector_Add(p.position, Pt);
        }

        //Hooke's Law
        vec2d Fs, dm, x;
        dm = Vector_SubtractModulus(s.point[1].position, s.point[0].position);
        x = ToVector_Subtract(dm, m.L0);

        Fs = ToVector_Multiply(x, m.Ks);

        vec2d Fd, Ft, d, v;
        d = Vector_Normalise(s.point[1].position, s.point[0].position);
        v = Vector_Subtract(s.point[1].velocity, s.point[0].velocity);

        Fd = Vector_Multiply(d, v);
        Fd = ToVector_Multiply(Fd, m.Kd);

        Ft = Vector_Add(Fs, Fd);

        vec2d F1, F2;
        F1 = Vector_Normalise(s.point[1].position, s.point[0].position);
        F1 = Vector_Multiply(F1, Ft);

        F2 = Vector_Normalise(s.point[0].position, s.point[1].position);
        F2 = Vector_Multiply(F2, Ft);

        //Spring Force
        s.point[0].force = Vector_Add(s.point[0].force, F1);
        s.point[1].force = Vector_Add(s.point[1].force, F2);
    }
}

void Mesh_Draw(mesh& m, HatzSim& hatzSim)
{
    for (spring& spr : m.springs)
    {
        hatzSim.DrawCircle(spr.point[0].position.x + (int)hatzSim.cameraPosX,
            spr.point[0].position.y + (int)hatzSim.cameraPosY, 1, olc::RED);

        hatzSim.DrawCircle(spr.point[1].position.x + (int)hatzSim.cameraPosX,
            spr.point[1].position.y + (int)hatzSim.cameraPosY, 1, olc::RED);

        hatzSim.DrawLine(spr.point[0].position.x + (int)hatzSim.cameraPosX, spr.point[0].position.y + (int)hatzSim.cameraPosY,
            spr.point[1].position.x + (int)hatzSim.cameraPosX, spr.point[1].position.y + (int)hatzSim.cameraPosY);
    }
}

void Mesh_Create(mesh& m)
{
    int length = m.L0;
    float mass = m.pointMass;
    int numberCubesX = m.numberCubesX;
    int numberCubesY = m.numberCubesY;

    if (numberCubesX % 2 == 0)
        numberCubesX--;

    if (numberCubesY % 2 == 0)
        numberCubesY--;

    int grow1 = 0;
    int grow2 = length;
    for (int i = 0; i < numberCubesX; i++)
    {
        for (int j = 0; j < numberCubesY; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 == 0)
                {
                    //Top
                    m.springs.push_back({ (float)length * i, (float)grow1, {}, {}, mass,
                                          (float)grow2, (float)grow1, {}, {}, mass });

                    //Right
                    m.springs.push_back({ (float)grow2 , (float)grow1 , {}, {}, mass,
                                          (float)grow2 , (float)grow1 + length, {}, {}, mass });

                    //Bottom
                    m.springs.push_back({ (float)grow2 , (float)grow1 + length, {}, {}, mass,
                                          (float)length * i, (float)length * (j + 1), {}, {}, mass });

                    //Left
                    m.springs.push_back({ (float)length * i, (float)length * (j + 1), {}, {}, mass,
                                          (float)length * i, (float)grow1, {}, {}, mass });
                }
                else
                {
                    //Right
                    m.springs.push_back({ (float)grow2 , (float)grow1 , {}, {}, mass,
                                          (float)grow2 , (float)grow1 + length, {}, {}, mass });

                    //Left
                    m.springs.push_back({ (float)length * i, (float)length * (j + 1), {}, {}, mass,
                                          (float)length * i, (float)grow1, {}, {}, mass });
                }
            }
            else
            {
                if (j % 2 == 0)
                {
                    //Top
                    m.springs.push_back({ (float)length * i, (float)grow1, {}, {}, mass,
                                          (float)grow2, (float)grow1, {}, {}, mass });

                    //Bottom
                    m.springs.push_back({ (float)grow2 , (float)grow1 + length, {}, {}, mass,
                                          (float)length * i, (float)length * (j + 1), {}, {}, mass });
                }
            }

            //Main Diagonal 
            m.springs.push_back({ (float)length * i, (float)grow1, {}, {}, mass,
                                  (float)grow2, (float)grow1 + length, {}, {}, mass });

            //Secondary Diagonal 
            m.springs.push_back({ (float)grow2, (float)grow1, {}, {}, mass,
                                  (float)length * i, (float)length * (j + 1), {}, {}, mass });

            grow1 += length;
        }
        grow1 = 0;
        grow2 += length;
    }
}