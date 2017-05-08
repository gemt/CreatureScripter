#include "mainwindow.h"
#include "warnings.h"
#include "worktabs.h"
#include "cache.h"
#include "dbconnectionsettings.h"
#include "timer.h"
#include "creaturesearcher.h"
#include "SettingsForm.h"
#include "qswwrapper.h"
#include "spellwork.h"

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
#include <QCloseEvent>
#include <QWidgetAction>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QCheckBox>

#define QT_DEBUG_PLUGINS



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentDisplayedSearch("-@g17h49j)=!ar676-&@jn0fgmq!`?=?ml&a1519&s36mc"),
      currentDIsplayedMapSearch("-@g17h49j)=!ar676-&@jn0fgmq!`?=?ml&a1519&s36mc")
{
    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    setCentralWidget(new QSplitter(Qt::Horizontal, this));
    QRect rec = QApplication::desktop()->screenGeometry();
    resize(rec.width()/2, rec.height()/2);

    nameSearchTimer.setSingleShot(true);
    connect(&nameSearchTimer, &QTimer::timeout, this, &MainWindow::onNameSearchTimeout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitWindow(LoadingScreen& ls)
{
    QSplitter* splitter = static_cast<QSplitter*>(centralWidget());
    QWidget* searchWidget = new QWidget();
    splitter->addWidget(searchWidget);

    QVBoxLayout* bl = new QVBoxLayout(searchWidget);

    QFormLayout* sl = new QFormLayout();
    bl->addLayout(sl);
    nameEntrySearch = new QLineEdit(searchWidget);
    //connect(nameEntrySearch, &QLineEdit::returnPressed, this, &MainWindow::onNameSearch);
    connect(nameEntrySearch, &QLineEdit::textChanged, this, &MainWindow::onNameSearchChange);
    sl->addRow(new QLabel("Name/Entry"), nameEntrySearch);

    mapSearch = new QLineEdit(searchWidget);
    sl->addRow(new QLabel("Map"), mapSearch);

    QCheckBox* onlyEventAICheckbox = new QCheckBox(this);
    sl->addRow("Only EventAI", onlyEventAICheckbox);
    onlyEventAICheckbox->setChecked(false);


    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    searcher = new CreatureSearcher(searchWidget, db, ls);
    bl->addWidget(searcher);
    connect(onlyEventAICheckbox, &QCheckBox::stateChanged, [this](int state){
        searcher->OnlyEventAI(state == Qt::Checked);
    });

    connect(mapSearch, &QLineEdit::textChanged, this, &MainWindow::onNameSearchChange);

    workTabs = new WorkTabs(this);
    splitter->addWidget(workTabs);

    connect(searcher, &CreatureSearcher::entrySelected, workTabs, &WorkTabs::addTab);

    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1000);
    splitter->setContentsMargins(0,0,0,0);

    ls.SetMessage("Initializing QSpellWorks");
    QSWWrapper::Get().qsw;

    QMenu* menu = QMainWindow::menuBar()->addMenu("Database");
    QAction* dbAct = new QAction(QIcon(":/icons/ico/Data-Settings-48.png"), "Connection Settings");
    connect(dbAct, &QAction::triggered, [this](){
        DBConnectionSettings dbSettings(this);
        if(dbSettings.exec() == QDialog::Accepted){
            //todo: reconnect to db, i guess
        }
    });

    QMainWindow::menuBar()->addSeparator();

    QAction* qswAct = new QAction(QIcon(":/icons/ico/Data-Settings-48.png"), "QSW Directories");
    connect(qswAct , &QAction::triggered, [this](){
        SettingsForm s(this);
        if(s.exec() == QDialog::Accepted){
            //todo: reconnect to db, i guess
        }
    });
    menu->addActions(QList<QAction*>{dbAct});

    QMenu* qswMenu = QMainWindow::menuBar()->addMenu("QSW");
    QAction* qswShowHide = new QAction("Toggle show/hide");
    connect(qswShowHide , &QAction::triggered, [this](){
        QSWWrapper::Get().setHidden(!QSWWrapper::Get().isHidden());
    });
    qswMenu->addAction(qswShowHide);
    connect(qswMenu->addAction("Directories"), &QAction::triggered, QSWWrapper::Get().qsw, &MainForm::slotSettings);
    connect(qswMenu->addAction("About QSW"), &QAction::triggered, QSWWrapper::Get().qsw, &MainForm::slotAbout);


    QMenu* pluginMenu = QMainWindow::menuBar()->addMenu("QSW Plugins");
    SpellInfoPlugins plugins = QSWWrapper::Get().qsw->m_sw->getPlugins();
    QButtonGroup* pluginGroup = new QButtonGroup(pluginMenu);
    pluginGroup->setExclusive(true);

    QString start_plugin = Cache::Get().settings.value("active-qsw-plugin", "pre-tbc").toString();
    for (SpellInfoPlugins::iterator itr = plugins.begin(); itr != plugins.end(); ++itr)
    {
        QString plugin_key = itr.key();
        QString plugin_name = itr.value().first.value("fullName").toString();
        QRadioButton *btn = new QRadioButton(plugin_name, pluginMenu);
        pluginGroup->addButton(btn);
        QWidgetAction* qwa= new QWidgetAction(pluginMenu);
        qwa->setDefaultWidget(btn);
        pluginMenu->addAction(qwa);
        qwa->setData(plugin_key);

        btn->setChecked(plugin_key == start_plugin);
        connect(btn, &QRadioButton::toggled, this, [this, qwa](bool checked){
            if(checked){
                QString plugin_name = qwa->data().toString();
                QSWWrapper::Get().qsw->m_sw->setActivePlugin(plugin_name);
                Cache::Get().settings.setValue("active-qsw-plugin", plugin_name);
            }
        });
    }
    QSWWrapper::Get().qsw->m_sw->setActivePlugin(start_plugin, &ls);
}

void MainWindow::onNameSearch()
{
    onNameSearchTimeout();
}

void MainWindow::onNameSearchChange(const QString&)
{
    //if query ends up slow it's possible to set this to something higher
    // so we don't do a new search for every keypress in the searchfield
    nameSearchTimer.start(100);
}

void MainWindow::onNameSearchTimeout()
{
    nameSearchTimer.stop();
    if(currentDisplayedSearch != nameEntrySearch->text()){
        currentDisplayedSearch = nameEntrySearch->text();
        searcher->Search(currentDisplayedSearch);
    }
    if(currentDIsplayedMapSearch != mapSearch->text()){
        currentDIsplayedMapSearch = mapSearch->text();
        searcher->SetZoneFilter(currentDIsplayedMapSearch);
    }
        return;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn =
            QMessageBox::question( this, "Close",
            tr("Are you sure?\n"),
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
        }
}
