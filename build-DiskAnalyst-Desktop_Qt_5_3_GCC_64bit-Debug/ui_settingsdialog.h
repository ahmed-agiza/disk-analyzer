/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QFormLayout *formLayout;
    QLabel *lblGraphDepth;
    QLineEdit *letGraphDepth;
    QCheckBox *chkNavigate;
    QCheckBox *chcReadable;
    QLabel *lblStartupDirectory;
    QPushButton *btnStartuoDirectory;
    QDialogButtonBox *bbxOkCancel;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(539, 274);
        formLayout = new QFormLayout(SettingsDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        lblGraphDepth = new QLabel(SettingsDialog);
        lblGraphDepth->setObjectName(QStringLiteral("lblGraphDepth"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblGraphDepth);

        letGraphDepth = new QLineEdit(SettingsDialog);
        letGraphDepth->setObjectName(QStringLiteral("letGraphDepth"));

        formLayout->setWidget(0, QFormLayout::FieldRole, letGraphDepth);

        chkNavigate = new QCheckBox(SettingsDialog);
        chkNavigate->setObjectName(QStringLiteral("chkNavigate"));
        chkNavigate->setChecked(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, chkNavigate);

        chcReadable = new QCheckBox(SettingsDialog);
        chcReadable->setObjectName(QStringLiteral("chcReadable"));

        formLayout->setWidget(2, QFormLayout::LabelRole, chcReadable);

        lblStartupDirectory = new QLabel(SettingsDialog);
        lblStartupDirectory->setObjectName(QStringLiteral("lblStartupDirectory"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblStartupDirectory);

        btnStartuoDirectory = new QPushButton(SettingsDialog);
        btnStartuoDirectory->setObjectName(QStringLiteral("btnStartuoDirectory"));

        formLayout->setWidget(3, QFormLayout::FieldRole, btnStartuoDirectory);

        bbxOkCancel = new QDialogButtonBox(SettingsDialog);
        bbxOkCancel->setObjectName(QStringLiteral("bbxOkCancel"));
        bbxOkCancel->setOrientation(Qt::Horizontal);
        bbxOkCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::FieldRole, bbxOkCancel);


        retranslateUi(SettingsDialog);
        QObject::connect(bbxOkCancel, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(bbxOkCancel, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Dialog", 0));
        lblGraphDepth->setText(QApplication::translate("SettingsDialog", "Maximum graph depth:", 0));
        chkNavigate->setText(QApplication::translate("SettingsDialog", "Navigate through chart", 0));
        chcReadable->setText(QApplication::translate("SettingsDialog", "Display sizes in human readble format", 0));
        lblStartupDirectory->setText(QString());
        btnStartuoDirectory->setText(QApplication::translate("SettingsDialog", "Change Startup Directory", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
