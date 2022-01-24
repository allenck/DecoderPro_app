#include "sensor.h"
#include "loggerfactory.h"

//Sensor::Sensor(QObject *parent)
//{
//}
//const /*static*/ int Sensor::ACTIVE       =0x02;
//const /*static*/ int Sensor::INACTIVE     =0x04;
Sensor::Sensor(QObject *parent) : AbstractNamedBean(parent) {}
Sensor::Sensor(QString sysName, QObject* parent) : AbstractNamedBean(sysName, parent) {}
Sensor::Sensor(QString sysName, QString userName, QObject* parent) : AbstractNamedBean(sysName, userName, parent) {}
/** {@inheritDoc} */
//@Override
/*default*/ /*public*/ int Sensor::getCommandedState() {
    return getState();
}
/*public*/ void Sensor::setCommandedState(int s)
{
 try {
     setState(s);
 } catch (JmriException* ex) {
     log->error("setCommandedState", ex);
 }

}

/*final*/ /*static*/ Logger* Sensor::log = LoggerFactory::getLogger("Sensor");
