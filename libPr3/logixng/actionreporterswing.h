#ifndef ACTIONREPORTERSWING_H
#define ACTIONREPORTERSWING_H

#include "abstractdigitalactionswing.h"

class JTabbedPane;
class JComboBox;
class JTextField;
class BeanSelectPanel;
class ActionReporterSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE ActionReporterSwing(QObject *parent=nullptr);
  ~ActionReporterSwing() {}
  ActionReporterSwing(const ActionReporterSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;
  QObject* sself() override {return this;}
 private:
  /*private*/ JTabbedPane* _tabbedPaneBean;
  /*private*/ JPanel* _panelBeanDirect;
  /*private*/ JPanel* _panelBeanReference;
  /*private*/ JPanel* _panelBeanLocalVariable;
  /*private*/ JPanel* _panelBeanFormula;

  /*private*/ BeanSelectPanel/*<Reporter>*/* _beanSelectPanel;
  /*private*/ JTextField* _beanReferenceTextField;
  /*private*/ JTextField* _beanLocalVariableTextField;
  /*private*/ JTextField* _beanFormulaTextField;


  /*private*/ JPanel* _panelReporterValue;
  /*private*/ JComboBox/*<ReporterValue>*/* _reporterValueComboBox;


  /*private*/ JTabbedPane* _tabbedPaneData;
  /*private*/ JPanel* _panelDataDirect;
  /*private*/ JPanel* _panelDataReference;
  /*private*/ JPanel* _panelDataLocalVariable;
  /*private*/ JPanel* _panelDataFormula;

  /*private*/ BeanSelectPanel/*<Memory>*/* _memorySelectPanel;
  /*private*/ JTextField* _dataReferenceTextField;
  /*private*/ JTextField* _dataLocalVariableTextField;
  /*private*/ JTextField* _dataFormulaTextField;
  /*private*/ void validateBeanSection(QList<QString>* errorMessages) ;
  /*private*/ void validateDataSection(QList<QString>* errorMessages);

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionReporterSwing)
#endif // ACTIONREPORTERSWING_H
