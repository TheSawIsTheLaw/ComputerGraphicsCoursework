#ifndef SPECIALGRAPHICSVIEW_HPP
#define SPECIALGRAPHICSVIEW_HPP

#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>

class SpecialGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SpecialGraphicsView(QWidget *parent = nullptr);

signals:
    void sendMouse(size_t x, size_t y);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // SPECIALGRAPHICSVIEW_HPP
