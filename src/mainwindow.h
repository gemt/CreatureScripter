#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QSettings>

#include "loadingscreen.h"

class QTableWidget;
class QLineEdit;
class Creature;
class QTabWidget;
class WorkTabs;
class QToolBar;
class CreatureSearcher;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitWindow(LoadingScreen& ls);

private slots:
    void onNameSearch();
    void onNameSearchChange(const QString&);
    void onNameSearchTimeout();

private:
    QSettings settings;
    CreatureSearcher* searcher;

    QLineEdit* nameEntrySearch;
    QLineEdit* mapSearch;
    QToolBar* toolbar;
    WorkTabs* workTabs;

    QString currentDisplayedSearch;
    QString currentDIsplayedMapSearch;
    QTimer nameSearchTimer;


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
