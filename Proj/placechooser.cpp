#include "placechooser.h"
#include "ui_placechooser.h"

#include <QErrorMessage>
#include <QDebug>

PlaceChooser::PlaceChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения модели");
}

PlaceChooser::~PlaceChooser() { delete ui; }

void PlaceChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceChooser::getXCell() { return xCell; }

void PlaceChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceChooser::getYCell() { return yCell; }

double PlaceChooser::getModelLength() { return modelLength; }

double PlaceChooser::getModelHeight() { return modelLength; }

PlaceChooser::checkBox PlaceChooser::getDirection() { return direction; }

void PlaceChooser::on_buttonBox_accepted()
{
    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    gotText = ui->lineEdit_3->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelLength = gotText.toDouble();

    gotText = ui->lineEdit_4->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelHeight = gotText.toDouble();

    if (ui->radioButton->isChecked())
        direction = checkBox::XAXIS;
    else
        direction = checkBox::YAXIS;

    if (xCell < 0 || yCell < 0 || modelLength <= 0 || modelHeight <= 0)
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Были переданы неверные данные.\n"
                         "Убедитесь, что в поле выбора ячейки расположения модели\n"
                         "передано положительное целочисленное значение.\n"
                         "Убедитесь, что в поле выбора размера модели\n"
                         "передано положительное вещественное значение.");
    }

    this->close();
}
