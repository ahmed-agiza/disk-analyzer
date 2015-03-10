#ifndef DIRECTORYANALYZER_H
#define DIRECTORYANALYZER_H

#include <QObject>
#include <QList>
#include "directoryentry.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

#define BUFF_SIZE 100

#define FLAG_SHOW_INODE 1
#define FLAG_RECURSE_MASK 2
#define FLAG_SHOW_BLOCKS 4
#define FLAG_SHOW_SIZE 8
#define FLAG_SHOW_DIRECTORY 16
#define FLAG_SHOW_ALL_FILES 32
#define FLAG_SHOW_ALL_ATTRS 64
#define FLAG_SHOW_FILE_TYPE 128
#define FLAG_SHOW_LINKS 256
#define FLAG_SHOW_OWNER 512
#define FLAG_SHOW_HUMAN_FORMAT 1024
#define FLAG_ONLY_FILES_AND_DIRS 2048


#define MAX_NAME_SIZE 2048
#define MAX_USER_SIZE 64
#define MAX_GROUP_SIZE 64
#define MAX_FULL_PATH_SIZE 2048

enum AnalysisTarget{Unkown = 0, SizeVisualization = 1, BlockVisualization = 2, DupeChecking = 3, FileSorting = 4, ExtenstionSorting = 5, GroupSorting = 6};



class DirectoryAnalyzer : public QObject
{
    Q_OBJECT
    QList<DirectoryEntry *> entries;
    DirectoryEntry *root;
    bool stopped;
    bool analysisDone;

    DirectoryEntry *statFile(char *path, char *name, int flags = 0, int depth = -1, DirectoryEntry *source = 0);
    void recursePath(char *dir, char *name, int flags, int depth = -1, DirectoryEntry *source = 0);

    static void getChildrenArray(DirectoryEntry *, QJsonArray &array);
    static void getChildrenArrayByBlocks(DirectoryEntry *, QJsonArray &array);
public:
    explicit DirectoryAnalyzer(QObject *parent = 0);
    QList<DirectoryEntry *> getEntries();
    QList<DirectoryEntry *> getRootEntries();

    static QJsonObject getEntriesJson(DirectoryEntry *rootEnry);
    static QString getEntriesJsonString(DirectoryEntry *rootEnry);

    static QJsonObject getEntriesJsonByBlock(DirectoryEntry *rootEnry);
    static QString getEntriesJsonStringByBlock(DirectoryEntry *rootEnry);

    DirectoryEntry *getRoot() const;

    ~DirectoryAnalyzer();
    bool getAnalysisDone() const;

signals:
    void analysisComplete(AnalysisTarget);
public slots:
    void startAnalysis(QString directory, QString name, int flags = 0, AnalysisTarget = Unkown);
    void setStopped(bool value);
    void setAnalysisDone(bool value);

};



#endif // DIRECTORYANALYZER_H
