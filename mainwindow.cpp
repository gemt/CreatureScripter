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
    cw->resize(rec.width()/2, rec.height()/2);

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

    entrySearch = new QLineEdit(cw);
    entrySearch->setValidator(new QIntValidator(0, 999999999, entrySearch));
    connect(entrySearch, &QLineEdit::returnPressed, this, &MainWindow::onEntrySearch);
    connect(entrySearch, &QLineEdit::textChanged, this, &MainWindow::onEntrySearchChange);

    sl->addRow(new QLabel("Name"), nameSearch);
    sl->addRow(new QLabel("Entry"), entrySearch);

    std::vector<Creature*> creatures = Creatures::Get().GetCreatures("");
    searchResults = new QTableWidget(creatures.size(), 2);
    searchResults->setHorizontalHeaderLabels(QStringList{"Entry", "Name"});
    searchResults->verticalHeader()->hide();
    searchResults->setSelectionBehavior(QAbstractItemView::SelectRows);
    searchResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 0; i < creatures.size(); i++) {
        searchResults->setItem(i, 0, creatures.at(i)->eItm);
        searchResults->setItem(i, 1, creatures.at(i)->nItm);
    }
    bl->addWidget(searchResults);
    searchResults->resizeColumnsToContents();
    searchResults->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::onNameSearch()
{
    onNameSearchTimeout();
}

void MainWindow::onEntrySearch()
{
    // entrySearch has a validator that only accepts ints

}

void MainWindow::onNameSearchChange(const QString& s)
{
    nameSearchTimer.start(500);
}

void MainWindow::onEntrySearchChange(const QString &)
{

}

void MainWindow::onNameSearchTimeout()
{
    nameSearchTimer.stop();
    if(currentDisplayedSearch == nameSearch->text())
        return;
    currentDisplayedSearch = nameSearch->text();

    std::vector<Creature*> ret = Creatures::Get().GetCreatures(nameSearch->text());
    for(int i = 0; i < searchResults->rowCount(); i++){
        if(i < ret.size()){ //size+1? nah dont think so
            searchResults->item(i, 0)->setText(QString("%1").arg(ret.at(i)->entry));
            searchResults->item(i, 1)->setText(ret.at(i)->name);
        }
        searchResults->setRowHidden(i, !(i < ret.size()));
    }
    return;
    while(searchResults->rowCount())
        searchResults->removeRow(searchResults->rowCount()-1);


    foreach(Creature const* p, ret){
        searchResults->insertRow(searchResults->rowCount());
        QTableWidgetItem* itm = new QTableWidgetItem(QString("%1").arg(p->entry));
        searchResults->setItem(searchResults->rowCount()-1, 0, itm);
        itm = new QTableWidgetItem(p->name);
        searchResults->setItem(searchResults->rowCount()-1, 1, itm);
    }
    //searchResults->resizeColumnsToContents();
    //searchResults->horizontalHeader()->setStretchLastSection(true);
}
