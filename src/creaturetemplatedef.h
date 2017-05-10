#ifndef CREATURETEMPLATEDEF_H
#define CREATURETEMPLATEDEF_H

#include <QVector>
#include "eventaidefcommon.h"

enum WidgetType{
    UNASSIGNED = 0,
    CONSTANT = 1,
    DROPDOWN_WIDGET=2,
    FLAGS_WIDGET=3,
    NUMBER_WIDGET=4,
    STRING_VALUE_DROPDOWN = 5,
};

struct TableTypeValue{
public:
    const WidgetType _type;
    const QString _field;
    const QString name;
    const QString tooltip;
    const QVector<EventAI::TypeValue> values;
};

class CreatureTemplateDef
{
public:
    static CreatureTemplateDef& Get(){
        static CreatureTemplateDef* instance = nullptr;
        if(!instance)
            instance = new CreatureTemplateDef();
        return *instance;
    }

    const QVector<TableTypeValue>& FieldTypes();
private:
    CreatureTemplateDef();
    QVector<TableTypeValue> _fieldTypes;

    void Load();
};

#endif // CREATURETEMPLATEDEF_H
