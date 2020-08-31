#ifndef USAGEFACADE_HPP
#define USAGEFACADE_HPP

#include "objects.hpp"
#include <QGraphicsScene>

class Drawer
{
public:
    void zBufferAlg(CellScene *scene, size_t bufLength, size_t bufWidth);
    QGraphicsScene *drawScene(CellScene *scene, QRectF rect);

private:
    std::vector<std::vector<size_t>> depthBuffer;
    std::vector<std::vector<size_t>> frameBuffer;
};

class UsageFacade
{
public:
    UsageFacade();

    void setCellScene(size_t width_, size_t length_);
    void changeCellScene(size_t newWidth, size_t newLength);
    bool isSceneSet();

    QGraphicsScene *drawScene(QRectF rect);

    QGraphicsScene *moveUpScene(double value, QRectF rect);
    QGraphicsScene *moveDownScene(double value, QRectF rect);
    QGraphicsScene *moveLeftScene(double value, QRectF rect);
    QGraphicsScene *moveRightScene(double value, QRectF rect);

private:
    CellScene *scene;

    Drawer *drawer;
};

#endif // USAGEFACADE_HPP
