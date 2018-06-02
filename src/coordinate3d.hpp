/**
 * @file
 * @brief     This class contains the Coordinate3D Class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP

class Coordinate3D {
  private:
    int x;
    int y;
    int z;

  public:
    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     */
    Coordinate3D(int x, int y, int z);
    /**
     * @brief This function returns the X value of the coordinate
     *
     * @return int
     */
    int getX();
    /**
     * @brief This function returns the Y value of the coordinate
     *
     * @return int
     */
    int getY();
    /**
     * @brief This function returns the Z value of the coordinate
     *
     * @return int
     */
    int getZ();
    /**
     * @brief This function sets the X variable to the value passed as parameter.
     *
     * @param value : int
     */
    void setX(int value);
    /**
     * @brief This function sets the Y variable to the value passed as parameter.
     *
     * @param value : int
     */
    void setY(int value);
    /**
     * @brief This function sets the Z variable to the value passed as parameter.
     *
     * @param value : int
     */
    void setZ(int value);
};

#endif // COORDINATE3D_HPP