#ifndef ABSTRACTAUDIOFRAME_H
#define ABSTRACTAUDIOFRAME_H
#include "jmrijframe.h"
#include <QGroupBox>
#include <qslider.h>
#include "libtables_global.h"

class QScrollArea;
class QVBoxLayout;
class JSlider;
class QSpinBox;
class QDoubleSpinBox;
class Audio;
class QLabel;
class JTextField;
class AudioTableDataModel;
class LIBTABLESSHARED_EXPORT AbstractAudioFrame : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit AbstractAudioFrame(QWidget *parent = 0);
 /*public*/ AbstractAudioFrame(QString title, AudioTableDataModel* model, QWidget *parent = 0);
 virtual /*public*/ void layoutFrame();
 virtual /*abstract*/ /*public*/ void resetFrame();
 virtual /*public*/ void populateFrame(Audio* a);
 static /*final*/ int INT_PRECISION;// = (int) Math.pow(10, Audio.DECIMAL_PLACES);
 static /*final*/ float FLT_PRECISION;// = 1 / (float) INT_PRECISION;

signals:

public slots:
private:
 AbstractAudioFrame* frame;// = this;

 QWidget* main;// = new JPanel();
 QVBoxLayout* mainLayout;
 QScrollArea* scroll;
 QVBoxLayout* scrollLayout;
//         = new JScrollPane(main,
//                 ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
//                 ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

 AudioTableDataModel* model;
 // Common UI components for Add/Edit Audio
 QLabel* sysNameLabel;// = new JLabel(tr("LabelSystemName"));
 JTextField* sysName;// = new JTextField(5);
 QLabel* userNameLabel;// = new QLabel(tr("User Name"));
 JTextField* userName;// = new JTextField(15);

 protected:
 /*protected*/ bool entryError(QString entry, QString prefix, QString counter);

 friend class AudioSourceFrame;
 friend class JPanelSliderf;
 friend class AudioBufferFrame;
 friend class AudioListenerFrame;
};
class QDoubleSlider : public QWidget
{
 Q_OBJECT
 JSlider* slider;
public:
 QDoubleSlider(QWidget* parent = 0);
 void setMinimum(double min);
 void setMaximum(double max);
 double value();
public slots:
 void setValue(double);
private slots:
 void on_slider_valueChanged(int);
signals:
 void valueChanged(double);
};

/**
 * A convenience class to create a JPanel to edit a Vector3f object using 3
 * separate QSpinBox* Swing objects
 */
/*protected*/ /*static*/ class JPanelVector3f : public QGroupBox
{
 Q_OBJECT
    /**
     *
     */
//    private static final long serialVersionUID = -2102431744610108951L;
    QLabel* xLabel;// = new JLabel(rba.getString("LabelX"));
    QSpinBox* xValue;// = new JSpinner();
    QLabel* yLabel;// = new JLabel(rba.getString("LabelY"));
    QSpinBox* yValue;// = new JSpinner();
    QLabel* zLabel;// = new JLabel(rba.getString("LabelZ"));
    QSpinBox* zValue;// = new JSpinner();
    QLabel* unitsLabel;// = new JLabel();
    void common();

public:
    JPanelVector3f(QWidget* parent = 0);
    JPanelVector3f(QString title, QWidget* parent = 0);
    JPanelVector3f(QString title, QString units, QWidget* parent = 0);
    /*public*/ void setValue(QVector3D value);
    /*public*/ QVector3D getValue();
private:
    /*private*/ void layoutPanel(QString title, QString units) ;
};

/**
 * A convenience class to create a JPanel for editing a float value using
 * combined JSlider and JSPinner Swing objects
 */
/*protected*/ /*static*/ class JPanelSliderf : public QGroupBox
{
 Q_OBJECT
    /**
     *
     */
//    private static final long serialVersionUID = -7201712611650896844L;

    QDoubleSlider* slider;// = new JSlider();

    QDoubleSpinBox* spinner;// = new JSpinner();
public:
    JPanelSliderf(QString title, float min, float max, int majorTicks, int minorTicks);
    /*public*/ void setValue(float value) ;
    /*public*/ float getValue();
public slots:
    void On_spinner_valueChanged();
    void On_sliderValueChanged();
};

#endif // ABSTRACTAUDIOFRAME_H
