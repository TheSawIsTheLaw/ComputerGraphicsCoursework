#include "illuminantplacechooser.hpp"
#include "ui_illuminantplacechooser.h"

IlluminantPlaceChooser::IlluminantPlaceChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IlluminantPlaceChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения источника света");
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

void IlluminantPlaceChooser::on_buttonBox_4_accepted()
{
    QString gotText = this->ui->XAngleInp->text();
    int xAngle_ = gotText.toInt();

    gotText = this->ui->YAngleInp->text();
    int yAngle_ = gotText.toInt();

    xAngle = xAngle_;
    yAngle = yAngle_;


    this->close();
}
