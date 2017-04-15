#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
class QTableWidget;
class QLineEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitTable();

private slots:
    void onNameSearch();
    void onEntrySearch();

    void onNameSearchChange(const QString&);
    void onEntrySearchChange(const QString&);

    void onNameSearchTimeout();

private:
    QTableWidget* searchResults;

    QLineEdit* nameSearch;
    QLineEdit* entrySearch;

    QString currentDisplayedSearch;

    QTimer nameSearchTimer;

};

#endif // MAINWINDOW_H
