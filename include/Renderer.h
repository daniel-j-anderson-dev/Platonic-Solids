#ifndef Renderer_H
#define Renderer_H
#pragma once
#include "../include/SDL2/SDL.h"
#include "../include/Quaternion.h"
#include "../include/Shape3D.h"
#include "../include/Transformer.h"

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

    void setAxes();
    void drawAxes();

    void  drawLine(rgbaColor color, Point startPoint, Point endPoint);
    void  drawShape(Shape3D shape);
    void  drawShapes(std::vector<Shape3D> shapes);

    void  clearScreen();
    void  update();
    void  handleEvents(SDL_Event event);
    void  handleInput(const Uint8* keys);

    void  run();
    
private:

    // TODO: take these out of this class
    // EventHandler
    SDL_Event     event;
    bool          isRunning;
    Uint64        startTime;
    Uint64        endTime;
    bool          isLocalRotation;
    bool          isWorldRotation;
    Point         axisOfRotation;
    Point         axisOfTranslation;

    // main
    std::vector<Shape3D> shapes;


    // you can stay :)
    SDL_Window*          window;
    SDL_Renderer*        renderer2D;
    SDL_Texture*         background;
    Point                ORIGIN;
    std::vector<Shape3D> axes;
};

#endif