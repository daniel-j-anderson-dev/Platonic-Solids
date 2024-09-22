#include "../include/Renderer.h"
#include "../include/Transformer.h"
#include "../include/EventHandler.h"

int main(int argc, char *argv[])
{
	Renderer  			 renderer3D        = Renderer(800, 800);
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
		handleEvents(event,
			renderer3D, axisOfTranslation, axisOfRotation,
			isLocalRotation, isWorldRotation, isRunning);

		if (isWorldRotation)
		{
			rotateShapesAboutPoint(
				renderer3D.getAxes(),
				{0, 0, 0},
				axisOfRotation,
				rotationSpeed
			);
			rotateShapesAboutPoint(
				renderer3D.getShapes(),
				{0, 0, 0},
				axisOfRotation,
				rotationSpeed
			);
		}
		else if (isLocalRotation)
			rotateShapesLocal(renderer3D.getShapes(), axisOfRotation, rotationSpeed);
		else
			rotateShapesAboutPoint(renderer3D.getShapes(), {0, 0, 0}, axisOfRotation, rotationSpeed);

		translateShapes(renderer3D.getShapes(), axisOfTranslation, movementSpeed);

		renderer3D.draw();
	}
}