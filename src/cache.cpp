#include "cache.h"
#include "creature.h"
#include "warnings.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlRecord>
#include <QStandardItem>
#include <QSqlDriver>
#include <QSqlField>
#include <QFile>
#include <QWindow>

QString Cache::MapName(unsigned int entry)
{
    return maps.value(entry, "Unknown map");
}

Cache::Cache(){
    QFile templateFile(":/css/QSpellWork/QSW/plugins/spellinfo/pre-tbc/pre-tbc.html");
    if (templateFile.open(QFile::ReadOnly)) {
        m_templateHtml = templateFile.readAll();
        templateFile.close();
    }
    QFile styleFile(":/css/QSpellWork/QSW/plugins/spellinfo/pre-tbc/pre-tbc.css");
    if (styleFile.open(QFile::ReadOnly)) {
        m_styleCss = styleFile.readAll();
        styleFile.close();
    }
}

QString Cache::Table(const QString& table) const{
    QSettings settings;
    return QString("%1.%2").arg(settings.value("worldDB").toString(), table);
}

QSqlDatabase Cache::GetDB()
{
    return QSqlDatabase::database(settings.value("connectionName").toString(), false);
}

bool Cache::Connect()
{
    qDebug() << "Connecting to database:";
    qDebug() << "connectionName:" << settings.value("connectionName").toString();
    qDebug() << "Hostname: " << settings.value("hostName").toString();
    qDebug() << "port: "     << settings.value("port").toInt();
    qDebug() << "username: "  << settings.value("username").toString();
    qDebug() << "password: "  << settings.value("password").toString();
    qDebug() << "dbName: "      << settings.value("worldDB").toString();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", settings.value("connectionName").toString());
    db.setHostName(settings.value("hostName").toString());
    db.setPort(settings.value("port").toInt());
    db.setDatabaseName(settings.value("worldDB").toString());
    db.setUserName(settings.value("username").toString());
    db.setPassword(settings.value("password").toString());
    qDebug() << settings.value("password").toString();
    bool ok = db.open();
    if(!ok)
    {
        Warnings::Warning(db.lastError().text());
        return false;
    }
    try{
        Cache::Get();
        Cache::Get().LoadMaps();

    }catch(std::exception& e){
        Warnings::Warning(e.what());
        return false;
    }
    return true;
}

bool Cache::isConnected()
{
    QSqlDatabase db = GetDB();
    return db.isOpen() && db.isValid();
}

void Cache::LoadMaps()
{
    static bool loaded = false;
    if(loaded) throw std::logic_error("Cache::LoadMaps called twize");
    else loaded = true;

    QSqlDatabase db = GetDB();
    if(!db.isOpen()){
        throw std::logic_error("Database connection not open");
    }
    QSqlQuery q(db);
    QString qry = QString("SELECT %1, %2 FROM %3").arg(
                db.driver()->escapeIdentifier(Tables::map_template::entry, QSqlDriver::FieldName),
                db.driver()->escapeIdentifier(Tables::map_template::mapname, QSqlDriver::FieldName),
                db.driver()->escapeIdentifier(Tables::worldTable<Tables::map_template>(), QSqlDriver::TableName));
    bool ret = q.exec(qry);
    int entryField = q.record().indexOf(Tables::map_template::entry);
    int nameField = q.record().indexOf(Tables::map_template::mapname);
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }

    while(q.next()){
        QString n = q.value(nameField).toString();//.toLower();
        unsigned int e = q.value(entryField).toUInt();
        maps[e] = n;
        map_vec.push_back(std::make_pair(e,n));
    }
}

const QVector<std::pair<unsigned int, QString> > &Cache::GetMapVec()
{
    return map_vec;
}

const QMap<unsigned int, QString> &Cache::GetMapMap()
{
    return maps;
}
