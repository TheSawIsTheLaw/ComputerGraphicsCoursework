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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SizeChooser *ui;
};

#endif // SIZECHOOSER_HPP
