#ifndef TEMPORARYFOLDER_H
#define TEMPORARYFOLDER_H

#include <QObject>
#include "file.h"
#include "exceptions.h"


class TemporaryFolder : public QObject
{
    Q_OBJECT
public:
    explicit TemporaryFolder(QObject *parent = nullptr);
    /*public*/ TemporaryFolder(File* parentFolder,QObject *parent);

    /*public*/ File* newFolder(QString folder) /*throw (IOException)*/;
    /*public*/ File* newFolder() /*throw (IOException)*/;

signals:

public slots:
private:
    /*private*/ /*final*/ File* parentFolder;
    /*private*/ File* folder;

};

#endif // TEMPORARYFOLDER_H
