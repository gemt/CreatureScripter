#include "warnings.h"
#include <QDebug>
#include <QPushButton>

void Warnings::Warning(QString warn, QMessageBox::Icon severity)
{
    qDebug() << warn;
    QMessageBox msgBox;
    msgBox.setText(warn);
    msgBox.setIcon(severity);
    msgBox.exec();
}

QString Warnings::confirmBox(const QString &text, const QStringList &opts, QWidget *parent)
{
    qDebug() << text << opts;
    QMessageBox msg(parent);
    msg.setText(text);
    foreach(const QString& s, opts){
        QPushButton* btn = new QPushButton(s);
        msg.addButton(btn, QMessageBox::ButtonRole::AcceptRole);
    }
    msg.exec();
    if(msg.clickedButton())
        return msg.clickedButton()->text();
    else
        return "";
}
