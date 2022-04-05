#ifndef IFTHENELSESWING_H
#define IFTHENELSESWING_H

#include "abstractdigitalactionswing.h"
#include "jcombobox.h"

class IfThenElseSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit IfThenElseSwing(QObject *parent = nullptr) : AbstractDigitalActionSwing(parent) {}
  ~IfThenElseSwing(){}
  IfThenElseSwing(const IfThenElseSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}

 private:
  /*private*/ JComboBox/*<Type>*/* _typeComboBox;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;


};
Q_DECLARE_METATYPE(IfThenElseSwing)
#endif // IFTHENELSESWING_H
