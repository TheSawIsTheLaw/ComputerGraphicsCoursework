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

QGraphicsScene *UsageFacade::rotateXScene(double angle, QRectF rect)
{
    scene->rotateX(angle);
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

QGraphicsScene *UsageFacade::rotateYScene(double angle, QRectF rect)
{
    scene->rotateY(angle);
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

void UsageFacade::addTable()
{
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    // Нижняя площадка
    Dot3D dot(50, 50, 801);
    std::vector<size_t> vec = {0};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(90);
    vec = {0, 1};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(90);
    vec = {0};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(50);
    vec = {0, 1};
    vertices.push_back(Vertex(dot, vec));

    // *Стержень*
    // Верх
    dot.setXCoordinate(60);
    dot.setYCoordinate(60);
    vec = {2, 3};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(80);
    vec = {2};
    vertices.push_back(Vertex(dot, vec));

    dot.setZCoordinate(750);
    vec = {2, 3};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(60);
    vec = {3};
    vertices.push_back(Vertex(dot, vec));

    // Лево
    dot.setZCoordinate(801);
    vec = {4, 5};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(80);
    vec = {4};
    vertices.push_back(Vertex(dot, vec));

    dot.setZCoordinate(750);
    vec = {4, 5};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(60);
    vec = {5};
    vertices.push_back(Vertex(dot, vec));

    // Низ
    dot.setZCoordinate(801);
    dot.setYCoordinate(80);
    vec = {6, 7};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(80);
    vec = {6};
    vertices.push_back(Vertex(dot, vec));

    dot.setZCoordinate(750);
    vec = {6, 7};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(60);
    vec = {7};
    vertices.push_back(Vertex(dot, vec));

    // Право
    dot.setZCoordinate(801);
    dot.setXCoordinate(80);
    vec = {8, 9};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(60);
    vec = {8};
    vertices.push_back(Vertex(dot, vec));

    dot.setZCoordinate(750);
    vec = {8, 9};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(80);
    vec = {9};
    vertices.push_back(Vertex(dot, vec));

    // Столешница
    dot.setXCoordinate(20);
    dot.setYCoordinate(90);
    vec = {10, 11};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(90);
    vec = {10};
    vertices.push_back(Vertex(dot, vec));

    dot.setYCoordinate(20);
    vec = {10, 11};
    vertices.push_back(Vertex(dot, vec));

    dot.setXCoordinate(20);
    vec = {11};
    vertices.push_back(Vertex(dot, vec));

    vec = {0, 1, 2}; // 0
    facets.push_back(vec);

    vec = {1, 2, 3}; // 1
    facets.push_back(vec);

    vec = {4, 5, 6}; // 2
    facets.push_back(vec);

    vec = {4, 6, 7}; // 3
    facets.push_back(vec);

    vec = {8, 9, 10}; // 4
    facets.push_back(vec);

    vec = {8, 10, 11}; // 5
    facets.push_back(vec);

    vec = {12, 13, 14}; // 6
    facets.push_back(vec);

    vec = {12, 14, 15}; // 7
    facets.push_back(vec);

    vec = {16, 17, 18}; // 8
    facets.push_back(vec);

    vec = {16, 18, 19}; // 9
    facets.push_back(vec);

    vec = {20, 21, 22}; // 10
    facets.push_back(vec);

    vec = {20, 22, 23}; // 11
    facets.push_back(vec);

    PolModel tableModel(vertices, facets);
    qDebug() << "Прошли через создание стола";
    scene->addModel(tableModel);
}

void Drawer::zBufForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices, size_t color)
{
    std::array<Dot3D, 3> dotsArr;
    for (std::vector<Facet>::iterator iter = facets.begin(); iter != facets.end(); iter++)
    {
        dotsArr[0] = vertices.at(iter->getUsedDots().at(0)).getPosition();
        dotsArr[1] = vertices.at(iter->getUsedDots().at(1)).getPosition();
        dotsArr[2] = vertices.at(iter->getUsedDots().at(2)).getPosition();

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

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

            if (zA > depthBuffer[round(xA)][curY])
            {
                depthBuffer[round(xA)][curY] = zA;
                frameBuffer[round(xA)][curY] = 2;
            }
            int curCol = color;
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
            }
            double curZ = zA + (zB - zA) * (round(xB) - xA) / (xB - xA);
            if (curZ >= depthBuffer[round(xB)][curY])
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

            if (zA > depthBuffer[round(xA)][curY])
            {
                depthBuffer[round(xA)][curY] = zA;
                frameBuffer[round(xA)][curY] = 2;
            }
            int curCol = color;
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
            if (curZ >= depthBuffer[round(xB)][curY])
            {
                depthBuffer[round(xB)][curY] = curZ;
                frameBuffer[round(xB)][curY] = 2;
            }
        }
    }
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

    PolModel model = scene->getPlateModel();
    std::vector<Facet> facets = model.getFacets();
    std::vector<Vertex> vertices = model.getVertices();
    zBufForModel(facets, vertices, 1);

    qDebug() << "Моделей на сцене:" << scene->getModelsNum();
    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        qDebug() << "Нашли дополнитульную модель";
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        zBufForModel(facets, vertices, 3);
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
    zBufferAlg(scene, rect.size().height(), rect.size().width());
    milliseconds end =
    duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    qDebug() << "Time for zBuf" << (end - start).count();

    QGraphicsScene *outScene = new QGraphicsScene;
    outScene->setSceneRect(rect);

    QPen blackPen(Qt::black);
    //    QPen redPen(Qt::red);

    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    //    int w = rect.size().width();  /* Put here what ever width you want */
    //    int h = rect.size().height(); /* Put here what ever height you want */

    //    FILE *f;
    //    unsigned char *img = NULL;
    //    int filesize = 54 + 3 * w * h; // w is your image width, h is image height, both
    //    int if (img)
    //        free(img);
    //    img = (unsigned char *) malloc(3 * w * h);
    //    int x;
    //    int y;

    //    for (int i = 0; i < w; i++)
    //    {
    //        for (int j = 0; j < h; j++)
    //        {
    //            x = i;
    //            y = (h - 1) - j;
    //            if (frameBuffer.at(i).at(h - 1 - j) == 1 || frameBuffer.at(i).at(h - 1 -
    //            j) == 0)
    //            {
    //                img[(x + y * w) * 3 + 2] = (unsigned char) (255);
    //                img[(x + y * w) * 3 + 1] = (unsigned char) (255);
    //                img[(x + y * w) * 3 + 0] = (unsigned char) (255);
    //            }
    //            else
    //            {
    //                img[(x + y * w) * 3 + 2] = (unsigned char) (0);
    //                img[(x + y * w) * 3 + 1] = (unsigned char) (0);
    //                img[(x + y * w) * 3 + 0] = (unsigned char) (0);
    //            }
    //        }
    //    }

    //    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0,
    //    0}; unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    //    0, 24, 0}; unsigned char bmppad[3] = {0, 0, 0};

    //    bmpfileheader[2] = (unsigned char) (filesize);
    //    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    //    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    //    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    //    bmpinfoheader[4] = (unsigned char) (w);
    //    bmpinfoheader[5] = (unsigned char) (w >> 8);
    //    bmpinfoheader[6] = (unsigned char) (w >> 16);
    //    bmpinfoheader[7] = (unsigned char) (w >> 24);
    //    bmpinfoheader[8] = (unsigned char) (h);
    //    bmpinfoheader[9] = (unsigned char) (h >> 8);
    //    bmpinfoheader[10] = (unsigned char) (h >> 16);
    //    bmpinfoheader[11] = (unsigned char) (h >> 24);

    //    f = fopen("img.bmp", "wt");
    //    if (f)
    //        qDebug() << "ОНО ОТКРЫЛОСЬ";
    //    fwrite(bmpfileheader, 1, 14, f);
    //    fwrite(bmpinfoheader, 1, 40, f);
    //    for (int i = 0; i < h; i++)
    //    {
    //        fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
    //        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
    //    }

    //    fclose(f);
    //    outScene->addPixmap(QPixmap("img.bmp"));

    qDebug() << rect.size().height() << rect.size().width();

    QImage *image =
    new QImage(rect.size().width(), rect.size().height(), QImage::Format_RGB32);
    image->fill(Qt::white);
    uint whiteCol = qRgb(255, 150, 255);
    uint blackCol = qRgb(0, 0, 0);
    uint goldCol = qRgb(255, 215, 0);

    for (size_t i = 0; i < rect.size().height(); i++)
        for (size_t j = 0; j < rect.size().width(); j++)
            if (frameBuffer.at(i).at(j) == 1)
            {
                image->setPixel(i, j, whiteCol);
                //                int z = 0;
                //                for (; z < rect.size().width() && frameBuffer.at(i).at(j
                //                + z) == 1; z++) {} outScene->addLine(i, j, i, j + z - 1,
                //                redPen); j += z - 1;
            }
            else if (frameBuffer.at(i).at(j) == 2)
            {
                image->setPixel(i, j, blackCol);
                //                int z = 0;
                //                for (; z < rect.size().width() && frameBuffer.at(i).at(j
                //                + z) == 2; z++) {} outScene->addLine(i, j, i, j + z - 1,
                //                blackPen); j += z - 1;
            }
            else if (frameBuffer.at(i).at(j) == 3)
            {
                image->setPixel(i, j, goldCol);
            }
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    qDebug() << "Time for drawing" << (end - start).count();
    outScene->addPixmap(QPixmap::fromImage(*image));
    delete image;
    //    qDebug() <<
    //    QPixmap("C:/Users/dobri/Desktop/FirstCurseWork/Proj/imgs/smert.jpg");
    return outScene;
}
