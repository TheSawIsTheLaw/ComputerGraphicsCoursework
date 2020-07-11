#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QListWidgetItem *tableIMG = new QListWidgetItem(QIcon("../Proj/imgs/table.png"), "Стол");
    ui->listWidget->addItem(tableIMG);

    QListWidgetItem *barTableIMG = new QListWidgetItem(QIcon("../Proj/imgs/barTable.png"), "Высокий стол");
    ui->listWidget->addItem(barTableIMG);

    QListWidgetItem *chairIMG = new QListWidgetItem(QIcon("../Proj/imgs/chair.png"), "Стул");
    ui->listWidget->addItem(chairIMG);

    QListWidgetItem *barChairIMG = new QListWidgetItem(QIcon("../Proj/imgs/barChair.png"), "Высокий стул");
    ui->listWidget->addItem(barChairIMG);

    QListWidgetItem *sofaIMG = new QListWidgetItem(QIcon("../Proj/imgs/sofa.png"), "Диван");
    ui->listWidget->addItem(sofaIMG);

    QListWidgetItem *greenIMG = new QListWidgetItem(QIcon("../Proj/imgs/green.png"), "Растение");
    ui->listWidget->addItem(greenIMG);

    QListWidgetItem *podiumIMG = new QListWidgetItem(QIcon("../Proj/imgs/podium.png"), "Подиум");
    ui->listWidget->addItem(podiumIMG);

    QListWidgetItem *proectorIMG = new QListWidgetItem(QIcon("../Proj/imgs/proector.png"), "Экран для проектора");
    ui->listWidget->addItem(proectorIMG);

    QListWidgetItem *tvIMG = new QListWidgetItem(QIcon("../Proj/imgs/tv.png"), "Плазменный телевизор");
    ui->listWidget->addItem(tvIMG);

    QListWidgetItem *cupboardIMG = new QListWidgetItem(QIcon("../Proj/imgs/cupboard.png"), "Шкаф");
    ui->listWidget->addItem(cupboardIMG);

    QListWidgetItem *rackIMG = new QListWidgetItem(QIcon("../Proj/imgs/rack.png"), "Стеллаж");
    ui->listWidget->addItem(rackIMG);

    QListWidgetItem *flashlightIMG = new QListWidgetItem(QIcon("../Proj/imgs/flashlight.png"), "Источник света");
    ui->listWidget->addItem(flashlightIMG);
}

MainWindow::~MainWindow()
{
    delete ui;
}

