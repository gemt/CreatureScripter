#ifndef SPELLIDWIDGET_H
#define SPELLIDWIDGET_H

#include <QWidget>
#include <QSqlRecord>

class QLabel;
class QPushButton;
class SpellIDWidget : public QWidget
{
public:
    SpellIDWidget(QSqlRecord& r, int idx, QWidget* parent = nullptr);

private slots:
    void onChangeSpellBtn();

private:
    QSqlRecord& record;
    int rIdx;
    QLabel* idLabel;
    QLabel* nameLabel;
    QPushButton* changeButton;

    void PopulateInfoFromDBC();

};

#endif // SPELLIDWIDGET_H
