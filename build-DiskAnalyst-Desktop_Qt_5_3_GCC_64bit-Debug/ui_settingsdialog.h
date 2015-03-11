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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QFormLayout *formLayout;
    QLabel *lblColorSet;
    QComboBox *cmbColorSet;
    QLabel *lblEntriesBy;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbtSize;
    QRadioButton *rbtBlocks;
    QCheckBox *chkReadable;
    QCheckBox *chkNavigate;
    QCheckBox *chkFading;
    QLabel *lblStartupDirectory;
    QPushButton *btnStartupDirectory;
    QDialogButtonBox *bbxOkCancel;
    QCheckBox *chkEnableRelative;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(539, 241);
        formLayout = new QFormLayout(SettingsDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        lblColorSet = new QLabel(SettingsDialog);
        lblColorSet->setObjectName(QStringLiteral("lblColorSet"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblColorSet);

        cmbColorSet = new QComboBox(SettingsDialog);
        cmbColorSet->setObjectName(QStringLiteral("cmbColorSet"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cmbColorSet);

        lblEntriesBy = new QLabel(SettingsDialog);
        lblEntriesBy->setObjectName(QStringLiteral("lblEntriesBy"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblEntriesBy);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rbtSize = new QRadioButton(SettingsDialog);
        rbtSize->setObjectName(QStringLiteral("rbtSize"));
        rbtSize->setChecked(true);

        horizontalLayout_2->addWidget(rbtSize);

        rbtBlocks = new QRadioButton(SettingsDialog);
        rbtBlocks->setObjectName(QStringLiteral("rbtBlocks"));

        horizontalLayout_2->addWidget(rbtBlocks);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_2);

        chkReadable = new QCheckBox(SettingsDialog);
        chkReadable->setObjectName(QStringLiteral("chkReadable"));
        chkReadable->setChecked(true);

        formLayout->setWidget(5, QFormLayout::LabelRole, chkReadable);

        chkNavigate = new QCheckBox(SettingsDialog);
        chkNavigate->setObjectName(QStringLiteral("chkNavigate"));
        chkNavigate->setChecked(true);

        formLayout->setWidget(6, QFormLayout::LabelRole, chkNavigate);

        chkFading = new QCheckBox(SettingsDialog);
        chkFading->setObjectName(QStringLiteral("chkFading"));
        chkFading->setChecked(true);

        formLayout->setWidget(7, QFormLayout::LabelRole, chkFading);

        lblStartupDirectory = new QLabel(SettingsDialog);
        lblStartupDirectory->setObjectName(QStringLiteral("lblStartupDirectory"));

        formLayout->setWidget(9, QFormLayout::LabelRole, lblStartupDirectory);

        btnStartupDirectory = new QPushButton(SettingsDialog);
        btnStartupDirectory->setObjectName(QStringLiteral("btnStartupDirectory"));

        formLayout->setWidget(9, QFormLayout::FieldRole, btnStartupDirectory);

        bbxOkCancel = new QDialogButtonBox(SettingsDialog);
        bbxOkCancel->setObjectName(QStringLiteral("bbxOkCancel"));
        bbxOkCancel->setOrientation(Qt::Horizontal);
        bbxOkCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::RestoreDefaults);
        bbxOkCancel->setCenterButtons(true);

        formLayout->setWidget(11, QFormLayout::SpanningRole, bbxOkCancel);

        chkEnableRelative = new QCheckBox(SettingsDialog);
        chkEnableRelative->setObjectName(QStringLiteral("chkEnableRelative"));
        chkEnableRelative->setChecked(true);

        formLayout->setWidget(8, QFormLayout::LabelRole, chkEnableRelative);


        retranslateUi(SettingsDialog);
        QObject::connect(bbxOkCancel, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(bbxOkCancel, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Dialog", 0));
        lblColorSet->setText(QApplication::translate("SettingsDialog", "Color Set:", 0));
        cmbColorSet->clear();
        cmbColorSet->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "Color Set 1", 0)
         << QApplication::translate("SettingsDialog", "Color Set 2", 0)
         << QApplication::translate("SettingsDialog", "Color Set 3", 0)
         << QApplication::translate("SettingsDialog", "Color Set 4", 0)
        );
        lblEntriesBy->setText(QApplication::translate("SettingsDialog", "List entries by:", 0));
        rbtSize->setText(QApplication::translate("SettingsDialog", "Size", 0));
        rbtBlocks->setText(QApplication::translate("SettingsDialog", "Allocated blocks", 0));
        chkReadable->setText(QApplication::translate("SettingsDialog", "Display sizes in readble format", 0));
        chkNavigate->setText(QApplication::translate("SettingsDialog", "Navigate through chart", 0));
        chkFading->setText(QApplication::translate("SettingsDialog", "Fading Animation", 0));
        lblStartupDirectory->setText(QString());
        btnStartupDirectory->setText(QApplication::translate("SettingsDialog", "Change Startup Directory", 0));
        chkEnableRelative->setText(QApplication::translate("SettingsDialog", "Enable Graph Relative Scaling", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
