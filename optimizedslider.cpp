#include "optimizedslider.h"

OptimizedSlider::OptimizedSlider(QWidget *parent)
    : QSlider(parent)
{

}

OptimizedSlider::~OptimizedSlider()
{

}

void OptimizedSlider::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    // qDebug() << QT_DEBUG_OUTPUT << x;

    double percent = x * 1.0 / this->width();
    int value = percent * (this->maximum() - this->minimum()) + this->minimum();

    this->setValue(value);

    QSlider::mousePressEvent(event);
}
