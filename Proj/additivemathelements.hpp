#ifndef ADDITIVEMATHELEMENTS_HPP
#define ADDITIVEMATHELEMENTS_HPP

#include <vector>
#include <iostream>

#include "QDebug"

class Dot2D
{
private:
    double xCoordinate, yCoordinate;

public:
    double getXCoordinate();
    void setXCoordinate(double value);

    double getYCoordinate();
    void setYCoordinate(double value);
};

class Dot3D
{
private:
    double xCoordinate, yCoordinate, zCoordinate;

public:
    Dot3D() {};
    Dot3D(double xCoord_, double yCoord_, double zCoord_) : xCoordinate(xCoord_), yCoordinate(yCoord_), zCoordinate(zCoord_) {}

    double getXCoordinate() const;
    void setXCoordinate(double value);

    double getYCoordinate() const;
    void setYCoordinate(double value);

    double getZCoordinate() const;
    void setZCoordinate(double value);

    friend std::ostream &operator<<(std::ostream &os, const Dot3D &dot);
    friend QDebug operator<<(QDebug deb, const Dot3D &dot);
};

class MathVec
{
private:
    double xInc, yInc, zInc;

public:
    double getXInc();
    void setXInc(double value);

    double getYInc();
    void setYInc(double value);

    double getZInc();
    void setZInc(double value);
};

#endif // ADDITIVEMATHELEMENTS_HPP
