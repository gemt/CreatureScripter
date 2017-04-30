#ifndef SPELLIDWIDGET_H
#define SPELLIDWIDGET_H

#include <QWidget>
#include <QSqlRecord>
#include "eventaidef.h"

class QLabel;
class QPushButton;
class SpellIDWidget : public QWidget
{
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
    QPushButton* changeButton;

    void PopulateInfoFromDBC();

};

#endif // SPELLIDWIDGET_H
