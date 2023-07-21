#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"

#include "QDebug"
#include "QScreen"
#include <QDesktopWidget>

#include <QtWin>
#include <thread>

#include <animwindow.h>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerManager = new TimerManager(ui->minutesLabel,ui->secondsLabel);
    float scaleFactor = QGuiApplication::primaryScreen()->logicalDotsPerInch() / 96.0;

    this->resize(constants::WINDOWS_WIDTH * scaleFactor,
                 constants::WINDOWS_HEIGHT * scaleFactor);


}

void MainWindow::wheelEvent(QWheelEvent* e)
{
    bool IsUp = e->angleDelta().y() > 0;
    auto cursorPos = e->pos();
    if(IsCursorOnLabel(cursorPos,ui->minutesLabel))
        timerManager->ChangeMinutes(IsUp);
    else if(IsCursorOnLabel(cursorPos,ui->secondsLabel))
        timerManager->ChangeSeconds(IsUp);
}

MainWindow::~MainWindow()
{
    delete timerManager;
    delete ui;
}

bool MainWindow::IsCursorOnLabel(QPoint p, QLabel *lb)
{
    auto label_x = lb->pos().x();
    auto label_y = lb->pos().y();
    auto cursor_x = p.x();
    auto cursor_y = p.y();
    return cursor_x > label_x &&
            cursor_x < label_x + lb->size().width() &&
            cursor_y > label_y &&
            cursor_y < label_y + lb->size().height();
}

void MainWindow::PlayAnimation()
{
    using std::chrono::operator""s;
    //std::this_thread::sleep_for(5s);
    QWidget* a = new AnimWindow();


    //a->setWindowFlag(Qt::SubWindow, true);
   // a->setWindowFlag(Qt::X11BypassWindowManagerHint, true);

    //a->setWindowState(Qt::WindowFullScreen);
    //a->setWindowOpacity(0.5);
    //a->setStyleSheet("background-color: rgba(255,255,255,255);");

    QRect screenres = QApplication::desktop()->screenGeometry(0);
    a->move(QPoint(screenres.x(), screenres.y()));
    a->resize(screenres.width(), screenres.height());


    //a->setAttribute(Qt::WA_TranslucentBackground, true);
    //a->setAttribute(Qt::WA_NoSystemBackground, true);
    //a->setAttribute(Qt::WA_AlwaysStackOnTop, true);
    //a->setAttribute(Qt::WA_OpaquePaintEvent, true);

    //a->showFullScreen();
    //QtWin::enableBlurBehindWindow(a);

    a->show();

    QPropertyAnimation* anim = new QPropertyAnimation(a,"param");
    anim->setDuration(3000);
    anim->setStartValue(0);
    anim->setEndValue(120);
    anim->start();
}


void MainWindow::on_blinkButton_clicked()
{
    PlayAnimation();
}
