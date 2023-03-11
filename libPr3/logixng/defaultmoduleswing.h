#ifndef DEFAULTMODULESWING_H
#define DEFAULTMODULESWING_H

#include "abstractswingconfigurator.h"
#include "threadingutil.h"
#include "joptionpane.h"

class ModuleParametersTableModel;
class DefaultModuleSwing : public AbstractSwingConfigurator
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultModuleSwing(QObject *parent = nullptr);
  ~DefaultModuleSwing() {}
  DefaultModuleSwing(const DefaultModuleSwing&) : AbstractSwingConfigurator() {}
  /*public*/ QString getExecuteEvaluateMenuText() override;
  /*public*/ void executeEvaluate(/*@Nonnull*/ Base* object) override;
  /*public*/ BaseManager/*<? extends NamedBean>*/* getManager() override;
  /*public*/ JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ override;
  /*public*/ JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException */override;
  /*public*/ QString getExampleSystemName() override;
  /*public*/ QString getAutoSystemName() override;
  /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/ QString toString() override;
  /*public*/ void dispose() override;

  QObject* sself() override {return this;}

private:
  ModuleParametersTableModel* _moduleParametersTableModel;

protected:
  /*protected*/ JPanel* panel;
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) ;


};
Q_DECLARE_METATYPE(DefaultModuleSwing)
class DMS_ThreadingUtil : public ThreadAction
{
  Q_OBJECT
 public:
  void run()
  {
   JOptionPane::showMessageDialog(nullptr,
           tr("The action has completed"),
           tr("The action has been executed"),
           JOptionPane::PLAIN_MESSAGE);

  }
};

#endif // DEFAULTMODULESWING_H
