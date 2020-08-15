#ifndef SIZECHANGER_HPP
#define SIZECHANGER_HPP

#include <QDialog>

namespace Ui
{
class SizeChanger;
}

class SizeChanger : public QDialog
{
    Q_OBJECT

public:
    explicit SizeChanger(QWidget *parent = nullptr);
    ~SizeChanger();

    size_t getNewWidth();
    size_t getNewLength();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SizeChanger *ui;

    size_t newWidth = 0;
    size_t newLength = 0;
};

#endif // SIZECHANGER_HPP
