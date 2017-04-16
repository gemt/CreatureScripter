#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStyleFactory>
#include <QPalette>
#include "warnings.h"
#include "cache.h"
#include "creature.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
    darkPalette.setColor(QPalette::Highlight, QColor(18, 56, 94).light(200));
    qApp->setPalette(darkPalette);

    MainWindow w;
    w.show();

    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("gemt");
    QCoreApplication::setOrganizationDomain("github.com/gemt");
    QCoreApplication::setApplicationName("CreatureScripter");

    QSettings settings;
    settings.setValue("connectionName", QString("creature_script"));
    settings.setValue("hostName", "127.0.0.1");
    settings.setValue("port", 3306);
    settings.setValue("username", "root");
    settings.setValue("databaseName", "mangos");
    //settings.setValue("password", "");
    settings.setValue("worldDB", "mangos");

    qDebug() << "Connecting to database:";
    qDebug() << "connectionName:" << settings.value("connectionName").toStringList();
    qDebug() << "Hostname: " << settings.value("hostName").toString();
    qDebug() << "port: "     << settings.value("port").toInt();
    qDebug() << "dbName: "      << settings.value("databaseName").toString();
    qDebug() << "username: "  << settings.value("username").toString();
    qDebug() << "password: "  << settings.value("password").toString();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", settings.value("connectionName").toString());
    db.setHostName(settings.value("hostName").toString());
    db.setPort(settings.value("port").toInt());
    db.setDatabaseName(settings.value("databaseName").toString());
    db.setUserName(settings.value("username").toString());
    db.setPassword(settings.value("password").toString());
    bool ok = db.open();
    if(!ok)
    {
        Warnings::Warning("Unable to connect to db: " + db.lastError().text());    }

    try{
        Cache::Get();
        Cache::Get().LoadCreatures();
        Cache::Get().LoadSchemas();
        Cache::Get().LoadMaps();

    }catch(std::exception& e){
        Warnings::Warning(e.what());
        return 1;
    }
    w.InitWindow();
    return a.exec();
}
