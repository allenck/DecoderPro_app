#ifndef PROGDEFAULT_H
#define PROGDEFAULT_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ProgDefault : public QObject
{
    Q_OBJECT
public:
    explicit ProgDefault(QObject *parent = 0);
    /*volatile*/ static QString defaultProgFile;
    static /*public*/ QStringList findListOfProgFiles();
    /*synchronized*/ static /*public*/ QString getDefaultProgFile();
    /*synchronized*/ static /*public*/ void         setDefaultProgFile(QString s);

signals:

public slots:

};

#endif // PROGDEFAULT_H
