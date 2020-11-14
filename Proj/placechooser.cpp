#include "placechooser.h"
#include "ui_placechooser.h"

#include <QErrorMessage>

PlaceChooser::PlaceChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaceChooser)
{
    ui->setupUi(this);
}

PlaceChooser::~PlaceChooser()
{
    delete ui;
}

void PlaceChooser::setXCell(size_t xCell_)
{
    xCell = xCell_;
}

size_t PlaceChooser::getXCell()
{
    return xCell;
}

void PlaceChooser::setYCell(size_t yCell_)
{
    yCell = yCell_;
}

size_t PlaceChooser::getYCell()
{
    return yCell;
}

void PlaceChooser::on_buttonBox_accepted()
{
    QString gotText = this->ui->lineEdit->text();
    size_t xCell_ = gotText.toUInt();

    gotText = this->ui->lineEdit_2->text();
    size_t yCell_ = gotText.toUInt();

    if (xCell_ && yCell_)
    {
        xCell = xCell_;
        yCell = yCell_;
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
