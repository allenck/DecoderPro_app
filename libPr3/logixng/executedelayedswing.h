#ifndef EXECUTEDELAYEDSWING_H
#define EXECUTEDELAYEDSWING_H

#include "abstractdigitalactionswing.h"
#include <QObject>
#include "jlabel.h"

class JFormattedTextField;
class JTabbedPane;
class JComboBox;
class JCheckBox;
class ExecuteDelayedSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE ExecuteDelayedSwing(QObject *parent= nullptr);
  ~ExecuteDelayedSwing() {}
  ExecuteDelayedSwing(const ExecuteDelayedSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose() override;

  QObject* sself() override {return this;}

 private:
  /*private*/ /*final*/ JLabel* _unitLabel = new JLabel(tr("Unit"));
  /*private*/ JComboBox/*<TimerUnit>*/* _unitComboBox;
  /*private*/ JCheckBox* _resetIfAlreadyStarted;

  /*private*/ JTabbedPane* _tabbedPaneDelay;
  /*private*/ JFormattedTextField* _timerDelay;
  /*private*/ JPanel* _panelDelayDirect;
  /*private*/ JPanel* _panelDelayReference;
  /*private*/ JPanel* _panelDelayLocalVariable;
  /*private*/ JPanel* _panelDelayFormula;
  /*private*/ JTextField* _delayReferenceTextField;
  /*private*/ JTextField* _delayLocalVariableTextField;
  /*private*/ JTextField* _delayFormulaTextField;


 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExecuteDelayedSwing)
#endif // EXECUTEDELAYEDSWING_H
