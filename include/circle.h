#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H
#include "raylib.h"
#include <iostream>

class Circle
{
private:
    float radius;

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

    void scale(float rate)
    {
        this->radius *= rate;
    }
    
    void drawCenter()
    {
        DrawCircle(center.x, center.y, 2, color);
    }

    void drawCircle()
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