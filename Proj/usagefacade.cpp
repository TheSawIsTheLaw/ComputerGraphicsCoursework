#include "usagefacade.hpp"

#include "QDebug"
#include "QPen"

#include "config.hpp"

UsageFacade::UsageFacade()
{
    scene = new CellScene;

    drawer = new Drawer;
}

void UsageFacade::setCellScene(size_t width_, size_t length_)
{
    if (scene)
        delete scene;
    scene = new CellScene(width_, length_);
    qDebug("Set was done\n");
}

void UsageFacade::changeCellScene(size_t newWidth, size_t newLength)
{
    scene->changeSize(newWidth, newLength);
}

bool UsageFacade::isSceneSet() { return scene->getLength() && scene->getWidth(); }

QGraphicsScene *UsageFacade::drawScene(QRectF rect)
{
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

QGraphicsScene *Drawer::drawScene(CellScene *scene, QRectF rect)
{
    size_t width = scene->getWidth() * SCALE_FACTOR;
    size_t length = scene->getLength() * SCALE_FACTOR;

    scene->buildPlateModel(Dot3D(PLATE_START), Dot3D(length, width, PLATE_Z));

    // z-buf, возвращающий... Битмап?.. С значением ргб там на каждый пиксел, например.

    QGraphicsScene *outScene = new QGraphicsScene;
    outScene->setSceneRect(rect);

    outScene->addLine(0, 0, 1568, 1035, QPen(Qt::black));
    outScene->addLine(0, 0, 0, 0, QPen(Qt::blue)); // Ого, пиксел!

    return outScene;
}
