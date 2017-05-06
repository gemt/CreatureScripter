#include "changeswidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

ChangesWidget::ChangesWidget(QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout* l = new QVBoxLayout(this);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    l->addWidget(textEdit);

}
