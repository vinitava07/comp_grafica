#pragma once
#include "raylib.h"
#include <vector>
#include "circle.h"
#include "polygon.h"
#ifndef CLIPPING_H
#define CLIPPING_H
class Clipping
{
private:
    float u1, u2;

public:
    Color color = GREEN;
    Vector2 p1, p2;
    float xmin, xmax, ymin, ymax;
    std::vector<Polygon> polygons;
    bool hasP1 = false;
    
    Clipping()
    {
        polygons.reserve(30);
    }

    void setP1(Vector2 point)
    {
        this->p1 = point;
        hasP1 = true;
    }

    void setP2(Vector2 point)
    {
        // Atualiza o ponto p2 com o novo valor
        this->p2 = point;

        // Calcula os limites, independentemente da ordem dos pontos
        float newXmin = std::min(p1.x, p2.x);
        float newXmax = std::max(p1.x, p2.x);
        float newYmin = std::min(p1.y, p2.y);
        float newYmax = std::max(p1.y, p2.y);

        // Define os limites para o retângulo
        xmin = newXmin; // canto inferior esquerdo (x)
        xmax = newXmax; // canto inferior direito (x)
        ymin = newYmin; // canto inferior esquerdo (y)
        ymax = newYmax; // canto superior esquerdo (y)

        // p1 passa a ser o canto inferior esquerdo e p2 o canto superior direito.
        p1.x = newXmin;
        p1.y = newYmin;
        p2.x = newXmax;
        p2.y = newYmax;
    }

    void applyClip(std::vector<Polygon> mainPolygons, int cohen_liang)
    {
        polygons.clear();
        for (size_t i = 0; i < mainPolygons.size(); i++)
        {
            polygons.push_back(Polygon());
            for (size_t j = 0; j < mainPolygons.at(i).lines.size(); j++)
            {
                if (cohen_liang == 0)
                {
                    cohenSutherland(mainPolygons.at(i).lines.at(j), i);
                }
                else
                {
                    liangBarsky(mainPolygons.at(i).lines.at(j), i);
                }
            }
        }
    }

    void liangBarsky(Line line, int polNumber)
    {
        float dx, dy;
        u1 = 0;
        u2 = 1;
        float x1 = line.p1.x;
        float x2 = line.p2.x;
        float y1 = line.p1.y;
        float y2 = line.p2.y;
        dx = x2 - x1;
        dy = y2 - y1;

        if (clipTest(-dx, x1 - xmin))
        {
            if (clipTest(dx, xmax - x1))
            {
                if (clipTest(-dy, y1 - ymin))
                {
                    if (clipTest(dy, ymax - y1))
                    {
                        if (u2 < 1)
                        {
                            x2 = x1 + u2 * dx;
                            y2 = y1 + u2 * dy;
                        }
                        if (u1 > 0)
                        {
                            x1 = x1 + u1 * dx;
                            y1 = y1 + u1 * dy;
                        }
                        polygons.at(polNumber).addVertice(Vector2{(x1), (y1)});
                        polygons.at(polNumber).addVertice(Vector2{(x2), (y2)});
                    }
                }
            }
        }
    }

    bool clipTest(float p, float q)
    {
        float r;
        bool result = true;
        if (p < 0)
        {
            r = q / p;
            if (r > u2)
            {
                result = false;
            }
            else if (r > u1)
            {
                u1 = r;
            }
        }
        else if (p > 0)
        {
            r = q / p;
            if (r < u1)
            {
                result = false;
            }
            else if (r < u2)
            {
                u2 = r;
            }
        }
        else if (q < 0)
        {
            result = false;
        }

        return result;
    }

    void cohenSutherland(Line line, int polNumber)
    {

        bool aceite = false;
        bool feito = false;
        float x1, x2, y1, y2;
        x1 = line.p1.x;
        x2 = line.p2.x;
        y1 = line.p1.y;
        y2 = line.p2.y;
        float xint, yint;

        int c1, c2;
        while (!feito)
        {
            c1 = regionCode(Vector2{x1, y1});
            c2 = regionCode(Vector2{x2, y2});

            if (c1 == 0 && c2 == 0)
            {
                aceite = true;
                feito = true;
            }
            else if ((c1 & c2) != 0)
            {
                feito = true;
            }
            else
            {
                int cfora;
                cfora = (c1 != 0) ? c1 : c2;
                if (readBit(cfora, 0) == 1)
                {
                    xint = xmin;
                    yint = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                }
                else if (readBit(cfora, 1) == 1)
                {
                    xint = xmax;
                    yint = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                }
                else if (readBit(cfora, 2) == 1)
                {
                    yint = ymin;
                    xint = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                }
                else if (readBit(cfora, 3) == 1)
                {
                    yint = ymax;
                    xint = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                }

                if (c1 == cfora)
                {
                    x1 = xint;
                    y1 = yint;
                }
                else
                {
                    x2 = xint;
                    y2 = yint;
                }
            }
        }

        if (aceite)
        {
            polygons.at(polNumber).addVertice(Vector2{(x1), (y1)});
            polygons.at(polNumber).addVertice(Vector2{(x2), (y2)});
        }
    }

    int regionCode(Vector2 point)
    {
        int codigo = 0;

        if (point.x < xmin)
        {
            codigo += 1;
        }
        if (point.x > xmax)
        {

            codigo += 2;
        }
        if (point.y < ymin)
        {

            codigo += 4;
        }
        if (point.y > ymax)
        {

            codigo += 8;
        }

        return codigo;
    }

    int readBit(int number, int pos)
    {
        int bit = number & (1 << pos);
        if (bit > 0)
        {
            return 1;
        }
        return 0;
    }

    void drawClipArea(int dda_bre)
    {

        for (size_t i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).drawPolygonPoints();
            polygons.at(i).drawPolygon(dda_bre);
        }
        DrawRectangleLines(p1.x, p1.y, (abs(p1.x - p2.x)), abs(p1.y - p2.y), color);
    }

    void drawP1()
    {
        Vector2 mousePos = GetMousePosition();
        DrawCircle(p1.x, p1.y, 3, color);

        float xmin_l = std::min(p1.x, mousePos.x);
        float xmax_l = std::max(p1.x, mousePos.x);
        float ymin_l = std::min(p1.y, mousePos.y);
        float ymax_l = std::max(p1.y, mousePos.y);

        // O canto superior esquerdo deve ser (xmin_l, ymin)
        DrawRectangleLines(xmin_l, ymin_l, xmax_l - xmin_l, ymax_l - ymin_l, color);
    }
};

#endif