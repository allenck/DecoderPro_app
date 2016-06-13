#ifndef NOTCHTRANSITION_H
#define NOTCHTRANSITION_H
#include "soundbite.h"

class NotchTransition : public SoundBite
{
 Q_OBJECT
public:
 /*public*/ NotchTransition(QString name, QObject*parent=0);
     /*public*/ NotchTransition(VSDFile* vf, QString filename, QString sname, QString uname, QObject*parent=0);
     /*public*/ int getPrevNotch() ;
     /*public*/ int getNextNotch();
     /*public*/ void setPrevNotch(int p);
     /*public*/ void setNextNotch(int p);

private:
 /*private*/ int prev_notch;
 /*private*/ int next_notch;

};

#endif // NOTCHTRANSITION_H
