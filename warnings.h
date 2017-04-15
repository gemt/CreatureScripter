#ifndef WARNINGS_H
#define WARNINGS_H

#include <QMessageBox>
#include <QDebug>

static void Warning(const QString& warn)
{
    qDebug() << warn;
    QMessageBox msgBox;
    msgBox.setText(warn);
    msgBox.setIcon(QMessageBox::Icon::Warning);
    msgBox.exec();
}

#endif // WARNINGS_H
