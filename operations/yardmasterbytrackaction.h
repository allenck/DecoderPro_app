#ifndef YARDMASTERBYTRACKACTION_H
#define YARDMASTERBYTRACKACTION_H
#include "abstractaction.h"
#include "location.h"
#include "yardmasterbytrackframe.h"

namespace Operations {


class YardmasterByTrackAction : public AbstractAction
{
 Q_OBJECT
public:
 YardmasterByTrackAction(QObject *parent);
 /*public*/ YardmasterByTrackAction(QString s, Location* location, QObject* parent);
 /*public*/ YardmasterByTrackAction(QString s, QObject* parent);
 /*public*/ YardmasterByTrackAction(Location* location, QObject* parent);

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0);


private:
 void common();
 Location* _location;

 YardmasterByTrackFrame* f;// = null;

};
}
#endif // YARDMASTERBYTRACKACTION_H
