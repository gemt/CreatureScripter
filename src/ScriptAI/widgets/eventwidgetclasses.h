#ifndef EVENTWIDGETCLASSES_H
#define EVENTWIDGETCLASSES_H
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlRecord>

namespace EventAI{
class type_EventType : public QComboBox {
public:
    type_EventType(int  currType);
};
class type_ActionType : public QComboBox {
public:
    type_ActionType(int currType);
};

}

#endif // EVENTWIDGETCLASSES_H
