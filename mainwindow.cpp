#include "mainwindow.h"
#include "table.h"
#include "warnings.h"


#include <QDebug>
#include <QSqlError>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QHeaderView>
#include <QApplication>
#include <QDesktopWidget>

#define QT_DEBUG_PLUGINS
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentDisplayedSearch("-@-@!`?=?mlasmc")
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QWidget* cw = new QWidget(parent);
    setCentralWidget(cw);
    QRect rec = QApplication::desktop()->screenGeometry();
    resize(rec.width()/2, rec.height()/2);
    nameSearchTimer.setSingleShot(true);
    connect(&nameSearchTimer, &QTimer::timeout, this, &MainWindow::onNameSearchTimeout);

}

MainWindow::~MainWindow()
{

}

void MainWindow::InitTable()
{
    QWidget* cw = centralWidget();
    QVBoxLayout* bl = new QVBoxLayout(cw);

    QFormLayout* sl = new QFormLayout();
    bl->addLayout(sl);

    nameSearch = new QLineEdit(cw);
    connect(nameSearch, &QLineEdit::returnPressed, this, &MainWindow::onNameSearch);
    connect(nameSearch, &QLineEdit::textChanged, this, &MainWindow::onNameSearchChange);

    sl->addRow(new QLabel("Name/Entry"), nameSearch);

    std::vector<Creature*> creatures = Creatures::Get().GetCreatures("");
    searchResults = new QTableWidget((int)creatures.size(), 2);
    searchResults->setHorizontalHeaderLabels(QStringList{"Entry", "Name"});
    searchResults->verticalHeader()->hide();
    searchResults->setSelectionBehavior(QAbstractItemView::SelectRows);
    searchResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 0; i < creatures.size(); i++) {
        searchResults->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(creatures.at(i)->entry)));
        searchResults->setItem(i, 1, new QTableWidgetItem(creatures.at(i)->name));
    }
    bl->addWidget(searchResults);
    searchResults->resizeColumnsToContents();
    searchResults->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::onNameSearch()
{
    onNameSearchTimeout();
}

void MainWindow::onNameSearchChange(const QString&)
{
    nameSearchTimer.start(500);
}

void MainWindow::onNameSearchTimeout()
{
    nameSearchTimer.stop();
    if(currentDisplayedSearch == nameSearch->text())
        return;
    currentDisplayedSearch = nameSearch->text();

    std::vector<Creature*> ret = Creatures::Get().GetCreatures(currentDisplayedSearch);
    SetRows(ret);

}

void MainWindow::SetRows(const std::vector<Creature *> &vec)
{
    for(int i = 0; i < searchResults->rowCount(); i++){
        if(i < vec.size()){ //size+1? nah dont think so
            searchResults->item(i, 0)->setText(QString("%1").arg(vec.at(i)->entry));
            searchResults->item(i, 1)->setText(vec.at(i)->name);
        }
        searchResults->setRowHidden(i, !(i < vec.size()));
    }
}
