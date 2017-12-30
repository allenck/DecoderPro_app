#ifndef JMRIJFRAMEACTION_H
#define JMRIJFRAMEACTION_H
#include "abstractaction.h"

class Logger;
class JmriJFrameAction : public AbstractAction
{
 Q_OBJECT

public:
 //JmriJFrameAction(QObject* parent);
 /*public*/ JmriJFrameAction(QString s, QObject* parent);
 /*public*/ virtual QString getName();
 public slots:
  /*public*/ void actionPerformed();
   private:
 Logger* log;
};
#endif // JMRIJFRAMEACTION_H
