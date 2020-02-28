#ifndef LAYOUTTRACKEXPECTEDSTATE_H
#define LAYOUTTRACKEXPECTEDSTATE_H
#include "layouttrack.h"
#include "propertychangesupport.h"

template<class T>
class LayoutTrackExpectedState : public LayoutTrack
{
public:
 LayoutTrackExpectedState(T layoutTrack, int state, QObject *parent = nullptr);
 ~LayoutTrackExpectedState()  override{}
 //LayoutTrackExpectedState(const LayoutTrackExpectedState&)  {}
 /*public*/ int getExpectedState();
 /*public*/ void setExpectedState(int state) throw (UnsupportedOperationException);
 /*public*/ T getObject() ;

private:
 /*private*/ /*final*/ T layoutTrack;
 /*private*/ int state;

};

#endif // LAYOUTTRACKEXPECTEDSTATE_H
