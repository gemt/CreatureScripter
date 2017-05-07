#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QSplashScreen>

class QPainter;
class LoadingScreen : public QSplashScreen
{
public:
    LoadingScreen(QApplication* app, QWidget* parent = nullptr);

    void SetMessage(const QString& message);
    void InitProgress(int max);
    void setProgress(int v);
    int getProgress();
private:
    QApplication* app;
    int max, progress, prevstep, realProgress;
    QString message;

    // QSplashScreen interface
protected:
    void drawContents(QPainter *painter);
};

#endif // LOADINGSCREEN_H
