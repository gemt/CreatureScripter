#include "mainwindow.h"
#include "warnings.h"
#include "worktabs.h"
#include "cache.h"
#include "dbconnectionsettings.h"
#include "timer.h"
#include "creaturesearcher.h"

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
#include <QMenuBar>
#include <QIcon>


#define QT_DEBUG_PLUGINS



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentDisplayedSearch("-@g17h49j)=!ar676-&@jn0fgmq!`?=?ml&a1519&s36mc")
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    setCentralWidget(new QSplitter(Qt::Horizontal, this));
    QRect rec = QApplication::desktop()->screenGeometry();
    resize(rec.width()/2, rec.height()/2);

    nameSearchTimer.setSingleShot(true);
    connect(&nameSearchTimer, &QTimer::timeout, this, &MainWindow::onNameSearchTimeout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitWindow()
{
    QSplitter* splitter = static_cast<QSplitter*>(centralWidget());
    QWidget* searchWidget = new QWidget();
    splitter->addWidget(searchWidget);

    QVBoxLayout* bl = new QVBoxLayout(searchWidget);

    QFormLayout* sl = new QFormLayout();
    bl->addLayout(sl);
    nameSearch = new QLineEdit(searchWidget);
    connect(nameSearch, &QLineEdit::returnPressed, this, &MainWindow::onNameSearch);
    connect(nameSearch, &QLineEdit::textChanged, this, &MainWindow::onNameSearchChange);
    sl->addRow(new QLabel("Name/Entry"), nameSearch);

    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    searcher = new CreatureSearcher(searchWidget, db);
    bl->addWidget(searcher);

    workTabs = new WorkTabs(this);
    splitter->addWidget(workTabs);

    connect(searcher, &CreatureSearcher::entrySelected, workTabs, &WorkTabs::addTab);

    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1000);


    QMenu* menu = QMainWindow::menuBar()->addMenu("File");
    QAction* act = new QAction(QIcon(":/icons/ico/Data-Settings-48.png"), "DB Connection");
    connect(act, &QAction::triggered, [this](){
        DBConnectionSettings dbSettings(this);
        if(dbSettings.exec() == QDialog::Accepted){
            //todo: reconnect to db, i guess
        }
    });
    menu->addActions(QList<QAction*>{act});
}

void MainWindow::onNameSearch()
{
    onNameSearchTimeout();
}

void MainWindow::onNameSearchChange(const QString&)
{
    nameSearchTimer.start(100);
}

void MainWindow::onNameSearchTimeout()
{
    nameSearchTimer.stop();
    if(currentDisplayedSearch == nameSearch->text())
        return;
    currentDisplayedSearch = nameSearch->text();
    searcher->Search(currentDisplayedSearch);
}
