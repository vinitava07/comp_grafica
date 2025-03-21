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

public:
    std::vector<Line> lines;
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

    void closePolygon()
    {
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

    void translate(Vector2 rate)
    {
        for (size_t i = 0; i < lines.size(); i++)
        {
            lines.at(i).translate(rate);
        }
        for (size_t i = 0; i < vertices.size(); i++)
        {
            vertices.at(i).x += rate.x;
            vertices.at(i).y += rate.y;
        }
    }

    void rotate(double rad)
    {

        Vector2 firstPoint = vertices.at(0);
        translate(Vector2{-firstPoint.x, -firstPoint.y});

        for (size_t i = 0; i < lines.size(); i++)
        {
            lines.at(i).rotate(rad);
        }
        for (size_t i = 0; i < vertices.size(); i++)
        {
            double old_x = vertices.at(i).x;
            double old_y = vertices.at(i).y;
            vertices.at(i).x = old_x * cos(rad) - old_y * sin(rad);
            vertices.at(i).y = old_x * sin(rad) + old_y * cos(rad);
        }

        translate(firstPoint);
    }

    void reflectX()
    {
        Vector2 firstPoint = vertices.at(0);
        float y = firstPoint.y;
        for (size_t i = 0; i < lines.size(); i++)
        {
            lines.at(i).reflectX(y);
        }
        for (size_t i = 0; i < vertices.size(); i++)
        {
            float diff = abs(vertices.at(i).y - y);
            if (vertices.at(i).y > y)
            {
                vertices.at(i).y -= 2 * diff;
            }
            else if (vertices.at(i).y < y)
            {
                vertices.at(i).y += 2 * diff;
            }
        }
    }
    
    void reflectY()
    {
        Vector2 firstPoint = vertices.at(0);
        float x = firstPoint.x;
        for (size_t i = 0; i < lines.size(); i++)
        {
            lines.at(i).reflectY(x);
        }
        for (size_t i = 0; i < vertices.size(); i++)
        {
            float diff = abs(vertices.at(i).x - x);
            if (vertices.at(i).x > x)
            {
                vertices.at(i).x -= 2 * diff;
            }
            else if (vertices.at(i).x < x)
            {
                vertices.at(i).x += 2 * diff;
            }
        }
    }

    void scale(float rate){
        Vector2 firstPoint = vertices.at(0);
        translate(Vector2{-firstPoint.x, -firstPoint.y});

        for (size_t i = 0; i < lines.size(); i++)
        {
            lines.at(i).scale(rate);
        }
        for (size_t i = 0; i < vertices.size(); i++)
        {   
            double old_x = vertices.at(i).x;
            double old_y = vertices.at(i).y;
            vertices.at(i).x = old_x * rate;
            vertices.at(i).y = old_y * rate;
        }
        

        translate(firstPoint);

    }

    void drawPolygonPoints()
    {
        size_t range = vertices.size();
        for (size_t i = 0; i < range; i++)
        {
            DrawCircle(vertices.at(i).x, vertices.at(i).y, 3, color);
        }
    }

    void drawPolygon(int dda_bre)
    {
        if (dda_bre == 0)
        {

            for (size_t i = 0; i < lines.size(); i++)
            {
                lines.at(i).drawDDA();
            }
        }
        else
        {
            for (size_t i = 0; i < lines.size(); i++)
            {
                lines.at(i).drawBresenham();
            }
        }
    }
};

#endif