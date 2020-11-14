#ifndef PLACECHOOSER_H
#define PLACECHOOSER_H

#include <QDialog>

namespace Ui {
class PlaceChooser;
}

class PlaceChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceChooser(QWidget *parent = nullptr);
    ~PlaceChooser();

    void setXCell(size_t xCell_);
    size_t getXCell();

    void setYCell(size_t yCell_);
    size_t getYCell();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PlaceChooser *ui;

    size_t xCell = 0;
    size_t yCell = 0;
};

#endif // PLACECHOOSER_H
