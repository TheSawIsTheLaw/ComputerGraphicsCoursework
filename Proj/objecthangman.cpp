#include "objecthangman.hpp"
#include "ui_objecthangman.h"

#include <QErrorMessage>
#include "rotationchooser.hpp"

// Возможно тут стоит добавлять информацию о том, на какой клетке находится объект.
// Ну ещё и источники света с их градусами выводить!
ObjectHangman::ObjectHangman(CellScene *scene_, QWidget *parent)
: QDialog(parent), ui(new Ui::ObjectHangman)
{
    ui->setupUi(this);

    scene = scene_;

    for (size_t i = 0; i < scene->getModelsNum(); i++)
        ui->listWidget->addItem(QString::number(i) + ". " + scene->getModel(i).getName() +
                                " on cell (" + QString::number(scene->getModel(i).getUsedCells()[0][0]) +
                                "; " + QString::number(scene->getModel(i).getUsedCells()[0][1]) + ")");

    for (size_t i = 0; i < scene->getIllumNum(); i++)
        ui->listWidget->addItem(
        QString::number(scene->getModelsNum() + i) + ". Illuminant with angles (" +
        QString::number(scene->getIlluminant(i).getXAngle()) +
        "°; " + QString::number(scene->getIlluminant(i).getYAngle()) + "°)");
}

ObjectHangman::~ObjectHangman() { delete ui; }

void ObjectHangman::on_pushButton_clicked()
{
    int curRow = this->ui->listWidget->currentRow();
    if (curRow < 0)
        return;

    if (curRow < (int)scene->getModelsNum())
        scene->deleteModel(curRow);
    else
        scene->deleteIlluminant(curRow - scene->getModelsNum());
}

void ObjectHangman::changeModel(int index)
{

}

void ObjectHangman::on_pushButton_2_clicked()
{
    int curRow = this->ui->listWidget->currentRow();
    if (curRow < 0)
        return;

    if (curRow > (int)scene->getModelsNum())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Выбранный объект является источником света."
                         "Его прямое изменение не предусмотрено.");
    }
    else
        changeModel(curRow);
}
