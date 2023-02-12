#include "../include/Camera.h"

Camera::Camera()
{
    // this->position    = Quaternion(0, 0, 0, 10); // pos 10 on z axis
    // this->orientation = Quaternion(0, 0, 0, -1); // looking down -z axis
}

// Camera::Camera(Quaternion position, Quaternion orientation, double viewportDist)
// {
//     this->setPosition(position);
//     this->setOrientation(orientation);
//     this->setViewportDist(viewportDist);
// }

Camera::~Camera()
{

}

// Quaternion Camera::getPosition()
// {
//     return this->position;
// }

// Quaternion Camera::getOrientation()
// {
//     return this->orientation;
// }

// double     Camera::getViewportDist()
// {
//     return viewportDist;
// }

// void Camera::setPosition(Quaternion position)
// {
//     this->position = position;
// }

// void Camera::setOrientation(Quaternion orientation)
// {
//     this->orientation = orientation;
// }

// void Camera::setViewportDist(double viewportDist)
// {
//     this->viewportDist = viewportDist;
// }