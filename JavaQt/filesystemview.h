#ifndef FILESYSTEMVIEW_H
#define FILESYSTEMVIEW_H

#include <QObject>
#include "file.h"

class FileSystemView : public QObject
{
  Q_OBJECT
 public:
  explicit FileSystemView(QObject *parent = nullptr);

  /*public*/ bool isParent(File* file, File* file1);
 signals:

};

#endif // FILESYSTEMVIEW_H
