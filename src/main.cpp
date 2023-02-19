#include "../include/Renderer.h"
#include "../include/Transformer.h"
#include "../include/EventHandler.h"

int main(int argc, char *argv[])
{
	Renderer     renderer = Renderer(1920, 1080);
	Transformer  transformer;
	EventHandler eventHandler;
	renderer.run();
}