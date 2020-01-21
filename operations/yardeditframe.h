#ifndef YARDEDITFRAME_H
#define YARDEDITFRAME_H
#include "trackeditframe.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT YardEditFrame : public TrackEditFrame
 {
   Q_OBJECT
 public:
  YardEditFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ QString getClassName();

 };
}
#endif // YARDEDITFRAME_H
