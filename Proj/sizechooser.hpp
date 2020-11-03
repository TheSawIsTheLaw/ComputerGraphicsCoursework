#ifndef SIZECHOOSER_HPP
#define SIZECHOOSER_HPP

#include <QDialog>

namespace Ui
{
class SizeChooser;
}

class SizeChooser : public QDialog
{
    Q_OBJECT

public:
    explicit SizeChooser(QWidget *parent = nullptr);
    ~SizeChooser();

    void setWidth(size_t width_);
    size_t getWidth();

    size_t getheight();
    void setheight(size_t height_);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SizeChooser *ui;

    size_t width = 0;
    size_t height = 0;
};

#endif // SIZECHOOSER_HPP
