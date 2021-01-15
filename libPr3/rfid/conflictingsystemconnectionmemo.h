#ifndef CONFLICTINGSYSTEMCONNECTIONMEMO_H
#define CONFLICTINGSYSTEMCONNECTIONMEMO_H
#include "defaultsystemconnectionmemo.h"

class ConflictingSystemConnectionMemo : public DefaultSystemConnectionMemo
{
 Q_OBJECT
public:
 /*public*/ ConflictingSystemConnectionMemo(QString prefix, QString userName, QObject* parent = nullptr);

 /*public*/ void _register();

};

#endif // CONFLICTINGSYSTEMCONNECTIONMEMO_H
