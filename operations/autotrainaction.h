#ifndef AUTOTRAINACTION_H
#define AUTOTRAINACTION_H

#include <QObject>

class Logger;
class PropertyChangeListener;
class Sensor;
class TransitSectionAction;
class TransitSection;
class ActiveTrain;
class AutoActiveTrain;
class AutoTrainAction : public QObject
{
 Q_OBJECT
public:
 //explicit AutoTrainAction(QObject *parent = 0);
 /*public*/ AutoTrainAction(AutoActiveTrain* aat, QObject* parent = 0);
 /*public*/ /*synchronized*/ void executeAction(TransitSectionAction* tsa);


signals:

public slots:

private:
 Logger* log;
 // operational instance variables
 /*private*/ AutoActiveTrain* _autoActiveTrain;// = null;
 /*private*/ ActiveTrain* _activeTrain;// = null;
 /*private*/ QList<TransitSection*>* _activeTransitSectionList;// = new ArrayList<TransitSection>();
 /*private*/ QList<TransitSectionAction*>* _activeActionList;// = new ArrayList<TransitSectionAction>();
 /*private*/ /*synchronized*/ void completedAction(TransitSectionAction* tsa);
 /*private*/ /*synchronized*/ void checkDelay(TransitSectionAction* tsa);
 // this method is called to listen to a Done Sensor if one was provided
 // if Status is WORKING, and sensor goes Active, Status is set to READY
 /*private*/ Sensor* _doneSensor;// = NULL;
 /*private*/ PropertyChangeListener* _doneSensorListener;// = NULL;
 /*private*/ /*synchronized*/ void listenToDoneSensor(TransitSectionAction* tsa);

protected:
 /*protected*/ /*synchronized*/ void removeTransitSection(TransitSection* ts);
 /*protected*/ /*synchronized*/ void addTransitSection(TransitSection* ts);
 /*protected*/ /*synchronized*/ void clearRemainingActions();
 /*protected*/ /*synchronized*/ void cancelDoneSensor();

 friend class AutoActiveTrain;
};

#endif // AUTOTRAINACTION_H
