#ifndef DUPESCHECKER_H
#define DUPESCHECKER_H

#include <QObject>

#include "directoryentry.h"


class DupesChecker : public QObject
{
    Q_OBJECT
    bool stopped;
    bool analysisDone;

    QString hashFile(QString);

public:
    explicit DupesChecker(QObject *parent = 0);

    bool getAnalysisDone() const;

signals:
    void analysisComplete(QList<QPair<QString, QString> >);
    void onProgress(int);

public slots:
    void startAnalysis(DirectoryEntriesList entries, DirectoryEntry *rootEntry);
    void setStopped(bool value);
    void setAnalysisDone(bool value);

};

#endif // DUPESCHECKER_H
