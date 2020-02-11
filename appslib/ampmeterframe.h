#ifndef AMPMETERFRAME_H
#define AMPMETERFRAME_H

#include "jmrijframe.h"
#include "jlabel.h"
#include "namedicon.h"
#include "multimeter.h"

class QPushButton;
class AmpMeterFrame : public JmriJFrame
{
 Q_OBJECT
public:
 AmpMeterFrame(QWidget* parent = nullptr);
 /*public*/ void initComponents();
 /*synchronized*/ /*public*/ void scaleImage();
 /*public*/ void dispose();
 /*public*/ QString getClassName() { return "jmri.jmrit.ampmeter.AmpMeterFrame";}

public slots:
 void propertyChange(PropertyChangeEvent*) { update();}

private:
 QPushButton* b;
 // GUI member declarations
 QList<JLabel*> digitIcons;
 JLabel* percent;
 JLabel* decimal;
 JLabel* milliAmp;
 JLabel* amp;

 double aspect;
 double iconAspect;

 /*private*/ int startWidth;
 /*private*/ int startHeight;

 MultiMeter* meter;

 QVector<NamedIcon*> digits;// = new NamedIcon[10];
 NamedIcon* percentIcon;
 NamedIcon* decimalIcon;
 NamedIcon* milliAmpIcon;
 NamedIcon* ampIcon;
 /*private*/ void buildContents();
 /*synchronized*/ void update();
 void resizeEvent(QResizeEvent *e);

private slots:
 void on_button_clicked();


};

#endif // AMPMETERFRAME_H
