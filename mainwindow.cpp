#include "mainwindow.h"
#include "warnings.h"
#include "worktabs.h"
#include "cache.h"

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
#include <QSplitter>
#include <QTabWidget>

#define QT_DEBUG_PLUGINS
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentDisplayedSearch("-@-@!`?=?mlasmc")
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    setCentralWidget(new QSplitter(Qt::Horizontal, this));
    QRect rec = QApplication::desktop()->screenGeometry();
    resize(rec.width()/2, rec.height()/2);
    nameSearchTimer.setSingleShot(true);
    connect(&nameSearchTimer, &QTimer::timeout, this, &MainWindow::onNameSearchTimeout);

    QSplitter splitter;
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitWindow()
{
    QSplitter* splitter = static_cast<QSplitter*>(centralWidget());
    QRect rec = QApplication::desktop()->screenGeometry();
    int creatureTableWidth;
    {
        QWidget* searchWidget = new QWidget();
        splitter->addWidget(searchWidget);

        QVBoxLayout* bl = new QVBoxLayout(searchWidget);
        QFormLayout* sl = new QFormLayout();
        bl->addLayout(sl);

        nameSearch = new QLineEdit(searchWidget);
        connect(nameSearch, &QLineEdit::returnPressed, this, &MainWindow::onNameSearch);
        connect(nameSearch, &QLineEdit::textChanged, this, &MainWindow::onNameSearchChange);

        sl->addRow(new QLabel("Name/Entry"), nameSearch);

        std::vector<Creature*> creatures = Cache::Get().GetCreatures("");
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
        creatureTableWidth = searchResults->width();

        connect(searchResults, &QTableWidget::cellActivated, this, &MainWindow::onCreatureSelect);
    }
    {
        workTabs = new WorkTabs(workTabs);
        splitter->addWidget(workTabs);
    }
    splitter->setSizes(QList<int>{(int)(creatureTableWidth*1.5), rec.width()-creatureTableWidth});
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

    std::vector<Creature*> ret = Cache::Get().GetCreatures(currentDisplayedSearch);
    SetRows(ret);
}

void MainWindow::onCreatureSelect(int row, int)
{
    QWidget* newTab = new QWidget();
    bool ok;
    unsigned int entry = searchResults->item(row, 0)->text().toUInt(&ok);
    if(!ok){
        Warnings::Warning("Unable to read entry from selected collumn");
        return;
    }
    workTabs->addTab(entry);
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
