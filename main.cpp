#include "raylib.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"
#include "gui.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "clipping.h"

#define WIDTH 800
#define HEIGHT 600
enum DrawType
{
    NONE = -1,
    POLYGON = 0,
    CIRCLE = 1,
    CLIP = 2,

};

// Variáveis globais de estado
bool isClipped = false;
Gui gui = Gui();
Clipping clipping = Clipping();
std::vector<Polygon> polygons;
std::vector<Circle> circles;

DrawType drawType = POLYGON;

void drawCalls();
void updateUserMouseAction();
void checkButtons();

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WIDTH, HEIGHT, "paint fake");
    SetTargetFPS(60);
    // Personalizar cores da caixa de texto
    GuiSetStyle(VALUEBOX, BORDER_COLOR_NORMAL, ColorToInt(DARKGRAY)); // Borda normal
    GuiSetStyle(VALUEBOX, BORDER_COLOR_FOCUSED, ColorToInt(BLUE));    // Borda ao focar
    GuiSetStyle(VALUEBOX, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));  // Fundo normal
    GuiSetStyle(VALUEBOX, BASE_COLOR_FOCUSED, ColorToInt(WHITE));     // Fundo ao focar
    GuiSetStyle(VALUEBOX, BASE_COLOR_PRESSED, ColorToInt(WHITE));     // Fundo ao editar
    GuiSetStyle(VALUEBOX, TEXT_COLOR_NORMAL, ColorToInt(BLACK));      // Cor do texto
    // setup circles and polygons
    circles.reserve(30);
    polygons.reserve(30);

    while (!WindowShouldClose())
    {

        updateUserMouseAction();
        checkButtons();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        drawCalls();

        gui.drawGui();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
// Verifica interações do usuário com os botões da interface
void checkButtons()
{
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
    if (gui.translateBtn)
    {
        gui.translateBtn = false;
        Vector2 t = Vector2{(float)gui.xValue, (float)gui.yValue};
        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).translate(t);
        }
        for (size_t i = 0; i < circles.size(); i++)
        {
            circles.at(i).translate(t);
        }
    }
    if (gui.rotateBtn)
    {
        gui.rotateBtn = false;
        double rad = (double)gui.degrees * M_PI / 180.0;
        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).rotate(rad);
        }
    }
    if (gui.scaleBtn)
    {
        gui.scaleBtn = false;
        float scaleRate = (float)gui.scaleRate / 10;
        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).scale(scaleRate);
        }
        for (size_t i = 0; i < circles.size(); i++)
        {
            circles.at(i).scale(scaleRate);
        }
    }
    if (gui.reflectXBtn)
    {
        gui.reflectXBtn = false;
        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).reflectX();
        }
    }
    if (gui.reflectYBtn)
    {
        gui.reflectYBtn = false;
        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).reflectY();
        }
    }
    if (gui.clipBtn)
    {
        gui.clipBtn = false;
        clipping.hasP1 = false;
        drawType = CLIP;
    }
    if (gui.clearClipBtn)
    {
        gui.clearClipBtn = false;
        clipping.hasP1 = false;
        drawType = NONE;
        isClipped = false;
    }
}
// Executa as chamadas de desenho
void drawCalls()
{
    if (isClipped)
    {
        clipping.applyClip(polygons, gui.cohen_liang);
        clipping.drawClipArea(gui.dda_bre);
    }
    else
    {
        if (clipping.hasP1)
        {
            clipping.drawP1();
        }
        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).drawPolygonPoints();
            if (polygons.at(i).closed)
            {
                polygons.at(i).drawPolygon(gui.dda_bre);
            }
        }
    }
    for (size_t i = 0; i < circles.size(); i++)
    {
        circles.at(i).drawCenter();
        if (circles.at(i).complete)
        {
            circles.at(i).drawCircle();
        }
    }
}
// Captura interações do usuário com o mouse
void updateUserMouseAction()
{
    Vector2 mousePos = GetMousePosition();
    size_t polygonsSize = polygons.size();
    size_t circlesSize = circles.size();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (!gui.checkCollisions(mousePos)) // Ignore clicks on buttons
        {
            if (drawType == POLYGON && polygonsSize > 0 && !polygons.at(polygonsSize - 1).closed)
            {
                polygons.at(polygonsSize - 1).addVertice(mousePos);
            }
            else if (drawType == CIRCLE && circlesSize > 0)
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
            else if (drawType == CLIP)
            {
                if (!clipping.hasP1)
                {
                    isClipped = false;
                    clipping.setP1(mousePos);
                }
                else
                {
                    clipping.setP2(mousePos);
                    isClipped = true;
                    drawType = NONE;
                }
            }
        }
    }
}
