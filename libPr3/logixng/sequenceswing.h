#ifndef SEQUENCESWING_H
#define SEQUENCESWING_H

#include "abstractdigitalactionswing.h"

class JCheckBox;
class SequenceSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE SequenceSwing(QObject* parent = nullptr) {}
  ~SequenceSwing() {}
  SequenceSwing(const SequenceSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return this;}

 private:
  /*private*/ JCheckBox* _startImmediately;
  /*private*/ JCheckBox* _runContinuously;
 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(SequenceSwing)
#endif // SEQUENCESWING_H
