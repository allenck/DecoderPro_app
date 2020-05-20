#ifndef NAMEDBEANUSAGEREPORT_H
#define NAMEDBEANUSAGEREPORT_H

#include <QObject>

class NamedBean;
class NamedBeanUsageReport : public QObject
{
 Q_OBJECT
public:
 /*public*/ NamedBeanUsageReport(/*@Nonnull*/ QString usageKey);
 /*public*/ NamedBeanUsageReport(/*@Nonnull*/ QString usageKey, NamedBean* usageBean);
 /*public*/ NamedBeanUsageReport(/*@Nonnull*/ QString usageKey, QString usageData);
 /*public*/ NamedBeanUsageReport(/*@Nonnull*/ QString usageKey, NamedBean* usageBean, QString usageData);

 /*final*/ /*public*/ QString usageKey;
 /*final*/ /*public*/ NamedBean* usageBean;
 /*final*/ /*public*/ QString usageData;

signals:

public slots:
};

#endif // NAMEDBEANUSAGEREPORT_H
