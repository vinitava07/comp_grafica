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


void drawCalls();
void updateUserAction();
void updateGUI();

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WIDTH, HEIGHT, "paint fake");
    SetTargetFPS(60);
    // Personalizar cores da caixa de texto
    GuiSetStyle(VALUEBOX, BORDER_COLOR_NORMAL, ColorToInt(DARKGRAY));  // Borda normal
    GuiSetStyle(VALUEBOX, BORDER_COLOR_FOCUSED, ColorToInt(BLUE));     // Borda ao focar
    GuiSetStyle(VALUEBOX, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));   // Fundo normal
    GuiSetStyle(VALUEBOX, BASE_COLOR_FOCUSED, ColorToInt(WHITE));      // Fundo ao focar
    GuiSetStyle(VALUEBOX, BASE_COLOR_PRESSED, ColorToInt(WHITE));      // Fundo ao editar
    GuiSetStyle(VALUEBOX, TEXT_COLOR_NORMAL, ColorToInt(BLACK));       // Cor do texto
    //setup circles and polygons
    circles.reserve(30);
    polygons.reserve(30);

    while (!WindowShouldClose())
    {

        updateUserAction();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        drawCalls();

        gui.update();

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

void updateGUI()
{
    gui.update();
}
