#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>

class QTableWidget;
class QLineEdit;
class Creature;
class QTabWidget;
class WorkTabs;
class QToolBar;

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
    void onCreatureSelect(int, int);
private:
    QTableWidget* searchResults;
    QLineEdit* nameSearch;
    QToolBar* toolbar;
    WorkTabs* workTabs;

    QString currentDisplayedSearch;
    QTimer nameSearchTimer;

    void SetRows(const std::vector<Creature*>& vec);
};

#endif // MAINWINDOW_H
