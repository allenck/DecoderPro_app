#ifndef TRACKEDITCOMMENTSACTION_H
#define TRACKEDITCOMMENTSACTION_H

#include "abstractaction.h"
#include "appslib_global.h"

class JActionEvent;
namespace Operations
{
class TrackEditFrame;
 class APPSLIBSHARED_EXPORT TrackEditCommentsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrackEditCommentsAction(TrackEditFrame* tef);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
  private:
   /*private*/ TrackEditFrame* _tef;

 };
}
#endif // TRACKEDITCOMMENTSACTION_H
