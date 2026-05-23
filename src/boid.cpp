#include "boid.hpp"
#include <random>

float Boid::minSpeed = 0.0f;
float Boid::maxSpeed = 0.0f;
float Boid::coherenceFactor = 0.0f;
float Boid::separationFactor = 0.0f;
float Boid::seperationDistance = 0.0f;
float Boid::alignmentFactor = 0.0f;
float Boid::perceptionRadius = 0.0f;
float Boid::minX = 0.0f;
float Boid::maxX = 0.0f;
float Boid::minY = 0.0f;
float Boid::maxY = 0.0f;
float Boid::turnFactor = 0.0f;
float Boid::mouseSeparationDistance = 0.0f;
float Boid::mouseSeparationFactor = 0.0f;

void Boid::InitSimulation(Vector2 screen)
{
    float borderOffset = 300.0f;
    minX = borderOffset, maxX = screen.x - borderOffset;
    minY = borderOffset, maxY = screen.y - borderOffset;

    minSpeed = 100.0f;
    maxSpeed = 200.0f;
    perceptionRadius = 50.0f;
    seperationDistance = 20.0f;

    
    coherenceFactor = 0.005f;
    separationFactor = 0.1f;
    alignmentFactor = 0.025f;
    
    mouseSeparationDistance = 100.0f;
    mouseSeparationFactor = 0.25;
    turnFactor = 3;
}

Boid::Boid()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> x_rand(minX, maxX);
    static std::uniform_real_distribution<float> y_rand(minY, maxY);

    static std::uniform_real_distribution<float> angle_rand(0.0f, 2.0f * PI);
    static std::uniform_real_distribution<float> speed_rand(minSpeed, maxSpeed);

    // position randomization
    this->position = Vector2{x_rand(gen), y_rand(gen)};

    // velocity randomization
    float speed = speed_rand(gen);
    float angle = angle_rand(gen);

    this->velocity = Vector2{speed * cosf(angle), speed * sinf(angle)};
}

void Boid::Update(const std::vector<Boid>& boids, const Vector2& mousePos)
{
    Vector2 close = {0.0f, 0.0f};
    Vector2 velocityAvg = {0.0f, 0.0f};
    Vector2 positionAvg = {0.0f, 0.0f};
    int neighbors = 0;

    Vector2 mouseClose = (Vector2Distance(position, mousePos) < mouseSeparationDistance ? (position - mousePos) : Vector2{0.0f, 0.0f});
    for (const auto& other : boids)
    {
        if (this == &other) continue;
        
        float distance = Vector2Distance(position, other.position);

        // Seperation
        if (distance <= Boid::seperationDistance)
        {
            close.x += position.x - other.position.x;
            close.y += position.y - other.position.y;
        }
        // Alignment & Cohesion
        if (distance <= Boid::perceptionRadius)
        {
            velocityAvg += other.velocity;
            positionAvg += other.position;
            neighbors++;
        }


    }
    this->velocity += close * Boid::separationFactor + mouseClose * Boid::mouseSeparationFactor;
    if (neighbors > 0)
    {
        velocityAvg /= neighbors;
        positionAvg /= neighbors;

        velocity += (velocityAvg - velocity) * Boid::alignmentFactor;   // alignment
        velocity += (positionAvg - position) * Boid::coherenceFactor;   // cohesion
    }

    if (position.x < minX)
        velocity.x += turnFactor;
    else if (position.x > maxX)
        velocity.x -= turnFactor;
    else if (position.y < minY)
        velocity.y += turnFactor;
    else if (position.y > maxY)
        velocity.y -= turnFactor;
    
    float speed = Vector2Length(velocity);

    if (speed > Boid::maxSpeed)
        velocity *= Boid::maxSpeed / speed;
    else if (speed < Boid::minSpeed)
        velocity *= Boid::minSpeed / speed; 

    position += velocity * GetFrameTime();
}

