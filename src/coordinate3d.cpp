/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   MIT
 */
#include "coordinate3d.hpp"

Coordinate3D::Coordinate3D() : x(0), y(0), z(0) {}

Coordinate3D::Coordinate3D(int x, int y, int z) : x(x), y(y), z(z) {
}