#ifndef SPELLIDWIDGET_H
#define SPELLIDWIDGET_H

#include "eventaidef.h"

#include <QWidget>
#include <QSqlRecord>
#include <QLabel>

class QLabel;
class QPushButton;

class SpellIDWidget : public QWidget
{
    Q_OBJECT
public:
    SpellIDWidget(QSqlRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private slots:
    void onChangeSpellBtn();

private:
    QSqlRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* iconLabel;

    void UpdateInfo();
};

#endif // SPELLIDWIDGET_H
