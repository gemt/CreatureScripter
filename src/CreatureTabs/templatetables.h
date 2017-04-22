#ifndef TEMPLATETABLES_H
#define TEMPLATETABLES_H

#include <QWidget>
#include <QSqlRecord>

class TemplateTables : public QWidget
{
    Q_OBJECT
public:
    TemplateTables(const QVector<std::pair<const char*,QSqlRecord>>& records, QWidget *parent = 0);

public slots:
    void onTextChange(const QString& s);

private:
};

#endif // TEMPLATETABLES_H
