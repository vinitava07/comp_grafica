#pragma once
#include <vector>
#include "raylib.h"
#include "line.h"
#include <iostream>
#ifndef POLYGON_H
#define POLYGON_H

class Polygon
{
private:
    std::vector<Vector2> vertices;
    std::vector<Line> lines;

public:
    Color color = RED;
    bool closed = false;
    Polygon()
    {
        vertices.reserve(30);
        lines.reserve(30);
    }

    void addVertice(Vector2 point)
    {
        vertices.push_back(point);
        int size = vertices.size();
        if (vertices.size() > 1)
        {
            lines.push_back(Line(vertices.at(size - 2), vertices.at(size - 1)));
        }
    }

    void closePolygon() {
        if (!closed)
        {
            int vSize = vertices.size();
            if (vSize > 2)
            {
                lines.push_back(Line(vertices.at(vSize - 1), vertices.at(0)));
            }
            this->closed = true;
        }
        
    }

    void drawPolygonPoints()
    {
        int range = vertices.size();
        for (int i = 0; i < range; i++)
        {
            DrawCircle(vertices.at(i).x, vertices.at(i).y, 3, color);
        }
    }

    void drawPolygon()
    {
        int vSize = vertices.size();
        for (int i = 0; i < lines.size(); i++)
        {
            lines.at(i).drawNormalBresenham();
        }
    }
};

#endif