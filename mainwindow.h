#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QLabel>
#include "timermanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void wheelEvent(QWheelEvent* e) override;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_blinkButton_clicked();

private:
    Ui::MainWindow *ui;
    TimerManager* timerManager;
    bool IsCursorOnLabel(QPoint p, QLabel* lb);
    void PlayAnimation();

};
#endif // MAINWINDOW_H
