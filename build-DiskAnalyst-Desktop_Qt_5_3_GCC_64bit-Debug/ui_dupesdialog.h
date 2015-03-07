/********************************************************************************
** Form generated from reading UI file 'dupesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUPESDIALOG_H
#define UI_DUPESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DupesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblDuplicates;
    QTableView *tblDuplicates;
    QDialogButtonBox *bbxClose;

    void setupUi(QDialog *DupesDialog)
    {
        if (DupesDialog->objectName().isEmpty())
            DupesDialog->setObjectName(QStringLiteral("DupesDialog"));
        DupesDialog->resize(620, 260);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DupesDialog->sizePolicy().hasHeightForWidth());
        DupesDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(DupesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lblDuplicates = new QLabel(DupesDialog);
        lblDuplicates->setObjectName(QStringLiteral("lblDuplicates"));

        verticalLayout->addWidget(lblDuplicates);

        tblDuplicates = new QTableView(DupesDialog);
        tblDuplicates->setObjectName(QStringLiteral("tblDuplicates"));
        tblDuplicates->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblDuplicates->setProperty("showDropIndicator", QVariant(false));
        tblDuplicates->setDragDropOverwriteMode(false);
        tblDuplicates->setAlternatingRowColors(true);
        tblDuplicates->setSelectionMode(QAbstractItemView::NoSelection);
        tblDuplicates->horizontalHeader()->setHighlightSections(false);
        tblDuplicates->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(tblDuplicates);

        bbxClose = new QDialogButtonBox(DupesDialog);
        bbxClose->setObjectName(QStringLiteral("bbxClose"));
        bbxClose->setOrientation(Qt::Horizontal);
        bbxClose->setStandardButtons(QDialogButtonBox::Close);
        bbxClose->setCenterButtons(true);

        verticalLayout->addWidget(bbxClose);


        retranslateUi(DupesDialog);
        QObject::connect(bbxClose, SIGNAL(accepted()), DupesDialog, SLOT(accept()));
        QObject::connect(bbxClose, SIGNAL(rejected()), DupesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DupesDialog);
    } // setupUi

    void retranslateUi(QDialog *DupesDialog)
    {
        DupesDialog->setWindowTitle(QApplication::translate("DupesDialog", "Found Duplicates", 0));
        lblDuplicates->setText(QApplication::translate("DupesDialog", "Duplicates:", 0));
    } // retranslateUi

};

namespace Ui {
    class DupesDialog: public Ui_DupesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUPESDIALOG_H
