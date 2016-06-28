#ifndef REPORTCONTEXT_H
#define REPORTCONTEXT_H

#include <QObject>

class ReportContext : public QObject
{
 Q_OBJECT
public:
 explicit ReportContext(QObject *parent = 0);
 /*public*/ QString getReport(bool reportNetworkInfo);
 /*public*/ void addScreenSize();

signals:

public slots:
private:
 QString report;// = "";
 void addString(QString val);
 void addProperty(QString prop);
 /*private*/ void addNetworkInfo();
 /*private*/ void addCommunicationPortInfo();

};

#endif // REPORTCONTEXT_H
