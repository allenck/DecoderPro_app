#ifndef SENSORGROUPCONDITIONAL_H
#define SENSORGROUPCONDITIONAL_H
#include "defaultconditional.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT SensorGroupConditional : public DefaultConditional
{
    Q_OBJECT
public:
    //explicit SensorGroupConditional(QObject *parent = 0);
    /*public*/ SensorGroupConditional(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ int calculate (bool enabled, PropertyChangeEvent* evt);

signals:

public slots:
private:
    Logger* log;
};

#endif // SENSORGROUPCONDITIONAL_H
