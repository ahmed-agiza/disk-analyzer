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
        MainWindow->resize(589, 500);
        MainWindow->setMinimumSize(QSize(0, 500));
        actionAnalyzeDirectory = new QAction(MainWindow);
        actionAnalyzeDirectory->setObjectName(QStringLiteral("actionAnalyzeDirectory"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/analysis-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAnalyzeDirectory->setIcon(icon);
        actionExploreDirectory = new QAction(MainWindow);
        actionExploreDirectory->setObjectName(QStringLiteral("actionExploreDirectory"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/Open-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExploreDirectory->setIcon(icon1);
        actionOpen_Terminal = new QAction(MainWindow);
        actionOpen_Terminal->setObjectName(QStringLiteral("actionOpen_Terminal"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/Apps-konsole-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Terminal->setIcon(icon2);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QStringLiteral("actionRefresh"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/Actions-view-refresh-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon3);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icons/settings-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        twgDirViewer = new QTreeView(centralWidget);
        twgDirViewer->setObjectName(QStringLiteral("twgDirViewer"));
        twgDirViewer->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(twgDirViewer, 0, 0, 1, 1);

        wvwCharts = new QWebView(centralWidget);
        wvwCharts->setObjectName(QStringLiteral("wvwCharts"));
        wvwCharts->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(wvwCharts, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 589, 20));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
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
