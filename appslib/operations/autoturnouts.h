#ifndef AUTOTURNOUTS_H
#define AUTOTURNOUTS_H

#include <QObject>

class Logger;
class LayoutEditor;
class Section;
class ActiveTrain;
class DispatcherFrame;
class AutoTurnouts : public QObject
{
 Q_OBJECT
public:
 //explicit AutoTurnouts(QObject *parent = 0);
 /*public*/ AutoTurnouts(DispatcherFrame* d);

signals:

public slots:

private:
 Logger* log;
 /*private*/ QString closedText;// = InstanceManager::urnoutManagerInstance().getClosedText();
 /*private*/ QString thrownText;// = InstanceManager::urnoutManagerInstance().getThrownText();
 // operational variables
protected:
 DispatcherFrame* _dispatcher;// = NULL;
private:
 bool userInformed;// = false;
 /*private*/ bool turnoutUtil(Section* s, int seqNum, Section* nextSection,ActiveTrain* at, LayoutEditor* le, bool trustKnownTurnouts, bool set, Section* prevSection);


protected:
 /*protected*/ bool checkTurnoutsInSection(Section* s, int seqNum, Section* nextSection,
                                           ActiveTrain* at, LayoutEditor* le, Section* prevSection);
 /*protected*/ bool setTurnoutsInSection(Section* s, int seqNum, Section* nextSection,
         ActiveTrain* at, LayoutEditor* le, bool trustKnownTurnouts, Section* prevSection);


};

#endif // AUTOTURNOUTS_H
