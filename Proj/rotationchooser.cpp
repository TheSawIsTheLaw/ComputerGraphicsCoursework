#include "rotationchooser.hpp"
#include "ui_rotationchooser.h"

rotationChooser::rotationChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rotationChooser)
{
    ui->setupUi(this);
}

rotationChooser::~rotationChooser()
{
    delete ui;
}

int rotationChooser::getNewXCell()
{
    return newXCell;
}

int rotationChooser::getNewYCell()
{
    return newYCell;
}

int rotationChooser::getXAngle()
{
    return xAngle;
}

int rotationChooser::getYAngle()
{
    return yAngle;
}

void rotationChooser::on_buttonBox_accepted()
{
    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        stat = ERROR_WAS_ACCURED;
        this->close();
        return;
    }
    xAngle = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        stat = ERROR_WAS_ACCURED;
        this->close();
        return;
    }
    yAngle = gotText.toInt();

    gotText = this->ui->lineEdit_3->text();
    if (gotText == "")
    {
        stat = ERROR_WAS_ACCURED;
        this->close();
        return;
    }
    newXCell = gotText.toInt();

    gotText = this->ui->lineEdit_4->text();
    if (gotText == "0")
    {
        stat = ERROR_WAS_ACCURED;
        this->close();
        return;
    }

    stat = ACTIONS_WERE_DONE;
}

void rotationChooser::on_buttonBox_rejected()
{
    stat = NO_ACTIONS;
    this->close();
}
