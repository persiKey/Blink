#ifndef ANIMWINDOW_H
#define ANIMWINDOW_H

#include <QWidget>

inline constexpr float HALF_PI = 1.57079632679f;
inline constexpr float PI = HALF_PI * 2;

class AnimWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AnimWindow(QWidget *parent = nullptr);
    Q_PROPERTY(int param READ getParam WRITE setParam)
    int param;
    void setParam(int p);
    int getParam();
protected:
    void paintEvent(QPaintEvent* e) override;
signals:

};


struct ElipseCalculations
{
    const float step = 0.001/2;
    float a;
    float b;
    float waveAmplitude = 50;
    float amountOfWaves = 20;
    float t;
    float phase = 0;

    float sin_t;
    float cos_t;

    float GetNormalComponent();
    float GetIntegral();
    float GetS();
    float GetMultiplyComponent();
    QPointF GetPoint(float t);
};

#endif // ANIMWINDOW_H
