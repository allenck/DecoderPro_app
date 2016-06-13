#ifndef PROFILEFILEFILTER_H
#define PROFILEFILEFILTER_H
#include "filefilter.h"

class ProfileFileFilter : public FileFilter
{
    Q_OBJECT
public:
    explicit ProfileFileFilter(QObject *parent = 0);
    /*public*/ bool accept(File* f);
    /*public*/ QString getDescription();

signals:

public slots:

};

#endif // PROFILEFILEFILTER_H
