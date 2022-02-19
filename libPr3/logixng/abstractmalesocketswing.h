#ifndef ABSTRACTMALESOCKETSWING_H
#define ABSTRACTMALESOCKETSWING_H

#include "abstractswingconfigurator.h"
#include "jpanel.h"
#include "jcombobox.h"
#include "jlabel.h"
#include "jcheckbox.h"

class AbstractMaleSocketSwing : public AbstractSwingConfigurator
{
  Q_OBJECT
 public:
  explicit AbstractMaleSocketSwing(QObject *parent = nullptr): AbstractSwingConfigurator(parent){}
  /*public*/  BaseManager/*<? extends NamedBean>*/* getManager()override;
  /*public*/  /*final*/ JPanel* getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  /*final*/ JPanel* getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/override;
  /*public*/  /*final*/ bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  /*final*/ void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString getExampleSystemName()override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  QString toString()override;
  /*public*/  /*final*/ void dispose()override;

 private:
  /*private*/ JPanel* panel;
  /*private*/ /*final*/ JLabel* errorHandlingLabel = new JLabel(tr("Error handling"));
  /*private*/ /*final*/ JLabel* catchAbortExecutionLabel = new JLabel(tr("Catch \"Abort execution\""));
  /*private*/ JComboBox/*<ErrorHandlingType>*/* errorHandlingComboBox;
  /*private*/ JCheckBox* catchAbortExecutionCheckBox;
  /*private*/ JPanel* subPanel;


 protected:
  /*protected*/ /*final*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);
  /*protected*/ JPanel* getSubPanel(/*@CheckForNull*/ Base* object);
  /*protected*/ void updateObjectForSubPanel(/*@Nonnull*/ Base* object);

};

#endif // ABSTRACTMALESOCKETSWING_H
