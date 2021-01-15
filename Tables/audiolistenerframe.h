#ifndef AUDIOLISTENERFRAME_H
#define AUDIOLISTENERFRAME_H
#include "abstractaudioframe.h"
#include "libtables_global.h"

class JSpinner;
class JActionEvent;
class LIBTABLESSHARED_EXPORT AudioListenerFrame : public AbstractAudioFrame
{
 Q_OBJECT
public:
 //explicit AudioListenerFrame(QWidget *parent = 0);
 /*public*/ AudioListenerFrame(QString title, AudioTableDataModel* model, QWidget *parent = 0);
 /*public*/ void layoutFrame();
 /*public*/ void resetFrame();
 /*public*/ void populateFrame(Audio* a);
 /*public*/ QString getClassName();

signals:

public slots:
 void applyPressed(JActionEvent* /*e*/ = 0);
private:
 JPanelVector3f* position;// = new JPanelVector3f(rba.getString("LabelPosition"),
//         rba.getString("UnitUnits"));
 JPanelVector3f* velocity;// = new JPanelVector3f(rba.getString("LabelVelocity"),
//         rba.getString("UnitU/S"));
 QLabel* oriAtLabel;// = new JLabel(rba.getString("LabelOrientationAt"));
 JPanelVector3f* oriAt;// = new JPanelVector3f("", rba.getString("UnitUnits"));
 QLabel* oriUpLabel;// = new JLabel(rba.getString("LabelOrientationUp"));
 JPanelVector3f* oriUp;// = new JPanelVector3f("", rba.getString("UnitUnits"));
 JPanelSliderf* gain;// = new JPanelSliderf(rba.getString("LabelGain"), 0.0f, 1.0f, 5, 4);
 JSpinner* metersPerUnit;// = new JSpinner();
 QLabel* metersPerUnitLabel;// = new JLabel(rba.getString("UnitM/U"));
 /*private*/ /*final*/ static QString PREFIX;// = "IAL";

};

#endif // AUDIOLISTENERFRAME_H
