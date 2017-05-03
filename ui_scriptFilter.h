/********************************************************************************
** Form generated from reading UI file 'scriptFilter.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPTFILTER_H
#define UI_SCRIPTFILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "scriptedit.h"

QT_BEGIN_NAMESPACE

class Ui_scriptFilter
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QListView *listView;
    QPushButton *buttonAdd;
    QPushButton *buttonClear;
    QPushButton *buttonRemove;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    ScriptEdit *scriptEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *scriptFilter)
    {
        if (scriptFilter->objectName().isEmpty())
            scriptFilter->setObjectName(QStringLiteral("scriptFilter"));
        scriptFilter->resize(280, 570);
        gridLayout_2 = new QGridLayout(scriptFilter);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(0, 0, 6, 0);
        groupBox = new QGroupBox(scriptFilter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        listView = new QListView(groupBox);
        listView->setObjectName(QStringLiteral("listView"));

        gridLayout->addWidget(listView, 1, 0, 1, 5);

        buttonAdd = new QPushButton(groupBox);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));

        gridLayout->addWidget(buttonAdd, 0, 0, 1, 1);

        buttonClear = new QPushButton(groupBox);
        buttonClear->setObjectName(QStringLiteral("buttonClear"));

        gridLayout->addWidget(buttonClear, 0, 2, 1, 1);

        buttonRemove = new QPushButton(groupBox);
        buttonRemove->setObjectName(QStringLiteral("buttonRemove"));

        gridLayout->addWidget(buttonRemove, 0, 4, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 2);

        groupBox_2 = new QGroupBox(scriptFilter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scriptEdit = new ScriptEdit(groupBox_2);
        scriptEdit->setObjectName(QStringLiteral("scriptEdit"));
        scriptEdit->setAcceptRichText(false);

        gridLayout_3->addWidget(scriptEdit, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 2);

        pushButton = new QPushButton(scriptFilter);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);

        gridLayout_2->addWidget(pushButton, 2, 0, 1, 2);


        retranslateUi(scriptFilter);

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(scriptFilter);
    } // setupUi

    void retranslateUi(QWidget *scriptFilter)
    {
        scriptFilter->setWindowTitle(QApplication::translate("scriptFilter", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("scriptFilter", "Bookmarks", Q_NULLPTR));
        buttonAdd->setText(QApplication::translate("scriptFilter", "Add", Q_NULLPTR));
        buttonClear->setText(QApplication::translate("scriptFilter", "Remove", Q_NULLPTR));
        buttonRemove->setText(QApplication::translate("scriptFilter", "Clear", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("scriptFilter", "Script", Q_NULLPTR));
        pushButton->setText(QApplication::translate("scriptFilter", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class scriptFilter: public Ui_scriptFilter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPTFILTER_H
