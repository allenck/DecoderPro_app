#ifndef LAYOUTWYEVIEW_H
#define LAYOUTWYEVIEW_H
#include "layoutturnoutview.h"
#include "layoutwye.h"

class LayoutWyeView : public LayoutTurnoutView
{
 public:
  /*public*/ LayoutWyeView(/*@Nonnull*/ LayoutWye* wye);

};

#endif // LAYOUTWYEVIEW_H
