#pragma once
#include <vector>
#include <cstdint>
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

    char inputText[128] = ""; // Buffer de entrada
    bool editMode = false;    // Controle de edição
    int value;

    Gui()
    {
        float first = 24;
        buttonsRect.reserve(30);
        buttonsRect.push_back(Rectangle{WIDTH - 125, first, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, first * 2, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, first * 3, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, first * 4, 120, 24});
    }
    void update()
    {
        // GuiTextInputBox(buttonsRect.at(3), "oi", "teste", "a;b", input, 100, teste);
        if (GuiButton(buttonsRect.at(CLOSE_POLYGON), "#191#Close Polygon "))
        {
            closePolygonBtn = !closePolygonBtn; // Toggle state on button press
        }
        else if (GuiButton(buttonsRect.at(NEW_POLYGON), "#191#New Polygon   "))
        {
            newPolygonBtn = !newPolygonBtn;
        }
        else if (GuiButton(buttonsRect.at(DRAW_CIRCLE), "#191#Draw Circle    "))
        {
            newCircleBtn = !newCircleBtn;
        }
        if (GuiValueBox(buttonsRect.at(3), inputText, &value, 0, INT32_MAX, editMode))
        {
            editMode = !editMode;
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