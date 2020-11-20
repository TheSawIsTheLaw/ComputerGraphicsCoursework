#include "usagefacade.hpp"

#include "QDebug"
#include "QPen"

#include <limits>

#include "math.h"

#include "config.hpp"

UsageFacade::UsageFacade() { drawer = new Drawer; }

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

bool UsageFacade::isSceneSet() { return scene; }

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

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::moveDownScene(double value, QRectF rect)
{
    scene->moveDown(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::moveRightScene(double value, QRectF rect)
{
    scene->moveRight(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::moveLeftScene(double value, QRectF rect)
{
    scene->moveLeft(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::scaleScene(double value, QRectF rect)
{
    scene->scale(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::rotateXScene(double angle, QRectF rect)
{
    scene->rotateX(angle);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::rotateYScene(double angle, QRectF rect)
{
    scene->rotateY(angle);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::rotateZScene(double angle, QRectF rect)
{
    scene->rotateZ(angle);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::toCenter(QRectF rect)
{
    scene->toCenter();

    return drawScene(rect);
}

CellScene *UsageFacade::getScene() { return scene; }

void UsageFacade::addQuad(std::vector<Vertex> &vertices, std::vector<Facet> &facets,
    int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4,
    int y4, int z4)
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

void UsageFacade::addTriangle(std::vector<Vertex> &vertices, std::vector<Facet> &facets,
    int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3)
{
    Dot3D dot;
    std::vector<size_t> vec;

    size_t size = facets.size();

    dot = Dot3D(x1, y1, z1);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x2, y2, z2);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x3, y3, z3);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    size = vertices.size();
    vec = {size - 3, size - 2, size - 1};
    facets.push_back(vec);
}

int UsageFacade::addTable(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int magicZ = PLATE_Z + 70 * modelHeight + 1;
    int magicX = (direction == PlaceChooser::checkBox::XAXIS)
                     ? SCALE_FACTOR * (xCell + modelLength - 1)
                     : xFactor;
    int magicY = (direction == PlaceChooser::checkBox::YAXIS)
                     ? SCALE_FACTOR * (yCell + modelLength - 1)
                     : yFactor;
    // Столешница
    addQuad(vertices, facets, xFactor + 20, yFactor + 20, magicZ + 10, xFactor + 20,
        magicY + 100, magicZ + 10, magicX + 100, magicY + 100, magicZ + 10, magicX + 100,
        yFactor + 20, magicZ + 10);

    addQuad(vertices, facets, xFactor + 20, yFactor + 20, magicZ, xFactor + 20,
        magicY + 100, magicZ, xFactor + 20, magicY + 100, magicZ + 10, xFactor + 20,
        yFactor + 20, magicZ + 10);
    addQuad(vertices, facets, xFactor + 20, magicY + 100, magicZ, magicX + 100,
        magicY + 100, magicZ, magicX + 100, magicY + 100, magicZ + 10, xFactor + 20,
        magicY + 100, magicZ + 10);
    addQuad(vertices, facets, magicX + 100, magicY + 100, magicZ, magicX + 100,
        yFactor + 20, magicZ, magicX + 100, yFactor + 20, magicZ + 10, magicX + 100,
        magicY + 100, magicZ + 10);
    addQuad(vertices, facets, magicX + 100, magicY + 100, magicZ, xFactor + 20,
        magicY + 100, magicZ, xFactor + 20, magicY + 100, magicZ + 10, magicX + 100,
        magicY + 100, magicZ + 10);

    addQuad(vertices, facets, xFactor + 20, yFactor + 20, magicZ, xFactor + 20,
        magicY + 100, magicZ, magicX + 100, magicY + 100, magicZ, magicX + 100,
        yFactor + 20, magicZ);

    // Ножка
    addQuad(vertices, facets, xFactor + 50, yFactor + 50, PLATE_Z + 1, magicX + 70,
        yFactor + 50, PLATE_Z + 1, magicX + 70, yFactor + 50, magicZ - 1, xFactor + 50,
        yFactor + 50, magicZ - 1);

    addQuad(vertices, facets, magicX + 70, yFactor + 50, PLATE_Z + 1, magicX + 70,
        magicY + 70, PLATE_Z + 1, magicX + 70, magicY + 70, magicZ - 1, magicX + 70,
        yFactor + 50, magicZ - 1);

    addQuad(vertices, facets, magicX + 70, magicY + 70, PLATE_Z + 1, xFactor + 50,
        magicY + 70, PLATE_Z + 1, xFactor + 50, magicY + 70, magicZ - 1, magicX + 70,
        magicY + 70, magicZ - 1);

    addQuad(vertices, facets, xFactor + 50, magicY + 70, PLATE_Z + 1, xFactor + 50,
        yFactor + 50, PLATE_Z + 1, xFactor + 50, yFactor + 50, magicZ - 1, xFactor + 50,
        magicY + 70, magicZ - 1);

    PolModel tableModel(vertices, facets, "Table");
    tableModel.setUsedCell(xCell, yCell);
    scene->addModel(tableModel);

    return 0;
}

int UsageFacade::addBarTable(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int magicZ = PLATE_Z + 120 * modelHeight + 1;
    int magicX = (direction == PlaceChooser::checkBox::XAXIS)
                     ? SCALE_FACTOR * (xCell + modelLength - 1)
                     : xFactor;
    int magicY = (direction == PlaceChooser::checkBox::YAXIS)
                     ? SCALE_FACTOR * (yCell + modelLength - 1)
                     : yFactor;
    // Столешница
    addQuad(vertices, facets, xFactor + 20, yFactor + 20, magicZ + 10, xFactor + 20,
        magicY + 100, magicZ + 10, magicX + 100, magicY + 100, magicZ + 10, magicX + 100,
        yFactor + 20, magicZ + 10);

    addQuad(vertices, facets, xFactor + 20, yFactor + 20, magicZ, xFactor + 20,
        magicY + 100, magicZ, xFactor + 20, magicY + 100, magicZ + 10, xFactor + 20,
        yFactor + 20, magicZ + 10);
    addQuad(vertices, facets, xFactor + 20, magicY + 100, magicZ, magicX + 100,
        magicY + 100, magicZ, magicX + 100, magicY + 100, magicZ + 10, xFactor + 20,
        magicY + 100, magicZ + 10);
    addQuad(vertices, facets, magicX + 100, magicY + 100, magicZ, magicX + 100,
        yFactor + 20, magicZ, magicX + 100, yFactor + 20, magicZ + 10, magicX + 100,
        magicY + 100, magicZ + 10);
    addQuad(vertices, facets, magicX + 100, magicY + 100, magicZ, xFactor + 20,
        magicY + 100, magicZ, xFactor + 20, magicY + 100, magicZ + 10, magicX + 100,
        magicY + 100, magicZ + 10);

    addQuad(vertices, facets, xFactor + 20, yFactor + 20, magicZ, xFactor + 20,
        magicY + 100, magicZ, magicX + 100, magicY + 100, magicZ, magicX + 100,
        yFactor + 20, magicZ);

    // Левый верхний
    int curY = yFactor + 20;
    addQuad(vertices, facets, xFactor + 30, curY, PLATE_Z + 1, xFactor + 20, curY,
        PLATE_Z + 1, xFactor + 20, curY, magicZ - 1, xFactor + 30, curY, magicZ - 1);
    curY = yFactor + 30;
    addQuad(vertices, facets, xFactor + 30, curY, PLATE_Z + 1, xFactor + 20, curY,
        PLATE_Z + 1, xFactor + 20, curY, magicZ - 1, xFactor + 30, curY, magicZ - 1);

    int curX = xFactor + 20;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = xFactor + 30;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    // Правый верхний
    curY = yFactor + 20;
    addQuad(vertices, facets, magicX + 100, curY, PLATE_Z + 1, magicX + 90, curY,
        PLATE_Z + 1, magicX + 90, curY, magicZ - 1, magicX + 100, curY, magicZ - 1);
    curY = yFactor + 30;
    addQuad(vertices, facets, magicX + 100, curY, PLATE_Z + 1, magicX + 90, curY,
        PLATE_Z + 1, magicX + 90, curY, magicZ - 1, magicX + 100, curY, magicZ - 1);

    curX = magicX + 90;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = magicX + 100;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    // Левый нижний
    curY = magicY + 90;
    addQuad(vertices, facets, xFactor + 30, curY, PLATE_Z + 1, xFactor + 20, curY,
        PLATE_Z + 1, xFactor + 20, curY, magicZ - 1, xFactor + 30, curY, magicZ - 1);
    curY = magicY + 100;
    addQuad(vertices, facets, xFactor + 30, curY, PLATE_Z + 1, xFactor + 20, curY,
        PLATE_Z + 1, xFactor + 20, curY, magicZ - 1, xFactor + 30, curY, magicZ - 1);

    curX = xFactor + 20;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = xFactor + 30;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    // Правый нижний
    curY = magicY + 90;
    addQuad(vertices, facets, magicX + 100, curY, PLATE_Z + 1, magicX + 90, curY,
        PLATE_Z + 1, magicX + 90, curY, magicZ - 1, magicX + 100, curY, magicZ - 1);
    curY = magicY + 100;
    addQuad(vertices, facets, magicX + 100, curY, PLATE_Z + 1, magicX + 90, curY,
        PLATE_Z + 1, magicX + 90, curY, magicZ - 1, magicX + 100, curY, magicZ - 1);

    curX = magicX + 90;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = magicX + 100;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    PolModel barTableModel(vertices, facets, "Bar table");
    barTableModel.setUsedCell(xCell, yCell);
    scene->addModel(barTableModel);

    return 0;
}

int UsageFacade::addChair(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int magicZ = PLATE_Z + 40 * modelHeight + 1;
    int magicX = SCALE_FACTOR * (xCell + modelLength - 1);
    int magicY = yFactor;

    int xFactorStart = xFactor + 30;
    int yFactorStart = yFactor + 30;
    int xMagicEnd = magicX + 90;
    int yMagicEnd = magicY + 90;
    // Седушка
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 10, xFactorStart,
        yMagicEnd, magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 10, xMagicEnd,
        yFactorStart, magicZ + 10);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xFactorStart, yMagicEnd, magicZ + 10, xFactorStart, yFactorStart,
        magicZ + 10);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, magicZ, xMagicEnd, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ + 10, xFactorStart, yMagicEnd, magicZ + 10);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart,
        magicZ, xMagicEnd, yFactorStart, magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 10);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, magicZ, xFactorStart, yFactorStart,
        magicZ, xFactorStart, yFactorStart, magicZ + 10, xMagicEnd, yFactorStart,
        magicZ + 10);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    yMagicEnd = magicY + 40;
    // Спинка
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 70, xFactorStart,
        yMagicEnd, magicZ + 70, xMagicEnd, yMagicEnd, magicZ + 70, xMagicEnd,
        yFactorStart, magicZ + 70);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 10, xFactorStart,
        yMagicEnd, magicZ + 10, xFactorStart, yMagicEnd, magicZ + 70, xFactorStart,
        yFactorStart, magicZ + 70);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, magicZ + 10, xMagicEnd, yMagicEnd,
        magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 70, xFactorStart, yMagicEnd,
        magicZ + 70);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, magicZ + 10, xMagicEnd, yFactorStart,
        magicZ + 10, xMagicEnd, yFactorStart, magicZ + 70, xMagicEnd, yMagicEnd,
        magicZ + 70);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, magicZ + 10, xFactorStart,
        yFactorStart, magicZ + 10, xFactorStart, yFactorStart, magicZ + 70, xMagicEnd,
        yFactorStart, magicZ + 70);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 10, xFactorStart,
        yMagicEnd, magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 10, xMagicEnd,
        yFactorStart, magicZ + 10);

    // Левый верхний
    int curY = yFactor + 30;
    addQuad(vertices, facets, xFactor + 40, curY, PLATE_Z + 1, xFactor + 30, curY,
        PLATE_Z + 1, xFactor + 30, curY, magicZ - 1, xFactor + 40, curY, magicZ - 1);
    curY = yFactor + 40;
    addQuad(vertices, facets, xFactor + 40, curY, PLATE_Z + 1, xFactor + 30, curY,
        PLATE_Z + 1, xFactor + 30, curY, magicZ - 1, xFactor + 40, curY, magicZ - 1);

    int curX = xFactor + 30;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = xFactor + 40;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    // Правый верхний
    curY = yFactor + 30;
    addQuad(vertices, facets, magicX + 90, curY, PLATE_Z + 1, magicX + 80, curY,
        PLATE_Z + 1, magicX + 80, curY, magicZ - 1, magicX + 90, curY, magicZ - 1);
    curY = yFactor + 40;
    addQuad(vertices, facets, magicX + 90, curY, PLATE_Z + 1, magicX + 80, curY,
        PLATE_Z + 1, magicX + 80, curY, magicZ - 1, magicX + 90, curY, magicZ - 1);

    curX = magicX + 80;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = magicX + 90;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    // Левый нижний
    curY = magicY + 80;
    addQuad(vertices, facets, xFactor + 40, curY, PLATE_Z + 1, xFactor + 30, curY,
        PLATE_Z + 1, xFactor + 30, curY, magicZ - 1, xFactor + 40, curY, magicZ - 1);
    curY = magicY + 90;
    addQuad(vertices, facets, xFactor + 40, curY, PLATE_Z + 1, xFactor + 30, curY,
        PLATE_Z + 1, xFactor + 30, curY, magicZ - 1, xFactor + 40, curY, magicZ - 1);

    curX = xFactor + 30;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = xFactor + 40;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    // Правый нижний
    curY = magicY + 80;
    addQuad(vertices, facets, magicX + 90, curY, PLATE_Z + 1, magicX + 80, curY,
        PLATE_Z + 1, magicX + 80, curY, magicZ - 1, magicX + 90, curY, magicZ - 1);
    curY = magicY + 90;
    addQuad(vertices, facets, magicX + 90, curY, PLATE_Z + 1, magicX + 80, curY,
        PLATE_Z + 1, magicX + 80, curY, magicZ - 1, magicX + 90, curY, magicZ - 1);

    curX = magicX + 80;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);
    curX = magicX + 90;
    addQuad(vertices, facets, curX, curY, PLATE_Z + 1, curX, curY - 10, PLATE_Z + 1, curX,
        curY - 10, magicZ - 1, curX, curY, magicZ - 1);

    PolModel chairModel(vertices, facets, "Chair");
    chairModel.setUsedCell(xCell, yCell);
    if (direction == PlaceChooser::checkBox::YAXIS)
        chairModel.rotateZ(-90);
    scene->addModel(chairModel);

    return 0;
}

int UsageFacade::addBarChair(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int magicZ = PLATE_Z + 40 * modelHeight + 1;
    int magicX = SCALE_FACTOR * (xCell + modelLength - 1);
    int magicY = yFactor;

    int xFactorStart = xFactor + 30;
    int yFactorStart = yFactor + 30;
    int xMagicEnd = magicX + 90;
    int yMagicEnd = magicY + 90;
    // Седушка
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 10, xFactorStart,
        yMagicEnd, magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 10, xMagicEnd,
        yFactorStart, magicZ + 10);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xFactorStart, yMagicEnd, magicZ + 10, xFactorStart, yFactorStart,
        magicZ + 10);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, magicZ, xMagicEnd, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ + 10, xFactorStart, yMagicEnd, magicZ + 10);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart,
        magicZ, xMagicEnd, yFactorStart, magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 10);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, magicZ, xFactorStart, yFactorStart,
        magicZ, xFactorStart, yFactorStart, magicZ + 10, xMagicEnd, yFactorStart,
        magicZ + 10);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    xFactorStart += 10;
    yFactorStart += 10;
    xMagicEnd -= 10;
    yMagicEnd -= 10;
    // Нижняя площадка
    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 5, xFactorStart,
        yMagicEnd, PLATE_Z + 5, xMagicEnd, yMagicEnd, PLATE_Z + 5, xMagicEnd,
        yFactorStart, PLATE_Z + 5);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xFactorStart, yMagicEnd, PLATE_Z + 5, xFactorStart,
        yFactorStart, PLATE_Z + 5);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd,
        PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 5, xFactorStart, yMagicEnd,
        PLATE_Z + 5);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd, yFactorStart,
        PLATE_Z + 1, xMagicEnd, yFactorStart, PLATE_Z + 5, xMagicEnd, yMagicEnd,
        PLATE_Z + 5);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1, xFactorStart,
        yFactorStart, PLATE_Z + 1, xFactorStart, yFactorStart, PLATE_Z + 5, xMagicEnd,
        yFactorStart, PLATE_Z + 5);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd,
        yFactorStart, PLATE_Z + 1);

    xFactorStart -= 10;
    yFactorStart -= 10;
    xMagicEnd += 10;

    yMagicEnd = magicY + 40;

    // Спинка
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 50, xFactorStart,
        yMagicEnd, magicZ + 50, xMagicEnd, yMagicEnd, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 10, xFactorStart,
        yMagicEnd, magicZ + 10, xFactorStart, yMagicEnd, magicZ + 50, xFactorStart,
        yFactorStart, magicZ + 50);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, magicZ + 10, xMagicEnd, yMagicEnd,
        magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 50, xFactorStart, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, magicZ + 10, xMagicEnd, yFactorStart,
        magicZ + 10, xMagicEnd, yFactorStart, magicZ + 50, xMagicEnd, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, magicZ + 10, xFactorStart,
        yFactorStart, magicZ + 10, xFactorStart, yFactorStart, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 10, xFactorStart,
        yMagicEnd, magicZ + 10, xMagicEnd, yMagicEnd, magicZ + 10, xMagicEnd,
        yFactorStart, magicZ + 10);

    // Ножка
    addQuad(vertices, facets, xFactor + 55, yFactor + 55, PLATE_Z + 6, magicX + 65,
        yFactor + 55, PLATE_Z + 6, magicX + 65, yFactor + 55, magicZ - 1, xFactor + 55,
        yFactor + 55, magicZ - 1);

    addQuad(vertices, facets, magicX + 65, yFactor + 55, PLATE_Z + 6, magicX + 65,
        magicY + 65, PLATE_Z + 6, magicX + 65, magicY + 65, magicZ - 1, magicX + 65,
        yFactor + 55, magicZ - 1);

    addQuad(vertices, facets, magicX + 65, magicY + 65, PLATE_Z + 6, xFactor + 55,
        magicY + 65, PLATE_Z + 6, xFactor + 55, magicY + 65, magicZ - 1, magicX + 65,
        magicY + 65, magicZ - 1);

    addQuad(vertices, facets, xFactor + 55, magicY + 65, PLATE_Z + 6, xFactor + 55,
        yFactor + 55, PLATE_Z + 6, xFactor + 55, yFactor + 55, magicZ - 1, xFactor + 55,
        magicY + 65, magicZ - 1);

    PolModel chairModel(vertices, facets, "Bar chair");
    chairModel.setUsedCell(xCell, yCell);

    if (direction == PlaceChooser::checkBox::YAXIS)
        chairModel.rotateZ(-90);

    scene->addModel(chairModel);

    return 0;
}

int UsageFacade::addSofa(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int magicZ = PLATE_Z + 40 * modelHeight + 1;
    int magicX = SCALE_FACTOR * (xCell + modelLength - 1);
    int magicY = yFactor;

    int xFactorStart = xFactor + 30;
    int yFactorStart = yFactor + 30;
    int xMagicEnd = magicX + 90;
    int yMagicEnd = magicY + 90;

    // Седушка
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xFactorStart, yMagicEnd, magicZ, xFactorStart,
        yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd,
        PLATE_Z + 1, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd, yFactorStart,
        PLATE_Z + 1, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1, xFactorStart,
        yFactorStart, PLATE_Z + 1, xFactorStart, yFactorStart, magicZ, xMagicEnd,
        yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd,
        yFactorStart, PLATE_Z + 1);

    yMagicEnd = magicY + 40;

    // Спинка
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 50, xFactorStart,
        yMagicEnd, magicZ + 50, xMagicEnd, yMagicEnd, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 1, xFactorStart,
        yMagicEnd, magicZ + 1, xFactorStart, yMagicEnd, magicZ + 50, xFactorStart,
        yFactorStart, magicZ + 50);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, magicZ + 1, xMagicEnd, yMagicEnd,
        magicZ + 1, xMagicEnd, yMagicEnd, magicZ + 50, xFactorStart, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, magicZ + 1, xMagicEnd, yFactorStart,
        magicZ + 1, xMagicEnd, yFactorStart, magicZ + 50, xMagicEnd, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, magicZ + 1, xFactorStart,
        yFactorStart, magicZ + 1, xFactorStart, yFactorStart, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 1, xFactorStart,
        yMagicEnd, magicZ + 1, xMagicEnd, yMagicEnd, magicZ + 1, xMagicEnd, yFactorStart,
        magicZ + 1);

    xFactorStart = xFactor + 20;
    yFactorStart = yFactor + 30;
    xMagicEnd = xFactor + 30;
    yMagicEnd = magicY + 90;
    // Левый подлокотник
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 50, xFactorStart,
        yMagicEnd, magicZ + 50, xMagicEnd, yMagicEnd, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xFactorStart, yMagicEnd, magicZ + 50, xFactorStart,
        yFactorStart, magicZ + 50);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd,
        PLATE_Z + 1, xMagicEnd, yMagicEnd, magicZ + 50, xFactorStart, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd, yFactorStart,
        PLATE_Z + 1, xMagicEnd, yFactorStart, magicZ + 50, xMagicEnd, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1, xFactorStart,
        yFactorStart, PLATE_Z + 1, xFactorStart, yFactorStart, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd,
        yFactorStart, PLATE_Z + 1);

    xFactorStart = magicX + 90;
    yFactorStart = yFactor + 30;
    xMagicEnd = magicX + 100;
    yMagicEnd = magicY + 90;
    // Правый подлокотник
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ + 50, xFactorStart,
        yMagicEnd, magicZ + 50, xMagicEnd, yMagicEnd, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xFactorStart, yMagicEnd, magicZ + 50, xFactorStart,
        yFactorStart, magicZ + 50);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd,
        PLATE_Z + 1, xMagicEnd, yMagicEnd, magicZ + 50, xFactorStart, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd, yFactorStart,
        PLATE_Z + 1, xMagicEnd, yFactorStart, magicZ + 50, xMagicEnd, yMagicEnd,
        magicZ + 50);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1, xFactorStart,
        yFactorStart, PLATE_Z + 1, xFactorStart, yFactorStart, magicZ + 50, xMagicEnd,
        yFactorStart, magicZ + 50);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd,
        yFactorStart, PLATE_Z + 1);

    PolModel sofaModel(vertices, facets, "Sofa");
    sofaModel.setUsedCell(xCell, yCell);

    if (direction == PlaceChooser::checkBox::YAXIS)
        sofaModel.rotateZ(-90);

    scene->addModel(sofaModel);

    return 0;
}

int UsageFacade::addPlant(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int xFactorStart = xFactor + 50;
    int yFactorStart = yFactor + 50;
    int xMagicEnd = xFactor + 70;
    int yMagicEnd = yFactor + 70;

    // Горшок
    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 20, xFactorStart,
        yMagicEnd, PLATE_Z + 20, xMagicEnd, yMagicEnd, PLATE_Z + 20, xMagicEnd,
        yFactorStart, PLATE_Z + 20);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xFactorStart, yMagicEnd, PLATE_Z + 20, xFactorStart,
        yFactorStart, PLATE_Z + 20);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd,
        PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 20, xFactorStart, yMagicEnd,
        PLATE_Z + 20);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd, yFactorStart,
        PLATE_Z + 1, xMagicEnd, yFactorStart, PLATE_Z + 20, xMagicEnd, yMagicEnd,
        PLATE_Z + 20);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1, xFactorStart,
        yFactorStart, PLATE_Z + 1, xFactorStart, yFactorStart, PLATE_Z + 20, xMagicEnd,
        yFactorStart, PLATE_Z + 20);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd,
        yFactorStart, PLATE_Z + 1);

    // Крона
    xFactorStart -= 10;
    yFactorStart -= 10;
    xMagicEnd += 10;
    yMagicEnd += 10;
    int magicZ = PLATE_Z + 51 + 50 * modelHeight;

    int xCenter = xFactorStart + (xMagicEnd - xFactorStart) / 2;
    int yCenter = yFactorStart + (yMagicEnd - yFactorStart) / 2;
    addTriangle(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 30,
                xFactorStart, yMagicEnd, PLATE_Z + 30, xCenter, yCenter, magicZ);
    addTriangle(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 30,
                xMagicEnd, yMagicEnd, PLATE_Z + 30, xCenter, yCenter, magicZ);
    addTriangle(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 30,
                xMagicEnd, yFactorStart, PLATE_Z + 30, xCenter, yCenter, magicZ);
    addTriangle(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 30,
                xFactorStart, yFactorStart, PLATE_Z + 30, xCenter, yCenter, magicZ);

    // Стебель
    magicZ = PLATE_Z + 30;
    xFactorStart = xFactor + 57;
    yFactorStart = yFactor + 57;
    xMagicEnd = xFactor + 63;
    yMagicEnd = yFactor + 63;

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 21, xFactorStart,
        yMagicEnd, PLATE_Z + 21, xFactorStart, yMagicEnd, magicZ, xFactorStart,
        yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 21, xMagicEnd, yMagicEnd,
        PLATE_Z + 21, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 21, xMagicEnd, yFactorStart,
        PLATE_Z + 21, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 21, xFactorStart,
        yFactorStart, PLATE_Z + 21, xFactorStart, yFactorStart, magicZ, xMagicEnd,
        yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 21, xFactorStart,
        yMagicEnd, PLATE_Z + 21, xMagicEnd, yMagicEnd, PLATE_Z + 21, xMagicEnd,
        yFactorStart, PLATE_Z + 21);

    PolModel plantModel(vertices, facets, "Plant");
    plantModel.setUsedCell(xCell, yCell);

    if (direction == PlaceChooser::checkBox::YAXIS)
        plantModel.rotateZ(-90);

    scene->addModel(plantModel);

    return 0;
}

int UsageFacade::addPodium(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;

    int magicZ = PLATE_Z + 40 * modelHeight + 1;
    int magicX = (direction == PlaceChooser::checkBox::XAXIS)
                     ? SCALE_FACTOR * (xCell + modelLength - 1)
                     : xFactor;
    int magicY = (direction == PlaceChooser::checkBox::YAXIS)
                     ? SCALE_FACTOR * (yCell + modelLength - 1)
                     : yFactor;

    int xFactorStart = xFactor + 30;
    int yFactorStart = yFactor + 30;
    int xMagicEnd = magicX + 90;
    int yMagicEnd = magicY + 90;

    // Подиум
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
        magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xFactorStart, yMagicEnd, magicZ, xFactorStart,
        yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd,
        PLATE_Z + 1, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd, yFactorStart,
        PLATE_Z + 1, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1, xFactorStart,
        yFactorStart, PLATE_Z + 1, xFactorStart, yFactorStart, magicZ, xMagicEnd,
        yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1, xFactorStart,
        yMagicEnd, PLATE_Z + 1, xMagicEnd, yMagicEnd, PLATE_Z + 1, xMagicEnd,
        yFactorStart, PLATE_Z + 1);

    PolModel podiumModel(vertices, facets, "Podium");
    podiumModel.setUsedCell(xCell, yCell);
    scene->addModel(podiumModel);

    return 0;
}

int UsageFacade::addScreen(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;
    Dot3D start(PLATE_START);

    int xFactorStart = xFactor + start.getXCoordinate() + (SCALE_FACTOR * modelLength) / 2 - 10;
    int yFactorStart = yFactor + 50;
    int xMagicEnd = xFactor + start.getXCoordinate() + (SCALE_FACTOR * modelLength) / 2 + 10;
    int yMagicEnd = yFactor + 70;

    // Основание
    int magicZ = PLATE_Z + 5;

    int xCenter = xFactorStart + (xMagicEnd - xFactorStart) / 2;
    int yCenter = yFactorStart + (yMagicEnd - yFactorStart) / 2;
    addTriangle(vertices, facets, xFactorStart, yFactorStart, PLATE_Z + 1,
                xFactorStart, yMagicEnd, PLATE_Z + 1, xCenter, yCenter, magicZ);
    addTriangle(vertices, facets, xFactorStart, yMagicEnd, PLATE_Z + 1,
                xMagicEnd, yMagicEnd, PLATE_Z + 1, xCenter, yCenter, magicZ);
    addTriangle(vertices, facets, xMagicEnd, yMagicEnd, PLATE_Z + 1,
                xMagicEnd, yFactorStart, PLATE_Z + 1, xCenter, yCenter, magicZ);
    addTriangle(vertices, facets, xMagicEnd, yFactorStart, PLATE_Z + 1,
                xFactorStart, yFactorStart, PLATE_Z + 1, xCenter, yCenter, magicZ);

    // Стойка
    magicZ = PLATE_Z + 3;
    int zEnd = magicZ + 100 * modelHeight;
    xFactorStart = xFactor + start.getXCoordinate() + (SCALE_FACTOR * modelLength) / 2 - 3;
    yFactorStart = yFactor + 57;
    xMagicEnd = xFactor + start.getXCoordinate() + (SCALE_FACTOR * modelLength) / 2 + 3;
    yMagicEnd = yFactor + 63;

    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);

    // Экран
    magicZ = zEnd + 1;
    zEnd += 100;
    xFactorStart = xFactor + 10;
    yFactorStart = yFactor + 57;
    xMagicEnd = SCALE_FACTOR * (xCell + modelLength - 1) + 110;
    yMagicEnd = yFactor + 63;
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);


    PolModel screenModel(vertices, facets, "Screen");
    screenModel.setUsedCell(xCell, yCell);

    if (direction == PlaceChooser::checkBox::YAXIS)
        screenModel.rotateZ(-90);

    scene->addModel(screenModel);

    return 0;
}

int UsageFacade::addTV(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    Dot3D dot;
    std::vector<size_t> vec;

    int xFactor = xCell * SCALE_FACTOR;
    int yFactor = yCell * SCALE_FACTOR;
    Dot3D start(PLATE_START);

    // Экран
    int magicZ = PLATE_Z + 100 * modelHeight + 1;
    int zEnd = magicZ + 50;
    int xFactorStart = xFactor + 10;
    int yFactorStart = start.getYCoordinate() + yFactor + 7;
    int xMagicEnd = SCALE_FACTOR * (xCell + modelLength - 1) + 110;
    int yMagicEnd = yFactorStart - 5;
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);

    // Задняя крышка
    magicZ += 10;
    zEnd = magicZ + 30;
    xFactorStart += 10;
    xMagicEnd -= 10;
    yFactorStart -= 10;
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);


    magicZ -= 10;
    xFactorStart -= 10;
    xMagicEnd += 10;
    yFactorStart += 10;

    yFactorStart += 2;
    yMagicEnd += 6;
    zEnd = magicZ + 5;
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);
    zEnd = magicZ + 5;
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);

    magicZ += 45;
    zEnd = magicZ + 5;
    addQuad(vertices, facets, xFactorStart, yFactorStart, magicZ, xFactorStart, yMagicEnd,
            magicZ, xMagicEnd, yMagicEnd, magicZ, xMagicEnd, yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xFactorStart, yMagicEnd, magicZ, xFactorStart,
            yFactorStart, magicZ);
    addQuad(vertices, facets, xFactorStart, yMagicEnd, zEnd, xMagicEnd, yMagicEnd,
            zEnd, xMagicEnd, yMagicEnd, magicZ, xFactorStart, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yMagicEnd, zEnd, xMagicEnd, yFactorStart,
            zEnd, xMagicEnd, yFactorStart, magicZ, xMagicEnd, yMagicEnd, magicZ);
    addQuad(vertices, facets, xMagicEnd, yFactorStart, zEnd, xFactorStart,
            yFactorStart, zEnd, xFactorStart, yFactorStart, magicZ, xMagicEnd,
            yFactorStart, magicZ);

    addQuad(vertices, facets, xFactorStart, yFactorStart, zEnd, xFactorStart,
            yMagicEnd, zEnd, xMagicEnd, yMagicEnd, zEnd, xMagicEnd,
            yFactorStart, zEnd);


    PolModel TVModel(vertices, facets, "TV");
    TVModel.setUsedCell(xCell, yCell);

    if (direction == PlaceChooser::checkBox::YAXIS)
        TVModel.rotateZ(-90);

    scene->addModel(TVModel);

    return 0;
}

int UsageFacade::addCupboard(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
}

int UsageFacade::addRack(int xCell, int yCell, double modelLength, double modelHeight,
    PlaceChooser::checkBox direction)
{
}

void UsageFacade::addIlluminant(int xAngle, int yAngle)
{
    Eigen::Matrix4f transMat;
    double radianXAngle = (double) xAngle * M_PI / 180.0;
    double radianYAngle = (double) yAngle * M_PI / 180.0;

    // clang-format off
    transMat << 1,           0,          0, 0,
               0, cos(radianXAngle), -sin(radianXAngle), 0,
               0, sin(radianXAngle),  cos(radianXAngle), 0,
               0,           0,          0, 1;
    // clang-format on

    Eigen::Matrix4f prodMat;
    // clang-format off
    prodMat << cos(radianYAngle), 0, sin(radianYAngle), 0,
                0, 1, 0, 0,
                -sin(radianYAngle), 0, cos(radianYAngle), 0,
                0, 0, 0, 1;
    // clang-format on

    transMat *= prodMat;

    Illuminant illum(transMat);
    illum.setAngles(xAngle, yAngle);
    scene->addIlluminant(illum);
}

void Drawer::specBorderPut(int x, int y, double z)
{
    if (x < 0 || x >= (int) depthBuffer.size() || y < 0 ||
        y >= (int) depthBuffer.at(0).size())
        return;
    if (std::fabs(z - depthBuffer.at(x).at(y)) < 1 || z > depthBuffer.at(x).at(y))
        frameBuffer.at(x).at(y) = 5;
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

void Drawer::interpolateRowIntoShadowMap(
    std::vector<std::vector<double>> *map, int xA, int xB, double zA, double zB, int curY)
{
    for (int curX = xA; curX <= xB; curX++)
    {
        double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
        if (curX >= (int) map->size() || curX < 0 || curY >= (int) map->at(0).size() ||
            curY < 0)
            continue;

        if (curZ > map->at(curX).at(curY))
            map->at(curX).at(curY) = curZ;
    }
}

void Drawer::shadowMapForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices,
    Eigen::Matrix4f &transMat, Illuminant *illum, size_t bufWidth, size_t bufHeight)
{
    std::array<Dot3D, 3> dotsArr;
    Eigen::Matrix4f toCenter;
    // clang-format off
    toCenter << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -X_CENTER, -Y_CENTER, -PLATE_Z - 5, 1;
    // clang-format on
    Eigen::Matrix4f backToStart;
    // clang-format off
    backToStart << 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   X_CENTER, Y_CENTER, PLATE_Z + 5, 1;
    // clang-format on
    std::vector<std::vector<double>> *shadowMap = &illum->getShadowMap();
    Eigen::Matrix4f illumMat = illum->getTransMat();

    Eigen::Matrix4f dotTransMat = toCenter * transMat * illumMat * backToStart;

    for (size_t curFaceNum = 0; curFaceNum < facets.size(); curFaceNum++)
    {
        Eigen::MatrixXf coordinatesVec(3, 4);

        std::vector<size_t> curDots = facets.at(curFaceNum).getUsedDots();
        dotsArr[0] = vertices.at(curDots.at(0)).getPosition();
        dotsArr[1] = vertices.at(curDots.at(1)).getPosition();
        dotsArr[2] = vertices.at(curDots.at(2)).getPosition();

        coordinatesVec << dotsArr[0].getXCoordinate(), dotsArr[0].getYCoordinate(),
            dotsArr[0].getZCoordinate(), 1, dotsArr[1].getXCoordinate(),
            dotsArr[1].getYCoordinate(), dotsArr[1].getZCoordinate(), 1,
            dotsArr[2].getXCoordinate(), dotsArr[2].getYCoordinate(),
            dotsArr[2].getZCoordinate(), 1;

        coordinatesVec *= dotTransMat;
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
#pragma omp parallel for
        for (int curY = (y1 < 0) ? 0 : y1;
             curY < ((y2 >= (int) bufHeight) ? (int) bufHeight - 1 : y2); curY++)
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

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            interpolateRowIntoShadowMap(shadowMap, xA, xB, zA, zB, curY);
        }
#pragma omp parallel for
        for (int curY = (y2 < 0) ? 0 : y2;
             curY <= ((y3 >= (int) bufHeight) ? (int) bufHeight - 1 : y3); curY++)
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

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            interpolateRowIntoShadowMap(shadowMap, xA, xB, zA, zB, curY);
        }
    }
}

void Drawer::zBufForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices,
    Eigen::Matrix4f &transMat, size_t color, CellScene *scene, size_t bufWidth,
    size_t bufHeight)
{
    std::array<Dot3D, 3> dotsArr;
    Eigen::Matrix4f toCenter;
    // clang-format off
    toCenter << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -X_CENTER, -Y_CENTER, -PLATE_Z - 5, 1;
    // clang-format on
    Eigen::Matrix4f backToStart;
    // clang-format off
    backToStart << 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   X_CENTER, Y_CENTER, PLATE_Z + 5, 1;
    // clang-format on

    Eigen::Matrix4f dotTransMat;
    dotTransMat = toCenter * transMat * backToStart;
    std::vector<Eigen::Matrix4f> illumDotMatrices;
    for (size_t i = 0; i < scene->getIllumNum(); i++)
        illumDotMatrices.push_back(
            toCenter * scene->getIlluminant(i).getTransMat() * backToStart);
    for (size_t curFaceNum = 0; curFaceNum < facets.size(); curFaceNum++)
    {
        Eigen::MatrixXf coordinatesVec(3, 4);

        std::vector<size_t> curDots = facets.at(curFaceNum).getUsedDots();
        dotsArr[0] = vertices.at(curDots.at(0)).getPosition();
        dotsArr[1] = vertices.at(curDots.at(1)).getPosition();
        dotsArr[2] = vertices.at(curDots.at(2)).getPosition();

        coordinatesVec << dotsArr[0].getXCoordinate(), dotsArr[0].getYCoordinate(),
            dotsArr[0].getZCoordinate(), 1, dotsArr[1].getXCoordinate(),
            dotsArr[1].getYCoordinate(), dotsArr[1].getZCoordinate(), 1,
            dotsArr[2].getXCoordinate(), dotsArr[2].getYCoordinate(),
            dotsArr[2].getZCoordinate(), 1;
        coordinatesVec *= dotTransMat;
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
#pragma omp parallel for
        for (int curY = (y1 < 0) ? 0 : y1;
             curY < ((y2 >= (int) bufHeight) ? (int) bufHeight - 1 : y2); curY++)
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

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                //                if (curX >= (int) depthBuffer.size() || curX < 0 ||
                //                    curY >= (int) depthBuffer.at(0).size() || curY < 0)
                //                    continue;
                if (curZ >= depthBuffer.at(curX).at(curY))
                {
                    short visible = 0;
                    Eigen::MatrixXf newCoordinates(1, 4);
                    for (size_t i = 0; i < scene->getIllumNum() && !visible; i++)
                    {
                        newCoordinates << curX, curY, curZ, 1;

                        newCoordinates *= illumDotMatrices.at(i);
                        std::vector<std::vector<double>> *shadowMap =
                            &scene->getIlluminant(i).getShadowMap();
                        int x = round(newCoordinates(0, 0));
                        int y = round(newCoordinates(0, 1));
                        if (x < (int) shadowMap->size() && x >= 0 &&
                            y < (int) shadowMap->at(0).size() && y >= 0 &&
                            std::fabs(shadowMap->at(x).at(y) - newCoordinates(0, 2)) < 2)
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
#pragma omp parallel for
        for (int curY = (y2 < 0) ? 0 : y2;
             curY <= ((y3 >= (int) bufHeight) ? (int) bufHeight - 1 : y3); curY++)
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

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
                //                                if (curX >= (int) depthBuffer.size() ||
                //                                curX < 0 ||
                //                                    curY >= (int)
                //                                    depthBuffer.at(0).size() || curY <
                //                                    0) continue;
                if (curZ >= depthBuffer.at(curX).at(curY))
                {
                    short visible = 0;
                    Eigen::MatrixXf newCoordinates(1, 4);
                    for (size_t i = 0; i < scene->getIllumNum() && !visible; i++)
                    {
                        newCoordinates << curX, curY, curZ, 1;

                        newCoordinates *= illumDotMatrices.at(i);
                        std::vector<std::vector<double>> *shadowMap =
                            &scene->getIlluminant(i).getShadowMap();
                        int x = round(newCoordinates(0, 0));
                        int y = round(newCoordinates(0, 1));
                        if (x < (int) shadowMap->size() && x >= 0 &&
                            y < (int) shadowMap->at(0).size() && y >= 0 &&
                            std::fabs(shadowMap->at(x).at(y) - newCoordinates(0, 2)) < 2)
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
        DDABordersForPolygon(x1, y1, z1, x2, y2, z2);
        DDABordersForPolygon(x1, y1, z1, x3, y3, z3);
        DDABordersForPolygon(x2, y2, z2, x3, y3, z3);
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
    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        for (size_t j = 0; j < scene->getIllumNum(); j++)
            shadowMapForModel(facets, vertices, scene->getTransMatrix(),
                &scene->getIlluminant(j), bufWidth, bufHeight);
    }

    model = scene->getPlateModel();
    facets = model.getFacets();
    vertices = model.getVertices();
    for (size_t j = 0; j < scene->getIllumNum(); j++)
        shadowMapForModel(facets, vertices, scene->getTransMatrix(),
            &scene->getIlluminant(j), bufWidth, bufHeight);

    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        zBufForModel(
            facets, vertices, scene->getTransMatrix(), 3, scene, bufWidth, bufHeight);
    }
    model = scene->getPlateModel();
    facets = model.getFacets();
    vertices = model.getVertices();
    zBufForModel(
        facets, vertices, scene->getTransMatrix(), 1, scene, bufWidth, bufHeight);

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
    uint darkGoldCol = qRgb(205, 170, 0);

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
                image->setPixel(i, j, blackCol /*qRgb(190, 130, 210)*/);
            }
        }

    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    qDebug() << "Time for drawing" << (end - start).count();
    outScene->addPixmap(QPixmap::fromImage(*image));
    delete image;
    for (size_t i = 0; i < scene->getIllumNum(); i++)
        scene->getIlluminant(i).clearShadowMap();
    //    qDebug() <<
    //    QPixmap("C:/Users/dobri/Desktop/FirstCurseWork/Proj/imgs/smert.jpg");
    return outScene;
}
