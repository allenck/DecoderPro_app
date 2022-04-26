#ifndef FILEHISTORY_H
#define FILEHISTORY_H

#include <QObject>
#include <QMetaType>
#include "liblayouteditor_global.h"
#include "instancemanagerautodefault.h"

class OperationMemo;
class LIBLAYOUTEDITORSHARED_EXPORT  FileHistory : public QObject, public InstanceManagerAutoDefault
{
 Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
public:
 /*public*/ class OperationMemo
 {
 public:
     /*public*/ QString type;  // load, store
     /*public*/ QString date;
     /*public*/ QString filename;
     /*public*/ FileHistory* history;  // only with load
 };
 Q_INVOKABLE explicit FileHistory(QObject *parent = 0);
 ~FileHistory() {}
 FileHistory(const FileHistory&) : QObject() {}
 /*public*/ void addOperation(
         QString type,
         QString date,
         QString filename,
         FileHistory* history
 );
 /*public*/ void addOperation(OperationMemo* r);
 /*public*/ void addOperation(
         QString type,
         QString filename,
         FileHistory* history
 );
 /*public*/ void purge(int keep);
 /*public*/ QString toString(QString prefix);
 /*public*/ QString toString();
 /*public*/ QList<OperationMemo*> getList();

signals:

public slots:
private:
 QList<OperationMemo*> list;// = new QList<OperationMemo*>();

};
Q_DECLARE_METATYPE(FileHistory)


#endif // FILEHISTORY_H
