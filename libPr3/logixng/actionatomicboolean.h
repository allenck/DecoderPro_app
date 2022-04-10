#ifndef ACTIONATOMICBOOLEAN_H
#define ACTIONATOMICBOOLEAN_H

#include "abstractdigitalaction.h"
#include "atomicboolean.h"

class ActionAtomicBoolean : public AbstractDigitalAction
{
  Q_OBJECT
 public:
  explicit ActionAtomicBoolean(AtomicBoolean *atomicBoolean, bool newValue, QObject *parent = nullptr);
  /*public*/  ActionAtomicBoolean(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  ActionAtomicBoolean(QString sys, QString user, AtomicBoolean* atomicBoolean,
                                  bool newValue, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) override;
  /*public*/  void setAtomicBoolean(AtomicBoolean* atomicBoolean);
  /*public*/  AtomicBoolean* getAtomicBoolean();
  /*public*/  void setNewValue(bool newValue);
  /*public*/  bool getNewValue();
  /*public*/  Category* getCategory()override;
  /*public*/  void execute()override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}
  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ AtomicBoolean* _atomicBoolean;
  /*private*/ bool _newValue;

};

#endif // ACTIONATOMICBOOLEAN_H
