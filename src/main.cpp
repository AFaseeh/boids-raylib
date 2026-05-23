#include "raylib.h"
#include "flock.hpp"

int main(void)
{
    const Vector2 screen = {1920, 1080};

    InitWindow(screen.x, screen.y, "Boids Simulation");

    SetTargetFPS(60);

    Flock flock;
    flock.Init(750, screen);
    while (!WindowShouldClose())
    {
        // Event handling
        //----------------------------------------------------------------------------------
        // maybe get mouse pos and make boids move away from it?

        // Update
        //----------------------------------------------------------------------------------
        flock.Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        flock.Draw();

        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}