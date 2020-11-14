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

    void setXCell(int xCell_);
    int getXCell();

    void setYCell(int yCell_);
    int getYCell();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PlaceChooser *ui;

    int xCell = 0;
    int yCell = 0;
};

#endif // PLACECHOOSER_H
