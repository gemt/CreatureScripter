#include "creatureeventai.h"

#include "collapsableframe.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>

namespace EventAI
{

CollapsibleFrame::CollapsibleFrame(const QString& buttonText, const QString& labelText, QWidget *parent)
    :QFrame(parent),
      _w(nullptr)
{
    setObjectName("CollapsibleFrame");
    setStyleSheet("#CollapsibleFrame { border: 3px solid black; }");

    setContentsMargins(0,0,0,0);
    //setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    //setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    //setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    l = new QVBoxLayout(this);
    //l->setContentsMargins(0,0,0,0);
    setLayout(l);

    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0,0,0,0);
    l->addLayout(headerLayout);
    l->setAlignment(headerLayout, Qt::AlignLeft);
    btn = new QPushButton(buttonText, this);
    headerLayout->addWidget(btn,0,Qt::AlignTop|Qt::AlignLeft);

    QPushButton* verboseBtn = new QPushButton("Toggle verbose", this);
    headerLayout->addWidget(verboseBtn, 0, Qt::AlignTop|Qt::AlignLeft);

    QLabel* label = new QLabel(labelText, this);
    headerLayout->addWidget(label, 0, Qt::AlignTop|Qt::AlignLeft);
    //QPushButton* resetBtn = new QPushButton("Reset Changes");
    //headerLayout->addWidget(resetBtn, 0, Qt::AlignTop|Qt::AlignRight);


    connect(btn, &QPushButton::clicked, [this, verboseBtn](){
        Q_ASSERT(_w);
        _w->setHidden(!_w->isHidden());
        verboseBtn->setHidden(_w->isHidden());
        adjustSize();
        parentWidget()->adjustSize();
    });

    connect(verboseBtn, &QPushButton::clicked, [this](){
        Q_ASSERT(_w);
        _w->verbose = !_w->verbose;
        _w->DoRemake();
    });
}

void CollapsibleFrame::SetWidget(EventEntry *w)
{
    Q_ASSERT(!_w);
    l->addWidget(w, 0,Qt::AlignTop|Qt::AlignLeft);
    _w = w;
}

}
