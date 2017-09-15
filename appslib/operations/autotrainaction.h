#ifndef AUTOTRAINACTION_H
#define AUTOTRAINACTION_H

#include <QObject>

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


signals:

public slots:

private:
 // operational instance variables
 /*private*/ AutoActiveTrain* _autoActiveTrain;// = null;
 /*private*/ ActiveTrain* _activeTrain;// = null;
 /*private*/ QList<TransitSection*>* _activeTransitSectionList;// = new ArrayList<TransitSection>();
 /*private*/ QList<TransitSectionAction*>* _activeActionList;// = new ArrayList<TransitSectionAction>();
};

#endif // AUTOTRAINACTION_H
