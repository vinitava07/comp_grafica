#pragma once
#include <vector>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>

#ifndef GUI_H
#define GUI_H

#define WIDTH 800
#define HEIGHT 600

class Gui
{
private:
    std::vector<Rectangle> buttonsRect;
    enum Buttons
    {
        NEW_POLYGON = 0,
        CLOSE_POLYGON,
        DRAW_CIRCLE,
    };

public:
    bool closePolygonBtn;
    bool newPolygonBtn;
    bool newCircleBtn;
    Gui()
    {
        float first = 24;
        buttonsRect.reserve(30);
        buttonsRect.push_back(Rectangle{WIDTH - 125, first, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, first * 2, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, first * 3, 120, 24});
    }
    void update()
    {
        if (GuiButton(buttonsRect.at(CLOSE_POLYGON), "#191#Close Polygon"))
        {
            closePolygonBtn = !closePolygonBtn; // Toggle state on button press
        }
        else if (GuiButton(buttonsRect.at(NEW_POLYGON), "#191#New Polygon"))
        {
            newPolygonBtn = !newPolygonBtn;
        }
        else if (GuiButton(buttonsRect.at(DRAW_CIRCLE), "#191#Draw Circle"))
        {
            newCircleBtn = !newCircleBtn;
        }
    }

    bool checkCollisions(Vector2 point)
    {
        for (int i = 0; i < buttonsRect.size(); i++)
        {
            if (CheckCollisionPointRec(point, buttonsRect.at(i)))
            {
                return true;
            }
        }
        return false;
    }
};

#endif