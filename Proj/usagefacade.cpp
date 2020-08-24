#include "usagefacade.hpp"

#include "QDebug"
#include "QPen"

#include "math.h"

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
        depthBuffer.push_back(
        std::vector<size_t>(bufWidth, 0));
        frameBuffer.push_back(std::vector<size_t>(bufWidth, 0));
    }

    //    qDebug() << "Frame Vec: " << frameBuffer;

    PolModel plate = scene->getPlateModel();
    std::vector<Facet> facets = plate.getFacets();
    std::vector<Vertex> vertices = plate.getVertices();
    std::array<Dot3D, 3> dotsArr;

    for (std::vector<Facet>::iterator iter = facets.begin(); iter != facets.end(); iter++)
    {
        dotsArr[0] = vertices.at(iter->getUsedDots().at(0)).getPosition();
        dotsArr[1] = vertices.at(iter->getUsedDots().at(1)).getPosition();
        dotsArr[2] = vertices.at(iter->getUsedDots().at(2)).getPosition();

        qDebug() << "CURRENT DOTS ARE:" << dotsArr[0] << dotsArr[1] << dotsArr[2];

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

        if (dotsArr[0].getYCoordinate() == dotsArr[1].getYCoordinate() &&
            dotsArr[0].getXCoordinate() < dotsArr[1].getXCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);

        qDebug() << "SORTED DOTS ARE:" << dotsArr[0] << dotsArr[1] << dotsArr[2];

        double x1 = dotsArr[0].getXCoordinate();
        double x2 = dotsArr[1].getXCoordinate();
        double x3 = dotsArr[2].getXCoordinate();

        double z1 = dotsArr[0].getZCoordinate();
        double z2 = dotsArr[1].getZCoordinate();
        double z3 = dotsArr[2].getZCoordinate();

        for (int curY = round(dotsArr[0].getYCoordinate());
             curY <= round(dotsArr[2].getYCoordinate()); curY++)
        {
            double aInc = 1;
            if (dotsArr[1].getYCoordinate() - dotsArr[0].getYCoordinate() != 0)
                aInc = (curY - dotsArr[0].getYCoordinate()) /
                       (dotsArr[1].getYCoordinate() - dotsArr[0].getYCoordinate());

            double bInc = (curY - dotsArr[0].getYCoordinate()) /
                          (dotsArr[2].getYCoordinate() - dotsArr[0].getYCoordinate());

            double xA = x1 + (x2 - x1) * aInc;
            double xB = x1 + (x3 - x1) * bInc;
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            qDebug() << "xA xB zA zB aInc bInc: " << xA << xB << zA << zB << aInc << bInc;

            if (zA > depthBuffer[round(xA)][curY])
            {
                depthBuffer[round(xA)][curY] = zA;
                frameBuffer[round(xA)][curY] = 2;
            }
            int curCol = 1;
            if (curY == round(dotsArr[0].getYCoordinate()) ||
                curY == round(dotsArr[2].getYCoordinate()))
                curCol = 2;
            for (int curX = round(xA) + 1; curX < round(xB); curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                if (curZ > depthBuffer[curX][curY])
                {
                    depthBuffer[curX][curY] = curZ;
                    frameBuffer[curX][curY] = curCol;
                }
            }
            double curZ = zA + (zB - zA) * (round(xB) - xA) / (xB - xA);
            if (curZ > depthBuffer[round(xB)][curY])
            {
                depthBuffer[round(xB)][curY] = curZ;
                frameBuffer[round(xB)][curY] = 2;
            }
        }
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

    QPen blackPen(Qt::black);
    QPen redPen(Qt::red);

    for (size_t i = 0; i < rect.size().width(); i++)
        for (size_t j = 0; j < rect.size().height(); j++)
            if (frameBuffer.at(i).at(j) == 1)
                outScene->addLine(i, j, i, j, redPen);
            else if (frameBuffer.at(i).at(j) == 2)
                outScene->addLine(i, j, i, j, blackPen);

    return outScene;
}
