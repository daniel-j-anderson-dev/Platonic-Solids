#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#pragma once
#include "../include/Point.h"
#include "../include/SDL2/SDL.h"

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();

    void  handleEvents(SDL_Event event);
    void  handleInput(const Uint8* keys);
    
private:
    bool          isRunning;
    Uint64        startTime;
    Uint64        endTime;
    bool          isLocalRotation;
    bool          isWorldRotation;
    Point         axisOfRotation;
    Point         axisOfTranslation;

};

#endif