#include "sizechooser.hpp"
#include "ui_sizechooser.h"

#include <QErrorMessage>

SizeChooser::SizeChooser(QWidget *parent) : QDialog(parent), ui(new Ui::SizeChooser)
{
    ui->setupUi(this);
}

SizeChooser::~SizeChooser() { delete ui; }

void SizeChooser::on_buttonBox_accepted()
{
    QString gotText = this->ui->lineEdit->text();
    size_t heightValue = gotText.toUInt();
    qDebug("height of cellPlate: %zu\n", heightValue);

    gotText = this->ui->lineEdit_2->text();
    size_t widthValue = gotText.toUInt();
    qDebug("Width of cellPlate: %zu\n", widthValue);

    if (heightValue && widthValue)
    {
        height = heightValue;
        width = widthValue;
    }
    else
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Были переданы некорректные значения.\n"
                         "При вводе убедитесь, что введённые зна"
                         "чения являются целочисленными положите"
                         "льными числами.");
    }
}

void SizeChooser::setWidth(size_t width_) { width = width_; }

size_t SizeChooser::getWidth() { return width; }

void SizeChooser::setheight(size_t height_) { height = height_; }

size_t SizeChooser::getheight() { return height; }
