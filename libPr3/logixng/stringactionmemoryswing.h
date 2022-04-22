#ifndef STRINGACTIONMEMORYSWING_H
#define STRINGACTIONMEMORYSWING_H

#include "abstractstringactionswing.h"

class BeanSelectPanel;
class StringActionMemorySwing : public AbstractStringActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringActionMemorySwing(QObject *parent = nullptr);
  ~StringActionMemorySwing() {}
  StringActionMemorySwing(const StringActionMemorySwing&) : AbstractStringActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}

 private:
  /*private*/ BeanSelectPanel/*<Memory>*/* memoryBeanPanel;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(StringActionMemorySwing)
#endif // STRINGACTIONMEMORYSWING_H
