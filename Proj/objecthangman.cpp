#include "objecthangman.hpp"
#include "ui_objecthangman.h"

// Возможно тут стоит добавлять информацию о том, на какой клетке находится объект.
// Ну ещё и источники света с их градусами выводить!
ObjectHangman::ObjectHangman(CellScene *scene, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectHangman)
{
    ui->setupUi(this);

    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        ui->listWidget->addItem(QString::number(i) + ". " + scene->getModel(i).getName());
    }
}

ObjectHangman::~ObjectHangman()
{
    delete ui;
}
