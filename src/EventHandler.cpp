#include "../include/EventHandler.hpp"
#include "Transformer.hpp"
#include <SDL_events.h>

void handleInput(const bool *keys, Renderer &renderer3D,
                 Point &axisOfTranslation, Point &axisOfRotation,
                 bool &isLocalRotation, bool &isWorldRotation,
                 bool &isRunning) {
    axisOfRotation = {0, 0, 0};
    axisOfTranslation = {0, 0, 0};
    isRunning = true;
    isLocalRotation = true;
    isWorldRotation = false;

    Point xAxis = renderer3D.xAxis();
    Point yAxis = renderer3D.yAxis();
    Point zAxis = renderer3D.zAxis();
    Point sumAxis = xAxis + yAxis + zAxis;

    if (keys[SDL_SCANCODE_ESCAPE])
        isRunning = false;
    if (keys[SDL_SCANCODE_LSHIFT])
        isLocalRotation = false;
    if (keys[SDL_SCANCODE_LCTRL])
        isWorldRotation = true;
    if (keys[SDL_SCANCODE_9]) {
        renderer3D.axesDefault();
        renderer3D.setShapes(platonicSolids());
        return;
    }
    if (keys[SDL_SCANCODE_0]) { // TODO: reset shape position relative to world
                                // axes
        renderer3D.setShapes(platonicSolids());
        return;
    }

    if (keys[SDL_SCANCODE_S])
        axisOfRotation += xAxis;
    if (keys[SDL_SCANCODE_W])
        axisOfRotation -= xAxis;
    if (keys[SDL_SCANCODE_D])
        axisOfRotation += yAxis;
    if (keys[SDL_SCANCODE_A])
        axisOfRotation -= yAxis;
    if (keys[SDL_SCANCODE_Q])
        axisOfRotation += zAxis;
    if (keys[SDL_SCANCODE_E])
        axisOfRotation -= zAxis;
    if (keys[SDL_SCANCODE_SPACE])
        axisOfRotation += sumAxis;

    if (keys[SDL_SCANCODE_RIGHT])
        axisOfTranslation += xAxis;
    if (keys[SDL_SCANCODE_LEFT]) // WHY DOESNT THIS WORK?!?!!?@!?!?
        axisOfTranslation -= xAxis;
    if (keys[SDL_SCANCODE_DOWN])
        axisOfTranslation += yAxis;
    if (keys[SDL_SCANCODE_UP])
        axisOfTranslation -= yAxis;
    if (keys[SDL_SCANCODE_PAGEUP]) // Z Translation is ambiguous without
                                   // perspective
        axisOfTranslation += zAxis;
    if (keys[SDL_SCANCODE_PAGEDOWN])
        axisOfTranslation -= zAxis;
}

void handleEvents(SDL_Event event, Renderer &renderer3D,
                  Point &axisOfTranslation, Point &axisOfRotation,
                  bool &isLocalRotation, bool &isWorldRotation,
                  bool &isRunning) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_KEY_DOWN: {
            handleInput(SDL_GetKeyboardState(nullptr), renderer3D,
                        axisOfTranslation, axisOfRotation, isLocalRotation,
                        isWorldRotation, isRunning);
            break;
        }

        case SDL_EVENT_KEY_UP: {
            handleInput(SDL_GetKeyboardState(nullptr), renderer3D,
                        axisOfTranslation, axisOfRotation, isLocalRotation,
                        isWorldRotation, isRunning);
            break;
        }

        case SDL_EVENT_QUIT: {
            isRunning = false;
            break;
        }
            // other events
        }
    }
}