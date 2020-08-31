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
