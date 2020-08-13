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

    if (!lengthValue || !widthValue)
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Были переданы некорректные значения.\n"
                         "При вводе убедитесь, что введённые значения являются целочисленными положительными числами.");
    }
}
