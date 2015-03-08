#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>

const QString GRAPH_DEPTH_KEY("graph_depth");
const QString LIST_BLOCKS_KEY("list_block");
const QString NAVIGATE_CHART_KEY("navigate_chart");
const QString FADING_KEY("fading");
const QString HUMAN_READABLE_KEY("human_readable");
const QString STARTUP_DIRECTORY_KEY("startup_directory");
const QString COLOR_SET_KEY("color_set");

class SettingsManager{
public:

    static void setGrapthDepth(int value){
       QSettings settings;
       settings.setValue(GRAPH_DEPTH_KEY, value);
    }
    static int getGrapthDepth(){
        QSettings settings;
        return settings.value(GRAPH_DEPTH_KEY, defaultGraphDepth()).toInt();
    }
    static int defaultGraphDepth(){
        return 4;
    }

    static void setStartupDir(QString value){
        QSettings settings;
        settings.setValue(STARTUP_DIRECTORY_KEY, value);
    }
    static QString getStartupDir(){
        QSettings settings;
        return settings.value(STARTUP_DIRECTORY_KEY, defaultStartupDir()).toString();
    }
    static QString defaultStartupDir(){
        return QDir::homePath() + QString("/");
    }

    static void setNavigateChart(bool value){
        QSettings settings;
        settings.setValue(NAVIGATE_CHART_KEY, value);
    }
    static bool getNavigateChart(){
        QSettings settings;
        return settings.value(NAVIGATE_CHART_KEY, defaultNavigateChart()).toBool();
    }
    static bool defaultNavigateChart(){
        return true;
    }

    static void setListEntriesByBlocks(bool value){
        QSettings settings;
        settings.setValue(LIST_BLOCKS_KEY, value);
    }
    static bool getListEntriesByBlocks(){
        QSettings settings;
        return settings.value(LIST_BLOCKS_KEY, defaultListEntriesByBlocks()).toBool();
    }
    static bool defaultListEntriesByBlocks(){
        return false;
    }

    static void setHumanReadable(bool value){
        QSettings settings;
        settings.setValue(HUMAN_READABLE_KEY, value);
    }
    static bool getHumanReadable(){
        QSettings settings;
        return settings.value(HUMAN_READABLE_KEY, defaultHumanReadable()).toBool();
    }
    static bool defaultHumanReadable(){
        return true;
    }

    static void setFadeEnabled(bool value){
        QSettings settings;
        settings.setValue(FADING_KEY, value);
    }
    static bool getFadeEnabled(){
        QSettings settings;
        return settings.value(FADING_KEY, defaultFadeEnabled()).toBool();
    }
    static bool defaultFadeEnabled(){
        return true;
    }

    static void setColorSet(int value){
       QSettings settings;
       settings.setValue(COLOR_SET_KEY, value);
    }
    static int getColorSet(){
        QSettings settings;
        return settings.value(COLOR_SET_KEY, defaultGraphDepth()).toInt();
    }
    static int defaultColorSet(){
        return 1;
    }

};
#endif // SETTINGSMANAGER_H
