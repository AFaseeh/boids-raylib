#include "flock.hpp"

void Flock::Init(int initialCount, Vector2 screen)
{
    Boid::InitSimulation(screen);
    for (int i = 0; i < initialCount; i++)
    {
        boids.push_back(Boid());
    }
}

void Flock::Update()
{
    for (auto& boid : boids) {
        boid.Update(boids);
    }
}

void Flock::Draw()
{
    for (const auto& boid : boids) {
        DrawCircleV(boid.position, 4.0f, BLUE);
    }
}
