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
    : QMainWindow(parent)
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QWidget* cw = new QWidget(parent);
    setCentralWidget(cw);
    //QRect rec = QApplication::desktop()->screenGeometry();
    //cw->resize(rec.width()/2, rec.height()/2);

    QVBoxLayout* bl = new QVBoxLayout(cw);

    QFormLayout* sl = new QFormLayout();
    bl->addLayout(sl);

    nameSearch = new QLineEdit(cw);
    connect(nameSearch, &QLineEdit::returnPressed, this, &MainWindow::onNameSearch);

    entrySearch = new QLineEdit(cw);
    entrySearch->setValidator(new QIntValidator(0, 999999999, entrySearch));
    connect(entrySearch, &QLineEdit::returnPressed, this, &MainWindow::onEntrySearch);

    sl->addRow(new QLabel("Name"), nameSearch);
    sl->addRow(new QLabel("Entry"), entrySearch);


    searchResults = new QTableWidget(0, 2, cw);
    searchResults->setHorizontalHeaderLabels(QStringList{"Entry", "Name"});
    searchResults->verticalHeader()->hide();
    bl->addWidget(searchResults);


}

MainWindow::~MainWindow()
{

}

void MainWindow::onNameSearch()
{
    while(searchResults->rowCount())
        searchResults->removeRow(searchResults->rowCount()-1);

    QVector<std::shared_ptr<Creature>> ret;
    try{
        ret = Creature::GetCreatures(nameSearch->text());
    }catch(std::exception& e){
        Warning(e.what());
    }
    foreach(const std::shared_ptr<Creature>& p, ret){
        searchResults->insertRow(searchResults->rowCount());
        QTableWidgetItem* itm = new QTableWidgetItem(QString("%1").arg(p->entry));
        searchResults->setItem(searchResults->rowCount()-1, 0, itm);
        itm = new QTableWidgetItem(p->name);
        searchResults->setItem(searchResults->rowCount()-1, 1, itm);
    }
    searchResults->resizeColumnsToContents();
    searchResults->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::onEntrySearch()
{
    // entrySearch has a validator that only accepts ints

}
