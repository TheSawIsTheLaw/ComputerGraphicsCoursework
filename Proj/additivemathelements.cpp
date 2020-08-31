#include "additivemathelements.hpp"
#include "QDebug"

double Dot3D::getXCoordinate() const { return xCoordinate; }

void Dot3D::setXCoordinate(double value) { xCoordinate = value; }

double Dot3D::getYCoordinate() const { return yCoordinate; }

void Dot3D::setYCoordinate(double value) { yCoordinate = value; }

double Dot3D::getZCoordinate() const { return zCoordinate; }

void Dot3D::setZCoordinate(double value) { zCoordinate = value; }

void Dot3D::moveDot(double xDif, double yDif, double zDif)
{
    xCoordinate += xDif;
    yCoordinate += yDif;
    zCoordinate += zDif;
}

void Dot3D::scaleDot(double coef, double xCenter, double yCenter, double zCenter)
{
    xCoordinate -= xCenter;
    yCoordinate -= yCenter;
    zCoordinate -= zCenter;

    Eigen::Matrix4f scaleMatrix;
    // clang-format off
    scaleMatrix << coef, 0, 0, 0,
                   0, coef, 0, 0,
                   0, 0, coef, 0,
                   0, 0,    0, 1;
    // clang-format on
    Eigen::MatrixXf coordinatesVec(1, 4);
    coordinatesVec << xCoordinate, yCoordinate, zCoordinate, 1;

//    std::cout << scaleMatrix << "\n\n" << coordinatesVec;

    coordinatesVec = coordinatesVec * scaleMatrix;
    xCoordinate = coordinatesVec(0, 0) + xCenter;
    yCoordinate = coordinatesVec(0, 1) + yCenter;
    zCoordinate = coordinatesVec(0, 2) + zCenter;

//    std::cout << "\n\n" << coordinatesVec * scaleMatrix << "\n-----------\n";
}

std::ostream &operator<<(std::ostream &os, const Dot3D &dot)
{
    os << "Dot3D: (" << dot.xCoordinate << "; " << dot.yCoordinate << "; "
       << dot.zCoordinate << ")\n";
    return os;
}

QDebug operator<<(QDebug deb, const Dot3D &dot)
{
    deb << "Dot3D: (" << dot.getXCoordinate() << "; " << dot.getYCoordinate() << "; "
        << dot.getZCoordinate() << ")\n";
    return deb;
}
