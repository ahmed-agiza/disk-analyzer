#include "dupeschecker.h"
#include "qdebug.h"
#include <QFile>
#include <QCryptographicHash>

QString DupesChecker::hashFile(QString filePath){
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QString hash = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex().constData();
        file.close();
        return hash;
    }

    return "";
}

DupesChecker::DupesChecker(QObject *parent) :
    QObject(parent), stopped(false), analysisDone(false){
}

bool DupesChecker::getAnalysisDone() const{
    return analysisDone;
}

void DupesChecker::startAnalysis(DirectoryEntriesList entries, DirectoryEntry *rootEntry){
    QMap<long long, QStringList> sizesTable;
    QMap<QString, QString> hashCache;
    QList<QPair<QString, QString> > duplicates;

    qDebug() << "Hashing..";

    for(int i = 0; i < entries.size() && !stopped; i++){
        emit onProgress(((i*1.0)/entries.size()) * 100);
        if (entries[i] == rootEntry || entries[i]->getEntrySize() == 0)
            continue;
        if (entries[i]->isValid() && entries[i]->isRegularFile()){
            QString entryPath = entries[i]->getPath() + entries[i]->getName();
            if(!sizesTable.contains(entries[i]->getEntrySize())){
                sizesTable[entries[i]->getEntrySize()].append(entryPath);
            }else{
                QList<QString> &matchingSize = sizesTable[entries[i]->getEntrySize()];
\
                QString entryHash;
                if(hashCache.contains(entryPath))
                    entryHash = hashCache[entryPath];
                else{
                    entryHash = hashFile(entryPath);
                    if (entryHash != "")
                        hashCache[entryPath] = entryHash;
                }

                if (entryHash == ""){
                    qDebug() << "Cannot hash " << entries[i]->getPath() + entries[i]->getName();
                }else{
                    for(int j = 0; j < matchingSize.size(); j++){
                        QString fileHash;
                        if(hashCache.contains(matchingSize[j]))
                            fileHash = hashCache[matchingSize[j]];
                        else{
                            fileHash = hashFile(matchingSize[j]);
                            if(fileHash != "")
                                hashCache[matchingSize[j]] = fileHash;
                        }

                        if(fileHash == ""){
                            qDebug() << "Cannot hash " << matchingSize[j];
                        }else if (fileHash == entryHash){
                            duplicates.append(QPair<QString, QString>(matchingSize[j], entryPath));
                        }\
                    }
                }
                matchingSize.append(entryPath);
            }

        }
    }
    qDebug() << "Done hashing";
    qDebug() << duplicates.size();
    analysisDone = (!stopped);
    qDebug() << analysisDone;
    emit analysisComplete(duplicates);
}

void DupesChecker::setStopped(bool value){
    qDebug() << "Stop checker? " << value;
    stopped = value;
}

void DupesChecker::setAnalysisDone(bool value){
    analysisDone = value;
}
