#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define FLEX

#include "QDebug"
#include <QErrorMessage>
#include <QShortcut>
#include <QTimer>

#ifdef FLEX
#include <QMediaPlayer>
#endif

#include "config.hpp"

#include "sizechanger.hpp"
#include "sizechooser.hpp"
#include "specialgraphicsview.hpp"
#include "placechooser.h"
#include "illuminantplacechooser.hpp"
#include "objecthangman.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    facade = new UsageFacade;

#ifdef FLEX
    QMediaPlayer *player = new QMediaPlayer();
    player->setMedia(QUrl("C:/Users/dobri/Downloads/BigBabyTape.mp3"));
    player->play();
#endif

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

    QShortcut *shortcutScaleUp = new QShortcut(QKeySequence("z"), this);
    QObject::connect(shortcutScaleUp, SIGNAL(activated()), this, SLOT(pictureScaleUp()));

    QShortcut *shortcutScaleDown = new QShortcut(QKeySequence("x"), this);
    QObject::connect(shortcutScaleDown, SIGNAL(activated()), this, SLOT(pictureScaleDown()));

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
    if (!facade->isSceneSet())
        return;
    qDebug() << "Крутим вниз";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveDownScene(MOVE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureUp()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Крутим вверх";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveUpScene(MOVE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureLeft()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Крутим влево";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveLeftScene(MOVE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRight()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Крутим вправо";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->moveRightScene(MOVE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureScaleUp()
{
    if (!facade->isSceneSet())
        return;
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->scaleScene(SCALE_VALUE + 1, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureScaleDown()
{
    if (!facade->isSceneSet())
        return;
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->scaleScene(1 - SCALE_VALUE, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateXRight()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Вертим по Х вниз";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene * setScene = facade->rotateXScene(ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateXLeft()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Вертим по Х";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateXScene(-ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateYRight()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Вертим по Y";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateYScene(ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateYLeft()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Вертим по Y влево";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateYScene(-ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateZRight()
{
    if (!facade->isSceneSet())
        return;
    qDebug() << "Вертим по z";
    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->rotateZScene(ROTATE_UNIT, ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateZLeft()
{
    if (!facade->isSceneSet())
        return;
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
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    int curRow = this->ui->listWidget->currentRow();
    if (curRow < 0)
        return;

    if (curRow >= 0 && curRow < 11)
    {
        PlaceChooser placeChooserWindow(nullptr);
        placeChooserWindow.setModal(true);
        placeChooserWindow.exec();
        if (placeChooserWindow.getXCell() < 0 || placeChooserWindow.getYCell() < 0)
            return;
        int retCode = 0;
        if (curRow == 0)
            retCode = facade->addTable(placeChooserWindow.getXCell(), placeChooserWindow.getYCell());

        if (retCode)
        {
            QErrorMessage *err = new QErrorMessage();
            err->showMessage("Указанная ячейка уже занята.");
            return;
        }
    }
    else
    {
        IlluminantPlaceChooser placeChooserWindow(nullptr);
        placeChooserWindow.setModal(true);
        placeChooserWindow.exec();

        facade->addIlluminant(placeChooserWindow.getXAngle(), placeChooserWindow.getYAngle());
    }

    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
}

void MainWindow::on_pushButton_7_clicked()
{
    ObjectHangman objectHangmanWindow(facade->getScene(), nullptr);

    objectHangmanWindow.setModal(true);
    objectHangmanWindow.exec();

    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
}
