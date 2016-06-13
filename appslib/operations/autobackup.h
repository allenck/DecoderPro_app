#ifndef AUTOBACKUP_H
#define AUTOBACKUP_H
#include "backupbase.h"
#include "appslib_global.h"
namespace Operations
{
class APPSLIBSHARED_EXPORT AutoBackup : public BackupBase
{
 Q_OBJECT
public:
 explicit AutoBackup(QObject *parent = 0);
 /*public*/ /*synchronized*/ void autoBackup(); //throws IOException

signals:

public slots:

};
}
#endif // AUTOBACKUP_H
