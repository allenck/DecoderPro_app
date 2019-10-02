#ifndef CONFLICTINGSYSTEMCONNECTIONMEMO_H
#define CONFLICTINGSYSTEMCONNECTIONMEMO_H
#include "systemconnectionmemo.h"

class ConflictingSystemConnectionMemo : public SystemConnectionMemo
{
public:
 /*public*/ ConflictingSystemConnectionMemo(QString prefix, QString userName, QObject* parent = nullptr);

 /*public*/ void _register();

};

#endif // CONFLICTINGSYSTEMCONNECTIONMEMO_H
