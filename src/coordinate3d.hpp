/**
 * @file
 * @brief     This class contains the Coordinate3D Class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP

class Coordinate3D {
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