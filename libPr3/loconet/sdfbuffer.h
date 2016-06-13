#ifndef SDFBUFFER_H
#define SDFBUFFER_H

#include <QObject>

class Logger;
class SdfMacro;
class SdfBuffer : public QObject
{
 Q_OBJECT
public:
 //explicit SdfBuffer(QObject *parent = 0);
 /*public*/ SdfBuffer(QVector<char>* buffer, QObject *parent = 0);
 /*public*/ SdfBuffer(QString name, QObject *parent);
 /*public*/ void resetIndex();
 /*public*/ int getAtIndex();
 /*public*/ int getAtIndexAndInc();
 /*public*/ bool moreData();
 /*public*/ void setAtIndex(int data);
 /*public*/ void setAtIndexAndInc(int data);
 /*public*/ void loadByteArray();
 /*public*/ QString toString();
 /*public*/ QVector<char>* getByteArray();
 /*public*/ QList<SdfMacro*>* getMacroList();

signals:
 void error(QString);

public slots:
private:
 void loadMacroList();
 // List of contained instructions
 QList<SdfMacro*>* ops;

 // byte[] representation
 QVector<char>* buffer;
 Logger* log;
protected:
 /*protected*/ int index;

};

#endif // SDFBUFFER_H
