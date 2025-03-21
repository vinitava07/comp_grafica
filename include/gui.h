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
    std::vector<Rectangle> buttonsRect; // Vetor que armazena os retângulos dos botões
    std::vector<Rectangle> inputRect;   // Vetor que armazena os retângulos dos campos de entrada

    // Buffers de entrada para os campos de texto
    char inputTranslateY[128] = "";
    bool editTranslateY = false;
    char inputTranslateX[128] = "";
    bool editTranslateX = false;
    char inputRotate[128] = "";
    bool editRotate = false;
    char inputScale[128] = "";
    bool editScale = false;

    // Enumeração dos botões da interface
    enum Buttons
    {
        NEW_POLYGON = 0,
        CLOSE_POLYGON,
        DRAW_CIRCLE,
        TRANSLATE,
        ROTATE,
        SCALE,
        REFLECT_X,
        REFLECT_Y,
        CLIPPING,
        CLEAR_CLIP,
        DDA_BRE,
        COHEN_LIANG,

    };

    // Enumeração dos campos de entrada de texto
    enum TextInputs
    {
        TRANSLATE_INPUT_X = 0,
        TRANSLATE_INPUT_Y,
        ROTATE_INPUT,
        SCALE_INPUT,

    };

public:
    int dda_bre = 0;     // Estado do toggle para DDA/BRE
    int cohen_liang = 0; // Estado do toggle para Cohen/Liang
    bool closePolygonBtn = false;
    bool newPolygonBtn = false;
    bool newCircleBtn = false;
    bool translateBtn = false;
    bool rotateBtn = false;
    bool scaleBtn = false;
    bool reflectXBtn = false;
    bool reflectYBtn = false;
    bool clipBtn = false;
    bool clearClipBtn = false;

    int xValue;    // Valor da translação em X
    int yValue;    // Valor da translação em Y
    int degrees;   // Valor da rotação em graus
    int scaleRate; // Taxa de escala

    Gui()
    {
        float firstBtn = 24;
        buttonsRect.reserve(30);
        inputRect.reserve(30);

        // Inicialização dos botões com seus respectivos retângulos
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (NEW_POLYGON + 1) + NEW_POLYGON * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (CLOSE_POLYGON + 1) + CLOSE_POLYGON * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (DRAW_CIRCLE + 1) + DRAW_CIRCLE * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (TRANSLATE + 1) + TRANSLATE * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (ROTATE + 1) + ROTATE * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (SCALE + 1) + SCALE * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (REFLECT_X + 1) + REFLECT_X * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (REFLECT_Y + 1) + REFLECT_Y * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (CLIPPING + 1) + CLIPPING * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 125, firstBtn * (CLEAR_CLIP + 1) + CLEAR_CLIP * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 245, firstBtn * (DDA_BRE + 1) + DDA_BRE * 10, 120, 24});
        buttonsRect.push_back(Rectangle{WIDTH - 245, firstBtn * (COHEN_LIANG + 1) + COHEN_LIANG * 10, 120, 24});

        // Inicialização dos campos de entrada de texto
        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 2)), 120, 24});
        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 4)), 120, 24});
        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 6)), 120, 24});
        inputRect.push_back(Rectangle{WIDTH - 250, firstBtn * ((TRANSLATE_INPUT_X + 8)), 120, 24});
    }

    void drawGui()
    {
        drawButtons();

        drawTextInputs();
    }
    // Método para desenhar e processar os botões
    void drawButtons()
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
        if (GuiButton(buttonsRect.at(SCALE), "#191#Scale"))
        {
            scaleBtn = !scaleBtn;
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
        if (GuiButton(buttonsRect.at(CLEAR_CLIP), "#191#CLEAR CLIP"))
        {
            clearClipBtn = !clearClipBtn;
        }
        GuiToggleGroup(buttonsRect.at(DDA_BRE), "DDA;BRE", &dda_bre);
        GuiToggleGroup(buttonsRect.at(COHEN_LIANG), "COHEN;LIANG", &cohen_liang);
    }
    // Método para desenhar e processar os campos de entrada de texto
    void drawTextInputs()
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
        DrawText("RATE / 10", WIDTH - 250, 24 * (TRANSLATE_INPUT_X + 7), 16, BLACK);
        if (GuiValueBox(inputRect.at(SCALE_INPUT), inputScale, &scaleRate, -360, 360, editScale))
        {
            editScale = !editScale;
        }
    }
    // Método para verificar colisões entre o mouse e os elementos da GUI
    bool checkCollisions(Vector2 point)
    {
        Rectangle ddaBreToggle = buttonsRect.at(DDA_BRE);
        Rectangle cohenLiangToggle = buttonsRect.at(COHEN_LIANG);

        for (size_t i = 0; i < buttonsRect.size(); i++)
        {
            if (CheckCollisionPointRec(point, buttonsRect.at(i)))
            {
                return true;
            }
        }
        for (size_t i = 0; i < inputRect.size(); i++)
        {
            if (CheckCollisionPointRec(point, inputRect.at(i)))
            {
                return true;
            }
        }

        if (CheckCollisionPointRec(point, Rectangle{ddaBreToggle.x, ddaBreToggle.y, ddaBreToggle.width * 2, ddaBreToggle.height}))
        {
            return true;
        }
        if (CheckCollisionPointRec(point, Rectangle{cohenLiangToggle.x, cohenLiangToggle.y, cohenLiangToggle.width * 2, cohenLiangToggle.height}))
        {
            return true;
        }

        return false;
    }
};

#endif