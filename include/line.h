#pragma once
#ifndef LINE_H
#define LINE_H
#include "raylib.h"
#include <cmath>

class Line
{
private:

public:
    Vector2 p1, p2;
    Color color = RED;

    Line(Vector2 p1, Vector2 p2)
    {
        this->p1 = p1;
        this->p2 = p2;
    }

    void translate(Vector2 rate)
    {
        this->p1.x += rate.x;
        this->p1.y += rate.y;

        this->p2.x += rate.x;
        this->p2.y += rate.y;
    }

    void rotate(double rad)
    {
        double old_x1 = p1.x, old_y1 = p1.y;
        p1.x = old_x1 * cos(rad) - old_y1 * sin(rad);
        p1.y = old_x1 * sin(rad) + old_y1 * cos(rad);

        double old_x2 = p2.x, old_y2 = p2.y;
        p2.x = old_x2 * cos(rad) - old_y2 * sin(rad);
        p2.y = old_x2 * sin(rad) + old_y2 * cos(rad);
    }

    void reflectX(float y)
    {
        float diff1 = abs(p1.y - y);
        float diff2 = abs(p2.y - y);
        if (p1.y > y)
        {
            p1.y -= 2 * diff1;
        }
        else if (p1.y < y)
        {
            p1.y += 2 * diff1;
        }

        if (p2.y > y)
        {
            p2.y -= 2 * diff2;
        }
        else if (p2.y < y)
        {
            p2.y += 2 * diff2;
        }
    }

    void reflectY(float x)
    {
        float diff1 = abs(p1.x - x);
        float diff2 = abs(p2.x - x);
        if (p1.x > x)
        {
            p1.x -= 2 * diff1;
        }
        else if (p1.x < x)
        {
            p1.x += 2 * diff1;
        }

        if (p2.x > x)
        {
            p2.x -= 2 * diff2;
        }
        else if (p2.x < x)
        {
            p2.x += 2 * diff2;
        }
    }

    void scale(float rate)
    {
        double old_x1 = p1.x, old_y1 = p1.y;
        p1.x = old_x1 * rate;
        p1.y = old_y1 * rate;
        double old_x2 = p2.x, old_y2 = p2.y;
        p2.x = old_x2 * rate;
        p2.y = old_y2 * rate;
    }

    void drawDDA()
    {
        int dx, dy, passos;
        float x_incr, y_incr, x, y;

        dx = p2.x - p1.x;
        dy = p2.y - p1.y;
        if (abs(dx) > abs(dy))
        {
            passos = abs(dx);
        }
        else
        {
            passos = abs(dy);
        }
        x_incr = (float)dx / passos;
        y_incr = (float)dy / passos;
        x = p1.x;
        y = p1.y;
        DrawPixel(x, y, color);
        for (int i = 0; i < passos; i++)
        {
            x += x_incr;
            y += y_incr;
            DrawPixel(round(x), round(y), color);
        }
    }

    void drawBresenham()
    {
        int dx, dy, x, y, c1, c2, p;
        int x_incr, y_incr;
        dx = (p2.x - p1.x);
        dy = (p2.y - p1.y);

        if (dx >= 0)
        {
            x_incr = 1;
        }
        else
        {
            x_incr = -1;
            dx = -dx;
        }
        if (dy >= 0)
        {
            y_incr = 1;
        }
        else
        {
            y_incr = -1;
            dy = -dy;
        }
        x = p1.x;
        y = p1.y;
        DrawPixel(x, y, color);
        if (dy < dx)
        {
            p = 2 * dy - dx;
            c1 = 2 * dy;
            c2 = 2 * (dy - dx);
            for (int i = 0; i < dx; i++)
            {
                x += x_incr;
                if (p < 0)
                {
                    p += c1;
                }
                else
                {
                    y += y_incr;
                    p += c2;
                }
                DrawPixel(x, y, color);
            }
        }
        else
        {
            p = 2 * dx - dy;
            c1 = 2 * dx;
            c2 = 2 * (dx - dy);
            for (int i = 0; i < dy; i++)
            {
                y += y_incr;
                if (p < 0)
                {
                    p += c1;
                }
                else
                {
                    x += x_incr;
                    p += c2;
                }
                DrawPixel(x, y, color);
            }
        }
    }
};

#endif