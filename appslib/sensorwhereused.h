#ifndef SENSORWHEREUSED_H
#define SENSORWHEREUSED_H

#include <QObject>

class JTextArea;
class NamedBean;
class SensorWhereUsed : public QObject
{
 Q_OBJECT
 explicit SensorWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* sensor);

signals:

public slots:
};

#endif // SENSORWHEREUSED_H
