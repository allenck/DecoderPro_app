#ifndef ACTIONLISTENONBEANSSWING_H
#define ACTIONLISTENONBEANSSWING_H

#include "abstractdigitalactionswing.h"

class ListenOnBeansTableModel;
class JTable;
class ActionListenOnBeansSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionListenOnBeansSwing(QObject *parent = nullptr);
  ~ActionListenOnBeansSwing(){}
  ActionListenOnBeansSwing(const ActionListenOnBeansSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:
  /*private*/ JTable* _listenOnBeansTable;
  /*private*/ ListenOnBeansTableModel* _listenOnBeansTableModel;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionListenOnBeansSwing)
#endif // ACTIONLISTENONBEANSSWING_H
