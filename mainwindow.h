#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableWidget;
class QLineEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onNameSearch();
    void onEntrySearch();

private:
    QTableWidget* searchResults;
    QLineEdit* nameSearch;
    QLineEdit* entrySearch;

};

#endif // MAINWINDOW_H
