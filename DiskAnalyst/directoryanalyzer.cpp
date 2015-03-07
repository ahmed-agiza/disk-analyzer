#include "directoryanalyzer.h"
#include "directoryentry.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


//#define DEBUG_SEPERATOR

DirectoryEntry *DirectoryAnalyzer::statFile(char *path, char *name, int flags, int depth, DirectoryEntry *source){
    struct stat buf;
    char full_path[MAX_FULL_PATH_SIZE];

    (void)flags;
#ifdef DEBUG_SEPERATOR
    //qDebug() << "Stating: " << path << " : " << name;
#endif

    if (path[strlen(path) - 1] != '/'){
#ifdef DEBUG_SEPERATOR
        qDebug() << "Adding / to " << path;
#endif
        strcat(path, "/");
#ifdef DEBUG_SEPERATOR
        qDebug() << "New path " << path;
#endif
    }

    sprintf(full_path, "%s%s", path, name);


    if (lstat(full_path, &buf) == -1) {
        perror("Stat error");
        qDebug() << full_path;
        DirectoryEntry *invalidEntry = new DirectoryEntry(QString(name), QString(path), 0, 0, -1);
        invalidEntry->setValidity(false);
        return invalidEntry;
    }

    QString entryName = QString(name);

    ENTRY_TYPE entryType = UNKNOWN;

    switch (buf.st_mode & S_IFMT) {
    case S_IFBLK: entryType = BLOCK_DEVICE;   break;
    case S_IFCHR: entryType = CHARACTER_DEVICE;  break;
    case S_IFDIR: entryType = DIRECTORY;   break;
    case S_IFIFO: entryType = FIFO_PIPE; break;
    case S_IFLNK: entryType = SYMLINK;   break;
    case S_IFREG: entryType = REGULAR_FILE;   break;
    case S_IFSOCK: entryType = SOCKET;   break;
    default:  entryType = UNKNOWN;  break;
    }

    long long entrySize = 0;
    if ((buf.st_blocks != 0) && (entryType == DIRECTORY || entryType == REGULAR_FILE))
        entrySize = (long long) buf.st_size;
    long long numberOfBlocks = (buf.st_blocks);

    DirectoryEntry *entry = new DirectoryEntry(entryName, QString(path), entrySize, numberOfBlocks, depth);
    entry->setType(entryType);
    if (source){
        entry->setSource(source);
        source->addChild(entry);
    }
    entry->setValidity(true);
    return entry;
}

void DirectoryAnalyzer::recursePath(char *dir, char *name, int flags, int depth, DirectoryEntry *source){
    DIR *dir_d;
    struct dirent *dir_inode;
    (void)flags;
    char fullPathArray[MAX_FULL_PATH_SIZE];

    if (dir[strlen(dir) - 1] != '/'){
#ifdef DEBUG_SEPERATOR
        qDebug() << "Adding / to " << dir;
#endif
        strcat(dir, "/");
#ifdef DEBUG_SEPERATOR
        qDebug() << "New dir: " << dir;
#endif
    }

    sprintf(fullPathArray, "%s%s", dir, name);

    if (strcmp(fullPathArray, ".") == 0 || strcmp(fullPathArray, "..") == 0)
        return;

    if (source)
        if (!source->isDirectory())
            return;

    if((dir_d = opendir(fullPathArray)) == NULL){
        perror("opendir");
        qDebug() << fullPathArray;
        return;
    }

    while((dir_inode = readdir(dir_d)) != NULL){

        if (strcmp(dir_inode->d_name, ".") == 0 || strcmp(dir_inode->d_name, "..") == 0 )
            continue;

        DirectoryEntry *newEntry = statFile(fullPathArray, dir_inode->d_name, 0, depth, source);
        if(!newEntry->isValid()){
            fprintf(stderr, "Invalid entry: %s%s\n", dir, dir_inode->d_name);
        }else{
            entries.append(newEntry);
            if (newEntry->isDirectory()){
                recursePath(fullPathArray, dir_inode->d_name, 0, depth + 1, newEntry);
                //qDebug() << "Recursing: " << newEntry->getName();
            }
        }


    }
    closedir(dir_d);

}

void DirectoryAnalyzer::getChildrenArray(DirectoryEntry *entry, QJsonArray &array){
    if (entry->getChildren().isEmpty())
        return;
    QSet<DirectoryEntry *> children = entry->getChildren();
    for(QSet<DirectoryEntry *>::iterator i = children.begin(); i != children.end(); i++){
        QJsonObject entryJson;
        entryJson.insert("name", (*i)->getName());
        entryJson.insert("size", (*i)->getEntrySize());
        QJsonArray childrenJsonBuf;
        getChildrenArray((*i), childrenJsonBuf);
        if(!childrenJsonBuf.isEmpty())
            entryJson.insert("children", childrenJsonBuf);
        array.push_back(entryJson);
    }
}

DirectoryAnalyzer::DirectoryAnalyzer(QObject *parent) :
    QObject(parent){
}

QList<DirectoryEntry *> DirectoryAnalyzer::getEntries(){
    return entries;
}

QList<DirectoryEntry *> DirectoryAnalyzer::getRootEntries(){
    QList<DirectoryEntry *> rootEntries;
    for(int i = 0; i < entries.size(); i++){
        if(entries[i]->getDepth() == 1)
            rootEntries.push_front(entries[i]);
    }
    return rootEntries;

}

QJsonObject DirectoryAnalyzer::getEntriesJson(DirectoryEntry *rootEnry){
    QSet<DirectoryEntry *> children = rootEnry->getChildren();
    QJsonObject rootEntryJson;
    rootEntryJson.insert("name", rootEnry->getName());
    rootEntryJson.insert("size", rootEnry->getEntrySize());
    QJsonArray rootEntryChildrenJson;
    for(QSet<DirectoryEntry *>::iterator i = children.begin(); i != children.end(); i++){
        QJsonObject entryJson;
        entryJson.insert("name", (*i)->getName());
        entryJson.insert("size", (*i)->getEntrySize());
        QJsonArray childrenBuf;
        getChildrenArray(*i, childrenBuf);
        if (!childrenBuf.isEmpty())
            entryJson.insert("children", childrenBuf);
        rootEntryChildrenJson.push_front(entryJson);
    }
    if (!rootEntryChildrenJson.isEmpty())
        rootEntryJson.insert("children", rootEntryChildrenJson);
    return rootEntryJson;
}

QString DirectoryAnalyzer::getEntriesJsonString(DirectoryEntry *rootEnry){
    return QString(QJsonDocument(getEntriesJson(rootEnry)).toJson(QJsonDocument::Compact));
}

DirectoryEntry *DirectoryAnalyzer::getRoot() const{
    return root;
}

DirectoryAnalyzer::~DirectoryAnalyzer(){
    for(int i = 0; i < entries.size(); i++)
        if (entries[i])
            delete entries[i];
}


void DirectoryAnalyzer::startAnalysis(QString directory, QString name, int flags){
    DIR *dir_d;
    struct dirent *dir_inode;

    char pathCharArray[MAX_FULL_PATH_SIZE];
    char nameCharArray[MAX_FULL_PATH_SIZE];
    char fullPathArray[MAX_FULL_PATH_SIZE];

    for(int i = 0; i < entries.size(); i++)
        if (entries[i])
            delete entries[i];
    entries.clear();

    if (!directory.endsWith("/")){
#ifdef DEBUG_SEPERATOR
        qDebug() << "Appending / to " << directory;
#endif
        directory.append("/");
    }


    strcpy(pathCharArray, directory.toLocal8Bit().data());
    strcpy(nameCharArray, name.toLocal8Bit().data());

    qDebug() << "Cat: " << pathCharArray << " - " << nameCharArray;


    sprintf(fullPathArray, "%s%s", pathCharArray, nameCharArray);

    if (strcmp(fullPathArray, ".") == 0 || strcmp(fullPathArray, "..") == 0)
        return;

    DirectoryEntry *rootEntry = statFile(pathCharArray, nameCharArray, flags, 0);
    root = rootEntry;
    entries.append(rootEntry);
    if (rootEntry->isDirectory()){
        if (!name.isEmpty() && !name.endsWith("/")){
#ifdef DEBUG_SEPERATOR
            qDebug() << "Name " << name;
            qDebug() << "Adding / to " << nameCharArray;
            qDebug() << "Adding / to " << fullPathArray;
#endif
            strcat(nameCharArray, "/");
            strcat(fullPathArray, "/");
        }
        if((dir_d = opendir(fullPathArray)) == NULL){
            perror("opendir");
            qDebug() << fullPathArray;
            return;
        }

        while((dir_inode = readdir(dir_d)) != NULL){

            if (strcmp(dir_inode->d_name, ".") == 0 || strcmp(dir_inode->d_name, "..") == 0 )
                continue;

            DirectoryEntry *newEntry = statFile(fullPathArray, dir_inode->d_name, 0, 1, rootEntry);
            if(!newEntry->isValid()){
                fprintf(stderr, "Invalid entry: %s%s\n", pathCharArray, dir_inode->d_name);
            }else{
                entries.append(newEntry);
                if (newEntry->isDirectory()){
                    recursePath(fullPathArray, dir_inode->d_name, 0, 2, newEntry);
                }
            }

        }
        closedir(dir_d);
    }

    emit analysisComplete();

}

