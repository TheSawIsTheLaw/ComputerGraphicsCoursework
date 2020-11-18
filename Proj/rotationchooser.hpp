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

    int getAngle();

    int getNewXCell();
    int getNewYCell();

    status stat = NO_ACTIONS;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::rotationChooser *ui;

    int angle = 0;
    int newXCell = 0, newYCell = 0;
};

#endif // ROTATIONCHOOSER_HPP
