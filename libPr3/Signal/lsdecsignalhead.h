#ifndef LSDECSIGNALHEAD_H
#define LSDECSIGNALHEAD_H

#include "defaultsignalhead.h"
#include "namedbeanhandle.h"
#include "turnout.h"

class LsDecSignalHead : public DefaultSignalHead
{
 public:
  /*public*/  LsDecSignalHead(QString sys, QString user,
                              NamedBeanHandle<Turnout*>* t1, int s1,
                              NamedBeanHandle<Turnout*>* t2, int s2,
                              NamedBeanHandle<Turnout*>* t3, int s3,
                              NamedBeanHandle<Turnout*>* t4, int s4,
                              NamedBeanHandle<Turnout*>* t5, int s5,
                              NamedBeanHandle<Turnout*>* t6, int s6,
                              NamedBeanHandle<Turnout*>* t7, int s7, QObject* parent = nullptr);

  /*public*/  LsDecSignalHead(QString sys,
                              NamedBeanHandle<Turnout*>* t1, int s1,
                              NamedBeanHandle<Turnout*>* t2, int s2,
                              NamedBeanHandle<Turnout*>* t3, int s3,
                              NamedBeanHandle<Turnout*>* t4, int s4,
                              NamedBeanHandle<Turnout*>* t5, int s5,
                              NamedBeanHandle<Turnout*>* t6, int s6,
                              NamedBeanHandle<Turnout*>* t7, int s7 , QObject* parent = nullptr);
  /*public*/  void setAppearance(int newAppearance)override;
  /*public*/  void setLit(bool newLit)override;
  /*public*/  void dispose()override;
  /*public*/  NamedBeanHandle<Turnout*>* getRed();
  /*public*/  NamedBeanHandle<Turnout*>* getYellow();
  /*public*/  NamedBeanHandle<Turnout*>* getGreen();
  /*public*/  NamedBeanHandle<Turnout*>* getFlashRed();
  /*public*/  NamedBeanHandle<Turnout*>* getFlashYellow();
  /*public*/  NamedBeanHandle<Turnout*>* getFlashGreen();
  /*public*/  NamedBeanHandle<Turnout*>* getDark() ;
  /*public*/  int getRedState();
  /*public*/  int getYellowState();
  /*public*/  int getGreenState();
  /*public*/  int getFlashRedState();
  /*public*/  int getFlashYellowState();
  /*public*/  int getFlashGreenState() ;
  /*public*/  int getDarkState();
  /*public*/  void setRed(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setYellow(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setGreen(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setFlashRed(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setFlashYellow(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setFlashGreen(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setDark(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setRedState(int i);
  /*public*/  void setYellowState(int i);
  /*public*/  void setGreenState(int i);
  /*public*/  void setFlashRedState(int i);
  /*public*/  void setFlashYellowState(int i);
  /*public*/  void setFlashGreenState(int i);
  /*public*/  void setDarkState(int i);

 private:
  static Logger* log;
  NamedBeanHandle<Turnout*>* mRed;
  NamedBeanHandle<Turnout*>* mYellow;
  NamedBeanHandle<Turnout*>* mGreen;
  NamedBeanHandle<Turnout*>* mFlashRed;
  NamedBeanHandle<Turnout*>* mFlashYellow;
  NamedBeanHandle<Turnout*>* mFlashGreen;
  NamedBeanHandle<Turnout*>* mDark;

  int mRedState;
  int mYellowState;
  int mGreenState;
  int mFlashRedState;
  int mFlashYellowState;
  int mFlashGreenState;
  int mDarkState;
  //@Override
  bool isTurnoutUsed(Turnout* t)override;

 protected:
  /*protected*/ void updateOutput()override;

};
#endif // LSDECSIGNALHEAD_H
