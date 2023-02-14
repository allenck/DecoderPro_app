#ifndef LOGIXSWING_H
#define LOGIXSWING_H

#include "abstractdigitalactionswing.h"

class LogixSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE LogixSwing(QObject* parent = nullptr);
  ~LogixSwing() {}
  LogixSwing(const LogixSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return this;}

//  Category getCategory() override {return Category::OTHER;}
//  void setup() {}
  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)
  {}
 private:

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};

#endif // LOGIXSWING_H
