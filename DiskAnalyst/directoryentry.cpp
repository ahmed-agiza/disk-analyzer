﻿#include "directoryentry.h"
#include <QString>



DirectoryEntry::DirectoryEntry():valid(false), type(UNKNOWN){

}

DirectoryEntry::DirectoryEntry(QString name, QString path, long long size, long long numberOfBlocks, int depth, DirectoryEntry *source, QSet<DirectoryEntry *> children)
    :valid(false), type(UNKNOWN), totalSizeCache(-1), executable(false){
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
        result.append(getFormattedSize(getEntrySize()));
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
long long DirectoryEntry::getNumberOfBlocks() const{
    return numberOfBlocks;
}

void DirectoryEntry::setNumberOfBlocks(long long value){
    numberOfBlocks = value;
}

QString DirectoryEntry::getFullPath() const{
    QString mPath = getPath();
    QString mName = getName();
    if (!mPath.endsWith("/"))
        mPath.append("/");
    if (mName.startsWith("/"))
        mName.remove(0, 1);
    return mPath + mName;
}

QString DirectoryEntry::getFormattedSize(long long size){
    if (size <= 1000)
        return QString(QString::number(size) + QString("B"));
      else if (size <= 1000000)
        return QString(QString::number(size/1000.0) + QString("KB"));
      else if(size <= 1000000000)
        return QString(QString::number(size/1000000.0) + QString("MB"));
      else
        return QString(QString::number(size/1000000000.0) + QString("GB"));
}
long long DirectoryEntry::getTotalSize(){
    if (totalSizeCache != -1)
        return totalSizeCache;
    if(isDirectory()){
        long long totalSize = 0;
        if(children.isEmpty()){
            totalSizeCache = 0;
            return 0;
        }else{
            for(QSet<DirectoryEntry *>::iterator i = children.begin(); i != children.end(); i++){
                if((*i)->isDirectory())
                    totalSize += (*i)->getEntrySize() + (*i)->getTotalSize();
                else
                    totalSize += (*i)->getEntrySize();
            }
            totalSizeCache = totalSize;
            return totalSize;
        }
    }else{
        totalSizeCache = getEntrySize();
        return getEntrySize();
    }
}

bool DirectoryEntry::operator==(DirectoryEntry &other){
    return (getTotalSize() == other.getTotalSize());
}

bool DirectoryEntry::operator!=(DirectoryEntry &other){
    return (getTotalSize() != other.getTotalSize());
}

bool DirectoryEntry::operator<(DirectoryEntry &other){
    return (getTotalSize() < other.getTotalSize());
}

bool DirectoryEntry::operator>(DirectoryEntry &other){
    return (getTotalSize() > other.getTotalSize());
}

bool DirectoryEntry::operator<=(DirectoryEntry &other){
    return (getTotalSize() <= other.getTotalSize());
}

bool DirectoryEntry::operator>=(DirectoryEntry &other){
    return (getTotalSize() >= other.getTotalSize());
}

bool DirectoryEntry::isLessThan(DirectoryEntry *first, DirectoryEntry *second){
    return first->getTotalSize() < second->getTotalSize();
}

bool DirectoryEntry::pairIsLessThan(QPair<QString, long long> &first, QPair<QString, long long> &second){
    return (first.second < second.second);
}
bool DirectoryEntry::isExecutable() const{
    return executable;
}

void DirectoryEntry::setExecutable(bool value){
    executable = value;
}





