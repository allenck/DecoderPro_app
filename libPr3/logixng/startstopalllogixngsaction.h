#ifndef STARTSTOPALLLOGIXNGSACTION_H
#define STARTSTOPALLLOGIXNGSACTION_H

#include "abstractaction.h"

class StartStopAllLogixNGsAction : public AbstractAction
{
 public:
  explicit StartStopAllLogixNGsAction(bool start, QObject *parent);
  /*public*/ StartStopAllLogixNGsAction(QString s, bool start, QObject *parent);

 public slots:
  /*public*/  void actionPerformed(JActionEvent* e =0)override;

 private:
  /*private*/ /*final*/ bool _start;

};

#endif // STARTSTOPALLLOGIXNGSACTION_H
