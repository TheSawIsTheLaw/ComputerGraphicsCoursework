#ifndef USAGEFACADE_HPP
#define USAGEFACADE_HPP

#include "objects.hpp"
#include <QGraphicsScene>

class Drawer
{
public:
    QGraphicsScene *drawScene(CellScene *scene);

private:
    std::vector<PolModel> models;
};

class UsageFacade
{
public:
    UsageFacade();

    void setCellScene(size_t width_, size_t length_);
    void changeCellScene(size_t newWidth, size_t newLength);
    bool isSceneSet();

    QGraphicsScene *drawScene();

private:
    CellScene *scene;

    Drawer *drawer;
};

#endif // USAGEFACADE_HPP
