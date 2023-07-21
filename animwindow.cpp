#include "animwindow.h"
#include <QPainter>
#include <QDebug>
#include <unordered_set>
#include <chrono>
#include <cmath>

float SinFromZeroToHalfPi(float x);

AnimWindow::AnimWindow(QWidget *parent) : QWidget(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setWindowFlags(Qt::WindowTransparentForInput |
                         Qt::WindowStaysOnTopHint |
                         Qt::FramelessWindowHint |
                         Qt::MaximizeUsingFullscreenGeometryHint);



}

void AnimWindow::setParam(int p)
{
    this->param = p;
    this->repaint();

}

int AnimWindow::getParam()
{
    return param;
}

void AnimWindow::paintEvent(QPaintEvent* e)
{

    const int pr = 300;
    QPointF elipse[pr+1];
    ElipseCalculations EC;
    EC.a = size().width()/2 - EC.waveAmplitude - 100;
    EC.b = size().height()/2 - EC.waveAmplitude- 100;
    EC.phase = param;

    QPainter painter(this);

    QPen pen(Qt::red);
    pen.setWidthF(2);
    painter.setPen(pen);

    float _t = 0;
    for (int i = 0; i < pr ; i++ )
    {
        elipse[i] = EC.GetPoint(_t);
        _t+=PI/pr;
    }

    QPointF curr = elipse[0] + QPointF(size().width()/2,size().height()/2);
    QPointF curr_neg = elipse[0] * -1 + QPointF(size().width()/2,size().height()/2);
    QPointF next, next_neg;
    for (int i = 1; i < pr-1;++i )
    {
        next = elipse[i+1] + QPointF(size().width()/2,size().height()/2);
        painter.drawLine(curr, next);
        curr = next;

        next_neg = elipse[i+1] * -1 + + QPointF(size().width()/2,size().height()/2);
        painter.drawLine(curr_neg,next_neg);
        curr_neg = next_neg;
    }

    painter.drawLine(elipse[0] + QPointF(size().width()/2,size().height()/2)
                     ,next_neg);
    painter.drawLine(elipse[0] * -1 + QPointF(size().width()/2,size().height()/2)
                     ,next);

    painter.end();
}


float SinFromZeroToPi(float x)
{
    //return sin(x);
    if(x > HALF_PI)
    {
       x -= PI;
       x *= -1;

    }
    else if (x < -HALF_PI)
    {
       x += PI;
       x *= -1;
    }


    return x - (x * x * x) / 6 + (x * x * x * x * x) / 120 - ((x * x * x * x * x * x * x) / (120 * 6 * 7));
}


float ElipseCalculations::GetNormalComponent()
{
    return 1/sqrt(b * b * cos_t * cos_t + a * a * sin_t * sin_t);
}

float ElipseCalculations::GetIntegral()
{
    float result = 0;
    float sin_m, cos_m;
    for (float m = 0; m < t ; m += step )
    {
        sin_m = SinFromZeroToPi(m);
        cos_m = SinFromZeroToPi(m - HALF_PI);
        result += step * sqrt(b * b * cos_m * cos_m + a * a * sin_m * sin_m);
    }
    return result;
}

float ElipseCalculations::GetS()
{
    float result = 0;
    float sin_m, cos_m;
    for (float m = 0; m < 2 * PI ; m += step )
    {
        sin_m = sin(m);
        cos_m = sin(HALF_PI - m);
        result += step * sqrt(b * b * cos_m * cos_m + a * a * sin_m * sin_m);
    }
    return result;
}

float ElipseCalculations::GetMultiplyComponent()
{
    return waveAmplitude * cos(amountOfWaves * 4 * HALF_PI * GetIntegral() / GetS() + phase) * GetNormalComponent();
}

QPointF ElipseCalculations::GetPoint(float _t)
{
    t = _t;

    sin_t = SinFromZeroToPi(t);
    cos_t = SinFromZeroToPi(HALF_PI - t);



    QPointF result;
    result.setX((a * cos_t + GetMultiplyComponent() * b * cos_t));
    result.setY((b * sin_t + GetMultiplyComponent() * a * sin_t));

    return result;
}
