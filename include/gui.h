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

    char inputRotate[128] = "";
    bool editRotate = false;

    enum Buttons
    {
        NEW_POLYGON = 0,
        CLOSE_POLYGON,
        DRAW_CIRCLE,
        TRANSLATE,
        ROTATE,
        REFLECT_X,
        REFLECT_Y,
        CLIPPING,
        DDA_BRE,

    };
    enum TextInputs
    {
        TRANSLATE_INPUT_X = 0,
        TRANSLATE_INPUT_Y,
        ROTATE_INPUT,

    };

public:
    int dda_bre = 0; // Índice do botão selecionado
    bool closePolygonBtn = false;
    bool newPolygonBtn = false;
    bool newCircleBtn = false;
    bool translateBtn = false;
    bool rotateBtn = false;
    bool reflectXBtn = false;
    bool reflectYBtn = false;
    bool clipBtn = false;

    int xValue;

    int yValue;

    int degrees;

    Gui()
    {
        float firstBtn = 24;
        buttonsRect.reserve(30);
        inputRect.reserve(30);

        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (NEW_POLYGON + 1), 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (CLOSE_POLYGON + 1) + 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (DRAW_CIRCLE + 1) + 20, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (TRANSLATE + 1) + 30, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (ROTATE + 1) + 40, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (REFLECT_X + 1) + 50, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (REFLECT_Y + 1) + 50, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (CLIPPING + 1) + 60, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 245, firstBtn * (DDA_BRE + 1) + 70, 120, 24});

        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 2)), 120, 24});
        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 4)), 120, 24});
        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 6)), 120, 24});
    }
    void drawGui()
    {
        buttons();

        textInputs();
    }

    void buttons()
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
        if (GuiButton(buttonsRect.at(ROTATE), "#191#Rotate"))
        {
            rotateBtn = !rotateBtn;
        }
        if (GuiButton(buttonsRect.at(REFLECT_X), "#191#Reflect X"))
        {
            reflectXBtn = !reflectXBtn;
        }
        if (GuiButton(buttonsRect.at(REFLECT_Y), "#191#Reflect Y"))
        {
            reflectYBtn = !reflectYBtn;
        }
        if (GuiButton(buttonsRect.at(CLIPPING), "#191#CLIP"))
        {
            clipBtn = !clipBtn;
        }
        GuiToggleGroup(buttonsRect.at(DDA_BRE), "DDA;BRE", &dda_bre);
    }

    void textInputs()
    {
        DrawText("X VALUE", WIDTH - 250, 24 * (TRANSLATE_INPUT_X + 1), 18, BLACK);
        if (GuiValueBox(inputRect.at(TRANSLATE_INPUT_X), inputTranslateX, &xValue, INT32_MIN, INT32_MAX, editTranslateX))
        {
            editTranslateX = !editTranslateX;
        }
        DrawText("Y VALUE", WIDTH - 250, 24 * (TRANSLATE_INPUT_X + 3), 18, BLACK);
        if (GuiValueBox(inputRect.at(TRANSLATE_INPUT_Y), inputTranslateY, &yValue, INT32_MIN, INT32_MAX, editTranslateY))
        {
            editTranslateY = !editTranslateY;
        }
        DrawText("DEGREES", WIDTH - 250, 24 * (TRANSLATE_INPUT_X + 5), 16, BLACK);
        if (GuiValueBox(inputRect.at(ROTATE_INPUT), inputRotate, &degrees, -360, 360, editRotate))
        {
            editRotate = !editRotate;
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