#pragma once
#include "raylib.h"
#include <cmath>
#ifndef RASTERIZATION_H
#define RASTERIZATION_H
typedef struct point
{
    int x, y;
} Point;

class Rasterization
{
private:
    int step = 0;
    int passos;
    double x, y, x_incr, y_incr;

public:
    bool desenhando = false;
    bool iniciou = false;


    void updateDDA(Point p1)
    {
        int start = 0;
        x = p1.x;
        y = p1.y;
        if (desenhando && step <= passos)
        {
            for (size_t i = 0; i < step; i++)
            {
                DrawPixel(round(x), round(y), RED);
                x += x_incr;
                y += y_incr;
            }
            step++;
        }
        else
        {
            desenhando = false; // Para quando termina
        }
    }

    void startDDA(Point p1, Point p2)
    {
        iniciou = true;
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;

        passos = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

        x_incr = dx / (double)passos;
        y_incr = dy / (double)passos;

        x = p1.x;
        y = p1.y;
        step = 0;
        desenhando = true; // Ativa a animação
    }

    void normalDDA(Point p1, Point p2)
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
        DrawPixel(x, y, RED);
        for (size_t i = 0; i < passos; i++)
        {
            x += x_incr;
            y += y_incr;
            DrawPixel(round(x), round(y), RED);
        }
    }
};

#endif
