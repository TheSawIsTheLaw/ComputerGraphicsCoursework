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

void Drawer::zBufferAlg(CellScene *scene, size_t bufLength, size_t bufWidth)
{
    depthBuffer.erase(depthBuffer.begin(), depthBuffer.end());
    frameBuffer.erase(frameBuffer.begin(), frameBuffer.end());

    for (size_t i = 0; i < bufLength; i++)
    {
        depthBuffer.push_back(std::vector<size_t>(bufWidth));
        frameBuffer.push_back(std::vector<size_t>(bufWidth));
    }

    PolModel plate = scene->getPlateModel();
    std::vector<Facet> facets = plate.getFacets();
    std::vector<Vertex> vertices = plate.getVertices();
    Dot3D dotA, dotB, dotC;

    for (std::vector<Facet>::iterator iter = facets.begin(); iter != facets.end() ; iter++)
    {
        dotA = vertices.at(iter->getUsedDots().at(0)).getPosition();
        dotB = vertices.at(iter->getUsedDots().at(1)).getPosition();
        dotC = vertices.at(iter->getUsedDots().at(2)).getPosition();

        qDebug() << "CURRENT DOTS ARE:" << dotA << dotB << dotC;
    }

}

QGraphicsScene *Drawer::drawScene(CellScene *scene, QRectF rect)
{
    size_t width = scene->getWidth() * SCALE_FACTOR;
    size_t length = scene->getLength() * SCALE_FACTOR;

    scene->buildPlateModel(Dot3D(PLATE_START), Dot3D(length, width, PLATE_Z));

    zBufferAlg(scene, rect.size().width(), rect.size().height());

    QGraphicsScene *outScene = new QGraphicsScene;
    outScene->setSceneRect(rect);

    outScene->addLine(0, 0, 1568, 1035, QPen(Qt::black));
    outScene->addLine(0, 0, 0, 0, QPen(Qt::blue)); // Ого, пиксел!

    return outScene;
}
