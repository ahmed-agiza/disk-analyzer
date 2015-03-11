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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
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
    QAction *actionUp;
    QAction *actionDuplicateFilesChecker;
    QAction *actionSelectRootDirectory;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTreeView *twgDirViewer;
    QTabWidget *tbsMain;
    QWidget *tabVisualizer;
    QHBoxLayout *horizontalLayout_2;
    QWebView *wvwCharts;
    QWidget *tabStatistics;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnLargestFiles;
    QPushButton *btnExtensions;
    QPushButton *btnSizeGroups;
    QWebView *wvwStatistics;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnBarChart;
    QPushButton *btnDoughChart;
    QMenuBar *menuBar;
    QMenu *menuAnalyze;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1346, 843);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 400));
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Icons/Awicons-Vista-Artistic-Chart-search.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAnalyzeDirectory = new QAction(MainWindow);
        actionAnalyzeDirectory->setObjectName(QStringLiteral("actionAnalyzeDirectory"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Icons/file-explore-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAnalyzeDirectory->setIcon(icon1);
        actionExploreDirectory = new QAction(MainWindow);
        actionExploreDirectory->setObjectName(QStringLiteral("actionExploreDirectory"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Icons/Folder-Open-icon (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExploreDirectory->setIcon(icon2);
        actionOpen_Terminal = new QAction(MainWindow);
        actionOpen_Terminal->setObjectName(QStringLiteral("actionOpen_Terminal"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Icons/Apps-Terminal-Pc-104-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Terminal->setIcon(icon3);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QStringLiteral("actionRefresh"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/Icons/Button-Refresh-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon4);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/Icons/settings-3-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon5);
        actionUp = new QAction(MainWindow);
        actionUp->setObjectName(QStringLiteral("actionUp"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/Icons/Button-Upload-icon (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUp->setIcon(icon6);
        actionDuplicateFilesChecker = new QAction(MainWindow);
        actionDuplicateFilesChecker->setObjectName(QStringLiteral("actionDuplicateFilesChecker"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/Icons/duplicate-icon-md.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDuplicateFilesChecker->setIcon(icon7);
        actionSelectRootDirectory = new QAction(MainWindow);
        actionSelectRootDirectory->setObjectName(QStringLiteral("actionSelectRootDirectory"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/Icons/Folder-Add-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectRootDirectory->setIcon(icon8);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        twgDirViewer = new QTreeView(centralWidget);
        twgDirViewer->setObjectName(QStringLiteral("twgDirViewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twgDirViewer->sizePolicy().hasHeightForWidth());
        twgDirViewer->setSizePolicy(sizePolicy1);
        twgDirViewer->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(twgDirViewer, 0, 0, 1, 1);

        tbsMain = new QTabWidget(centralWidget);
        tbsMain->setObjectName(QStringLiteral("tbsMain"));
        tabVisualizer = new QWidget();
        tabVisualizer->setObjectName(QStringLiteral("tabVisualizer"));
        horizontalLayout_2 = new QHBoxLayout(tabVisualizer);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        wvwCharts = new QWebView(tabVisualizer);
        wvwCharts->setObjectName(QStringLiteral("wvwCharts"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(wvwCharts->sizePolicy().hasHeightForWidth());
        wvwCharts->setSizePolicy(sizePolicy2);
        wvwCharts->setMinimumSize(QSize(1000, 0));
        wvwCharts->setUrl(QUrl(QStringLiteral("about:blank")));
        wvwCharts->setZoomFactor(1);
        wvwCharts->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::Qt4CompatiblePainting|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);

        horizontalLayout_2->addWidget(wvwCharts);

        tbsMain->addTab(tabVisualizer, QString());
        tabStatistics = new QWidget();
        tabStatistics->setObjectName(QStringLiteral("tabStatistics"));
        verticalLayout = new QVBoxLayout(tabStatistics);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnLargestFiles = new QPushButton(tabStatistics);
        btnLargestFiles->setObjectName(QStringLiteral("btnLargestFiles"));

        horizontalLayout->addWidget(btnLargestFiles);

        btnExtensions = new QPushButton(tabStatistics);
        btnExtensions->setObjectName(QStringLiteral("btnExtensions"));

        horizontalLayout->addWidget(btnExtensions);

        btnSizeGroups = new QPushButton(tabStatistics);
        btnSizeGroups->setObjectName(QStringLiteral("btnSizeGroups"));

        horizontalLayout->addWidget(btnSizeGroups);


        verticalLayout->addLayout(horizontalLayout);

        wvwStatistics = new QWebView(tabStatistics);
        wvwStatistics->setObjectName(QStringLiteral("wvwStatistics"));
        sizePolicy2.setHeightForWidth(wvwStatistics->sizePolicy().hasHeightForWidth());
        wvwStatistics->setSizePolicy(sizePolicy2);
        wvwStatistics->setUrl(QUrl(QStringLiteral("about:blank")));
        wvwStatistics->setZoomFactor(0.82);
        wvwStatistics->setRenderHints(QPainter::Qt4CompatiblePainting|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);

        verticalLayout->addWidget(wvwStatistics);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 10, -1, -1);
        btnBarChart = new QPushButton(tabStatistics);
        btnBarChart->setObjectName(QStringLiteral("btnBarChart"));
        btnBarChart->setCheckable(true);
        btnBarChart->setChecked(true);

        horizontalLayout_3->addWidget(btnBarChart);

        btnDoughChart = new QPushButton(tabStatistics);
        btnDoughChart->setObjectName(QStringLiteral("btnDoughChart"));
        btnDoughChart->setCheckable(true);

        horizontalLayout_3->addWidget(btnDoughChart);


        verticalLayout->addLayout(horizontalLayout_3);

        tbsMain->addTab(tabStatistics, QString());

        gridLayout->addWidget(tbsMain, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1346, 20));
        menuAnalyze = new QMenu(menuBar);
        menuAnalyze->setObjectName(QStringLiteral("menuAnalyze"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuAnalyze->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuAnalyze->addAction(actionAnalyzeDirectory);
        menuAnalyze->addAction(actionSelectRootDirectory);
        menuTools->addAction(actionExploreDirectory);
        menuTools->addAction(actionOpen_Terminal);
        menuTools->addAction(actionDuplicateFilesChecker);
        menuTools->addSeparator();
        menuTools->addAction(actionSettings);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionSelectRootDirectory);
        mainToolBar->addAction(actionAnalyzeDirectory);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExploreDirectory);
        mainToolBar->addAction(actionOpen_Terminal);
        mainToolBar->addAction(actionDuplicateFilesChecker);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUp);
        mainToolBar->addAction(actionRefresh);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSettings);

        retranslateUi(MainWindow);

        tbsMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Disk Analyst", 0));
        actionAnalyzeDirectory->setText(QApplication::translate("MainWindow", "Analyze Directory", 0));
#ifndef QT_NO_TOOLTIP
        actionAnalyzeDirectory->setToolTip(QApplication::translate("MainWindow", "Analyze Selected Directory", 0));
#endif // QT_NO_TOOLTIP
        actionAnalyzeDirectory->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0));
        actionExploreDirectory->setText(QApplication::translate("MainWindow", "Explore Directory", 0));
#ifndef QT_NO_TOOLTIP
        actionExploreDirectory->setToolTip(QApplication::translate("MainWindow", "Show Containing Directory", 0));
#endif // QT_NO_TOOLTIP
        actionExploreDirectory->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actionOpen_Terminal->setText(QApplication::translate("MainWindow", "Open Terminal", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen_Terminal->setToolTip(QApplication::translate("MainWindow", "Launch Terminal in the Current Root Directory", 0));
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
        actionUp->setText(QApplication::translate("MainWindow", "Up", 0));
#ifndef QT_NO_TOOLTIP
        actionUp->setToolTip(QApplication::translate("MainWindow", "Navigate Up One directory", 0));
#endif // QT_NO_TOOLTIP
        actionUp->setShortcut(QApplication::translate("MainWindow", "Ctrl+U", 0));
        actionDuplicateFilesChecker->setText(QApplication::translate("MainWindow", "Duplicate Files Checker", 0));
#ifndef QT_NO_TOOLTIP
        actionDuplicateFilesChecker->setToolTip(QApplication::translate("MainWindow", "Run Duplicate Files Checker in the Current Root Directory", 0));
#endif // QT_NO_TOOLTIP
        actionSelectRootDirectory->setText(QApplication::translate("MainWindow", "Select Root Directory", 0));
#ifndef QT_NO_TOOLTIP
        actionSelectRootDirectory->setToolTip(QApplication::translate("MainWindow", "Select Root Directory", 0));
#endif // QT_NO_TOOLTIP
        actionSelectRootDirectory->setShortcut(QApplication::translate("MainWindow", "Shift+O", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About", 0));
#endif // QT_NO_TOOLTIP
        tbsMain->setTabText(tbsMain->indexOf(tabVisualizer), QApplication::translate("MainWindow", "Visualizer", 0));
        btnLargestFiles->setText(QApplication::translate("MainWindow", "Largest Files Statistics", 0));
        btnExtensions->setText(QApplication::translate("MainWindow", "Extenstions Statistics", 0));
        btnSizeGroups->setText(QApplication::translate("MainWindow", "Size Group Statistics", 0));
        btnBarChart->setText(QApplication::translate("MainWindow", "Bar chart", 0));
        btnDoughChart->setText(QApplication::translate("MainWindow", "Doughnut chart", 0));
        tbsMain->setTabText(tbsMain->indexOf(tabStatistics), QApplication::translate("MainWindow", "Statistics", 0));
        menuAnalyze->setTitle(QApplication::translate("MainWindow", "Explore", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
