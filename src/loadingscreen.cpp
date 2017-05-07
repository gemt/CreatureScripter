#include "loadingscreen.h"
#include <QPainter>
#include <QStyleOptionProgressBarV2>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>

LoadingScreen::LoadingScreen(QApplication *app, QWidget *parent)
    : QSplashScreen(parent),
      app(app)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::FramelessWindowHint);
    QRect r = QApplication::desktop()->screenGeometry();
    resize(r.width()/4, r.height()/4);
    window()->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,window()->size(),
                                              QApplication::desktop()->availableGeometry()));
    setCursor(Qt::BusyCursor);
}

void LoadingScreen::SetMessage(const QString &message)
{
    this->message = message;
    repaint();
}

void LoadingScreen::InitProgress(int max)
{
    this->max = max;
    prevstep = 0;
}

void LoadingScreen::setProgress(int v)
{
    realProgress = v;
    progress = 100.0f/max*v;
    if(progress>100)
        progress=100;
    else if(progress<0)
        progress=0;
    if(prevstep != progress)
        repaint();
    prevstep = progress;
}

int LoadingScreen::getProgress()
{
    return realProgress;
}

void LoadingScreen::drawContents(QPainter *painter)
{
    QSplashScreen::drawContents(painter);
    QRect r = rect();

    // Set style for progressbar...
    QStyleOptionProgressBarV2 pbstyle;
    pbstyle.initFrom(this);
    pbstyle.state = QStyle::State_Enabled;
    pbstyle.textVisible = true;
    pbstyle.text = message;
    pbstyle.minimum = 0;
    pbstyle.maximum = 100;
    pbstyle.progress = progress;
    pbstyle.invertedAppearance = false;
    pbstyle.rect = QRect(r.center().x()-r.width()/4, //left
                         r.center().y()+r.height()/10, //top
                         r.width()/2, // widht
                         r.height()/10); // height


    style()->drawControl(QStyle::CE_ProgressBar, &pbstyle, painter, this);
}
