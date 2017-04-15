#include "worktabs.h"
#include "warnings.h"

WorkTabs::WorkTabs(QWidget *parent) :
    QTabWidget(parent)
{
    setTabsClosable(true);

    connect(this, &QTabWidget::tabCloseRequested, this, &WorkTabs::onTabCloseRequest);
}

void WorkTabs::onTabCloseRequest(int idx)
{
    QString yes = "Yes";
    QString ret = Warnings::confirmBox(QString("Close %1?").arg(tabText(idx)),
                             QStringList{yes, "Cancel"}, this);
    if(ret == yes) {
        removeTab(idx);
    }
}
