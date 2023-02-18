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
    template <int size>
    void  rotateShapesLocal(Shape3D (&shapes)[size], Point axis, double angle);
    void  rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle);
    template <int size>
    void  rotateShapesAboutPoint(Shape3D (&shapes)[size],Point centerOfRotation, Point axis, double angle);

    void setAxes();
    void drawAxes();
    // void drawDashedLine(Point color, Point startPoint, Point endPoint, int dashLength);

    void  drawLine(Point color, Point startPoint, Point endPoint);
    void  drawShape(Shape3D shape);
    template <int size>
    void  drawShapes(Shape3D (&shapes)[size]);

    void  clearScreen();
    void  handleEvents(SDL_Event event);
    void  handleInput(const Uint8* keys);

    void  run();
    
private:

    SDL_Window*   window;
    SDL_Renderer* renderer2D;
    SDL_Event     event;
    bool          isRunning;
    bool          isLocalRotation;

    Point         axisOfRotation;
    Point         ORIGIN;
    Shape3D       shapes[5];
    Shape3D       axes[3];
};

#endif