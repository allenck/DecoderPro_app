#ifndef MERGSD2SIGNALHEAD_H
#define MERGSD2SIGNALHEAD_H

#include "defaultsignalhead.h"
#include "namedbeanhandle.h"
#include "turnout.h"

class MergSD2SignalHead : public DefaultSignalHead
{
 public:
  /*public*/  MergSD2SignalHead(QString sys, QString user, int aspect, NamedBeanHandle<Turnout*>* t1, NamedBeanHandle<Turnout*>* t2, NamedBeanHandle<Turnout*>* t3, bool feather, bool home, QObject* parent = nullptr);
  /*public*/  MergSD2SignalHead(QString sys, int aspect, NamedBeanHandle<Turnout*>* t1, NamedBeanHandle<Turnout*>* t2, NamedBeanHandle<Turnout*>* t3, bool feather, bool home, QObject* parent= nullptr);
  /*public*/  void setAppearance(int newAppearance)override;
  /*public*/  void setLit(bool newLit)override;
  /*public*/  NamedBeanHandle<Turnout*>* getInput1();
  /*public*/  NamedBeanHandle<Turnout*>* getInput2() ;
  /*public*/  NamedBeanHandle<Turnout*>* getInput3();
  /*public*/  int getAspects() ;
  /*public*/  bool getFeather();
  /*public*/  bool getHome();
  /*public*/  void setInput1(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setInput2(NamedBeanHandle<Turnout*>* t) ;
  /*public*/  void setInput3(NamedBeanHandle<Turnout*>* t);
  /*public*/  void setAspects(int i);
  /*public*/  void setFeather(bool boo);
  /*public*/  void setHome(bool boo);
  /*public*/  QVector<int> getValidStates() override;
  /*public*/  QVector<QString> getValidStateKeys() override;
  /*public*/  QVector<QString> getValidStateNames()override;
  bool isTurnoutUsed(Turnout* t);
  /*public*/  void dispose()override;

 private: static Logger* log;
  NamedBeanHandle<Turnout*>* mInput1 = nullptr; //Section directly infront of the Signal
  NamedBeanHandle<Turnout*>* mInput2 = nullptr; //Section infront of the next Signal
  NamedBeanHandle<Turnout*>* mInput3 = nullptr; //Section infront of the second Signal

  int mAspects = 2;
  bool mFeather = false;
  bool mHome = true; //Home Signal = true, Distance Signal = false
  /*final*/ static /*private*/ QVector<int> validStates2AspectHome;// = new int[]{
//      RED,
//      GREEN
//  };
  /*final*/ static /*private*/ QVector<QString> validStateKeys2AspectHome;// = new String[]{
//      "SignalHeadStateRed",
//      "SignalHeadStateGreen"
//  };

  /*final*/ static /*private*/ QVector<int> validStates2AspectDistant;// = new int[]{
//      YELLOW,
//      GREEN
//  };
  /*final*/ static /*private*/ QVector<QString> validStateKeys2AspectDistant;// = new String[]{
//      "SignalHeadStateYellow",
//      "SignalHeadStateGreen"
//  };

  /*final*/ static /*private*/ QVector<int> validStates3Aspect;// = new int[]{
//      RED,
//      YELLOW,
//      GREEN
//  };
  /*final*/ static /*private*/QVector<QString> validStateKeys3Aspect;// = new String[]{
//      "SignalHeadStateRed",
//      "SignalHeadStateYellow",
//      "SignalHeadStateGreen"
//  };

  /*final*/ static /*private*/ QVector<int> validStates4Aspect;// = new int[]{
//      RED,
//      YELLOW,
//      LUNAR,
//      GREEN
//  };
  /*final*/ static /*private*/ QVector<QString> validStateKeys4Aspect;// = new String[]{
//      "SignalHeadStateRed",
//      "SignalHeadStateYellow",
//      "SignalHeadStateLunar",
//      "SignalHeadStateGreen"
//  };
  QMap<QString, QString> stateMap = {{"SignalHeadStateRed", tr("red")}, {"SignalHeadStateYellow", tr("yellow")},
                                    {"SignalHeadStateLunar", tr("lunar")}, {"SignalHeadStateGreen", tr("green")},
                                    };

 protected:
  /*protected*/ void updateOutput()override;

};

#endif // MERGSD2SIGNALHEAD_H
