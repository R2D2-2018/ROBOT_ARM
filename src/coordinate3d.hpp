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
    Coordinate3D(int x, int y, int z);
    int getX();
    int getY();
    int getZ();
};

#endif // COORDINATE3D_HPP