/**
 * @file
 * @brief     This class contains the Coordinate3D struct
 * @author    Jeroen van Hattem, Jeffrey de Waal and Wiebe van Breukelen
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP

namespace RobotArm {

struct Coordinate3D {
  public:
    int x;
    int y;
    int z;

    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     */
    Coordinate3D();

    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     * @param x X constant
     * @param y Y constant
     * @param z Z constant
     */
    Coordinate3D(const int x, const int y, const int z);

    /**
     * @brief Used to add coordinate.
     *
     * @param coord Coordinate.
     */
    void operator+=(const Coordinate3D &coord);

    /**
     * @brief Used to substract coordinate.
     *
     * @param coord Coordinate.
     */
    void operator-=(const Coordinate3D &coord);

    /**
     * @brief Operator+
     *
     * @param coord
     * @return Coordinate3D
     */
    Coordinate3D operator+(const Coordinate3D &coord) const;

    /**
     * @brief
     *
     * @param coord
     * @return Coordinate3D
     */
    Coordinate3D operator-(const Coordinate3D &coord) const;
};

} // namespace RobotArm

#endif // COORDINATE3D_HPP
