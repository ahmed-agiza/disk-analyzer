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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DupesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblDuplicates;
    QTableWidget *tblDuplicates;
    QDialogButtonBox *bbxClose;

    void setupUi(QDialog *DupesDialog)
    {
        if (DupesDialog->objectName().isEmpty())
            DupesDialog->setObjectName(QStringLiteral("DupesDialog"));
        DupesDialog->resize(580, 260);
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

        tblDuplicates = new QTableWidget(DupesDialog);
        if (tblDuplicates->columnCount() < 6)
            tblDuplicates->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblDuplicates->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblDuplicates->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblDuplicates->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblDuplicates->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblDuplicates->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblDuplicates->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tblDuplicates->setObjectName(QStringLiteral("tblDuplicates"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tblDuplicates->sizePolicy().hasHeightForWidth());
        tblDuplicates->setSizePolicy(sizePolicy1);
        tblDuplicates->setFrameShape(QFrame::StyledPanel);
        tblDuplicates->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblDuplicates->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblDuplicates->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tblDuplicates->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblDuplicates->setTabKeyNavigation(false);
        tblDuplicates->setProperty("showDropIndicator", QVariant(false));
        tblDuplicates->setDragDropOverwriteMode(false);
        tblDuplicates->setAlternatingRowColors(true);
        tblDuplicates->setSelectionMode(QAbstractItemView::NoSelection);
        tblDuplicates->setSelectionBehavior(QAbstractItemView::SelectItems);
        tblDuplicates->setTextElideMode(Qt::ElideMiddle);
        tblDuplicates->setSortingEnabled(false);
        tblDuplicates->setRowCount(0);
        tblDuplicates->setColumnCount(6);
        tblDuplicates->horizontalHeader()->setVisible(true);
        tblDuplicates->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tblDuplicates->horizontalHeader()->setStretchLastSection(false);
        tblDuplicates->verticalHeader()->setVisible(false);

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
        QTableWidgetItem *___qtablewidgetitem = tblDuplicates->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DupesDialog", "First Entry", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tblDuplicates->horizontalHeaderItem(3);
        ___qtablewidgetitem1->setText(QApplication::translate("DupesDialog", "Second Entry", 0));
    } // retranslateUi

};

namespace Ui {
    class DupesDialog: public Ui_DupesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUPESDIALOG_H
