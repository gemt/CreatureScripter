#ifndef WORKTABS_H
#define WORKTABS_H

#include <QTabWidget>

class WorkTabs : public QTabWidget
{
public:
    WorkTabs(QWidget *parent);

private slots:
    void onTabCloseRequest(int);
};

#endif // WORKTABS_H
