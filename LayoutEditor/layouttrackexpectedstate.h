#ifndef LAYOUTTRACKEXPECTEDSTATE_H
#define LAYOUTTRACKEXPECTEDSTATE_H
#include "layouttrack.h"
#include "propertychangesupport.h"
#include "bean.h"

template<class T>
class LayoutTrackExpectedState : public Bean
{
  //Q_OBJECT
public:
 LayoutTrackExpectedState(T layoutTrack, int state, QObject *parent = nullptr) ;
 ~LayoutTrackExpectedState()  override{}
 //LayoutTrackExpectedState(const LayoutTrackExpectedState&)  {}
 /*public*/ int getExpectedState();
 /*public*/ void setExpectedState(int state) throw (UnsupportedOperationException);
 /*public*/ T getObject() ;
 /*public*/ bool canRemove() {return  false;}
 /*public*/ void setObjects(LayoutEditor* le) {}
 /*public*/ LayoutTrack* getConnection(HitPointType::TYPES type) /*throw (JmriException)*/{return nullptr;}
 /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ {}

private:
 /*private*/ /*final*/ T layoutTrack;
 /*private*/ int state;

};

#endif // LAYOUTTRACKEXPECTEDSTATE_H
