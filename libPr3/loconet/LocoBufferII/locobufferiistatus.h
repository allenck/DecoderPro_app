#ifndef LOCOBUFFERIISTATUS_H
#define LOCOBUFFERIISTATUS_H

#include <QObject>

class LocoBufferIIStatus : public QObject
{
 Q_OBJECT
public:
 explicit LocoBufferIIStatus(int version, int breaks, int errors, QObject *parent = nullptr);
 /*public*/ int version, breaks, errors;

signals:

public slots:
};

#endif // LOCOBUFFERIISTATUS_H
