#ifndef FLOATCONTROL_H
#define FLOATCONTROL_H
#include "control.h"

class FloatControl : public Control
{
 Q_OBJECT
public:
 //explicit FloatControl(QObject *parent = 0);
 /*public*/ void setValue(float newValue);
  /*public*/ float getValue();
 /*public*/ float getMaximum();
 /*public*/ float getMinimum();
 /*public*/ QString getUnits();
 /*public*/ QString getMinLabel();
 /*public*/ QString getMidLabel();
 /*public*/ QString getMaxLabel();
 /*public*/ float getPrecision();
 /*public*/ int getUpdatePeriod();
 /*public*/ void shift(float from, float to, int microseconds);
 /*public*/ QString toString();

 class Type : public Control::Type
 {
 public:
  /*public*/ static /*final*/ Type* MASTER_GAIN;//            = new Type("Master Gain");
  /*public*/ static /*final*/ Type* AUX_SEND;//                       = new Type("AUX Send");
  /*public*/ static /*final*/ Type* AUX_RETURN;//                     = new Type("AUX Return");
  /*public*/ static /*final*/ Type* REVERB_SEND;//            = new Type("Reverb Send");
  /*public*/ static /*final*/ Type* REVERB_RETURN;//          = new Type("Reverb Return");
  /*public*/ static /*final*/ Type* VOLUME;//                         = new Type("Volume");
  /*public*/ static /*final*/ Type* PAN;//                            = new Type("Pan");
  /*public*/ static /*final*/ Type* BALANCE;//                        = new Type("Balance");
  /*public*/ static /*final*/ Type* SAMPLE_RATE;//            = new Type("Sample Rate");
 protected:
  /*protected*/ Type(QString name, QObject* parent = 0);

 };

signals:

public slots:
private:
 // FINAL VARIABLES

 /**
  * The minimum supported value.
  */
 /*private*/ float minimum;

 /**
  * The maximum supported value.
  */
 /*private*/ float maximum;

 /**
  * The control's precision.
  */
 /*private*/ float precision;

 /**
  * The smallest time increment in which a value change
  * can be effected during a value shift, in microseconds.
  */
 /*private*/ int updatePeriod;


 /**
  * A label for the units in which the control values are expressed,
  * such as "dB" for decibels.
  */
 /*private*/ /*final*/ QString units;

 /**
  * A label for the minimum value, such as "Left."
  */
 /*private*/ /*final*/ QString minLabel;

 /**
  * A label for the maximum value, such as "Right."
  */
 /*private*/ /*final*/ QString maxLabel;

 /**
  * A label for the mid-point value, such as "Center."
  */
 /*private*/ /*final*/ QString midLabel;
 // STATE VARIABLES

 /**
  * The current value.
  */
 /*private*/ float value;

protected:
 /*protected*/ FloatControl(Type* type, float minimum, float maximum,
         float precision, int updatePeriod, float initialValue,
         QString units, QString minLabel ="", QString midLabel="", QString maxLabel ="",
         QObject* parent = 0);

};

#endif // FLOATCONTROL_H
