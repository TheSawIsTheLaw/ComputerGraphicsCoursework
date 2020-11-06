#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include <QErrorMessage>
#include <QShortcut>
#include <QTimer>

#include "config.hpp"

#include "sizechanger.hpp"
#include "sizechooser.hpp"
#include "specialgraphicsview.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    facade = new UsageFacade;

    QListWidgetItem *tableIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/table.png"), "Стол");
    ui->listWidget->addItem(tableIMG);

    QListWidgetItem *barTableIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/barTable.png"), "Высокий стол");
    ui->listWidget->addItem(barTableIMG);

    QListWidgetItem *chairIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/chair.png"), "Стул");
    ui->listWidget->addItem(chairIMG);

    QListWidgetItem *barChairIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/barChair.png"), "Высокий стул");
    ui->listWidget->addItem(barChairIMG);

    QListWidgetItem *sofaIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/sofa.png"), "Диван");
    ui->listWidget->addItem(sofaIMG);

    QListWidgetItem *greenIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/green.png"), "Растение");
    ui->listWidget->addItem(greenIMG);

    QListWidgetItem *podiumIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/podium.png"), "Подиум");
    ui->listWidget->addItem(podiumIMG);

    QListWidgetItem *proectorIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/proector.png"), "Экран для\nпроектора");
    ui->listWidget->addItem(proectorIMG);

    QListWidgetItem *tvIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/tv.png"), "Плазменный\nтелевизор");
    ui->listWidget->addItem(tvIMG);

    QListWidgetItem *cupboardIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/cupboard.png"), "Шкаф");
    ui->listWidget->addItem(cupboardIMG);

    QListWidgetItem *rackIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/rack.png"), "Стеллаж");
    ui->listWidget->addItem(rackIMG);

    QListWidgetItem *flashlightIMG =
    new QListWidgetItem(QIcon("../Proj/imgs/flashlight.png"), "Источник света");
    ui->listWidget->addItem(flashlightIMG);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget::connect(ui->graphicsView, SIGNAL(sendMouse(size_t, size_t)), this, SLOT(getMouseEvent(size_t, size_t)));

    QShortcut *shortcutDown = new QShortcut(QKeySequence("down"), this);
    QObject::connect(shortcutDown, SIGNAL(activated()), this, SLOT(pictureDown()));

    QShortcut *shortcutUp = new QShortcut(QKeySequence("up"), this);
    QObject::connect(shortcutUp, SIGNAL(activated()), this, SLOT(pictureUp()));

    QShortcut *shortcutLeft = new QShortcut(QKeySequence("left"), this);
    QObject::connect(shortcutLeft, SIGNAL(activated()), this, SLOT(pictureLeft()));

    QShortcut *shortcutRight = new QShortcut(QKeySequence("right"), this);
    QObject::connect(shortcutRight, SIGNAL(activated()), this, SLOT(pictureRight()));

    QShortcut *shortcutRotateXRight = new QShortcut(QKeySequence("s"), this);
    QObject::connect(shortcutRotateXRight, SIGNAL(activated()), this, SLOT(pictureRotateXRight()));

    QShortcut *shortcutRotateXLeft = new QShortcut(QKeySequence("w"), this);
    QObject::connect(shortcutRotateXLeft, SIGNAL(activated()), this, SLOT(pictureRotateXLeft()));

    QShortcut *shortcutRotateYRight = new QShortcut(QKeySequence("d"), this);
    QObject::connect(shortcutRotateYRight, SIGNAL(activated()), this, SLOT(pictureRotateYRight()));

    QShortcut *shortcutRotateYLeft = new QShortcut(QKeySequence("a"), this);
    QObject::connect(shortcutRotateYLeft, SIGNAL(activated()), this, SLOT(pictureRotateYLeft()));

    QShortcut *shortcutRotateZLeft = new QShortcut(QKeySequence("q"), this);
    QObject::connect(shortcutRotateZLeft, SIGNAL(activated()), this, SLOT(pictureRotateZLeft()));

    QShortcut *shortcutRotateZRight = new QShortcut(QKeySequence("e"), this);
    QObject::connect(shortcutRotateZRight, SIGNAL(activated()), this, SLOT(pictureRotateZRight()));
}

//void MainWindow::updateScene()
//{
//    ui->graphicsView->scene()->clear();
//    ui->graphicsView->scene()->addPixmap(QPixmap("img.bmp"));
//    ui->graphicsView->show();
//    qDebug("UPD");
//    QTimer::singleShot(26, this, SLOT(updateScene()));
//}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::getMouseEvent(size_t x_, size_t y_)
{
    qDebug() << "Приняли ивент:" << x_ << y_ << '\n';
}

void MainWindow::pictureDown()
{
    qDebug() << "Крутим вниз";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveDownScene(MOVE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureUp()
{
    qDebug() << "Крутим вверх";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveUpScene(MOVE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureLeft()
{
    qDebug() << "Крутим влево";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveLeftScene(MOVE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRight()
{
    qDebug() << "Крутим вправо";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveRightScene(MOVE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateXRight()
{
    qDebug() << "Вертим по Х";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene * setScene = facade->rotateXScene(ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateXLeft()
{
    qDebug() << "Вертим по Х";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateXScene(-ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateYRight()
{
    qDebug() << "Вертим по Y";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateYScene(ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateYLeft()
{
    qDebug() << "Вертим по Y";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateYScene(-ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateZRight()
{
    qDebug() << "Вертим по z";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateZScene(ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateZLeft()
{
    qDebug() << "Вертим по z";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateZScene(-ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::on_pushButton_4_clicked()
{
    SizeChooser chooserWindow(nullptr);
    chooserWindow.setModal(true);
    chooserWindow.exec();

    if (!chooserWindow.getWidth() || !chooserWindow.getheight())
        return;

    qDebug() << ui->graphicsView->rect();

    facade->setCellScene(chooserWindow.getWidth(), chooserWindow.getheight());
    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
//    QTimer::singleShot(26, this, SLOT(updateScene()));
}

void MainWindow::on_pushButton_5_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    SizeChanger changerWindow(nullptr);
    changerWindow.setModal(true);
    changerWindow.exec();
}

void MainWindow::on_pushButton_clicked()
{
    int curRow = this->ui->listWidget->currentRow();
    if (curRow < 0)
        return;

    if (curRow == 0)
        facade->addTable();

    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);

    qDebug() << "Добавили стол...";
}
