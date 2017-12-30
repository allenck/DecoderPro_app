#ifndef CONNECTIONNAMEFROMSYSTEMNAME_H
#define CONNECTIONNAMEFROMSYSTEMNAME_H

#include <QObject>
#include "libPr3_global.h"

class SystemConnectionMemo;
class LIBPR3SHARED_EXPORT ConnectionNameFromSystemName : public QObject
{
    Q_OBJECT
public:
    //explicit ConnectionNameFromSystemName(QObject *parent = 0);
    static /*public*/ QString getConnectionName(QString prefix);
    static /*public*/ QString getPrefixFromName(QString name);
    static /*public*/ SystemConnectionMemo* getSystemConnectionMemoFromSystemPrefix(/*@Nonnull */QString systemPrefix);
    static /*public*/ SystemConnectionMemo* getSystemConnectionMemoFromUserName(/*@Nonnull*/ QString userName);

signals:

public slots:

};

#endif // CONNECTIONNAMEFROMSYSTEMNAME_H
