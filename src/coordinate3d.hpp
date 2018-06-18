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
    /**
     * @brief Parameters describing a three dimensional location within space.
     *
     */
    int x, y, z;

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
     * @brief Used to add coordinates.
     *
     * @param coord Coordinate.
     */
    void operator+=(const Coordinate3D &coord);

    /**
     * @brief Used to substract coordinates.
     *
     * @param coord Coordinate.
     */
    void operator-=(const Coordinate3D &coord);

    /**
     * @brief The addition operator of two Coordinate3D objects.
     *
     * @param coord Constatn coordinate to add.
     * @return Coordinate3D New Coordinate3D object as the result of the addition.
     */
    Coordinate3D operator+(const Coordinate3D &coord) const;

    /**
     * @brief The substract operator of two Coordinate3D objects.
     *
     * @param coord Constant coordinate to substract.
     * @return Coordinate3D New Coordinate3D object as the result of the substraction.
     */
    Coordinate3D operator-(const Coordinate3D &coord) const;
};

} // namespace RobotArm

#endif // COORDINATE3D_HPP
