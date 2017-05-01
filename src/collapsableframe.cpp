
#include "collapsableframe.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
CollapsibleFrame::CollapsibleFrame(QString headerText, QWidget *parent)
    :QWidget(parent),
      _w(nullptr)
{
    l = new QVBoxLayout(this);
    setLayout(l);
    btn = new QPushButton(headerText);
    //btn->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    l->addWidget(btn,0,Qt::AlignTop|Qt::AlignLeft);
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    //l->setSizeConstraint(QLayout::SetFixedSize);
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
