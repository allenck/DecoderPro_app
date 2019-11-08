#ifndef TRACKREPORTER_H
#define TRACKREPORTER_H
#include "abstractreporter.h"

//class Deque;
class Collection;
class TrackReporter : public AbstractReporter
{
public:
 /*public*/ TrackReporter(QString systemName, QObject* parent = nullptr);
 /*public*/ TrackReporter(QString systemName, QString userName, QObject* parent = nullptr);
 /*public*/ void setReport(QVariant r) override;
 /*public*/ int getState() override;
 /*public*/ void setState(int s) override;
 virtual /*public*/ Collection* getCollection();
 /*public*/ void pushEast(QVariant o);
 /*public*/ void pushWest(QVariant o);
 /*public*/ QVariant pullEast();
 /*public*/ QVariant pullWest();

private:
 // /*private*/ Deque* collection = nullptr;
 /*private*/ Collection* collection = nullptr;

  int state = 0;


};

#endif // TRACKREPORTER_H
