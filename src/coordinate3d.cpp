/**
 * @file
 * @brief     Robot Arm class
 * @author    Jeroen van Hattem, Jeffrey de Waal, Wiebe van Breukelen, Sam Zandee
 * @license   See LICENSE
 */
#include "coordinate3d.hpp"

namespace RobotArm {

Coordinate3D::Coordinate3D(){}

Coordinate3D::Coordinate3D(const int x = 0, const int y = 0, const int z = 0) : x(x), y(y), z(z) {
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