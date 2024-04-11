#ifndef OPTIMIZEDSLIDER_H
#define OPTIMIZEDSLIDER_H

#pragma once

#include <QObject>
#include "qheaders.h"

class OptimizedSlider : public QSlider
{
public:
    OptimizedSlider(QWidget *parent);
    ~OptimizedSlider();

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // OPTIMIZEDSLIDER_H
