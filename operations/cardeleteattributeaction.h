#ifndef CARDELETEATTRIBUTEACTION_H
#define CARDELETEATTRIBUTEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"
#include "carattributeeditframe.h"

class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarDeleteAttributeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ CarDeleteAttributeAction(CarAttributeEditFrame* caef);
  public slots:
  /*public*/ void actionPerformed(JActionEvent* ae = 0);
 private:
  QPointer<CarAttributeEditFrame> caef;
  Logger* log;
 };
}
#endif // CARDELETEATTRIBUTEACTION_H
