#ifndef SIZECHOOSER_HPP
#define SIZECHOOSER_HPP

#include <QDialog>

namespace Ui {
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

    size_t getLength();
    void setLength(size_t length_);

private slots:
    void on_buttonBox_accepted();


private:
    Ui::SizeChooser *ui;

    size_t width = 0;
    size_t length = 0;
};

#endif // SIZECHOOSER_HPP
