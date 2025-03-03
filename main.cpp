#include "raylib.h"
#include "rasterization.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 600, "raygui - controls test suite");
    SetTargetFPS(60);

    Point p1 = {100, 100};
    Point p2 = {200, 200};
    bool showMessageBox = false;
    Rasterization r = Rasterization();
    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        
        if (GuiButton({24, 24, 120, 30}, "#191#Show Message"))
        {
            r.startDDA(p1, p2);
            showMessageBox = true;
        }
        if (showMessageBox)
        {
            int result = GuiMessageBox({85, 70, 250, 100},
                                       "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

            if (result >= 0)
                showMessageBox = false;
        }
        if (r.desenhando)
        {
            r.updateDDA(p1);
        }
        else if(r.iniciou == true)
        {
            r.normalDDA(p1, p2);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
