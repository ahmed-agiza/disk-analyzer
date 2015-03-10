#ifndef DIRECTORYENTRY_H
#define DIRECTORYENTRY_H

#include <QString>
#include <QSet>

typedef enum {BLOCK_DEVICE, CHARACTER_DEVICE, DIRECTORY, FIFO_PIPE, SYMLINK, REGULAR_FILE, SOCKET, UNKNOWN} ENTRY_TYPE;

class DirectoryEntry{

public:
    DirectoryEntry();
    DirectoryEntry(QString, QString, long long, long long, int, DirectoryEntry * = 0, QSet<DirectoryEntry *> = QSet<DirectoryEntry *> ());

    QString getName() const;
    void setName(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    int getDepth() const;
    void setDepth(int value);

    long long getEntrySize() const;
    void setEntrySize(long long value);

    DirectoryEntry *getSource() const;
    void setSource(DirectoryEntry *value);

    bool isValid() const;
    void setValidity(bool value);

    QSet<DirectoryEntry *> getChildren() const;
    void setChildren(const QSet<DirectoryEntry *> &value);
    void addChild(DirectoryEntry *value);
    void removeChild(DirectoryEntry* value);

    QString toQString(bool humanReadable = false) const;

    ENTRY_TYPE getType() const;
    void setType(const ENTRY_TYPE &value);

    bool isDirectory() const;
    bool isRegularFile() const;

    long long getNumberOfBlocks() const;
    void setNumberOfBlocks(long long value);

    QString getFullPath() const;

    static QString getFormattedSize(long long);

    long long getTotalSize();


    bool operator==(DirectoryEntry &other);
    bool operator!=(DirectoryEntry &other);
    bool operator<(DirectoryEntry &other);
    bool operator>(DirectoryEntry &other);
    bool operator<=(DirectoryEntry &other);
    bool operator>=(DirectoryEntry &other);

    static bool isLessThan(DirectoryEntry *first, DirectoryEntry *second);
    static bool pairIsLessThan(QPair<QString, long long> &first, QPair<QString, long long> &second);


    bool isExecutable() const;
    void setExecutable(bool value);

private:
    QString name;
    QString path;
    int depth;
    long long entrySize;
    long long numberOfBlocks;
    DirectoryEntry *source;
    QSet<DirectoryEntry *> children;
    bool valid;
    ENTRY_TYPE type;
    long long totalSizeCache;
    bool executable;

};

typedef QList<DirectoryEntry *> DirectoryEntriesList;


#endif // DIRECTORYENTRY_H
