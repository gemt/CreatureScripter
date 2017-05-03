
#include "collapsableframe.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
CollapsibleFrame::CollapsibleFrame(QString headerText, QWidget *parent)
    :QWidget(parent),
      _w(nullptr)
{
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    //l->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);

    setLayout(l);
    btn = new QPushButton(headerText);
    l->addWidget(btn,0,Qt::AlignTop|Qt::AlignLeft);
}

void CollapsibleFrame::SetWidget(QWidget *w)
{
    Q_ASSERT(!_w);
    l->addWidget(w, 0,Qt::AlignTop|Qt::AlignLeft);
    _w = w;
    connect(btn, &QPushButton::clicked, [this](){
        _w->setHidden(!_w->isHidden());
        adjustSize();
        parentWidget()->adjustSize();
    });
}
