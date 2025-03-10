#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H
#include "structures.h"
#include "raylib.h"
#include <iostream>

class Circle
{
private:
    int radius;
    int g_x, g_y, g_p;
    void drawCirclePoints(int a, int b)
    {
        DrawPixel(center.x + a, center.y + b, color);
        DrawPixel(center.x - a, center.y + b, color);
        DrawPixel(center.x + a, center.y - b, color);
        DrawPixel(center.x - a, center.y - b, color);

        DrawPixel(center.x + b, center.y + a, color);
        DrawPixel(center.x - b, center.y + a, color);
        DrawPixel(center.x + b, center.y - a, color);
        DrawPixel(center.x - b, center.y - a, color);
    }

public:
    Color color = BLUE;
    bool desenhando = false;
    bool iniciou = false;
    bool complete = false;

    bool hasCenter = false;
    bool hasRadius = false;
    Vector2 center;

    void setCenter(Vector2 pos)
    {
        this->center = pos;
        this->hasCenter = true;
    }
    void setRadius(Vector2 pos)
    {
        int dx = pos.x - center.x;
        int dy = pos.y - center.y;
        int quadratic = pow(dx, 2) + pow(dy, 2);
        this->radius = round(sqrt(quadratic));
        this->complete = true;
    }

    void translate(Vector2 rate)
    {
        center.x += rate.x;
        center.y += rate.y;
    }

    void drawCenter()
    {
        DrawCircle(center.x, center.y, 2, color);
    }

    void startCircle()
    {
        g_x = 0;
        g_y = radius;
        g_p = 3 - (2 * radius);
        desenhando = true;
        iniciou = true;
    }
    
    void updateCircle()
    {
        int x, y, p;
        x = 0;
        y = radius;
        p = 3 - (2 * radius);
        if (desenhando && g_x < g_y)
        {
            while (x < g_x)
            {
                if (p < 0)
                {
                    p = p + (4 * x) + 6;
                }
                else
                {
                    p = p + (4 * (x - y)) + 10;
                    y--;
                }
                x++;
                drawCirclePoints(x, y);
            }
            if (g_p < 0)
            {
                g_p = g_p + (4 * x) + 6;
            }
            else
            {
                g_p = g_p + (4 * (x - y)) + 10;
                g_y--;
            }
            g_x++;
        }
        else
        {
            desenhando = false; // Para quando termina
        }
    }

    void draw()
    {
        int x, y, p;
        x = 0;
        y = radius;
        p = 3 - (2 * radius);
        drawCirclePoints(x, y);
        while (x < y)
        {
            if (p < 0)
            {
                p = p + (4 * x) + 6;
            }
            else
            {
                p = p + (4 * (x - y)) + 10;
                y--;
            }
            x++;
            drawCirclePoints(x, y);
        }
    }
};

#endif