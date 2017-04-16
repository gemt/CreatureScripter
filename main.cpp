#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "warnings.h"
#include "table.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const QString splitterSheetV =			\
    "QSplitter[orientation=\"2\"]::handle {	\
        border: 3px dashed black;			\
        margin: 1px 50px;					\
        min-height: 10px;					\
        max-height: 10px;					\
    }";
    a.setStyleSheet(splitterSheetV);
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
        CreatureCache::Get();
        CreatureCache::Get().LoadCreatures();
    }catch(std::exception& e){
        Warnings::Warning(e.what());
        return 1;
    }
    w.InitWindow();
    return a.exec();
}
