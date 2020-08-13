#include "sizechooser.hpp"
#include "ui_sizechooser.h"

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
