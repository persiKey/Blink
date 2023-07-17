#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"

#include "QDebug"
#include "QScreen"
#include <QDesktopWidget>

#include <thread>
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
    std::this_thread::sleep_for(5s);
    QWidget* a = new QWidget();

    a->setFocusPolicy(Qt::NoFocus);
    a->setWindowFlag(Qt::WindowTransparentForInput, true);
    a->setWindowFlag(Qt::WindowStaysOnTopHint, true);
    //a->setWindowState(Qt::WindowFullScreen);
    a->setWindowOpacity(0.5);
    a->setStyleSheet("background-color: orange;");

    QRect screenres = QApplication::desktop()->screenGeometry(0);
    a->move(QPoint(screenres.x(), screenres.y()));
    a->resize(screenres.width(), screenres.height());
    a->showFullScreen();
    //a->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //a->show();
}


void MainWindow::on_blinkButton_clicked()
{
    PlayAnimation();
}
