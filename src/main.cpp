#include "../include/Renderer.h"

int main(int argc, char *argv[])
{
	Renderer  renderer = Renderer(1920, 1080);
	SDL_Event event;
	
	bool	  isRunning = true;

	renderer.run();
}