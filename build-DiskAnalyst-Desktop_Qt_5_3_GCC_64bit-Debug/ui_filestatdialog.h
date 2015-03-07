/********************************************************************************
** Form generated from reading UI file 'filestatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESTATDIALOG_H
#define UI_FILESTATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_FileStatDialog
{
public:
    QFormLayout *formLayout;
    QLabel *lblLblFilename;
    QLabel *lblFilename;
    QLabel *lblLblFilePath;
    QLabel *lblFilePath;
    QLabel *lblLblFileExtension;
    QLabel *lblFileExtension;
    QLabel *lblLblFileType;
    QLabel *lblFileType;
    QLabel *lblLblInodeNumber;
    QLabel *lblInodeNumber;
    QLabel *lblLblMode;
    QLabel *lblMode;
    QLabel *lblLblLinkCount;
    QLabel *lblLblOwnership;
    QLabel *lblOwnership;
    QLabel *lblLblPreferredIOSize;
    QLabel *lblPreferredIOSize;
    QLabel *lblLblFileSize;
    QLabel *lblFileSize;
    QLabel *lblLblBlocksAllocated;
    QLabel *lblBlocksAllocated;
    QLabel *lblLblLastStatus;
    QLabel *lblLastStatus;
    QLabel *lblLblLastFileAccess;
    QLabel *lblLastFileAccess;
    QLabel *lblLastFileModification;
    QDialogButtonBox *bbxClose;
    QLabel *lblLinkCount;
    QLabel *lblLblLastFileModification;

    void setupUi(QDialog *FileStatDialog)
    {
        if (FileStatDialog->objectName().isEmpty())
            FileStatDialog->setObjectName(QStringLiteral("FileStatDialog"));
        FileStatDialog->resize(292, 338);
        formLayout = new QFormLayout(FileStatDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        lblLblFilename = new QLabel(FileStatDialog);
        lblLblFilename->setObjectName(QStringLiteral("lblLblFilename"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblLblFilename);

        lblFilename = new QLabel(FileStatDialog);
        lblFilename->setObjectName(QStringLiteral("lblFilename"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblFilename);

        lblLblFilePath = new QLabel(FileStatDialog);
        lblLblFilePath->setObjectName(QStringLiteral("lblLblFilePath"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblLblFilePath);

        lblFilePath = new QLabel(FileStatDialog);
        lblFilePath->setObjectName(QStringLiteral("lblFilePath"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblFilePath);

        lblLblFileExtension = new QLabel(FileStatDialog);
        lblLblFileExtension->setObjectName(QStringLiteral("lblLblFileExtension"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblLblFileExtension);

        lblFileExtension = new QLabel(FileStatDialog);
        lblFileExtension->setObjectName(QStringLiteral("lblFileExtension"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lblFileExtension);

        lblLblFileType = new QLabel(FileStatDialog);
        lblLblFileType->setObjectName(QStringLiteral("lblLblFileType"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblLblFileType);

        lblFileType = new QLabel(FileStatDialog);
        lblFileType->setObjectName(QStringLiteral("lblFileType"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lblFileType);

        lblLblInodeNumber = new QLabel(FileStatDialog);
        lblLblInodeNumber->setObjectName(QStringLiteral("lblLblInodeNumber"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblLblInodeNumber);

        lblInodeNumber = new QLabel(FileStatDialog);
        lblInodeNumber->setObjectName(QStringLiteral("lblInodeNumber"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lblInodeNumber);

        lblLblMode = new QLabel(FileStatDialog);
        lblLblMode->setObjectName(QStringLiteral("lblLblMode"));

        formLayout->setWidget(5, QFormLayout::LabelRole, lblLblMode);

        lblMode = new QLabel(FileStatDialog);
        lblMode->setObjectName(QStringLiteral("lblMode"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lblMode);

        lblLblLinkCount = new QLabel(FileStatDialog);
        lblLblLinkCount->setObjectName(QStringLiteral("lblLblLinkCount"));

        formLayout->setWidget(6, QFormLayout::LabelRole, lblLblLinkCount);

        lblLblOwnership = new QLabel(FileStatDialog);
        lblLblOwnership->setObjectName(QStringLiteral("lblLblOwnership"));

        formLayout->setWidget(7, QFormLayout::LabelRole, lblLblOwnership);

        lblOwnership = new QLabel(FileStatDialog);
        lblOwnership->setObjectName(QStringLiteral("lblOwnership"));

        formLayout->setWidget(7, QFormLayout::FieldRole, lblOwnership);

        lblLblPreferredIOSize = new QLabel(FileStatDialog);
        lblLblPreferredIOSize->setObjectName(QStringLiteral("lblLblPreferredIOSize"));

        formLayout->setWidget(8, QFormLayout::LabelRole, lblLblPreferredIOSize);

        lblPreferredIOSize = new QLabel(FileStatDialog);
        lblPreferredIOSize->setObjectName(QStringLiteral("lblPreferredIOSize"));

        formLayout->setWidget(8, QFormLayout::FieldRole, lblPreferredIOSize);

        lblLblFileSize = new QLabel(FileStatDialog);
        lblLblFileSize->setObjectName(QStringLiteral("lblLblFileSize"));

        formLayout->setWidget(9, QFormLayout::LabelRole, lblLblFileSize);

        lblFileSize = new QLabel(FileStatDialog);
        lblFileSize->setObjectName(QStringLiteral("lblFileSize"));

        formLayout->setWidget(9, QFormLayout::FieldRole, lblFileSize);

        lblLblBlocksAllocated = new QLabel(FileStatDialog);
        lblLblBlocksAllocated->setObjectName(QStringLiteral("lblLblBlocksAllocated"));

        formLayout->setWidget(10, QFormLayout::LabelRole, lblLblBlocksAllocated);

        lblBlocksAllocated = new QLabel(FileStatDialog);
        lblBlocksAllocated->setObjectName(QStringLiteral("lblBlocksAllocated"));

        formLayout->setWidget(10, QFormLayout::FieldRole, lblBlocksAllocated);

        lblLblLastStatus = new QLabel(FileStatDialog);
        lblLblLastStatus->setObjectName(QStringLiteral("lblLblLastStatus"));

        formLayout->setWidget(11, QFormLayout::LabelRole, lblLblLastStatus);

        lblLastStatus = new QLabel(FileStatDialog);
        lblLastStatus->setObjectName(QStringLiteral("lblLastStatus"));

        formLayout->setWidget(11, QFormLayout::FieldRole, lblLastStatus);

        lblLblLastFileAccess = new QLabel(FileStatDialog);
        lblLblLastFileAccess->setObjectName(QStringLiteral("lblLblLastFileAccess"));

        formLayout->setWidget(12, QFormLayout::LabelRole, lblLblLastFileAccess);

        lblLastFileAccess = new QLabel(FileStatDialog);
        lblLastFileAccess->setObjectName(QStringLiteral("lblLastFileAccess"));

        formLayout->setWidget(12, QFormLayout::FieldRole, lblLastFileAccess);

        lblLastFileModification = new QLabel(FileStatDialog);
        lblLastFileModification->setObjectName(QStringLiteral("lblLastFileModification"));

        formLayout->setWidget(13, QFormLayout::FieldRole, lblLastFileModification);

        bbxClose = new QDialogButtonBox(FileStatDialog);
        bbxClose->setObjectName(QStringLiteral("bbxClose"));
        bbxClose->setOrientation(Qt::Vertical);
        bbxClose->setStandardButtons(QDialogButtonBox::Close);

        formLayout->setWidget(14, QFormLayout::FieldRole, bbxClose);

        lblLinkCount = new QLabel(FileStatDialog);
        lblLinkCount->setObjectName(QStringLiteral("lblLinkCount"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lblLinkCount);

        lblLblLastFileModification = new QLabel(FileStatDialog);
        lblLblLastFileModification->setObjectName(QStringLiteral("lblLblLastFileModification"));

        formLayout->setWidget(13, QFormLayout::LabelRole, lblLblLastFileModification);


        retranslateUi(FileStatDialog);
        QObject::connect(bbxClose, SIGNAL(accepted()), FileStatDialog, SLOT(accept()));
        QObject::connect(bbxClose, SIGNAL(rejected()), FileStatDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FileStatDialog);
    } // setupUi

    void retranslateUi(QDialog *FileStatDialog)
    {
        FileStatDialog->setWindowTitle(QString());
        lblLblFilename->setText(QApplication::translate("FileStatDialog", "File name:", 0));
        lblFilename->setText(QString());
        lblLblFilePath->setText(QApplication::translate("FileStatDialog", "File path:", 0));
        lblFilePath->setText(QString());
        lblLblFileExtension->setText(QApplication::translate("FileStatDialog", "Extension:", 0));
        lblFileExtension->setText(QString());
        lblLblFileType->setText(QApplication::translate("FileStatDialog", "File type:", 0));
        lblFileType->setText(QString());
        lblLblInodeNumber->setText(QApplication::translate("FileStatDialog", "I-Node number: ", 0));
        lblInodeNumber->setText(QString());
        lblLblMode->setText(QApplication::translate("FileStatDialog", "Mode:", 0));
        lblMode->setText(QString());
        lblLblLinkCount->setText(QApplication::translate("FileStatDialog", "Link count:", 0));
        lblLblOwnership->setText(QApplication::translate("FileStatDialog", "Ownership:", 0));
        lblOwnership->setText(QString());
        lblLblPreferredIOSize->setText(QApplication::translate("FileStatDialog", "Preferred I/O block size:", 0));
        lblPreferredIOSize->setText(QString());
        lblLblFileSize->setText(QApplication::translate("FileStatDialog", "File size:", 0));
        lblFileSize->setText(QString());
        lblLblBlocksAllocated->setText(QApplication::translate("FileStatDialog", "Blocks allocated:", 0));
        lblBlocksAllocated->setText(QString());
        lblLblLastStatus->setText(QApplication::translate("FileStatDialog", "Last status change:", 0));
        lblLastStatus->setText(QString());
        lblLblLastFileAccess->setText(QApplication::translate("FileStatDialog", "Last file access:", 0));
        lblLastFileAccess->setText(QString());
        lblLastFileModification->setText(QString());
        lblLinkCount->setText(QString());
        lblLblLastFileModification->setText(QApplication::translate("FileStatDialog", "Last file modification:", 0));
    } // retranslateUi

};

namespace Ui {
    class FileStatDialog: public Ui_FileStatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESTATDIALOG_H
