#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>

class Boid
{
private:
    /* data */
public:
    Vector2 position;
    Vector2 velocity;
    static float minSpeed, maxSpeed;
    static float coherenceFactor;
    static float separationFactor, seperationDistance;
    static float alignmentFactor;
    static float perceptionRadius;
    static float minX, maxX, minY, maxY, turnFactor;
    static float mouseSeparationDistance, mouseSeparationFactor;

    static void InitSimulation(Vector2 screen);

    Boid();
    void Update(const std::vector<Boid>& boids, const Vector2& mousePos);
};