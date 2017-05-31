#ifndef SPELLIDWIDGET_H
#define SPELLIDWIDGET_H

#include "eventaidef.h"
#include "clickablewidget.h"
#include "mangosrecord.h"

#include <QWidget>
#include <QSqlRecord>
#include <QLabel>

class QPushButton;

class SpellIDWidget : public ClickableWidget
{
    Q_OBJECT
public:
    SpellIDWidget(MangosRecord& r, const QString fieldName, const QString tooltip,  QWidget* parent = nullptr);

private slots:
    void onChangeSpellBtn();

private:
    MangosRecord& record;
    int rIdx;
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* iconLabel;

    void UpdateInfo();

    // ClickableWidget interface
public:
    void OnClicked() override;
};

#endif // SPELLIDWIDGET_H
