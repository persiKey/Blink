#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QLabel>
#include <QSound>

#include "timermanager.h"
#include "animwindow.h"
#include "constants.h"
#include "soundmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void wheelEvent(QWheelEvent* e) override;
    void TimeoutActions();
    void PrepareAnimation();
    void ClearAnimation();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_blinkButton_clicked();

private:
    Ui::MainWindow *ui;
    TimerManager* timerManager;
    AnimWindow *animWindows;
    int amountOfDisplaysLeft;
    SoundManager sound;
    QTimer mainTimer;

    bool IsCursorOnLabel(QPoint p, QLabel* lb);
};
#endif // MAINWINDOW_H
