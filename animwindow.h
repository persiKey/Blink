#ifndef ANIMWINDOW_H
#define ANIMWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include "constants.h"

using namespace constants::Animation;

class WavyEllipseDrawer : public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(float bDiff READ getBDiff WRITE setBDiff);
    Q_PROPERTY(float phase READ getPhase WRITE setPhase);

    void setBDiff(float newBDiff);
    void setPhase(float newPhase);

    float getBDiff();
    float getPhase();

    float t;
    float bDiff;
    float phase = 0;

    QPointF anchorPoints[AMOUNT_OF_POINTS];
    float a;
    float b;
    float B;
    float waveAmplitude = WAVE_AMPLITUDE;
    float amountOfWaves = AMOUNT_OF_WAVES;


    float sin_t;
    float cos_t;

    float GetNormalComponent();
    float GetArcLenghtCoef();
    float GetMultiplyComponent();
    QPointF GetPoint();

    QSize drawSize;
public:
    void setDrawAreaSize(QSize);
    void Draw(QPainter& painter);
};


class AnimWindow : public QWidget
{
    Q_OBJECT
private:
    WavyEllipseDrawer elipse;

    QPropertyAnimation* closeAnim;
    QPropertyAnimation* openAnim;
    QPropertyAnimation* phaseAnim;
    QSequentialAnimationGroup* bAnim;
    QParallelAnimationGroup* mainAnim;

protected:
    void paintEvent(QPaintEvent* e) override;
    void resizeEvent(QResizeEvent *event) override;

public:
    explicit AnimWindow(QWidget *parent = nullptr);
    void StartAnimation();
public slots:
    void OnAnimationEnd();
signals:
    void finished();
};



#endif // ANIMWINDOW_H
