#ifndef RAWSTATUS_H
#define RAWSTATUS_H

#include <QObject>
#include <QVector>
class RawStatus : public QObject
{
 Q_OBJECT
public:
 explicit RawStatus(int rawdata0, int rawdata1, int rawdata2, int rawdata3, int rawdata4, int rawdata5, int rawdata6, int rawdata7, QObject *parent = nullptr);
 /**
  * raw data
  */
 /*public*/ QVector<int> raw = QVector<int>(8);

signals:

public slots:
};

#endif // RAWSTATUS_H
