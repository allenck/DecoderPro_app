#ifndef CHANGETRACKSTYPEACTION_H
#define CHANGETRACKSTYPEACTION_H
#include "abstractaction.h"
#include "locationeditframe.h"
#include "appslib_global.h"

namespace Operations
{
 class LocationEditFrame;
 class APPSLIBSHARED_EXPORT ChangeTracksTypeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ChangeTracksTypeAction(LocationEditFrame* lef);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  /*private*/ LocationEditFrame* _lef;

 };
}
#endif // CHANGETRACKSTYPEACTION_H
