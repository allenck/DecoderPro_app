#ifndef CTCFILES_H
#define CTCFILES_H

#include <QObject>

class File;
class Logger;
class CTCFiles : public QObject
{
  Q_OBJECT
 public:
  //explicit CTCFiles(QObject *parent = nullptr);
  /*public*/ static File* getFile(QString fileName);
  /*public*/ static QString getFileLocation();
  /*public*/ static QString getFullName(QString fileName);
  /*public*/ static bool fileExists(QString fileName);
  /*public*/ static bool copyFile(QString sourceFileName, QString destFileName, bool replace);
  /*public*/ static bool renameFile(QString oldFileName, QString newFileName, bool replace);
  /*public*/ static bool deleteFile(QString fileName);
  /*public*/ static QString addExtensionIfMissing(QString path, QString missingExtension);
  /*public*/ static QString changeExtensionTo(QString path, QString newExtension);
  /*public*/ static QString removeFileExtension(QString filename);
  /*public*/ static QString getFilenameOnly(QString path);

 signals:

 public slots:
 private:
  static Logger* log;
};

#endif // CTCFILES_H
