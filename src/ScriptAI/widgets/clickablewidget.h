#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QWidget>

class ClickableWidget: public QWidget {
    Q_OBJECT
public:
    ClickableWidget(QWidget* parent=nullptr) :QWidget(parent) {}
    ClickableWidget(const ClickableWidget& other) {}
    virtual ~ClickableWidget(){}
    virtual void OnClicked(){}
};
Q_DECLARE_METATYPE(ClickableWidget)

#endif // CLICKABLEWIDGET_H
