#ifndef IDENTIFYDECODERTESTACTION_H
#define IDENTIFYDECODERTESTACTION_H
#include "abstractaction.h"

class Logger;
class IdentifyDecoderTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  IdentifyDecoderTestAction(QObject* parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;

};

#endif // IDENTIFYDECODERTESTACTION_H
