#ifndef WARNINGS_H
#define WARNINGS_H

#include <QMessageBox>

class Warnings
{
public:
    static void Warning(QString warn,QMessageBox::Icon severity = QMessageBox::Warning);

    static QString confirmBox(const QString &text, const QStringList &opts, QWidget *parent);
};



#endif // WARNINGS_H
