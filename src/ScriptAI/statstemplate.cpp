#include "statstemplate.h"
#include "tables.h"
#include "creaturetemplatedef.h"
#include "flagswidget.h"
#include "defaultlineedit.h"
#include "typevaluewidget.h"
#include "stringwidget.h"


#include <QSharedPointer>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>

StatsTemplate::StatsTemplate(std::shared_ptr<Tables::creature_template> _creature, QWidget *parent) :
    QWidget(parent), _creature(_creature)
{
    using namespace Tables;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);
    QLineEdit* filterLineEdit = new QLineEdit(this);
    formLayout->addRow("Filter", filterLineEdit);
    connect(filterLineEdit, &QLineEdit::textChanged, this, &StatsTemplate::onFilterChanged);

    const QVector<TableTypeValue>&  fields = CreatureTemplateDef::Get().FieldTypes();

    table = new QTableWidget(fields.size(), 2, this);
    mainLayout->addWidget(table);

    QWidget* w = nullptr;
    int row = 0;
    foreach(const TableTypeValue& field, fields){
        _creature->record.value(field._field);
        table->setItem(row, 0, new QTableWidgetItem(field.name));
        switch(field._type){
        case UNASSIGNED:
            Q_ASSERT(field.values.isEmpty());
            w = new DefaultLineEdit(_creature->record, field._field, field.tooltip, this);
            break;
        case CONSTANT:
            w = new QLabel(_creature->record.value(field._field).toString(), this);
            break;
        case DROPDOWN_WIDGET:
            w = new TypeValueWidget(field.values, _creature->record, field._field, this);
            break;
        case FLAGS_WIDGET:
            w = new FlagsWidget(field.values, _creature->record, field._field, this, false);
            break;
        case NUMBER_WIDGET:
            Q_ASSERT(field.values.isEmpty());
            w = new DefaultLineEdit(_creature->record, field._field, field.tooltip, this);
            break;
        case STRING_VALUE_DROPDOWN:
            w = new StringWidget(_creature->record, field._field, field.tooltip, this);
            break;
        }
        table->setCellWidget(row, 1, w);
        row++;
    }
    table->setHorizontalHeaderLabels(QStringList{"Field", "Value"});
    table->verticalHeader()->setHidden(true);
    table->resizeColumnsToContents();
}

void StatsTemplate::onFilterChanged(const QString &filt)
{
    QString filtLower = filt.toLower();
    for(int i = 0; i < table->rowCount(); i++){
        if(table->item(i, 0)->text().toLower().contains(filtLower)){
            table->setRowHidden(i, false);
        }else{
            table->setRowHidden(i, true);
        }
    }
}
