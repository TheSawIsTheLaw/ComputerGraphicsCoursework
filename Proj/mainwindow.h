#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QMouseEvent>

#include "usagefacade.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void getMouseEvent(size_t x_, size_t y_);

//    void updateScene();

    void pictureDown();
    void pictureUp();
    void pictureLeft();
    void pictureRight();

    void pictureScaleUp();
    void pictureScaleDown();

    void pictureRotateXRight();
    void pictureRotateXLeft();
    void pictureRotateYRight();
    void pictureRotateYLeft();
    void pictureRotateZRight();
    void pictureRotateZLeft();

    void pictureToCenter();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    UsageFacade *facade;
};

#endif // MAINWINDOW_H
