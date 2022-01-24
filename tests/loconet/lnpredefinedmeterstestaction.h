#ifndef LNPREDEFINEDMETERSTESTACTION_H
#define LNPREDEFINEDMETERSTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnPredefinedMetersTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  LnPredefinedMetersTestAction(QObject* parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LNPREDEFINEDMETERSTESTACTION_H
