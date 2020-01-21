#ifndef INTERCHANGEEDITFRAME_H
#define INTERCHANGEEDITFRAME_H
#include "trackeditframe.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT InterchangeEditFrame : public TrackEditFrame
 {
  Q_OBJECT
 public:
  InterchangeEditFrame(QWidget* parent=0);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ QString getClassName();

 };
}
#endif // INTERCHANGEEDITFRAME_H
