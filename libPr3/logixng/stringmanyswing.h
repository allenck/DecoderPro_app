#ifndef STRINGMANYSWING_H
#define STRINGMANYSWING_H

#include "abstractstringactionswing.h"

class StringManySwing : public AbstractStringActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringManySwing(QObject *parent = nullptr);
  ~StringManySwing() {}
  StringManySwing(const StringManySwing&) : AbstractStringActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(StringManySwing)
#endif // STRINGMANYSWING_H
