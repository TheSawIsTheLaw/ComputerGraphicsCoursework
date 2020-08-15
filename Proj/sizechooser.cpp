#include "sizechooser.hpp"
#include "ui_sizechooser.h"

#include <QErrorMessage>

SizeChooser::SizeChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeChooser)
{
    ui->setupUi(this);
}

SizeChooser::~SizeChooser()
{
    delete ui;
}

void SizeChooser::on_buttonBox_accepted()
{
    QString gotText = this->ui->lineEdit->text();
    size_t lengthValue = gotText.toUInt();
    qDebug("Length of cellPlate: %zu\n", lengthValue);

    gotText = this->ui->lineEdit_2->text();
    size_t widthValue = gotText.toUInt();
    qDebug("Width of cellPlate: %zu\n", widthValue);

    if (lengthValue && widthValue)
    {
        length = lengthValue;
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

void SizeChooser::setWidth(size_t width_)
{
    width = width_;
}

size_t SizeChooser::getWidth()
{
    return width;
}

void SizeChooser::setLength(size_t length_)
{
    length = length_;
}

size_t SizeChooser::getLength()
{
    return length;
}
