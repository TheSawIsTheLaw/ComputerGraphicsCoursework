#include "specialgraphicsview.hpp"
#include "QDebug"

SpecialGraphicsView::SpecialGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void SpecialGraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Нажали" << event->x() << event->y() << '\n';
}

void SpecialGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    emit sendMouse(event->x(), event->y());
    qDebug() << "Движ..." << event->x() << event->y() << '\n';
}
