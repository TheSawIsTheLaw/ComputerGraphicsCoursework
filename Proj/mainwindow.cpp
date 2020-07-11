#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Стол");
    ui->listWidget->addItem("Высокий стол");
    ui->listWidget->addItem("Стул");
    ui->listWidget->addItem("Высокий стул");
    ui->listWidget->addItem("Диван");
    ui->listWidget->addItem("Растение в горшке");
    ui->listWidget->addItem("Подиум");
    ui->listWidget->addItem("Экран для проектора");
    ui->listWidget->addItem("Плазменный телевизор");
    ui->listWidget->addItem("Шкаф");
    ui->listWidget->addItem("Стеллаж");
    ui->listWidget->addItem("Источник света");
}

MainWindow::~MainWindow()
{
    delete ui;
}

