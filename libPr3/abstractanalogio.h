#ifndef ABSTRACTANALOGIO_H
#define ABSTRACTANALOGIO_H
#include "abstractnamedbean.h"
#include "analogio.h"

class AbstractAnalogIO : public /*AbstractNamedBean*/ AnalogIO
{
  Q_OBJECT
 public:
  AbstractAnalogIO(/*@Nonnull*/ QString systemName, bool commandedValueSetsKnownValue, QObject* parent = nullptr);
  /*public*/ AbstractAnalogIO(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName, bool commandedValueSetsKnownValue, QObject *parent=nullptr);
  /*public*/ void setCommandedAnalogValue(double value) throw (JmriException);
  /*public*/ double getCommandedAnalogValue();
  /*public*/ double getKnownAnalogValue();
  /*public*/ double getState(double v);
  /*public*/ void setState(double value) throw (JmriException);
  /*public*/ QString getBeanType();
  /*public*/ int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n);

 private:
  /*private*/ /*final*/ bool _commandedValueSetsKnownValue;
  /*private*/ double _commandedValue = 0.0;
  /*private*/ double _knownValue = 0.0;
protected:
  /*abstract*/ virtual /*protected*/ void sendValueToLayout(double value) throw (JmriException) =0;
  /*protected*/ void setValue(double newValue);
  /*abstract*/ virtual /*protected*/ bool cutOutOfBoundsValues() =0;

};

#endif // ABSTRACTANALOGIO_H
