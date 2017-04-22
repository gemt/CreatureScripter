#ifndef TEMPLATETABLES_H
#define TEMPLATETABLES_H

#include <QWidget>

class TemplateTables : public QWidget
{
    Q_OBJECT
public:
    explicit TemplateTables(QWidget *parent = 0);


public slots:
    void onTextChange(const QString& s);

private:
};

#endif // TEMPLATETABLES_H
