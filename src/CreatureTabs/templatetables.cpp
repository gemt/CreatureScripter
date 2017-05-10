#include "templatetables.h"
#include "tables.h"
#include "mangosrecord.h"
#include "stringwidget.h"

#include <QVector>
#include <QLineEdit>
#include <QSqlRecord>
#include <QSqlField>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

TemplateTables::TemplateTables(std::shared_ptr<Tables::creature_template> _creature, QWidget *parent) :
    QWidget(parent), _creature(_creature)
{
    using namespace Tables;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);
    QLineEdit* filterLineEdit = new QLineEdit(this);
    formLayout->addRow("Filter", filterLineEdit);
    connect(filterLineEdit, &QLineEdit::textChanged, this, &TemplateTables::onFilterChanged);

    table = new QTableWidget(0, 2, this);
    mainLayout->addWidget(table);
    table->setHorizontalHeaderLabels(QStringList{"Field", "Value"});
    table->verticalHeader()->setHidden(true);

    _creature->record.count();

    InsertTable(_creature->record);
    InsertTable(_creature->equipment->record);
    InsertTable(_creature->template_addon->record);
    for(int i = 0; i < creature_template::MAX_MODEL_INFO; i++){
        InsertTable(_creature->model_info[i]->record);
    }
    table->resizeColumnsToContents();
}

void TemplateTables::onFilterChanged(const QString &filt)
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

void TemplateTables::InsertTable(MangosRecord &r)
{
    for(int i = 0; i < r.count(); i++){
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(r.table+"."+r.fieldName(i)));
        table->setCellWidget(table->rowCount()-1, 1, new StringWidget(r, r.fieldName(i), "", this));
    }
}
