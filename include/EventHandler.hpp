#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#pragma once
#include "../include/Renderer.hpp"

void handleInput(const bool* keys, Renderer &renderer3D, Point &axisOfTranslation, Point &axisOfRotation, bool &isLocalRotation, bool &isWorldRotation, bool &isRunning);
void handleEvents(SDL_Event event,  Renderer &renderer3D, Point &axisOfTranslation, Point &axisOfRotation, bool &isLocalRotation, bool &isWorldRotation, bool &isRunning);

#endif