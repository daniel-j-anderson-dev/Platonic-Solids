#ifndef Renderer_H
#define Renderer_H
#pragma once
#include "../include/SDL2/SDL.h"
#include "../include/Shape3D.h"
#include "../include/Transformer.h"
#include <cmath>

struct rgbaColor
{
	int red;
	int green;
	int blue;
	int alpha;
};

class Renderer
{
public:
    Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT);
    ~Renderer();

    // assessors
    Point xAxis();
    Point yAxis();
    Point zAxis();
    std::vector<Shape3D> *getAxes();
    std::vector<Shape3D> *getShapes();
    std::vector<Point> allAxes();
    std::pair<Point, double> getWorldOrientation();

    // mutators
    void axesDefault();
    void setShapes(std::vector<Shape3D> *shapes);

    // actions
    void drawLine(rgbaColor color, Point startPoint, Point endPoint);
    void drawShape(Shape3D shape);
    void drawShapes(std::vector<Shape3D> shapes);
    void drawAxes();

    void clearScreen();
    void update();
    void draw();

private:

    SDL_Window*          window;
    SDL_Renderer*        renderer2D;
    SDL_Texture*         background;
    Point                ORIGIN;
    std::vector<Shape3D> *shapes;
    std::vector<Shape3D> axes;
    Uint64               startTime;
    Uint64               endTime;
};

#endif