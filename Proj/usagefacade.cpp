#include "usagefacade.hpp"

#include "QDebug"

void UsageFacade::setCellScene(size_t width_, size_t length_)
{
    // Чимстка помяти???..
    scene = new CellScene(width_, length_);
    qDebug("Set was done\n");
}
