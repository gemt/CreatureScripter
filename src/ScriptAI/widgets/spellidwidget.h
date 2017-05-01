#ifndef SPELLIDWIDGET_H
#define SPELLIDWIDGET_H

#include "eventaidef.h"

#include <QWidget>
#include <QSqlRecord>
#include <QLabel>

namespace Spell{
struct entry;
}
class QLabel;
class QPushButton;

class SpellIconWidget : public QLabel {
    Q_OBJECT
public:
    SpellIconWidget(const QImage& img, QWidget* parent);
signals:
    void spellIconClicked();
protected:
    void mouseDoubleClickEvent(QMouseEvent*);
};

class SpellIDWidget : public QWidget
{
    Q_OBJECT
public:
    SpellIDWidget(QSqlRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private slots:
    void onChangeSpellBtn();
    void onShowSpellDetails();

private:
    QSqlRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
    QLabel* idLabel;
    QLabel* nameLabel;
    SpellIconWidget* iconLabel;

    const Spell::entry* spellInfo;

};

#endif // SPELLIDWIDGET_H
