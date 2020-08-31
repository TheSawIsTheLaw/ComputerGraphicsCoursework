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

QGraphicsScene *UsageFacade::moveUpScene(double value, QRectF rect)
{
    scene->moveUp(value);
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

QGraphicsScene *UsageFacade::moveDownScene(double value, QRectF rect)
{
    scene->moveDown(value);
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

QGraphicsScene *UsageFacade::moveRightScene(double value, QRectF rect)
{
    scene->moveRight(value);
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

QGraphicsScene *UsageFacade::moveLeftScene(double value, QRectF rect)
{
    scene->moveLeft(value);
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
        depthBuffer.push_back(std::vector<size_t>(bufWidth, 0));
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

        //        qDebug() << "CURRENT DOTS ARE:" << dotsArr[0] << dotsArr[1] <<
        //        dotsArr[2];

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

        //        if (dotsArr[0].getYCoordinate() == dotsArr[1].getYCoordinate() &&
        //            dotsArr[0].getXCoordinate() < dotsArr[1].getXCoordinate())
        //            std::swap(dotsArr[0], dotsArr[1]);

        //        if (dotsArr[1].getYCoordinate() == dotsArr[2].getYCoordinate() &&
        //            dotsArr[1].getXCoordinate() > dotsArr[2].getXCoordinate())
        //            std::swap(dotsArr[1], dotsArr[2]);

        //        qDebug() << "SORTED DOTS ARE:" << dotsArr[0] << dotsArr[1] <<
        //        dotsArr[2];

        double x1 = dotsArr[0].getXCoordinate();
        double x2 = dotsArr[1].getXCoordinate();
        double x3 = dotsArr[2].getXCoordinate();

        double z1 = dotsArr[0].getZCoordinate();
        double z2 = dotsArr[1].getZCoordinate();
        double z3 = dotsArr[2].getZCoordinate();

        for (int curY = round(dotsArr[0].getYCoordinate());
             curY <= round(dotsArr[1].getYCoordinate()); curY++)
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

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
                std::swap(aInc, bInc);
            }

            //            qDebug() << "xA xB zA zB aInc bInc: " << xA << xB << zA << zB <<
            //            aInc << bInc;

            if (zA > depthBuffer[round(xA)][curY])
            {
                depthBuffer[round(xA)][curY] = zA;
                frameBuffer[round(xA)][curY] = 2;
            }
            int curCol = 1;
            if (curY == round(dotsArr[0].getYCoordinate()))
            {
                curCol = 2;
            }

            for (int curX = round(xA) + 1; curX < round(xB); curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                if (curZ > depthBuffer[curX][curY])
                {
                    depthBuffer[curX][curY] = curZ;
                    if (frameBuffer[curX][curY] != 2)
                        frameBuffer[curX][curY] = curCol;
                }
                // А КАКОГО ХРЕНА ЭТО РАБОТАЕТ? КАКИМ ОБРАЗОМ ОДНО ГОВНО ЗАЛЕЗАЕТ НА
                // ДРУГОЕ?
                // ПОЧЕМУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУ
            }
            double curZ = zA + (zB - zA) * (round(xB) - xA) / (xB - xA);
            if (curZ > depthBuffer[round(xB)][curY])
            {
                depthBuffer[round(xB)][curY] = curZ;
                frameBuffer[round(xB)][curY] = 2;
            }
        }

        for (int curY = round(dotsArr[1].getYCoordinate());
             curY <= round(dotsArr[2].getYCoordinate()); curY++)
        {
            double aInc = 0;
            if (dotsArr[2].getYCoordinate() - dotsArr[1].getYCoordinate() != 0)
                aInc = (curY - dotsArr[1].getYCoordinate()) /
                       (dotsArr[2].getYCoordinate() - dotsArr[1].getYCoordinate());

            double bInc = (curY - dotsArr[0].getYCoordinate()) /
                          (dotsArr[2].getYCoordinate() - dotsArr[0].getYCoordinate());

            double xA = x2 + (x3 - x2) * aInc;
            double xB = x1 + (x3 - x1) * bInc;
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
                std::swap(aInc, bInc);
            }

            //            qDebug() << "xA xB zA zB aInc bInc: " << xA << xB << zA << zB <<
            //            aInc << bInc;

            if (zA > depthBuffer[round(xA)][curY])
            {
                depthBuffer[round(xA)][curY] = zA;
                frameBuffer[round(xA)][curY] = 2;
            }
            int curCol = 1;
            if (curY == round(dotsArr[2].getYCoordinate()))
                curCol = 2;
            for (int curX = round(xA) + 1; curX < round(xB); curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                if (curZ >= depthBuffer[curX][curY])
                {
                    depthBuffer[curX][curY] = curZ;
                    if (frameBuffer[curX][curY] != 2)
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

    using namespace std::chrono;
    milliseconds start =
    duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    zBufferAlg(scene, rect.size().width(), rect.size().height());
    milliseconds end =
    duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    qDebug() << "Time for zBuf" << (end - start).count();

    QGraphicsScene *outScene = new QGraphicsScene;
    outScene->setSceneRect(rect);

    QPen blackPen(Qt::black);
    QPen redPen(Qt::red);

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    int w = rect.size().width();  /* Put here what ever width you want */
    int h = rect.size().height(); /* Put here what ever height you want */

    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3 * w * h; // w is your image width, h is image height, both int
    if (img)
        free(img);
    img = (unsigned char *) malloc(3 * w * h);
    int x;
    int y;

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            x = i;
            y = (h - 1) - j;
            if (frameBuffer.at(i).at(h - 1 - j) == 1 || frameBuffer.at(i).at(h - 1 - j) == 0)
            {
                img[(x + y * w) * 3 + 2] = (unsigned char) (255);
                img[(x + y * w) * 3 + 1] = (unsigned char) (255);
                img[(x + y * w) * 3 + 0] = (unsigned char) (255);
            }
            else
            {
                img[(x + y * w) * 3 + 2] = (unsigned char) (0);
                img[(x + y * w) * 3 + 1] = (unsigned char) (0);
                img[(x + y * w) * 3 + 0] = (unsigned char) (0);
            }
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    bmpinfoheader[4] = (unsigned char) (w);
    bmpinfoheader[5] = (unsigned char) (w >> 8);
    bmpinfoheader[6] = (unsigned char) (w >> 16);
    bmpinfoheader[7] = (unsigned char) (w >> 24);
    bmpinfoheader[8] = (unsigned char) (h);
    bmpinfoheader[9] = (unsigned char) (h >> 8);
    bmpinfoheader[10] = (unsigned char) (h >> 16);
    bmpinfoheader[11] = (unsigned char) (h >> 24);

    f = fopen("img.bmp", "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for (int i = 0; i < h; i++)
    {
        fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
    }
    fclose(f);

    //    for (size_t i = 0; i < rect.size().width(); i++)
    //        for (size_t j = 0; j < rect.size().height(); j++)
    //            if (frameBuffer.at(i).at(j) == 1)
    //                outScene->addLine(i, j, i, j, redPen);
    //            else if (frameBuffer.at(i).at(j) == 2)
    //                outScene->addLine(i, j, i, j, blackPen);
    outScene->addPixmap(QPixmap("img.bmp"));
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    qDebug() << "Time for drawing" << (end - start).count();
    //    qDebug() <<
    //    QPixmap("C:/Users/dobri/Desktop/FirstCurseWork/Proj/imgs/smert.jpg");
    ///! Если в один момент мне станет очень грустно, я соберусь с силами и буду собирать
    ///свой личный png файл, который потом буду ставить сюда.
    /// И дело тут не в том, что мне это надо, я просто чётко чую, что я, ***, должен.
    return outScene;
}
