#include "../include/Renderer.h"
#include "../include/Transformer.h"

void handleInput(const Uint8* keys, Renderer &renderer3D, Point &axisOfTranslation, Point &axisOfRotation, bool &isLocalRotation, bool &isWorldRotation, bool &isRunning);
void handleEvents(SDL_Event event,  Renderer &renderer3D, Point &axisOfTranslation, Point &axisOfRotation, bool &isLocalRotation, bool &isWorldRotation, bool &isRunning);

int main(int argc, char *argv[])
{
	Renderer  			 renderer3D        = Renderer(1920, 1080);
	std::vector<Shape3D> shapes            = platonicSolids();
	renderer3D.setShapes(&shapes);
	SDL_Event 			 event;
	bool	  			 isRunning         = true;
    bool         		 isLocalRotation   = true;
    bool         		 isWorldRotation   = false;
    Point        		 axisOfRotation    = {0, 0, 0};
    Point         		 axisOfTranslation = {0, 0, 0};
	double 				 rotationSpeed     = .05;
	double				 movementSpeed     = 5;

	while (isRunning)
	{
		handleEvents(
			event,
			renderer3D, axisOfTranslation, axisOfRotation,
			isLocalRotation, isWorldRotation, isRunning);

		if (isWorldRotation)
		{
			rotateShapesAboutPoint(*(renderer3D.getAxes()),   {0, 0, 0}, axisOfRotation, rotationSpeed);
			rotateShapesAboutPoint(shapes, {0, 0, 0}, axisOfRotation, rotationSpeed);
		}
		else if (isLocalRotation)
		{
			rotateShapesLocal(shapes, axisOfRotation, rotationSpeed);
		}
		else
		{
			rotateShapesAboutPoint(shapes, {0, 0, 0}, axisOfRotation, rotationSpeed);
		}

		translateShapes(shapes, axisOfTranslation, movementSpeed);

		renderer3D.draw();
	}
}

void handleInput(const Uint8* keys, Renderer &renderer3D, Point &axisOfTranslation, Point &axisOfRotation, bool &isLocalRotation, bool &isWorldRotation, bool &isRunning)
{
	axisOfRotation    = {0, 0, 0};
	axisOfTranslation = {0, 0, 0};
	isRunning		= true;
	isLocalRotation = true;
	isWorldRotation = false;

	Point xAxis   = renderer3D.xAxis();
	Point yAxis   = renderer3D.yAxis();
	Point zAxis   = renderer3D.zAxis();
	Point sumAxis = {xAxis.x+yAxis.x+zAxis.x, xAxis.y+yAxis.y+zAxis.y, xAxis.z+yAxis.z+zAxis.z};

	if (keys[SDL_SCANCODE_ESCAPE])
		isRunning 		= false;
	if (keys[SDL_SCANCODE_LSHIFT])
		isLocalRotation = false;
	if (keys[SDL_SCANCODE_LCTRL])
		isWorldRotation = true;
	if (keys[SDL_SCANCODE_0])
	{// TODO: reset shape position relative to world axes
		std::vector<Shape3D> *shapes = renderer3D.getShapes();
		*shapes = platonicSolids();
		renderer3D.axesDefault();
		return;
	}

	if (keys[SDL_SCANCODE_S])
	{
		axisOfRotation.x += xAxis.x;
		axisOfRotation.y += xAxis.y;
		axisOfRotation.z += xAxis.z;
	}
	if (keys[SDL_SCANCODE_W])
	{
		axisOfRotation.x -= xAxis.x;
		axisOfRotation.y -= xAxis.y;
		axisOfRotation.z -= xAxis.z;
	}
	if (keys[SDL_SCANCODE_D])
	{
		axisOfRotation.x += yAxis.x;
		axisOfRotation.y += yAxis.y;
		axisOfRotation.z += yAxis.z;
	}
	if (keys[SDL_SCANCODE_A])
	{
		axisOfRotation.x -= yAxis.x;
		axisOfRotation.y -= yAxis.y;
		axisOfRotation.z -= yAxis.z;
	}
	if (keys[SDL_SCANCODE_Q])
	{
		axisOfRotation.x += zAxis.x;
		axisOfRotation.y += zAxis.y;
		axisOfRotation.z += zAxis.z;
	}
	if (keys[SDL_SCANCODE_E])
	{
		axisOfRotation.x -= zAxis.x;
		axisOfRotation.y -= zAxis.y;
		axisOfRotation.z -= zAxis.z;
	}
	if (keys[SDL_SCANCODE_SPACE])
	{
		axisOfRotation.x += sumAxis.x;
		axisOfRotation.y += sumAxis.y;
		axisOfRotation.z += sumAxis.z;
	}

	if (keys[SDL_SCANCODE_RIGHT])
	{
		axisOfTranslation.x += xAxis.x;
		axisOfTranslation.y += xAxis.y;
		axisOfTranslation.z += xAxis.z;
	}
	if (keys[SDL_SCANCODE_LEFT]) // WHY DOESNT THIS WORK?!?!!?@!?!?
	{
		axisOfTranslation.x -= xAxis.x;
		axisOfTranslation.x -= xAxis.y;
		axisOfTranslation.x -= xAxis.z;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		axisOfTranslation.x += yAxis.x;
		axisOfTranslation.y += yAxis.y;
		axisOfTranslation.z += yAxis.z;
	}
	if (keys[SDL_SCANCODE_UP])
	{
		axisOfTranslation.x -= yAxis.x;
		axisOfTranslation.y -= yAxis.y;
		axisOfTranslation.z -= yAxis.z;
	}
	if (keys[SDL_SCANCODE_PAGEUP])
	{
		axisOfTranslation.x += zAxis.x;
		axisOfTranslation.y += zAxis.y;
		axisOfTranslation.z += zAxis.z;
	}
	if (keys[SDL_SCANCODE_PAGEDOWN])
	{
		axisOfTranslation.x -= zAxis.x;
		axisOfTranslation.y -= zAxis.y;
		axisOfTranslation.z -= zAxis.z;
	}
}

void handleEvents(SDL_Event event,  Renderer &renderer3D, Point &axisOfTranslation, Point &axisOfRotation, bool &isLocalRotation, bool &isWorldRotation, bool &isRunning)
{	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				handleInput(SDL_GetKeyboardState(NULL),
				renderer3D, axisOfTranslation, axisOfRotation,
				isLocalRotation, isWorldRotation, isRunning);
				break;

			case SDL_KEYUP:
				handleInput(SDL_GetKeyboardState(NULL),
				renderer3D, axisOfTranslation, axisOfRotation,
				isLocalRotation, isWorldRotation, isRunning);
				break;
			// other events
		}
	}
}