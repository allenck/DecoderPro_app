#ifndef FILEHISTORYXML_H
#define FILEHISTORYXML_H
#include "abstractxmladapter.h"
#include "filehistory.h"


class FileHistory;
class FileHistoryXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit FileHistoryXml(QObject *parent = 0);
 /*public*/ bool load(QDomElement e) throw (Exception);
 /*public*/ bool loadDirectly(QDomElement e) throw (Exception);
 static /*public*/ FileHistory* loadFileHistory(QDomElement e);
 static /*public*/ void loadOperation(FileHistory* r, QDomElement e);
 /*public*/ void load(QDomElement e, QObject* o) throw (Exception);
 /*public*/ QDomElement store(QObject* o);
 static /*public*/ QDomElement storeDirectly(QObject* o, QDomDocument doc);
 static QDomElement historyElement(FileHistory* r, int depth, QDomDocument doc);
 static QDomElement operationElement(FileHistory::OperationMemo* r, int depth, QDomDocument doc);

signals:

public slots:
private:
 static int defaultDepth;// = 5;

};
class MyOperationMemo : public FileHistory::OperationMemo
{
public:
 MyOperationMemo();
};

#endif // FILEHISTORYXML_H
