#ifndef FORSWING_H
#define FORSWING_H

#include "abstractdigitalactionswing.h"
#include <QObject>

class ForSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ForSwing(QObject *parent = nullptr)
   : AbstractDigitalActionSwing(parent) {setObjectName("ForSwing");}
  ~ForSwing() {}
  ForSwing(const ForSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ForSwing)
#endif // FORSWING_H
