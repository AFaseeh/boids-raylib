#pragma once
#include "boid.hpp"
#include <vector>

class Flock
{
private:
    std::vector<Boid> boids;
public:
    void Init(int initialCount, Vector2 screen);
    
    void Update(const Vector2& mousePos);
    void Draw();
};