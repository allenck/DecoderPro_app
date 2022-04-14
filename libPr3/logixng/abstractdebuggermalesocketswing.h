#ifndef ABSTRACTDEBUGGERMALESOCKETSWING_H
#define ABSTRACTDEBUGGERMALESOCKETSWING_H

#include "abstractswingconfigurator.h"

class AbstractDebuggerMaleSocketSwing : public AbstractSwingConfigurator
{
  Q_OBJECT

 public:
  explicit AbstractDebuggerMaleSocketSwing(QObject *parent = nullptr) : AbstractSwingConfigurator(parent) {}
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager() override;
  /*public*/  /*final*/ JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/  /*final*/ JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/  /*final*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  bool validateSubPanel(/*@Nonnull*/ QList<QString> errorMessages) ;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  /*final*/ void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  QString toString()override;
  /*public*/  /*final*/ void dispose()override;

 private:
  /*private*/ JPanel* panel;
//    private JPanel tablePanel;
//    private JTable table;
//    private LocalVariableTableModel tableModel;

protected:
  /*protected*/ JPanel* createSubPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);
  /*protected*/ /*final*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);

};

#endif // ABSTRACTDEBUGGERMALESOCKETSWING_H
