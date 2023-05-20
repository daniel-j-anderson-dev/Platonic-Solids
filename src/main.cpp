#include "../include/Renderer.h"
#include "../include/Transformer.h"
#include "../include/EventHandler.h"

int main(int argc, char *argv[])
{
	Renderer  			 renderer3D        = Renderer(800, 800);
	SDL_Event 			 event;
	std::vector<Shape3D> shapes            = platonicSolids();
	renderer3D.setShapes(&shapes);

	bool	  			 isRunning         = true;
    bool         		 isLocalRotation   = true;
    bool         		 isWorldRotation   = false;

    Point        		 axisOfRotation    = {0, 0, 0};
    Point         		 axisOfTranslation = {0, 0, 0};
	double 				 rotationSpeed     = .05;
	double				 movementSpeed     = 5;

	while (isRunning)
	{
		handleEvents(event,
			renderer3D, axisOfTranslation, axisOfRotation,
			isLocalRotation, isWorldRotation, isRunning);

		if (isWorldRotation)
		{
			rotateShapesAboutPoint(*(renderer3D.getAxes()),   {0, 0, 0}, axisOfRotation, rotationSpeed);
			rotateShapesAboutPoint(shapes, 					  {0, 0, 0}, axisOfRotation, rotationSpeed);
		}
		else if (isLocalRotation)
			rotateShapesLocal(shapes, axisOfRotation, rotationSpeed);
		else
			rotateShapesAboutPoint(shapes, {0, 0, 0}, axisOfRotation, rotationSpeed);

		translateShapes(shapes, axisOfTranslation, movementSpeed);

		renderer3D.draw();
	}
}