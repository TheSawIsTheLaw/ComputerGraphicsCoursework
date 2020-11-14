#include "illuminantplacechooser.hpp"
#include "ui_illuminantplacechooser.h"

IlluminantPlaceChooser::IlluminantPlaceChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IlluminantPlaceChooser)
{
    ui->setupUi(this);
}

IlluminantPlaceChooser::~IlluminantPlaceChooser()
{
    delete ui;
}

void IlluminantPlaceChooser::setXAngle(int degrees)
{
    xAngle = degrees;
}

int IlluminantPlaceChooser::getXAngle()
{
    return xAngle;
}

void IlluminantPlaceChooser::setYAngle(int degrees)
{
    yAngle = degrees;
}

int IlluminantPlaceChooser::getYAngle()
{
    return yAngle;
}
