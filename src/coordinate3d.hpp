/**
 * @file
 * @brief     This class contains the Coordinate3D struct
 * @author    Jeroen van Hattem, Jeffrey de Waal and Wiebe van Breukelen
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP

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
     * @param x : int
     * @param y : int
     * @param z : int
     *
     */
    Coordinate3D(int x, int y, int z);
};

#endif // COORDINATE3D_HPP
