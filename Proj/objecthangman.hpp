#ifndef OBJECTHANGMAN_HPP
#define OBJECTHANGMAN_HPP

#include <QDialog>
#include "objects.hpp"

namespace Ui {
class ObjectHangman;
}

class ObjectHangman : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectHangman(CellScene *scene, QWidget *parent = nullptr);
    ~ObjectHangman();

private:
    Ui::ObjectHangman *ui;
};

#endif // OBJECTHANGMAN_HPP
