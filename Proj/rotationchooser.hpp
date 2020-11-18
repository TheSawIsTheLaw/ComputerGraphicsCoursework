#ifndef ROTATIONCHOOSER_HPP
#define ROTATIONCHOOSER_HPP

#include <QDialog>

namespace Ui {
class rotationChooser;
}

class rotationChooser : public QDialog
{
    Q_OBJECT

public:
    explicit rotationChooser(QWidget *parent = nullptr);
    ~rotationChooser();

    enum status {
        NO_ACTIONS,
        ACTIONS_WERE_DONE,
        ERROR_WAS_ACCURED
    };

    int getXAngle();
    int getYAngle();

    int getNewXCell();
    int getNewYCell();

    status stat = NO_ACTIONS;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::rotationChooser *ui;

    int xAngle = 0, yAngle = 0;
    int newXCell = 0, newYCell = 0;
};

#endif // ROTATIONCHOOSER_HPP
