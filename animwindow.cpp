#include "animwindow.h"
#include <QPainter>
#include <QDebug>
#include <chrono>
#include <cmath>
#include <QResizeEvent>
#include <thread>

extern "C" double cephes_ellie ( double phi, double m );


float SinFromZeroToHalfPi(float x);

AnimWindow::AnimWindow(QWidget *parent) : QWidget(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setWindowFlags(Qt::WindowTransparentForInput |
                         Qt::WindowStaysOnTopHint |
                         Qt::FramelessWindowHint |
                         Qt::MaximizeUsingFullscreenGeometryHint);

    closeAnim = new QPropertyAnimation(&elipse,"bDiff");
    closeAnim->setStartValue(0);
    closeAnim->setEndValue(300);
    closeAnim->setDuration(ANIMMATION_DURATION/2);
    closeAnim->setEasingCurve(QEasingCurve::InCubic);

    openAnim = new QPropertyAnimation(&elipse,"bDiff");
    openAnim->setStartValue(300);
    openAnim->setEndValue(0);
    openAnim->setDuration(ANIMMATION_DURATION/2);
    openAnim->setEasingCurve(QEasingCurve::OutCubic);

    bAnim  =  new QSequentialAnimationGroup;
    bAnim->addAnimation(closeAnim);
    bAnim->addAnimation(openAnim);


    phaseAnim = new QPropertyAnimation(&elipse,"phase");
    phaseAnim->setStartValue(0);
    phaseAnim->setEndValue(100);
    phaseAnim->setDuration(ANIMMATION_DURATION);

    mainAnim = new QParallelAnimationGroup;
    mainAnim->addAnimation(bAnim);
    mainAnim->addAnimation(phaseAnim);
    QObject::connect(mainAnim,SIGNAL(finished()),this,SLOT(close()));
}

void AnimWindow::StartAnimation()
{
    mainAnim->start();
    std::thread([this]() {
        while(this->mainAnim->state() != QAbstractAnimation::Stopped)
        {
            this->update();
            std::this_thread::sleep_for(std::chrono::operator""ms(10));
        }
    }).detach();

}


void AnimWindow::paintEvent(QPaintEvent* )
{
    QPainter painter(this);

    QPen pen(QColor(255,128,0));
    pen.setWidthF(5);
    painter.setPen(pen);

    elipse.Draw(painter);

    painter.end();
}

void AnimWindow::resizeEvent(QResizeEvent *event)
{
    elipse.setDrawAreaSize(event->size());
}


float SinFromZeroToPi(float x)
{
    if(x > M_PI_2)
    {
       x -= M_PI;
       x *= -1;

    }
    else if (x < - M_PI_2)
    {
       x += M_PI;
       x *= -1;
    }

    return x - (x * x * x) / 6 + (x * x * x * x * x) / 120 - ((x * x * x * x * x * x * x) / (120 * 6 * 7));
}


void WavyEllipseDrawer::setB(float newB)
{
    bDiff = newB;
    b = B - bDiff;
}

void WavyEllipseDrawer::setPhase(float newPhase)
{
    phase = newPhase;
}

float WavyEllipseDrawer::getB()
{
    return bDiff;
}

float WavyEllipseDrawer::getPhase()
{
    return phase;
}

float WavyEllipseDrawer::GetNormalComponent()
{
    return 1/sqrt(b * b * cos_t * cos_t + a * a * sin_t * sin_t);
}

float WavyEllipseDrawer::GetIntegral()
{
    return cephes_ellie(t,(1 - (a * a)/(b * b)));
}

float WavyEllipseDrawer::GetS()
{
    return cephes_ellie(2 * M_PI,(1 - (a * a)/(b * b)));
}

float WavyEllipseDrawer::GetMultiplyComponent()
{
    return waveAmplitude * cos(amountOfWaves * 2 * M_PI * GetIntegral() / GetS() + phase) * GetNormalComponent();
}

QPointF WavyEllipseDrawer::GetPoint()
{
    sin_t = SinFromZeroToPi(t);
    cos_t = SinFromZeroToPi(M_PI_2 - t);


    QPointF result;
    result.setX((a * cos_t + GetMultiplyComponent() * b * cos_t));
    result.setY((b * sin_t + GetMultiplyComponent() * a * sin_t));

    return result;
}

void WavyEllipseDrawer::setDrawAreaSize(QSize Size)
{
    drawSize = Size;
    a = drawSize.width()/2 - waveAmplitude;
    B = drawSize.height()/2 - waveAmplitude;
}

void WavyEllipseDrawer::Draw(QPainter &painter)
{
    this->t = 0;
    for (int i = 0; i < AMOUNT_OF_POINTS ; i++ )
    {
        anchorPoints[i] = GetPoint();
        t += M_PI / AMOUNT_OF_POINTS;
    }

    QPointF curr = anchorPoints[0] + QPointF(drawSize.width()/2, drawSize.height()/2);
    QPointF curr_neg = anchorPoints[0] * - 1 + QPointF(drawSize.width()/2, drawSize.height()/2);
    QPointF next, next_neg;

    for (int i = 1; i < AMOUNT_OF_POINTS-1;++i )
    {
        next = anchorPoints[i+1] + QPointF(drawSize.width()/2,drawSize.height()/2);
        painter.drawLine(curr, next);
        curr = next;

        next_neg = anchorPoints[i+1] * - 1 + + QPointF(drawSize.width()/2, drawSize.height()/2);
        painter.drawLine(curr_neg,next_neg);
        curr_neg = next_neg;
    }

    painter.drawLine(anchorPoints[0] + QPointF(drawSize.width()/2,drawSize.height()/2),next_neg);
    painter.drawLine(anchorPoints[0] * -1 + QPointF(drawSize.width()/2,drawSize.height()/2) ,next);
}
