/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem, Jeffrey de Waal, Wiebe van Breukelen
 * @license   See LICENSE
 */
#include "coordinate3d.hpp"

namespace RobotArm {

Coordinate3D::Coordinate3D() : x(0), y(0), z(0) {
}

Coordinate3D::Coordinate3D(const int x, const int y, const int z) : x(x), y(y), z(z) {
}

void Coordinate3D::operator+=(const Coordinate3D &coord) {
    x += coord.x;
    y += coord.y;
    z += coord.z;
}

void Coordinate3D::operator-=(const Coordinate3D &coord) {
    x -= coord.x;
    y -= coord.y;
    z -= coord.z;
}

Coordinate3D Coordinate3D::operator+(const Coordinate3D &coord) const {
    Coordinate3D newCoord(*this);

    newCoord += coord;

    return newCoord;
}

Coordinate3D Coordinate3D::operator-(const Coordinate3D &coord) const {
    Coordinate3D newCoord(*this);

    newCoord -= coord;

    return newCoord;
}

} // namespace RobotArm