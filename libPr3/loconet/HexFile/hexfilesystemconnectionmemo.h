#ifndef HEXFILESYSTEMCONNECTIONMEMO_H
#define HEXFILESYSTEMCONNECTIONMEMO_H
#include "loconetsystemconnectionmemo.h"

class HexFileSystemConnectionMemo : public LocoNetSystemConnectionMemo
{
 Q_OBJECT

public:
 HexFileSystemConnectionMemo(QObject* parent = nullptr);
 /*public*/ LnSensorManager* getSensorManager();

};

#endif // HEXFILESYSTEMCONNECTIONMEMO_H
