#include "usagefacade.hpp"

#include "QDebug"
#include "QPen"

#include <limits>

#include "math.h"

#include "config.hpp"

UsageFacade::UsageFacade()
{
    scene = new CellScene;

    drawer = new Drawer;
}

void UsageFacade::setCellScene(size_t width_, size_t height_)
{
    if (scene)
        delete scene;
    scene = new CellScene(width_, height_);
    qDebug("Set was done\n");
}

void UsageFacade::changeCellScene(size_t newWidth, size_t newheight)
{
    scene->changeSize(newWidth, newheight);
}

bool UsageFacade::isSceneSet() { return scene->getHeight() && scene->getWidth(); }

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

QGraphicsScene *UsageFacade::rotateZScene(double angle, QRectF rect)
{
    scene->rotateZ(angle);
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

void UsageFacade::addQuad(std::vector<Vertex> &vertices, std::vector<Facet> &facets,
int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4,
int z4)
{
    Dot3D dot;
    std::vector<size_t> vec;

    size_t size = facets.size();

    dot = Dot3D(x1, y1, z1);
    vec = {size, size + 1};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x2, y2, z2);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x3, y3, z3);
    vec = {size, size + 1};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x4, y4, z4);
    vec = {size + 1};
    vertices.push_back(Vertex(dot, vec));

    size = vertices.size();
    vec = {size - 4, size - 3, size - 2};
    facets.push_back(vec);
    vec = {size - 4, size - 2, size - 1};
    facets.push_back(vec);
}

void UsageFacade::addTable()
{
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    addQuad(vertices, facets, 20, 20, 851, 20, 100, 851, 100, 100, 851, 100, 20, 851);

    addQuad(vertices, facets, 50, 50, 801, 70, 50, 801, 70, 50, 850, 50, 50, 850);

    addQuad(vertices, facets, 70, 50, 801, 70, 70, 801, 70, 70, 850, 70, 50, 850);

    addQuad(vertices, facets, 70, 70, 801, 50, 70, 801, 50, 70, 850, 70, 70, 850);

    addQuad(vertices, facets, 50, 70, 801, 50, 50, 801, 50, 50, 850, 50, 70, 850);

    PolModel tableModel(vertices, facets);
    qDebug() << "Прошли через создание стола";
    scene->addModel(tableModel);
}

void UsageFacade::addIlluminant()
{
    Eigen::Matrix4f transMat;
    // clang-format off
    transMat << cos(-ROTATE_UNIT), 0, sin(-ROTATE_UNIT), 0,
                0, 1, 0, 0,
                -sin(-ROTATE_UNIT), 0, cos(-ROTATE_UNIT), 0,
                0, 0, 0, 1;
    // clang-format on

    Eigen::Matrix4f prodMat;
    // clang-format off
    prodMat << 1,           0,          0, 0,
               0, cos(ROTATE_UNIT), -sin(ROTATE_UNIT), 0,
               0, sin(ROTATE_UNIT),  cos(ROTATE_UNIT), 0,
               0,           0,          0, 1;
    // clang-format on

    transMat *= prodMat;

    Illuminant illum(transMat);
    scene->addIlluminant(illum);
    qDebug() << "Добавили";
}

void Drawer::specBorderPut(int x, int y, double z)
{
    try
    {
        if (std::fabs(z - depthBuffer.at(x).at(y)) < 5 || z > depthBuffer.at(x).at(y))
            frameBuffer.at(x).at(y) = 5;
    }
    catch (std::exception &err)
    {
    }
}

void Drawer::DDABordersForPolygon(
int xStart, int yStart, double zStart, int xEnd, int yEnd, double zEnd)
{
    if (xStart == xEnd && yStart == yEnd)
    {
        specBorderPut(xStart, yStart, zStart);
        return;
    }

    double deltaX = xEnd - xStart;
    double deltaY = yEnd - yStart;
    double deltaZ = zEnd - zStart;

    int trX = abs(deltaX);
    int trY = abs(deltaY);

    int length;
    if (trX > trY)
        length = trX;
    else
        length = trY;

    deltaX /= length;
    deltaY /= length;
    deltaZ /= length;

    double curX = xStart;
    double curY = yStart;
    double curZ = zStart;

    for (int i = 0; i < length; i++)
    {
        specBorderPut(round(curX), round(curY), curZ);
        curX += deltaX;
        curY += deltaY;
        curZ += deltaZ;
    }
}

void Drawer::interpolateRowIntoShadowMap(std::vector<std::vector<double>> *map, int xA,
int xB, double zA, double zB, int curY, Eigen::Matrix4f &toCenter,
Eigen::Matrix4f &backToStart, Eigen::Matrix4f &illumMat)
{
    try
    {
        for (int curX = xA; curX <= xB; curX++)
        {
            double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
            Eigen::MatrixXf newCoordinates(1, 4);
            newCoordinates << curX, curY, curZ, 1;
            newCoordinates *= toCenter;
            newCoordinates *= illumMat;
            newCoordinates *= backToStart;
            int x = round(newCoordinates(0, 0));
            int y = round(newCoordinates(0, 1));
            if (x >= (int) depthBuffer.size() || x < 0 ||
                y >= (int) depthBuffer.at(0).size() || y < 0)
                continue;
            if (curZ > map->at(x).at(y))
                map->at(x).at(y) = newCoordinates(0, 2);
        }
    }
    catch (std::exception &err)
    {
        qDebug() << err.what();
    }
}

void Drawer::shadowMapForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices,
Eigen::Matrix4f &transMat, Illuminant *illum)
{
    std::array<Dot3D, 3> dotsArr;
    Eigen::Matrix4f toCenter;
    // clang-format off
    toCenter << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -X_CENTER, -Y_CENTER, -PLATE_Z, 1;
    // clang-format on
    Eigen::Matrix4f backToStart;
    // clang-format off
    backToStart << 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   X_CENTER, Y_CENTER, PLATE_Z, 1;
    // clang-format on
    std::vector<std::vector<double>> *shadowMap = &illum->getBuf();
    Eigen::Matrix4f illumMat = illum->getTransMat();
    for (std::vector<Facet>::iterator iter = facets.begin(); iter != facets.end(); iter++)
    {
        Eigen::MatrixXf coordinatesVec(3, 4);

        dotsArr[0] = vertices.at(iter->getUsedDots().at(0)).getPosition();
        dotsArr[1] = vertices.at(iter->getUsedDots().at(1)).getPosition();
        dotsArr[2] = vertices.at(iter->getUsedDots().at(2)).getPosition();

        coordinatesVec << dotsArr[0].getXCoordinate(), dotsArr[0].getYCoordinate(),
        dotsArr[0].getZCoordinate(), 1, dotsArr[1].getXCoordinate(),
        dotsArr[1].getYCoordinate(), dotsArr[1].getZCoordinate(), 1,
        dotsArr[2].getXCoordinate(), dotsArr[2].getYCoordinate(),
        dotsArr[2].getZCoordinate(), 1;
        coordinatesVec *= toCenter;
        coordinatesVec *= transMat;
        coordinatesVec *= backToStart;
        dotsArr[0] =
        Dot3D(coordinatesVec(0, 0), coordinatesVec(0, 1), coordinatesVec(0, 2));
        dotsArr[1] =
        Dot3D(coordinatesVec(1, 0), coordinatesVec(1, 1), coordinatesVec(1, 2));
        dotsArr[2] =
        Dot3D(coordinatesVec(2, 0), coordinatesVec(2, 1), coordinatesVec(2, 2));

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

        int x1 = round(dotsArr[0].getXCoordinate());
        int x2 = round(dotsArr[1].getXCoordinate());
        int x3 = round(dotsArr[2].getXCoordinate());

        double z1 = dotsArr[0].getZCoordinate();
        double z2 = dotsArr[1].getZCoordinate();
        double z3 = dotsArr[2].getZCoordinate();

        int y1 = round(dotsArr[0].getYCoordinate());
        int y2 = round(dotsArr[1].getYCoordinate());
        int y3 = round(dotsArr[2].getYCoordinate());

        for (int curY = y1; curY < y2; curY++)
        {
            double aInc = 0;
            if (y1 != y2)
                aInc = (double) (curY - y1) / (y2 - y1);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x1 + (x2 - x1) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            interpolateRowIntoShadowMap(
            shadowMap, xA, xB, zA, zB, curY, toCenter, backToStart, illumMat);
        }

        for (int curY = y2; curY <= y3; curY++)
        {
            double aInc = 0;
            if (y2 != y3)
                aInc = (double) (curY - y2) / (y3 - y2);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x2 + (x3 - x2) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            interpolateRowIntoShadowMap(
            shadowMap, xA, xB, zA, zB, curY, toCenter, backToStart, illumMat);
        }
    }
}

void Drawer::zBufForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices,
Eigen::Matrix4f &transMat, size_t color, CellScene *scene)
{
    std::array<Dot3D, 3> dotsArr;
    Eigen::Matrix4f toCenter;
    // clang-format off
    toCenter << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -X_CENTER, -Y_CENTER, -PLATE_Z, 1;
    // clang-format on
    Eigen::Matrix4f backToStart;
    // clang-format off
    backToStart << 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   X_CENTER, Y_CENTER, PLATE_Z, 1;
    // clang-format on
    for (std::vector<Facet>::iterator iter = facets.begin(); iter != facets.end(); iter++)
    {
        Eigen::MatrixXf coordinatesVec(3, 4);

        dotsArr[0] = vertices.at(iter->getUsedDots().at(0)).getPosition();
        dotsArr[1] = vertices.at(iter->getUsedDots().at(1)).getPosition();
        dotsArr[2] = vertices.at(iter->getUsedDots().at(2)).getPosition();

        coordinatesVec << dotsArr[0].getXCoordinate(), dotsArr[0].getYCoordinate(),
        dotsArr[0].getZCoordinate(), 1, dotsArr[1].getXCoordinate(),
        dotsArr[1].getYCoordinate(), dotsArr[1].getZCoordinate(), 1,
        dotsArr[2].getXCoordinate(), dotsArr[2].getYCoordinate(),
        dotsArr[2].getZCoordinate(), 1;
        coordinatesVec *= toCenter;
        coordinatesVec *= transMat;
        coordinatesVec *= backToStart;
        dotsArr[0] =
        Dot3D(coordinatesVec(0, 0), coordinatesVec(0, 1), coordinatesVec(0, 2));
        dotsArr[1] =
        Dot3D(coordinatesVec(1, 0), coordinatesVec(1, 1), coordinatesVec(1, 2));
        dotsArr[2] =
        Dot3D(coordinatesVec(2, 0), coordinatesVec(2, 1), coordinatesVec(2, 2));

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

        int x1 = round(dotsArr[0].getXCoordinate());
        int x2 = round(dotsArr[1].getXCoordinate());
        int x3 = round(dotsArr[2].getXCoordinate());

        double z1 = dotsArr[0].getZCoordinate();
        double z2 = dotsArr[1].getZCoordinate();
        double z3 = dotsArr[2].getZCoordinate();

        int y1 = round(dotsArr[0].getYCoordinate());
        int y2 = round(dotsArr[1].getYCoordinate());
        int y3 = round(dotsArr[2].getYCoordinate());

        for (int curY = round(dotsArr[0].getYCoordinate());
             curY < round(dotsArr[1].getYCoordinate()); curY++)
        {
            double aInc = 0;
            if (y1 != y2)
                aInc = (double) (curY - y1) / (y2 - y1);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x1 + (x2 - x1) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                if (curX >= (int) depthBuffer.size() || curX < 0 ||
                    curY >= (int) depthBuffer.at(0).size() || curY < 0)
                    continue;
                if (curZ > depthBuffer.at(curX).at(curY))
                {
                    short visible = 0;
                    Illuminant *illum;
                    Eigen::MatrixXf newCoordinates(1, 4);
                    for (size_t i = 0; i < scene->getIllumNum() && !visible; i++)
                    {
                        newCoordinates << curX, curY, curZ, 1;
                        illum = &scene->getIlluminant(i);

                        newCoordinates *= toCenter;
                        newCoordinates *= illum->getTransMat();
                        newCoordinates *= backToStart;
                        std::vector<std::vector<double>> *shadowMap = &illum->getBuf();
                        int x = round(newCoordinates(0, 0));
                        int y = round(newCoordinates(0, 1));
                        if (x < (int) shadowMap->size() && x > 0 &&
                            y < (int) shadowMap->at(0).size() && y > 0 &&
                            std::fabs(shadowMap->at(x).at(y) - newCoordinates(0, 2)) < 1)
                            visible = 1;
                    }
                    depthBuffer.at(curX).at(curY) = curZ;
                    if (scene->getIllumNum())
                    {
                        frameBuffer.at(curX).at(curY) = color + visible;
                    }
                    else
                        frameBuffer.at(curX).at(curY) = color + 1;
                }
            }
        }

        for (int curY = round(dotsArr[1].getYCoordinate());
             curY <= round(dotsArr[2].getYCoordinate()); curY++)
        {
            double aInc = 0;
            if (y2 != y3)
                aInc = (double) (curY - y2) / (y3 - y2);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x2 + (x3 - x2) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                if (curX >= (int) depthBuffer.size() || curX < 0 ||
                    curY >= (int) depthBuffer.at(0).size() || curY < 0)
                    continue;
                if (curZ > depthBuffer.at(curX).at(curY))
                {
                    short visible = 0;
                    Illuminant *illum;
                    Eigen::MatrixXf newCoordinates(1, 4);
                    for (size_t i = 0; i < scene->getIllumNum() && !visible; i++)
                    {
                        newCoordinates << curX, curY, curZ, 1;
                        illum = &scene->getIlluminant(i);

                        newCoordinates *= toCenter;
                        newCoordinates *= illum->getTransMat();
                        newCoordinates *= backToStart;
                        std::vector<std::vector<double>> *shadowMap = &illum->getBuf();
                        int x = round(newCoordinates(0, 0));
                        int y = round(newCoordinates(0, 1));
                        if (x < (int) shadowMap->size() && x > 0 &&
                            y < (int) shadowMap->at(0).size() && y > 0 &&
                            std::fabs(shadowMap->at(x).at(y) - newCoordinates(0, 2)) < 1)
                            visible = 1;
                    }
                    depthBuffer.at(curX).at(curY) = curZ;
                    if (scene->getIllumNum())
                    {
                        frameBuffer.at(curX).at(curY) = color + visible;
                    }
                    else
                        frameBuffer.at(curX).at(curY) = color + 1;
                }
            }
        }
        DDABordersForPolygon(x1, round(dotsArr[0].getYCoordinate()), z1, x2,
        round(dotsArr[1].getYCoordinate()), z2);
        DDABordersForPolygon(x1, round(dotsArr[0].getYCoordinate()), z1, x3,
        round(dotsArr[2].getYCoordinate()), z3);
        DDABordersForPolygon(x2, round(dotsArr[1].getYCoordinate()), z2, x3,
        round(dotsArr[2].getYCoordinate()), z3);
    }
}

void Drawer::zBufferAlg(CellScene *scene, size_t bufHeight, size_t bufWidth)
{
    depthBuffer.erase(depthBuffer.begin(), depthBuffer.end());
    frameBuffer.erase(frameBuffer.begin(), frameBuffer.end());

    for (size_t i = 0; i < bufWidth; i++)
    {
        depthBuffer.push_back(std::vector<double>(bufHeight, 0));
        frameBuffer.push_back(std::vector<size_t>(bufHeight, 0));
    }

    PolModel model;
    std::vector<Facet> facets;
    std::vector<Vertex> vertices;
    Illuminant *illuminant;
    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        for (size_t j = 0; j < scene->getIllumNum(); j++)
        {
            illuminant = &scene->getIlluminant(j);
            shadowMapForModel(facets, vertices, scene->getTransMatrix(), illuminant);
        }
    }

    model = scene->getPlateModel();
    facets = model.getFacets();
    vertices = model.getVertices();
    for (size_t j = 0; j < scene->getIllumNum(); j++)
    {
        illuminant = &scene->getIlluminant(j);
        shadowMapForModel(facets, vertices, scene->getTransMatrix(), illuminant);
    }

    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        zBufForModel(facets, vertices, scene->getTransMatrix(), 3, scene);
    }
    model = scene->getPlateModel();
    facets = model.getFacets();
    vertices = model.getVertices();
    zBufForModel(facets, vertices, scene->getTransMatrix(), 1, scene);

    for (size_t i = 0; i < scene->getIllumNum(); i++)
        scene->getIlluminant(i).clearShadowMap();
}

QGraphicsScene *Drawer::drawScene(CellScene *scene, QRectF rect)
{
    size_t width = scene->getWidth() * SCALE_FACTOR;
    size_t height = scene->getHeight() * SCALE_FACTOR;

    scene->buildPlateModel(Dot3D(PLATE_START), Dot3D(width, height, PLATE_Z));

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

    //    qDebug() << rect.size().height() << rect.size().width();

    QImage *image =
    new QImage(rect.size().width(), rect.size().height(), QImage::Format_RGB32);
    image->fill(Qt::white);
    uint plateCol = qRgb(255, 150, 255);
    uint darkPlateCol = qRgb(190, 130, 190);
    uint blackCol = qRgb(0, 0, 0);
    uint goldCol = qRgb(255, 215, 0);
    uint darkGoldCol = qRgb(235, 200, 0);

    for (size_t i = 0; i < rect.size().width() - 1; i++)
        for (size_t j = 0; j < rect.size().height() - 1; j++)
        {
            if (frameBuffer.at(i).at(j) == 1)
            {
                image->setPixel(i, j, darkPlateCol);
            }
            else if (frameBuffer.at(i).at(j) == 2)
            {
                image->setPixel(i, j, plateCol);
            }
            else if (frameBuffer.at(i).at(j) == 3)
            {
                image->setPixel(i, j, darkGoldCol);
            }
            else if (frameBuffer.at(i).at(j) == 4)
            {
                image->setPixel(i, j, goldCol);
            }
            else if (frameBuffer.at(i).at(j) == 5)
            {
                image->setPixel(i, j, blackCol);
            }
        }
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    qDebug() << "Time for drawing" << (end - start).count();
    outScene->addPixmap(QPixmap::fromImage(*image));
    delete image;
    for (size_t i = 0; i < scene->getIllumNum(); i++)
    { scene->getIlluminant(i).clearShadowMap(); }
    //    qDebug() <<
    //    QPixmap("C:/Users/dobri/Desktop/FirstCurseWork/Proj/imgs/smert.jpg");
    return outScene;
}
