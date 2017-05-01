#ifndef COLLAPSABLEFRAME_H
#define COLLAPSABLEFRAME_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class CollapsibleFrame : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* l;
    QPushButton* btn;
    QWidget* _w;
public:
    CollapsibleFrame(QString headerText, QWidget *parent);
    void SetWidget(QWidget* w);

};

#endif // COLLAPSABLEFRAME_H
