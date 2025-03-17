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
public:
    Color color = RED;
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
        this->p2 = point;
        Vector2 aux = p1;

        if (p2.y < p1.y && p2.x < p1.x)
        {
            p1 = p2;
            p2 = aux;
        }
        else if (p2.x < p1.x && p2.y > p1.y)
        {
            float diff = abs(p2.x - p1.x);
            p2.x += diff;
            p1.x -= diff;
        }
        else if (p2.x > p1.x && p2.y < p1.y)
        {
            float diff = abs(p2.y - p1.y);
            p2.y += diff;
            p1.y -= diff;
        }

        xmin = p1.x;
        xmax = p2.x;
        ymax = p1.y;
        ymin = p2.y;
    }

    void applyClip(std::vector<Polygon> mainPolygons)
    {
        polygons.clear();
        bool isLine = false;
        for (int i = 0; i < mainPolygons.size(); i++)
        {
            polygons.push_back(Polygon());
            for (int j = 0; j < mainPolygons.at(i).lines.size(); j++)
            {
                isLine = (mainPolygons.at(i).lines.size() == 1);
                cohenSutherland(mainPolygons.at(i).lines.at(j), i, isLine);
            }

            polygons.at(i).closePolygon();
        }
    }

    void cohenSutherland(Line line, int polNumber, bool isLine)
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

            if (isLine)
            {
                polygons.at(polNumber).addVertice(Vector2{(x1), (y1)});
                polygons.at(polNumber).addVertice(Vector2{(x2), (y2)});
            }
            else
            {
                polygons.at(polNumber).addVertice(Vector2{(x1), (y1)});
            }
        }
    }

    int regionCode(Vector2 point)
    {
        int codigo = 0;

        if (point.x < xmin)
        {
            codigo += 1;
            // printf("xmin ");
        }
        if (point.x > xmax)
        {
            // printf("xmax ");

            codigo += 2;
        }
        if (point.y > ymin)
        {
            // printf("ymin ");

            codigo += 4;
        }
        if (point.y < ymax)
        {
            // printf("ymax ");

            codigo += 8;
        }
        // printf("XMIN %f xMAX: %f yMIN: %f YMAX: %f\n", xmin, xmax, ymin, ymax);

        // printf("REGION CODE %d x: %f y: %f \n", codigo, point.x, point.y);

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
        // printf("%d\n", polygons.at(0).lines.size());
        DrawRectangleLines(p1.x, p1.y, (abs(p1.x - p2.x)), abs(p1.y - p2.y), color);
        for (int i = 0; i < polygons.size(); i++)
        {
            polygons.at(i).drawPolygonPoints();
            if (polygons.at(i).closed)
            {
                polygons.at(i).drawPolygon(dda_bre);
            }
        }
    }
};

#endif