#ifndef AUDIOSOURCEFRAME_H
#define AUDIOSOURCEFRAME_H
#include "abstractaudioframe.h"

class QComboBox;
class QSpinBox;
class QCheckBox;
class JActionEvent;
class AudioTableDataModel;
class Audio;
class QLabel;
class AudioSourceFrame : public AbstractAudioFrame
{
 Q_OBJECT
public:
// explicit AudioSourceFrame(QWidget *parent = 0);
 /*public*/ AudioSourceFrame(QString title, AudioTableDataModel* model, QWidget *parent = 0);
 /*public*/ void resetFrame();
 /*public*/ void populateFrame(Audio* a);
 /*public*/ void updateBufferList();
 /*public*/ void layoutFrame();
 /*public*/ QString getClassName();

signals:

public slots:
 void okPressed(JActionEvent* e = 0);
 void On_loopMin_valueChanged();
 void On_loopMax_valueChanged();
 void On_loopInfinite_toggled();
 void On_refDistance_valueChanged();
 void On_maxDistance_valueChanged();
private:
// /*private*/ static final long serialVersionUID = -933611748183387484L;

 /*private*/ static int counter;// = 1;

 /*private*/ bool _newSource;

 /*private*/ /*final*/ QObject* lock;// = new Object();

 // UI components for Add/Edit Source
 QLabel* assignedBufferLabel;// = new JLabel(tr("LabelAssignedBuffer"));
 QComboBox* assignedBuffer;// = new JComboBox<String>();
 QLabel* loopMinLabel;// = new JLabel(tr("LabelLoopMin"));
 QSpinBox* loopMin;// = new JSpinner();
 QLabel* loopMaxLabel;// = new JLabel(tr("LabelLoopMax"));
 QSpinBox* loopMax;// = new JSpinner();
 //    QLabel* loopMinDelayLabel = new JLabel(tr("LabelLoopMin"));
 //    QSpinBox* loopMinDelay = new JSpinner();
 //    QLabel* loopMaxDelayLabel = new JLabel(tr("LabelLoopMax"));
 //    QSpinBox* loopMaxDelay = new JSpinner();
 //    QLabel* loopDelayUnitsLabel = new JLabel(tr("UnitMS"));
 QCheckBox* loopInfinite;// = new JCheckBox(tr("LabelLoopInfinite"));
 JPanelVector3f* position;// = new JPanelVector3f("",
//         tr("UnitUnits"));
 QCheckBox* positionRelative;// = new JCheckBox(tr("LabelPositionRelative"));
 JPanelVector3f* velocity;// = new JPanelVector3f(tr("Velocity"),
//         tr("UnitU/S"));
 JPanelSliderf* gain;// = new JPanelSliderf(tr("Gain"), 0.0f, 1.0f, 5, 4);
 JPanelSliderf* pitch;// = new JPanelSliderf(tr("Pitch"), 0.5f, 2.0f, 6, 5);
 QLabel* refDistanceLabel;// = new JLabel(tr("LabelReferenceDistance"));
 QSpinBox* refDistance;// = new JSpinner();
 QLabel* maxDistanceLabel;// = new JLabel(tr("Maximum Distance"));
 QSpinBox* maxDistance;// = new JSpinner();
 QLabel* distancesLabel;// = new JLabel(tr("Unit Units"));
 QLabel* rollOffFactorLabel;// = new JLabel(tr("LabelRollOffFactor"));
 QSpinBox* rollOffFactor;// = new JSpinner();
 QLabel* fadeInTimeLabel;// = new JLabel(tr("Fade In"));
 QSpinBox* fadeInTime;// = new JSpinner();
 QLabel* fadeOutTimeLabel;// = new JLabel(tr("Fade Out"));
 QSpinBox* fadeOutTime;// = new JSpinner();
 QLabel* fadeTimeUnitsLabel;// = new JLabel(tr("Unit MS"));
 Logger* log;
};

#endif // AUDIOSOURCEFRAME_H
