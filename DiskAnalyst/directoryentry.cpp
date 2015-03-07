#include "directoryentry.h"
#include <QString>

DirectoryEntry::DirectoryEntry(QString name, QString path, long long size, long long numberOfBlock, int depth, DirectoryEntry *source, QSet<DirectoryEntry *> children)
    :valid(false), type(UNKNOWN){
    setName(name);
    setPath(path);
    setEntrySize(size);
    setDepth(depth);
    setSource(source);
    setChildren(children);
    setNumberOfBlocks(numberOfBlocks);
}

QString DirectoryEntry::getName() const{
    return name;
}

void DirectoryEntry::setName(const QString &value){
    name = value;
}
QString DirectoryEntry::getPath() const{
    return path;
}

void DirectoryEntry::setPath(const QString &value){
    QString newPath(value);
    if (newPath.endsWith("//"))
        newPath.remove(newPath.length() - 1, 1);
    if (!newPath.endsWith("/"))
        newPath.append("/");
    path = newPath;
}
int DirectoryEntry::getDepth() const{
    return depth;
}

void DirectoryEntry::setDepth(int value){
    depth = value;
}
long long DirectoryEntry::getEntrySize() const{
    return entrySize;
}

void DirectoryEntry::setEntrySize(long long value){
    entrySize = value;
}
DirectoryEntry *DirectoryEntry::getSource() const{
    return source;
}

void DirectoryEntry::setSource(DirectoryEntry *value){
    source = value;
}

bool DirectoryEntry::isValid() const{
    return valid;
}

void DirectoryEntry::setValidity(bool value){
    valid = value;
}
QSet<DirectoryEntry *> DirectoryEntry::getChildren() const{
    return children;
}

void DirectoryEntry::setChildren(const QSet<DirectoryEntry *> &value){
    children = value;
}

void DirectoryEntry::addChild(DirectoryEntry *value){
    children.insert(value);
}

void DirectoryEntry::removeChild(DirectoryEntry *value){
    children.remove(value);
}

QString DirectoryEntry::toQString(bool humanReadable) const{
    QString result("Name: ");
    result.append(getName());
    result.append("\n");
    result.append("Path: ");
    result.append(getPath());
    result.append("\n");
    result.append("Size: ");
    if(humanReadable){
        if (getEntrySize() <= 1000)
            result.append(QString::number(getEntrySize()) + QString("B"));
          else if (getEntrySize() <= 1000000)
            result.append(QString::number(getEntrySize()/1000.0) + QString("KB"));
          else if(getEntrySize() <= 1000000000)
            result.append(QString::number(getEntrySize()/1000000.0) + QString("MB"));
          else
            result.append(QString::number(getEntrySize()/1000000000.0) + QString("GB"));
    }else{
        result.append(QString::number(getEntrySize()));
        result.append("B");
    }
    result.append("\n");
    result.append("Depth: ");
    result.append(QString::number(getDepth()));
    result.append("\n");
    return result;
}
ENTRY_TYPE DirectoryEntry::getType() const{
    return type;
}

void DirectoryEntry::setType(const ENTRY_TYPE &value){
    type = value;
}

bool DirectoryEntry::isDirectory() const{
    return (type == DIRECTORY);
}

bool DirectoryEntry::isRegularFile() const{
   return (type == REGULAR_FILE);
}
long long DirectoryEntry::getNumberOfBlocks() const
{
    return numberOfBlocks;
}

void DirectoryEntry::setNumberOfBlocks(long long value)
{
    numberOfBlocks = value;
}


