#include "dbconnectionsettings.h"
#include "cache.h"
#include "warnings.h"

#include <QFormLayout>
#include <QSettings>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
DBConnectionSettings::DBConnectionSettings(QWidget *parent) :
    QDialog(parent)
{
    setToolTip("Connection Settings");
    QFormLayout* l = new QFormLayout(this);
    setLayout(l);

    QSettings settings;

    origConnectionName = settings.value("connectionName", "creature_scripter").toString();
    origHostName = settings.value("hostName", "127.0.0.1").toString();
    origPort = settings.value("port", "3306").toString();
    origWorldDB = settings.value("worldDB", "mangos").toString();
    origUsername = settings.value("username", "root").toString();
    origPassword = settings.value("password", "").toString();
    origMPQDir = settings.value("mpq-dir", "").toString();

    connection = new QLineEdit(origConnectionName, this);
    hostname = new QLineEdit(origHostName, this);
    port = new QLineEdit(origPort, this);
    worlddb = new QLineEdit(origWorldDB, this);
    username = new QLineEdit(origUsername, this);
    password = new QLineEdit(origPassword, this);
    mpqDir = new QLineEdit(origMPQDir, this);

    l->addRow("Connection Name", connection);
    l->addRow("Hostname", hostname);
    l->addRow("Port", port);
    l->addRow("Username", username);
    l->addRow("Password", password);
    l->addRow("World DB name", worlddb);
    l->addRow("MPQ Directory", mpqDir);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttons->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &QDialog::accept);

    connect(buttons->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &QDialog::reject);

    l->addWidget(buttons);
}

void DBConnectionSettings::done(int i)
{
    QSettings settings;
    if(i == Accepted){
        settings.setValue("connectionName", connection->text());
        settings.setValue("hostName", hostname->text());
        settings.setValue("port", port->text());
        settings.setValue("username", username->text());
        settings.setValue("password", password->text());
        settings.setValue("worldDB", worlddb->text());
        settings.setValue("mpq-dir", mpqDir->text());

        if(Cache::Get().isConnected()){
            Warnings::Warning("Restart the program to reconnect");
        }else{
            Cache::Get().Connect();
        }
    }else{
        settings.setValue("connectionName", origConnectionName);
        settings.setValue("hostName", origHostName);
        settings.setValue("port", origPort);
        settings.setValue("username", origUsername);
        settings.setValue("password", origPassword);
        settings.setValue("worldDB", origWorldDB);
        settings.setValue("mpq-dir", origMPQDir);
    }
    QDialog::done(i);
}
