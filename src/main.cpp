#include "SDL.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create the window
    SDL_Window *window = SDL_CreateWindow("Line Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Define the points
    SDL_Point p1 = { 100, 100 };
    SDL_Point p2 = { 200, 200 };

    // Set the draw color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw the line
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);

    // Update the window
    SDL_RenderPresent(renderer);

    // Wait for a quit event
    SDL_Event event;
    while (true) {
        if (SDL_WaitEvent(&event) && event.type == SDL_QUIT) {
            break;
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
