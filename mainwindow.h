#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QSettings>

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

    void InitWindow();

private slots:
    void onNameSearch();
    void onNameSearchChange(const QString&);
    void onNameSearchTimeout();

private:
    QSettings settings;
    CreatureSearcher* searcher;

    QLineEdit* nameSearch;
    QToolBar* toolbar;
    WorkTabs* workTabs;

    QString currentDisplayedSearch;
    QTimer nameSearchTimer;

};

#endif // MAINWINDOW_H
