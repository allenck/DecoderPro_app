#ifndef AMPMETERFRAME_H
#define AMPMETERFRAME_H

#include "jmrijframe.h"
#include "jlabel.h"
#include "namedicon.h"
#include "abstractmultimeter.h"

class QPushButton;
class AmpMeterFrame : public JmriJFrame, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
 AmpMeterFrame(QWidget* parent = nullptr);
 /*public*/ void initComponents() override;
 /*synchronized*/ /*public*/ void scaleImage();
 /*public*/ void dispose() override;
 /*public*/ QString getClassName()  override{ return "jmri.jmrit.ampmeter.AmpMeterFrame";}
 QObject* pself() override {return (QObject*)this;}

public slots:
 void propertyChange(PropertyChangeEvent*) override { update();}

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

 AbstractMultiMeter* meter;

 QVector<NamedIcon*> digits;// = new NamedIcon[10];
 NamedIcon* percentIcon;
 NamedIcon* decimalIcon;
 NamedIcon* milliAmpIcon;
 NamedIcon* ampIcon;
 /*private*/ void buildContents();
 /*synchronized*/ void update();
 void resizeEvent(QResizeEvent *e)override;
 bool initDone = false;

private slots:
 void on_button_clicked();


};

#endif // AMPMETERFRAME_H
