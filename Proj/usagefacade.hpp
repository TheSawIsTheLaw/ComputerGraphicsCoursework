#ifndef USAGEFACADE_HPP
#define USAGEFACADE_HPP

#include "objects.hpp"

class UsageFacade
{
public:
    void setCellScene(size_t width_, size_t length_);

private:
    CellScene *scene;

};

#endif // USAGEFACADE_HPP
