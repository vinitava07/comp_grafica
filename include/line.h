#pragma once
#ifndef LINE_H
#define LINE_H
#include "structures.h"
#include "raylib.h"
#include <cmath>

class Line
{
private:
    int step = 0;
    int g_passos;
    double g_x, g_y, g_x_incr, g_y_incr;
    Vector2 p1, p2;

public:
    Color color = RED;
    bool desenhando = false;
    bool iniciou = false;
    
    Line(Vector2 p1, Vector2 p2)
    {
        this->p1 = p1;
        this->p2 = p2;
    }
    void updateDDA()
    {
        int start = 0;
        g_x = p1.x;
        g_y = p1.y;
        if (desenhando && step <= g_passos)
        {
            for (size_t i = 0; i < step; i++)
            {
                DrawPixel(round(g_x), round(g_y), color);
                g_x += g_x_incr;
                g_y += g_y_incr;
            }
            step++;
        }
        else
        {
            desenhando = false; // Para quando termina
        }
    }

    void startDDA()
    {
        iniciou = true;
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;

        g_passos = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

        g_x_incr = dx / (double)g_passos;
        g_y_incr = dy / (double)g_passos;

        g_x = p1.x;
        g_y = p1.y;
        step = 0;
        desenhando = true; // Ativa a animação
    }

    void drawNormalDDA()
    {
        int dx, dy, passos, k;
        double x_incr, y_incr, x, y;

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
        x_incr = dx / passos;
        y_incr = dy / passos;
        x = p1.x;
        y = p1.y;
        DrawPixel(x, y, color);
        for (size_t i = 0; i < passos; i++)
        {
            x += x_incr;
            y += y_incr;
            DrawPixel(round(x), round(y), color);
        }
    }

    void drawNormalBresenham()
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