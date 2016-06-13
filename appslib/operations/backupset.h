#ifndef BACKUPSET_H
#define BACKUPSET_H

#include <QObject>
#include <QDate>
#include "appslib_global.h"

class QDate;
class File;
namespace Operations
{
 class APPSLIBSHARED_EXPORT BackupSet : public QObject
 {
  Q_OBJECT
 public:
   explicit BackupSet(QObject *parent = 0);
  /*public*/ BackupSet(File* dir, QObject *parent = 0);
  ~BackupSet() {}
  BackupSet(const BackupSet&) {}
  /*public*/ void _delete();
  /*public*/ QString getSetName();
  /*public*/ QString toString();

 signals:

 public slots:
 private:
  /*private*/ QString _setName;
  /*private*/ QDate _lastModifiedDate;
  /*private*/ File* _dir;
  /*private*/ void deleteDirectoryAndFiles(File* dir);

 };
}
Q_DECLARE_METATYPE(Operations::BackupSet)
#endif // BACKUPSET_H
