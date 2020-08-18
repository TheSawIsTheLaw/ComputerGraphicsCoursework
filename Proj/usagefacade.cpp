#include "usagefacade.hpp"

#include "QDebug"
#include "QPen"

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
    size_t width = scene->getWidth() * 60;
    size_t length = scene->getLength() * 60;

    scene->setStartOfPlate(Dot3D(0, 0, 0));

    QGraphicsScene *outScene = new QGraphicsScene;
    outScene->setSceneRect(rect); // To define

    outScene->addLine(0, 0, 1568, 1035, QPen(Qt::black));

    return outScene;
}
