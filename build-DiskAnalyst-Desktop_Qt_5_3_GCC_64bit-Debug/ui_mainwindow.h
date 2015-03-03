/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAnalyzeDirectory;
    QAction *actionExploreDirectory;
    QAction *actionOpen_Terminal;
    QAction *actionRefresh;
    QAction *actionSettings;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTreeView *twgDirViewer;
    QWebView *wvwCharts;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1070, 693);
        MainWindow->setMinimumSize(QSize(0, 500));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Icons/Awicons-Vista-Artistic-Chart-search.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAnalyzeDirectory = new QAction(MainWindow);
        actionAnalyzeDirectory->setObjectName(QStringLiteral("actionAnalyzeDirectory"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Icons/analysis-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAnalyzeDirectory->setIcon(icon1);
        actionExploreDirectory = new QAction(MainWindow);
        actionExploreDirectory->setObjectName(QStringLiteral("actionExploreDirectory"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Icons/Open-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExploreDirectory->setIcon(icon2);
        actionOpen_Terminal = new QAction(MainWindow);
        actionOpen_Terminal->setObjectName(QStringLiteral("actionOpen_Terminal"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Icons/Apps-konsole-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Terminal->setIcon(icon3);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QStringLiteral("actionRefresh"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/Icons/Actions-view-refresh-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon4);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/Icons/settings-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        twgDirViewer = new QTreeView(centralWidget);
        twgDirViewer->setObjectName(QStringLiteral("twgDirViewer"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(twgDirViewer->sizePolicy().hasHeightForWidth());
        twgDirViewer->setSizePolicy(sizePolicy);
        twgDirViewer->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(twgDirViewer, 0, 0, 1, 1);

        wvwCharts = new QWebView(centralWidget);
        wvwCharts->setObjectName(QStringLiteral("wvwCharts"));
        sizePolicy.setHeightForWidth(wvwCharts->sizePolicy().hasHeightForWidth());
        wvwCharts->setSizePolicy(sizePolicy);
        wvwCharts->setMinimumSize(QSize(1000, 0));
        wvwCharts->setUrl(QUrl(QStringLiteral("about:blank")));
        wvwCharts->setZoomFactor(1);
        wvwCharts->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);

        gridLayout->addWidget(wvwCharts, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1070, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionAnalyzeDirectory);
        mainToolBar->addAction(actionExploreDirectory);
        mainToolBar->addAction(actionOpen_Terminal);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionRefresh);
        mainToolBar->addAction(actionSettings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Disk Analyst", 0));
        actionAnalyzeDirectory->setText(QApplication::translate("MainWindow", "Analyze Directory", 0));
#ifndef QT_NO_TOOLTIP
        actionAnalyzeDirectory->setToolTip(QApplication::translate("MainWindow", "Open Directory for Analysis", 0));
#endif // QT_NO_TOOLTIP
        actionAnalyzeDirectory->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionExploreDirectory->setText(QApplication::translate("MainWindow", "Explore Directory", 0));
#ifndef QT_NO_TOOLTIP
        actionExploreDirectory->setToolTip(QApplication::translate("MainWindow", "Explore Directory", 0));
#endif // QT_NO_TOOLTIP
        actionExploreDirectory->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actionOpen_Terminal->setText(QApplication::translate("MainWindow", "Open Terminal", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen_Terminal->setToolTip(QApplication::translate("MainWindow", "Open Terminal in the Current Directory", 0));
#endif // QT_NO_TOOLTIP
        actionOpen_Terminal->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", 0));
        actionRefresh->setText(QApplication::translate("MainWindow", "Refresh", 0));
#ifndef QT_NO_TOOLTIP
        actionRefresh->setToolTip(QApplication::translate("MainWindow", "Refresh", 0));
#endif // QT_NO_TOOLTIP
        actionRefresh->setShortcut(QApplication::translate("MainWindow", "F5", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
#ifndef QT_NO_TOOLTIP
        actionSettings->setToolTip(QApplication::translate("MainWindow", "Settings", 0));
#endif // QT_NO_TOOLTIP
        actionSettings->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
