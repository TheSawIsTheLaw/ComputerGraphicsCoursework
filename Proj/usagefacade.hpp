#ifndef USAGEFACADE_HPP
#define USAGEFACADE_HPP

#include "objects.hpp"
#include <QGraphicsScene>

class Drawer
{
public:
    void zBufferAlg(CellScene *scene, size_t bufheight, size_t bufWidth);
    void zBufForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices, Eigen::Matrix4f &transMat, size_t color);
    QGraphicsScene *drawScene(CellScene *scene, QRectF rect);

private:
    std::vector<std::vector<size_t>> depthBuffer;
    std::vector<std::vector<size_t>> frameBuffer;
};

class UsageFacade
{
public:
    UsageFacade();

    void setCellScene(size_t width_, size_t height_);
    void changeCellScene(size_t newWidth, size_t newheight);
    bool isSceneSet();

    QGraphicsScene *drawScene(QRectF rect);

    void addTable();

    QGraphicsScene *moveUpScene(double value, QRectF rect);
    QGraphicsScene *moveDownScene(double value, QRectF rect);
    QGraphicsScene *moveLeftScene(double value, QRectF rect);
    QGraphicsScene *moveRightScene(double value, QRectF rect);

    QGraphicsScene *rotateXScene(double angle, QRectF rect);
    QGraphicsScene *rotateYScene(double angle, QRectF rect);

private:
    CellScene *scene;

    void addQuad(std::vector<Vertex> &vertices, std::vector<Facet> &facets,
                 int x1, int y1, int z1,
                 int x2, int y2, int z2,
                 int x3, int y3, int z3,
                 int x4, int y4, int z4);

    Drawer *drawer;
};

#endif // USAGEFACADE_HPP
