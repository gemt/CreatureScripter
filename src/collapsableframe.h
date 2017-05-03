#ifndef COLLAPSABLEFRAME_H
#define COLLAPSABLEFRAME_H

#include <QWidget>
#include <QFrame>
class QVBoxLayout;
class QPushButton;
class CollapsibleFrame : public QFrame
{
    Q_OBJECT
private:
    QVBoxLayout* l;
    QPushButton* btn;
    QWidget* _w;
public:
    CollapsibleFrame(const QString& buttonText, const QString& labelText, QWidget *parent);
    void SetWidget(QWidget* w);

};

#endif // COLLAPSABLEFRAME_H
