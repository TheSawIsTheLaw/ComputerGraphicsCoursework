#ifndef USAGEFACADE_HPP
#define USAGEFACADE_HPP

#include "objects.hpp"

class UsageFacade
{
public:
    UsageFacade();

    void setCellScene(size_t width_, size_t length_);

    void changeCellScene(size_t newWidth, size_t newLength);

    bool isSceneSet();

private:
    CellScene *scene;
};

#endif // USAGEFACADE_HPP
