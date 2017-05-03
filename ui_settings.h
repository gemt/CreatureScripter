/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *dbcLable;
    QLabel *mpqLabel;
    QLineEdit *mpqDir;
    QPushButton *mpqButton;
    QLineEdit *dbcDir;
    QPushButton *dbcButton;
    QComboBox *mpqLocale;
    QLabel *mpqLocaleLabel;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QStringLiteral("settings"));
        settings->resize(320, 240);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qsw/resources/mangos.ico"), QSize(), QIcon::Normal, QIcon::Off);
        settings->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 200, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(settings);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 301, 141));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        dbcLable = new QLabel(layoutWidget);
        dbcLable->setObjectName(QStringLiteral("dbcLable"));

        gridLayout->addWidget(dbcLable, 4, 0, 1, 1);

        mpqLabel = new QLabel(layoutWidget);
        mpqLabel->setObjectName(QStringLiteral("mpqLabel"));

        gridLayout->addWidget(mpqLabel, 0, 0, 1, 1);

        mpqDir = new QLineEdit(layoutWidget);
        mpqDir->setObjectName(QStringLiteral("mpqDir"));

        gridLayout->addWidget(mpqDir, 1, 0, 1, 1);

        mpqButton = new QPushButton(layoutWidget);
        mpqButton->setObjectName(QStringLiteral("mpqButton"));
        mpqButton->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(mpqButton, 1, 1, 1, 1);

        dbcDir = new QLineEdit(layoutWidget);
        dbcDir->setObjectName(QStringLiteral("dbcDir"));

        gridLayout->addWidget(dbcDir, 5, 0, 1, 1);

        dbcButton = new QPushButton(layoutWidget);
        dbcButton->setObjectName(QStringLiteral("dbcButton"));
        dbcButton->setMaximumSize(QSize(30, 16777215));

        gridLayout->addWidget(dbcButton, 5, 1, 1, 1);

        mpqLocale = new QComboBox(layoutWidget);
        mpqLocale->setObjectName(QStringLiteral("mpqLocale"));

        gridLayout->addWidget(mpqLocale, 3, 0, 1, 2);

        mpqLocaleLabel = new QLabel(layoutWidget);
        mpqLocaleLabel->setObjectName(QStringLiteral("mpqLocaleLabel"));

        gridLayout->addWidget(mpqLocaleLabel, 2, 0, 1, 1);


        retranslateUi(settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "Settings", Q_NULLPTR));
        dbcLable->setText(QApplication::translate("settings", "Please enter DBC directory:", Q_NULLPTR));
        mpqLabel->setText(QApplication::translate("settings", "Please select MPQ directory:", Q_NULLPTR));
        mpqButton->setText(QApplication::translate("settings", "...", Q_NULLPTR));
        dbcButton->setText(QApplication::translate("settings", "...", Q_NULLPTR));
        mpqLocaleLabel->setText(QApplication::translate("settings", "Current MPQ locale:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
