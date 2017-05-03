/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_main
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionFind;
    QAction *modeStandart;
    QAction *modeCompare;
    QAction *actionRegExp;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_4;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QTableView *SpellList;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_12;
    QFontComboBox *comboBox;
    QFontComboBox *comboBox_2;
    QFontComboBox *comboBox_3;
    QFontComboBox *comboBox_4;
    QFontComboBox *comboBox_5;
    QPushButton *adFilterButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_11;
    QLineEdit *findLine_e3;
    QLabel *findLine_l3;
    QLineEdit *findLine_e1;
    QLabel *findLine_l1;
    QWebEngineView *webView1;
    QWidget *page_2;
    QGridLayout *gridLayout_9;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *compareSpell_1;
    QLabel *slabel1;
    QWebEngineView *webView2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *slabel2;
    QLineEdit *compareSpell_2;
    QWebEngineView *webView3;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *main)
    {
        if (main->objectName().isEmpty())
            main->setObjectName(QStringLiteral("main"));
        main->resize(900, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(main->sizePolicy().hasHeightForWidth());
        main->setSizePolicy(sizePolicy);
        main->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qsw/resources/mangos.ico"), QSize(), QIcon::Normal, QIcon::Off);
        main->setWindowIcon(icon);
        main->setDocumentMode(false);
        main->setDockNestingEnabled(false);
        main->setUnifiedTitleAndToolBarOnMac(false);
        actionExit = new QAction(main);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setCheckable(false);
        actionExit->setVisible(true);
        actionExit->setIconVisibleInMenu(false);
        actionAbout = new QAction(main);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionFind = new QAction(main);
        actionFind->setObjectName(QStringLiteral("actionFind"));
        actionFind->setCheckable(true);
        actionFind->setVisible(true);
        modeStandart = new QAction(main);
        modeStandart->setObjectName(QStringLiteral("modeStandart"));
        modeStandart->setCheckable(true);
        modeStandart->setChecked(true);
        modeCompare = new QAction(main);
        modeCompare->setObjectName(QStringLiteral("modeCompare"));
        modeCompare->setCheckable(true);
        actionRegExp = new QAction(main);
        actionRegExp->setObjectName(QStringLiteral("actionRegExp"));
        actionRegExp->setCheckable(true);
        centralWidget = new QWidget(main);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(9, -1, 9, -1);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_4 = new QGridLayout(page);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(page);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(280, 0));
        widget->setMaximumSize(QSize(280, 16777215));
        widget->setAutoFillBackground(true);
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        SpellList = new QTableView(widget);
        SpellList->setObjectName(QStringLiteral("SpellList"));
        sizePolicy.setHeightForWidth(SpellList->sizePolicy().hasHeightForWidth());
        SpellList->setSizePolicy(sizePolicy);
        SpellList->setMaximumSize(QSize(280, 16777215));
        SpellList->setSizeIncrement(QSize(0, 0));
        SpellList->setFocusPolicy(Qt::WheelFocus);
        SpellList->setContextMenuPolicy(Qt::ActionsContextMenu);
        SpellList->setAutoFillBackground(false);
        SpellList->setFrameShape(QFrame::StyledPanel);
        SpellList->setFrameShadow(QFrame::Sunken);
        SpellList->setLineWidth(1);
        SpellList->setMidLineWidth(0);
        SpellList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        SpellList->setAutoScroll(true);
        SpellList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        SpellList->setTabKeyNavigation(true);
        SpellList->setDragEnabled(true);
        SpellList->setDragDropMode(QAbstractItemView::DragOnly);
        SpellList->setAlternatingRowColors(false);
        SpellList->setSelectionMode(QAbstractItemView::SingleSelection);
        SpellList->setSelectionBehavior(QAbstractItemView::SelectRows);
        SpellList->setTextElideMode(Qt::ElideMiddle);
        SpellList->setShowGrid(true);
        SpellList->setGridStyle(Qt::SolidLine);
        SpellList->setSortingEnabled(true);
        SpellList->setWordWrap(false);
        SpellList->setCornerButtonEnabled(false);
        SpellList->horizontalHeader()->setDefaultSectionSize(40);
        SpellList->horizontalHeader()->setHighlightSections(false);
        SpellList->horizontalHeader()->setStretchLastSection(true);
        SpellList->verticalHeader()->setVisible(false);
        SpellList->verticalHeader()->setCascadingSectionResizes(false);
        SpellList->verticalHeader()->setDefaultSectionSize(17);
        SpellList->verticalHeader()->setMinimumSectionSize(17);

        gridLayout_5->addWidget(SpellList, 3, 1, 1, 1);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setMinimumSize(QSize(280, 130));
        groupBox_2->setMaximumSize(QSize(280, 16777215));
        gridLayout_13 = new QGridLayout(groupBox_2);
        gridLayout_13->setSpacing(0);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_13->setContentsMargins(5, 3, 5, 3);
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_12->setHorizontalSpacing(0);
        gridLayout_12->setVerticalSpacing(2);
        comboBox = new QFontComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 20));
        comboBox->setEditable(false);
        comboBox->setCurrentIndex(162);
        comboBox->setMaxVisibleItems(20);
        comboBox->setFrame(true);
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setPointSize(8);
        font.setStyleStrategy(QFont::PreferDefault);
        comboBox->setCurrentFont(font);

        gridLayout_12->addWidget(comboBox, 0, 0, 1, 1);

        comboBox_2 = new QFontComboBox(groupBox_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(0, 20));
        comboBox_2->setEditable(false);
        comboBox_2->setCurrentIndex(162);
        comboBox_2->setMaxVisibleItems(20);
        comboBox_2->setInsertPolicy(QComboBox::InsertAtBottom);
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font1.setPointSize(8);
        comboBox_2->setCurrentFont(font1);

        gridLayout_12->addWidget(comboBox_2, 1, 0, 1, 1);

        comboBox_3 = new QFontComboBox(groupBox_2);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setMinimumSize(QSize(0, 20));
        comboBox_3->setEditable(false);
        comboBox_3->setCurrentIndex(162);
        comboBox_3->setMaxVisibleItems(20);
        comboBox_3->setCurrentFont(font1);

        gridLayout_12->addWidget(comboBox_3, 2, 0, 1, 1);

        comboBox_4 = new QFontComboBox(groupBox_2);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        comboBox_4->setMinimumSize(QSize(0, 20));
        comboBox_4->setEditable(false);
        comboBox_4->setCurrentIndex(162);
        comboBox_4->setMaxVisibleItems(20);
        comboBox_4->setCurrentFont(font1);

        gridLayout_12->addWidget(comboBox_4, 3, 0, 1, 1);

        comboBox_5 = new QFontComboBox(groupBox_2);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));
        comboBox_5->setMinimumSize(QSize(0, 20));
        comboBox_5->setEditable(false);
        comboBox_5->setCurrentIndex(162);
        comboBox_5->setMaxVisibleItems(20);
        comboBox_5->setCurrentFont(font1);

        gridLayout_12->addWidget(comboBox_5, 4, 0, 1, 1);


        gridLayout_13->addLayout(gridLayout_12, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 1, 1, 1, 1);

        adFilterButton = new QPushButton(widget);
        adFilterButton->setObjectName(QStringLiteral("adFilterButton"));
        adFilterButton->setAutoFillBackground(false);
        adFilterButton->setCheckable(true);
        adFilterButton->setChecked(false);
        adFilterButton->setFlat(false);

        gridLayout_5->addWidget(adFilterButton, 2, 1, 1, 1);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(280, 65));
        groupBox->setMaximumSize(QSize(280, 16777215));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_14 = new QGridLayout(groupBox);
        gridLayout_14->setSpacing(0);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_14->setContentsMargins(5, 3, 5, 3);
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setHorizontalSpacing(6);
        gridLayout_11->setVerticalSpacing(2);
        findLine_e3 = new QLineEdit(groupBox);
        findLine_e3->setObjectName(QStringLiteral("findLine_e3"));

        gridLayout_11->addWidget(findLine_e3, 1, 1, 1, 1);

        findLine_l3 = new QLabel(groupBox);
        findLine_l3->setObjectName(QStringLiteral("findLine_l3"));

        gridLayout_11->addWidget(findLine_l3, 1, 0, 1, 1);

        findLine_e1 = new QLineEdit(groupBox);
        findLine_e1->setObjectName(QStringLiteral("findLine_e1"));
        findLine_e1->setMinimumSize(QSize(0, 0));
        findLine_e1->setFrame(true);
        findLine_e1->setCursorPosition(0);

        gridLayout_11->addWidget(findLine_e1, 0, 1, 1, 1);

        findLine_l1 = new QLabel(groupBox);
        findLine_l1->setObjectName(QStringLiteral("findLine_l1"));

        gridLayout_11->addWidget(findLine_l1, 0, 0, 1, 1);


        gridLayout_14->addLayout(gridLayout_11, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 1, 1, 1);


        gridLayout_4->addWidget(widget, 0, 0, 2, 1);

        webView1 = new QWebEngineView(page);
        webView1->setObjectName(QStringLiteral("webView1"));
        webView1->setFocusPolicy(Qt::NoFocus);
        webView1->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(webView1, 0, 1, 2, 1);

        stackedWidget->addWidget(page);
        webView1->raise();
        widget->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        sizePolicy.setHeightForWidth(page_2->sizePolicy().hasHeightForWidth());
        page_2->setSizePolicy(sizePolicy);
        gridLayout_9 = new QGridLayout(page_2);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(page_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setMaximumSize(QSize(16777215, 16777215));
        splitter->setBaseSize(QSize(0, 0));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setMidLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(5);
        splitter->setChildrenCollapsible(true);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        compareSpell_1 = new QLineEdit(layoutWidget);
        compareSpell_1->setObjectName(QStringLiteral("compareSpell_1"));

        gridLayout->addWidget(compareSpell_1, 0, 1, 1, 1);

        slabel1 = new QLabel(layoutWidget);
        slabel1->setObjectName(QStringLiteral("slabel1"));

        gridLayout->addWidget(slabel1, 0, 0, 1, 1);

        webView2 = new QWebEngineView(layoutWidget);
        webView2->setObjectName(QStringLiteral("webView2"));

        gridLayout->addWidget(webView2, 1, 0, 1, 2);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        slabel2 = new QLabel(layoutWidget1);
        slabel2->setObjectName(QStringLiteral("slabel2"));

        gridLayout_2->addWidget(slabel2, 0, 0, 1, 1);

        compareSpell_2 = new QLineEdit(layoutWidget1);
        compareSpell_2->setObjectName(QStringLiteral("compareSpell_2"));

        gridLayout_2->addWidget(compareSpell_2, 0, 1, 1, 1);

        webView3 = new QWebEngineView(layoutWidget1);
        webView3->setObjectName(QStringLiteral("webView3"));

        gridLayout_2->addWidget(webView3, 1, 0, 1, 2);

        splitter->addWidget(layoutWidget1);

        gridLayout_9->addWidget(splitter, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);

        main->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(main);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setAcceptDrops(true);
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setFloatable(true);
        main->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(main);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(main);
    } // setupUi

    void retranslateUi(QMainWindow* main)
    {
        main->setWindowTitle(QApplication::translate("main", "QSW - Qt SpellWork for 1.12.x", Q_NULLPTR));
        actionExit->setText(QApplication::translate("main", "Exit", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("main", "About...", Q_NULLPTR));
        actionFind->setText(QApplication::translate("main", "Find", Q_NULLPTR));
        actionFind->setShortcut(QApplication::translate("main", "Return", Q_NULLPTR));
        modeStandart->setText(QApplication::translate("main", "Standart", Q_NULLPTR));
        modeCompare->setText(QApplication::translate("main", "Compare", Q_NULLPTR));
        actionRegExp->setText(QApplication::translate("main", "Use RegExp", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("main", "Fast Filter", Q_NULLPTR));
        adFilterButton->setText(QApplication::translate("main", "Scripted filter >>", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("main", "Search", Q_NULLPTR));
        findLine_l3->setText(QApplication::translate("main", "Description:", Q_NULLPTR));
        findLine_l1->setText(QApplication::translate("main", "Id or Name:", Q_NULLPTR));
        slabel1->setText(QApplication::translate("main", "Spell Id 1:", Q_NULLPTR));
        slabel2->setText(QApplication::translate("main", "Spell Id 2:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class main: public Ui_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
