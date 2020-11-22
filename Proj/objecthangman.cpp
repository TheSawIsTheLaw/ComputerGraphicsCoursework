#include "objecthangman.hpp"
#include "ui_objecthangman.h"

#include "rotationchooser.hpp"

#include <QErrorMessage>

ObjectHangman::ObjectHangman(CellScene *scene_, QWidget *parent)
: QDialog(parent), ui(new Ui::ObjectHangman)
{
    ui->setupUi(this);
    this->setWindowTitle("Изменение объектов сцены");

    scene = scene_;

    for (size_t i = 0; i < scene->getModelsNum(); i++)
        ui->listWidget->addItem(QString::number(i) + ". " + scene->getModel(i).getName() +
                                " on cell (" + QString::number(scene->getModel(i).getUsedXCell()) +
                                "; " + QString::number(scene->getModel(i).getUsedYCell()) + ")");

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

    close();
}

int ObjectHangman::changeModel(int num)
{
    rotationChooser rotationChooserWindow(scene->getModel(num).getUsedXCell(), scene->getModel(num).getUsedYCell(), nullptr);

    rotationChooserWindow.setModal(true);
    rotationChooserWindow.exec();

    if (rotationChooserWindow.stat == rotationChooser::status::ERROR_WAS_ACCURED)
        return 1;
    else if (rotationChooserWindow.stat == rotationChooser::status::NO_ACTIONS)
        return 2;

    PolModel curMod = scene->getModel(num);
    curMod.rotateZ(rotationChooserWindow.getAngle());
    curMod.moveTo(rotationChooserWindow.getNewXCell(), rotationChooserWindow.getNewYCell());
    scene->setModel(num, curMod);
    return 0;
}

void ObjectHangman::on_pushButton_2_clicked()
{
    int curRow = this->ui->listWidget->currentRow();
    if (curRow < 0)
        return;

    if (curRow < (int)scene->getModelsNum())
    {
        int ret = changeModel(curRow);
        if (ret == 1)
        {
            QErrorMessage *err = new QErrorMessage();
            err->showMessage("Были переданы неверные значения.");
        }
    }
    else
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Был выбран источник света. Его изменения не предусмотрены.");
    }

    close();
    return;
}
