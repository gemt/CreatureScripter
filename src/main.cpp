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
#include "dbconnectionsettings.h"
#include "eventaidef.h"

#include "MainForm.h"

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

bool CheckConnectionSettings(MainWindow& mw)
{
    QSettings settings;
    if(!settings.contains("worldDB"))
    {
        // First time startup
        DBConnectionSettings dbSettings(&mw);
        return dbSettings.exec() == QDialog::Accepted;
    }else{
        if(!Cache::Get().Connect()){
            DBConnectionSettings dbSettings(&mw);
            return dbSettings.exec() == QDialog::Accepted;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetStyle();
    SetAppInfo();
    MainWindow w;
    w.show();

    QDialog* d = new QDialog();
    QHBoxLayout* l = new QHBoxLayout(d);
    d->setLayout(l);
    l->addWidget(new MainForm());
    d->exec();
    try {
        EventAI::EventAIStorage::Get();
    }catch(std::exception& e){
        Warnings::Warning(e.what(), QMessageBox::Critical);
    }

    if(!CheckConnectionSettings(w)){
        return 1;
    }
    w.InitWindow();

    return a.exec();
}
