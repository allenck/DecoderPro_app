#ifndef ANALOGACTIONLIGHTINTENSITYSWING_H
#define ANALOGACTIONLIGHTINTENSITYSWING_H
#include "abstractanalogactionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class JTextField;
class AnalogActionLightIntensitySwing : public AbstractAnalogActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE AnalogActionLightIntensitySwing(QObject* parent = nullptr)
   : AbstractAnalogActionSwing(parent) {setObjectName("AnalogActionLightIntensitySwing");}
  ~AnalogActionLightIntensitySwing() {}
  AnalogActionLightIntensitySwing(const AnalogActionLightIntensitySwing&) : AbstractAnalogActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:
  /*private*/ JTabbedPane* _tabbedPaneLight;
  /*private*/ BeanSelectPanel/*<VariableLight>*/* lightBeanPanel;
  /*private*/ JPanel* _panelLightDirect;
  /*private*/ JPanel* _panelLightReference;
  /*private*/ JPanel* _panelLightLocalVariable;
  /*private*/ JPanel* _panelLightFormula;
  /*private*/ JTextField* _lightReferenceTextField;
  /*private*/ JTextField* _lightLocalVariableTextField;
  /*private*/ JTextField* _lightFormulaTextField;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogActionLightIntensitySwing);
#endif // ANALOGACTIONLIGHTINTENSITYSWING_H
