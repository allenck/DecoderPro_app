#ifndef DEFAULTBACKUP_H
#define DEFAULTBACKUP_H
#include "backupbase.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT DefaultBackup : public BackupBase
 {
  Q_OBJECT
 public:
  explicit DefaultBackup(QObject *parent = 0);

 signals:

 public slots:

 };
}
#endif // DEFAULTBCKUP_H
