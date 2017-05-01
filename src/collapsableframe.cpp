
#include "collapsableframe.h"
#include <QVBoxLayout>
#include <QPushButton>

CollapsibleFrame::CollapsibleFrame(QString headerText, QWidget *parent)
    :QWidget(parent),
      _w(nullptr),
      _hidden(false)
{
    l = new QVBoxLayout(this);
    setLayout(l);
    btn = new QPushButton(headerText);
    btn->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    l->addWidget(btn,0,Qt::AlignTop|Qt::AlignLeft);
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

}

void CollapsibleFrame::SetWidget(QWidget *w)
{
    Q_ASSERT(!_w);
    l->addWidget(w, 0,Qt::AlignTop|Qt::AlignLeft);
    _w = w;
    connect(btn, &QPushButton::clicked, [this](){
        if(_hidden){
            _hidden = false;
            qDebug() << _height;
            _w->resize(_w->width(),_height);
        }else{
            _hidden = true;
            _height = _w->size().height();
            qDebug() << _height;
            _w->resize(_w->width(),0);
        }
        adjustSize();
        return;
        _w->isHidden() ? _w->show() : _w->hide();
        parentWidget()->layout()->invalidate();
        parentWidget()->layout()->activate();
    });
    adjustSize();
}
