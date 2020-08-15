#include "sizechanger.hpp"
#include "ui_sizechanger.h"

#include <QErrorMessage>

SizeChanger::SizeChanger(QWidget *parent) : QDialog(parent), ui(new Ui::SizeChanger)
{
    ui->setupUi(this);
}

SizeChanger::~SizeChanger() { delete ui; }

void SizeChanger::on_buttonBox_accepted()
{
    size_t lengthValue = 0, widthValue = 0;

    size_t catchedErrors = 0;

    QString gotText = this->ui->lineEdit->text();
    if (gotText != "")
    {
        lengthValue = gotText.toUInt();
        qDebug("New length of cellPlate: %zu\n", lengthValue);

        if (!lengthValue)
            catchedErrors++;
    }

    gotText = this->ui->lineEdit_2->text();
    if (gotText != "")
    {
        widthValue = gotText.toUInt();
        qDebug("New width of cellPlate: %zu\n", widthValue);

        if (!widthValue)
            catchedErrors++;
    }

    if (!catchedErrors)
    {
        newWidth = widthValue;
        newLength = lengthValue;
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

size_t SizeChanger::getNewWidth() { return newWidth; }

size_t SizeChanger::getNewLength() { return newLength; }
