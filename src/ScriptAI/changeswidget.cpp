#include "changeswidget.h"
#include "tables.h"
#include "mangosrecord.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlField>
#include <QSqlDriver>
#include <QLabel>
ChangesWidget::ChangesWidget(QWidget *parent, std::shared_ptr<Tables::creature_template> _creature)
    :QWidget(parent)
{
    l = new QVBoxLayout(this);

    //textEdit = new QTextEdit(this);
    //textEdit->setReadOnly(true);
    //l->addWidget(textEdit);


    using namespace Tables;
    connect(&_creature->record, &MangosRecord::valueChanged, this, &ChangesWidget::ValueChanged);
    foreach(const MangosRecord& r, _creature->scripts->records){
        connect(&r, &MangosRecord::valueChanged, this, &ChangesWidget::ValueChanged);
    }
}

void ChangesWidget::ValueChanged(MangosRecord rec)
{
    QSqlDatabase db = Cache::Get().GetDB();
    Q_ASSERT(rec.editable.count() == rec.original.count());
    QVariant pkV = rec.original.value(rec.pk);
    QSqlField pkf;
    pkf.setValue(pkV);
    pkf.setType(pkV.type());


    QString updates;
    for(int i = 0; i < rec.editable.count(); i++){
        if(rec.editable.value(i) == rec.original.value(i))
            continue;

        QVariant vVal = rec.editable.value(i);
        QSqlField f;
        f.setValue(vVal);
        f.setType(vVal.type());
        if(!updates.isEmpty()){
            updates += ",";
        }
        updates += db.driver()->escapeIdentifier(rec.editable.fieldName(i), QSqlDriver::FieldName)
                + "=" + db.driver()->formatValue(f);
    }

    QString escaped_name = db.driver()->escapeIdentifier(rec.table, QSqlDriver::TableName);
    QString escaped_pk = db.driver()->escapeIdentifier(rec.pk, QSqlDriver::FieldName);
    QString escaped_pkv = db.driver()->formatValue(pkf);
    QString change_identifier = QString("%1,%2=%3").arg(escaped_name,escaped_pk,escaped_pkv);

    auto it = changes.find(change_identifier);
    if(updates.isEmpty()){
        // if there's no changes it must mean previous changes was reverted,
        // and the change must be registered in changes map
        Q_ASSERT(it != changes.end());
        QWidget* w = it.value();
        changes.erase(it);
        l->removeWidget(w);
        w->deleteLater();
    }
    else{
        QString updateStr = QString("UPDATE %1 SET %2 WHERE %3=%4;\n")
                .arg(escaped_name)
                .arg(updates)
                .arg(escaped_pk)
                .arg(escaped_pkv);
        if(it == changes.end()){
            QLabel* lbl = new QLabel(updateStr, this);
            lbl->setWordWrap(true);
            l->addWidget(lbl);
            changes[change_identifier] = lbl;
        }else{
            QLabel* lbl = static_cast<QLabel*>(it.value());
            lbl->setWordWrap(true);
            lbl->setText(updateStr);
        }
    }
}
