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
    std::vector<Rectangle> inputRect;
    char inputTranslateY[128] = "";
    bool editTranslateY = false;
    char inputTranslateX[128] = "";
    bool editTranslateX = false;

    enum Buttons
    {
        NEW_POLYGON = 0,
        CLOSE_POLYGON,
        DRAW_CIRCLE,
        TRANSLATE,

    };
    enum TextInputs
    {
        TRANSLATE_INPUT_X = 0,
        TRANSLATE_INPUT_Y,

    };

public:
    bool closePolygonBtn = false;
    bool newPolygonBtn = false;
    bool newCircleBtn = false;
    bool translateBtn = false;

    int xValue;

    int yValue;

    Gui()
    {
        float firstBtn = 24;
        buttonsRect.reserve(30);
        inputRect.reserve(30);

        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (NEW_POLYGON + 1), 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (CLOSE_POLYGON + 1), 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (DRAW_CIRCLE + 1), 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (TRANSLATE + 1), 120, 24});

        inputRect.push_back(Rectangle{WIDTH - 125, firstBtn * (5 + (TRANSLATE_INPUT_X + 1)), 120, 24});
        inputRect.push_back(Rectangle{WIDTH - 125, firstBtn * (5 + (TRANSLATE_INPUT_Y + 2)), 120, 24});
    }
    void update()
    {
        if (GuiButton(buttonsRect.at(CLOSE_POLYGON), "#191#Close Polygon "))
        {
            closePolygonBtn = !closePolygonBtn; // Toggle state on button press
        }
        if (GuiButton(buttonsRect.at(NEW_POLYGON), "#191#New Polygon   "))
        {
            newPolygonBtn = !newPolygonBtn;
        }
        if (GuiButton(buttonsRect.at(DRAW_CIRCLE), "#191#Draw Circle    "))
        {
            newCircleBtn = !newCircleBtn;
        }
        if (GuiButton(buttonsRect.at(TRANSLATE), "#191#Translate"))
        {
            translateBtn = !translateBtn;
        }
        DrawText("X VALUE", WIDTH - 125, 24 * (5 + TRANSLATE_INPUT_X), 16, BLACK);
        if (GuiValueBox(inputRect.at(TRANSLATE_INPUT_X), inputTranslateX, &xValue, INT32_MIN, INT32_MAX, editTranslateX))
        {
            editTranslateX = !editTranslateX;
        }
        DrawText("X VALUE", WIDTH - 125, 24 * (5 + TRANSLATE_INPUT_Y + 1), 16, BLACK);
        if (GuiValueBox(inputRect.at(TRANSLATE_INPUT_Y), inputTranslateY, &yValue, INT32_MIN, INT32_MAX, editTranslateY))
        {
            editTranslateY = !editTranslateY;
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
        for (int i = 0; i < inputRect.size(); i++)
        {
            if (CheckCollisionPointRec(point, inputRect.at(i)))
            {
                return true;
            }
        }
        return false;
    }
};

#endif