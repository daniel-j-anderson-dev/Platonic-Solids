#ifndef Renderer_H
#define Renderer_H
#pragma once
#include "../include/SDL2/SDL.h"
#include "../include/Quaternion.h"
#include "../include/Shape3D.h"

class Renderer
{
public:
    Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT);
    ~Renderer();


    void  setShapes();

    Point rotatePoint(Point point, Point axis, double angle);
    Point rotatePointAboutAnother(Point point, Point centerOfRotation, Point axis, double angle);
    void  rotateShapeLocal(Shape3D &shape, Point axis, double angle);
    void  rotateShapesLocal(Point axis, double angle);
    void  rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle);
    void  rotateShapesAboutPoint(Point centerOfRotation, Point axis, double angle);

    void  drawLine(Point startPoint, Point endPoint);
    void  drawShape(Shape3D shape);
    void  drawShapes(Shape3D shapes[]);

    void  clearScreen();
    void  handleEvents(SDL_Event event);
    Point getAxisOfRotation(const Uint8* keys);

    void  run();
    
private:

    SDL_Window*   window;
    SDL_Renderer* renderer2D;
    SDL_Event     event;
    const Uint8*  keys;
    bool          isRunning;
    bool          isLocalrotation;

    Point         axisOfRotation;
    Point         ORIGIN;
    Shape3D       shapes[5];
};

#endif