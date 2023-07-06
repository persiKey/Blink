#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"

#include "QDebug"
#include "QScreen"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    float scaleFactor = QGuiApplication::primaryScreen()->logicalDotsPerInch() / 96.0;

    this->resize(constants::WINDOWS_WIDTH * scaleFactor,
                 constants::WINDOWS_HEIGHT * scaleFactor);

}

void MainWindow::wheelEvent(QWheelEvent* e)
{
    QScreen *screen = QGuiApplication::primaryScreen();

    for(auto s : QGuiApplication::screens())
    {
        qDebug() << "Scale factor:" << s->logicalDotsPerInch() / 96.0 * 100;
    }
    qDebug() << "primary Scale factor:" << QGuiApplication::primaryScreen()->logicalDotsPerInch();

    if(e->pos().x() > ui->label_2->pos().x() &&
       e->pos().x() < ui->label_2->pos().x() + ui->label_2->size().width() &&
       e->pos().y() > ui->label_2->pos().y() &&
       e->pos().y() < ui->label_2->pos().y() + ui->label_2->size().height())
    {
        static int counter = 0;
        qDebug() << "Counter " << counter++ << '\n';
        //qDebug() << e->pos().x() << " " << e->pos().y();
        qDebug() << e->angleDelta();
        // + UP
        // - DOWN
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
