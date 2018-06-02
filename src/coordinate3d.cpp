/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "coordinate3d.hpp"

Coordinate3D::Coordinate3D(int x, int y, int z) : x(x), y(y), z(z) {
}

int Coordinate3D::getX() {
    return x;
}

int Coordinate3D::getY() {
    return y;
}

int Coordinate3D::getZ() {
    return z;
}

void Coordinate3D::setX(int value) {
    x = value;
}

void Coordinate3D::setY(int value) {
    y = value;
}

void Coordinate3D::setZ(int value) {
    z = value;
}