#ifndef EXPRESSIONSIGNALHEADSWING_H
#define EXPRESSIONSIGNALHEADSWING_H

#include "abstractdigitalexpressionswing.h"

class ExpressionSignalHead;
class JTabbedPane;
class BeanSelectPanel;
class JTextField;
class JComboBox;
class ExpressionSignalHeadSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  explicit ExpressionSignalHeadSwing(QObject *parent = nullptr);
  ~ExpressionSignalHeadSwing() {}
  ExpressionSignalHeadSwing(const ExpressionSignalHeadSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  static /*final*/ int NUM_COLUMNS_TEXT_FIELDS;// = 20;
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> *errorMessages);
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:
  /*private*/ /*static*/ class SignalHeadAppearance {

      /*private*/ int _state;
      /*private*/ QString _name;
public:
      //@Override
      /*public*/ QString toString() {
          return _name;
      }
   friend class ExpressionSignalHeadSwing;
  };


 private:
  /*private*/ JTabbedPane* _tabbedPaneSignalHead;
  /*private*/ BeanSelectPanel/*<SignalHead>*/* _signalHeadBeanPanel;
  /*private*/ JPanel* _panelSignalHeadDirect;
  /*private*/ JPanel* _panelSignalHeadReference;
  /*private*/ JPanel* _panelSignalHeadLocalVariable;
  /*private*/ JPanel* _panelSignalHeadFormula;
  /*private*/ JTextField* _signalHeadReferenceTextField;
  /*private*/ JTextField* _signalHeadLocalVariableTextField;
  /*private*/ JTextField* _signalHeadFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneQueryType;
  /*private*/ JPanel* _panelQueryTypeDirect;
  /*private*/ JPanel* _panelQueryTypeReference;
  /*private*/ JPanel* _panelQueryTypeLocalVariable;
  /*private*/ JPanel* _panelQueryTypeFormula;

  /*private*/ JComboBox/*<ExpressionSignalHead.QueryType>*/* _operationComboBox;
  /*private*/ JTextField* _signalHeadQueryReferenceTextField;
  /*private*/ JTextField* _signalHeadQueryLocalVariableTextField;
  /*private*/ JTextField* _signalHeadQueryFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneAppearanceType;
  /*private*/ JPanel* _panelAppearanceTypeDirect;
  /*private*/ JPanel* _panelAppearanceTypeReference;
  /*private*/ JPanel* _panelAppearanceTypeLocalVariable;
  /*private*/ JPanel* _panelAppearanceTypeFormula;

  /*private*/ JComboBox/*<SignalHeadAppearance>*/* _signalHeadAppearanceComboBox;
  /*private*/ JTextField* _signalHeadAppearanceReferenceTextField;
  /*private*/ JTextField* _signalHeadAppearanceLocalVariableTextField;
  /*private*/ JTextField* _signalHeadAppearanceFormulaTextField;

  /*private*/ BeanSelectPanel/*<SignalHead>*/* _exampleSignalHeadBeanPanel;
  /*private*/ void setGuiEnabledStates();
  /*private*/ void setAppearanceComboBox(ExpressionSignalHead* expression);

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExpressionSignalHeadSwing)
#endif // EXPRESSIONSIGNALHEADSWING_H
