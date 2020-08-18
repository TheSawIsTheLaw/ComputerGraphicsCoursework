#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include <mainwindow.h>
#include "objects.hpp"

#include "additivemathelements.hpp"

class Drawer
{
public:
    void drawScene(Ui::MainWindow *ui, CellScene *scene);

private:
    std::vector<PolModel> models;
};

#endif // MANAGERS_HPP
