#include "mainwindow.h"
#include "warnings.h"
#include "cache.h"
#include "creature.h"
#include "dbconnectionsettings.h"
#include "eventaidef.h"
#include "loadingscreen.h"
#include "qswwrapper.h"
#include "creaturetemplatedef.h"

#include <QApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStyleFactory>
#include <QPalette>
#undef QT_NO_DEBUG_OUTPUT
void SetStyle()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(215,215,215));
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::Highlight, QColor(150, 156, 150));
    qApp->setPalette(darkPalette);
}

void SetAppInfo()
{
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("gemt");
    QCoreApplication::setOrganizationDomain("github.com/gemt");
    QCoreApplication::setApplicationName("CreatureScripter");
}

bool CheckConnectionSettings(MainWindow& mw, LoadingScreen& ls)
{
    QSettings settings;
    if(!settings.contains("worldDB"))
    {
        // First time startup
        ls.hide();
        DBConnectionSettings dbSettings(&mw);
        bool ok = dbSettings.exec() == QDialog::Accepted;
        ls.show();
        return ok;

    }else{
        if(!Cache::Get().Connect()){
            ls.hide();
            DBConnectionSettings dbSettings(&mw);
            bool ok = dbSettings.exec() == QDialog::Accepted;
            ls.show();
            return ok;
        }
    }
    return true;
}

#include <QtDebug>
#include <QApplication>
#include <QFile>
#include <QTextStream>



QFile file("Log.txt");
void logFileOut(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QTextStream out(&file);
    out << QTime::currentTime().toString("hh:mm:ss.zzz ");
    switch (type) {
        case QtDebugMsg:
            out << "DBG" << " (" << context.line << ")";
            break;
        case QtWarningMsg:
            out << "WRN" << " (" << context.line << ")";
            break;
        case QtCriticalMsg:
            out << "CRT" << " (" << context.line << ")";
            break;
        case QtFatalMsg:
            out << "FTL" << " (" << context.line << ")";
            break;
        case QtInfoMsg:
            out << "INF" << " (" << context.line << ")";
            break;
    }
    out << " " << msg << '\n';
    out.flush();
}


bool setup_logging(){
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        Warnings::Warning("Unable to create and open log file");
        return false;
    }
    qInstallMessageHandler(logFileOut);
    return true;
}



int main(int argc, char *argv[])
{
    setup_logging();
    QApplication a(argc, argv);
    LoadingScreen loadingScreen(nullptr);
    loadingScreen.raise();
    loadingScreen.show();
    a.processEvents();

    SetStyle();
    SetAppInfo();
    a.processEvents();

    MainWindow w;

    try {
        EventAI::EventAIStorage::Get();
    }catch(std::exception& e){
        Warnings::Warning(e.what(), QMessageBox::Critical);
    }
    try {
        CreatureTemplateDef::Get();
    }catch(std::exception& e){
        Warnings::Warning(e.what(), QMessageBox::Critical);
    }

    if(!CheckConnectionSettings(w, loadingScreen)){
        return 1;
    }

    w.InitWindow(loadingScreen);

    loadingScreen.finish(&w);
    w.show();
    return a.exec();
}
