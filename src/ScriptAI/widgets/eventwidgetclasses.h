#ifndef EVENTWIDGETCLASSES_H
#define EVENTWIDGETCLASSES_H
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlRecord>

namespace EventAI{
class type_EventType : public QComboBox{
public:
    type_EventType(int  currType);
};
class type_ActionType : public QComboBox{
public:
    type_ActionType(int currType);
};

class type_MS : public QSpinBox {
    QSqlRecord& r;
    int idx;
public:
    type_MS(QSqlRecord& r, int idx);
};

}

#endif // EVENTWIDGETCLASSES_H
