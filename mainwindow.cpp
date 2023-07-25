#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"

#include <QDebug>
#include <QScreen>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSound>
#include <QDir>

#include <QtWin>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerManager = new TimerManager(ui->minutesLabel,ui->secondsLabel);
    float scaleFactor = QGuiApplication::primaryScreen()->logicalDotsPerInch() / 96.0;

    this->resize(constants::WINDOWS_WIDTH * scaleFactor,
                 constants::WINDOWS_HEIGHT * scaleFactor);

    mainTimer.setSingleShot(false);
    QObject::connect(&mainTimer,SIGNAL(timeout()), this, SLOT(TimeoutActions()));
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

void MainWindow::TimeoutActions()
{
    if(ui->soundCheckBox->isChecked())
        sound.PlayRandomSound();
    if(ui->animtaionCheckBox->isChecked())
        PrepareAnimation();
    if(ui->musicCheckBox->isChecked())
    {}

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

void MainWindow::PrepareAnimation()
{
    int amountOfDisplays = amountOfDisplaysLeft = QGuiApplication::screens().size();

    animWindows = new AnimWindow[amountOfDisplays];

    for (int i = 0; i < amountOfDisplays ; ++i )
    {
        auto screenGeometry = QGuiApplication::screens().at(i)->geometry();
        animWindows[i].move(screenGeometry.x(), screenGeometry.y());
        animWindows[i].resize(screenGeometry.width(), screenGeometry.height());
        animWindows[i].show();
        animWindows[i].StartAnimation();
        QObject::connect(animWindows + i,SIGNAL(finished()),this,SLOT(ClearAnimation()));
    }

/*

    //a->setWindowFlag(Qt::SubWindow, true);
   // a->setWindowFlag(Qt::X11BypassWindowManagerHint, true);

    //a->setWindowState(Qt::WindowFullScreen);
    //a->setWindowOpacity(0.5);

    //a->setAttribute(Qt::WA_TranslucentBackground, true);
    //a->setAttribute(Qt::WA_NoSystemBackground, true);
    //a->setAttribute(Qt::WA_AlwaysStackOnTop, true);
    //a->setAttribute(Qt::WA_OpaquePaintEvent, true);

    //QtWin::enableBlurBehindWindow(a);
*/
}

void MainWindow::ClearAnimation()
{
    if(!--amountOfDisplaysLeft)
        delete[] animWindows;
}


void MainWindow::on_blinkButton_clicked()
{
    mainTimer.setInterval(timerManager->GetSeconds()*1000);
    mainTimer.start();
    this->hide();
}
