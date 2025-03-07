#include "raylib.h"
#include "structures.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"
#include "gui.h"

#define WIDTH 800
#define HEIGHT 600
using namespace std;
enum DrawType
{
    POLYGON = 0,
    CIRCLE = 1,
    NONE = -1,
};

bool drawPoints = false;
Gui gui = Gui();
std::vector<Polygon> polygons;
std::vector<Circle> circles;

DrawType drawType = POLYGON;

void updateGUI()
{
    gui.update();
}

void updateUserAction()
{
    Vector2 mousePos = GetMousePosition();
    int polygonsSize = polygons.size();
    int circlesSize = circles.size();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (!gui.checkCollisions(mousePos)) // Ignore clicks on button
        {
            if (drawType == POLYGON && polygonsSize > 0 && !polygons.at(polygonsSize - 1).closed)
            {

                polygons.at(polygonsSize - 1).addVertice(mousePos);
            }
            if (drawType == CIRCLE && circlesSize > 0)
            {
                if (circles.at(circlesSize - 1).hasCenter == false)
                {
                    circles.at(circlesSize - 1).setCenter(mousePos);
                }
                else
                {
                    circles.at(circlesSize - 1).setRadius(mousePos);
                    drawType = NONE;
                }
            }
        }
    }
}

void drawCalls()
{
    for (int i = 0; i < polygons.size(); i++)
    {
        polygons.at(i).drawPolygonPoints();
        if (polygons.at(i).closed)
        {
            polygons.at(i).drawPolygon();
        }
    }
    for (int i = 0; i < circles.size(); i++)
    {
        circles.at(i).drawCenter();
        if (circles.at(i).complete)
        {
            circles.at(i).draw();
        }
    }
}

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WIDTH, HEIGHT, "paint fake");
    // SetTargetFPS(60);
    circles.reserve(30);
    polygons.reserve(30);

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        gui.update();

        updateUserAction();

        drawCalls();

        if (gui.newPolygonBtn)
        {
            drawType = POLYGON;
            polygons.push_back(Polygon());
            gui.newPolygonBtn = false;
        }

        if (gui.closePolygonBtn)
        {
            gui.closePolygonBtn = false;
            drawType = NONE;
            if (polygons.size() > 0)
            {
                polygons.at(polygons.size() - 1).closePolygon();
            }
            
        }

        if (gui.newCircleBtn)
        {
            gui.newCircleBtn = false;
            drawType = CIRCLE;
            circles.push_back(Circle());
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
