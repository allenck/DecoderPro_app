#ifndef BLOCKTABLEACTION_H
#define BLOCKTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "libtables_global.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "jtextfield.h"
#include "windowadapter.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include <QRadioButton>

class Block;
class UserPreferencesManager;
class QComboBox;
class QLabel;
class JTextField;
class QCheckBox;
class DecimalFormat;
class LIBTABLESSHARED_EXPORT BlockTableAction : public AbstractTableAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit BlockTableAction(QObject *parent = NULL);
 ~BlockTableAction() {}
 BlockTableAction(const BlockTableAction& other) : AbstractTableAction(other.text(), other.parent()) {}
 Q_INVOKABLE/*public*/ BlockTableAction(QString actionName, QObject *parent);
 /*public*/ void addToFrame(BeanTableFrame* f) override;
/*public*/ void setMenuBar(BeanTableFrame* f) override;
 Q_INVOKABLE /*public*/ QString getClassDescription() override;
 /*public*/ /*final*/ static QString BLOCK_METRIC_PREF;// = BlockTableAction.class.getName() + ":LengthUnitMetric"; // NOI18N

signals:

public slots:
 void okPressed(JActionEvent* e = 0);
 void cancelPressed(JActionEvent *e = 0);


private:
 void common();
 JmriJFrame* addFrame = NULL;
 JTextField* sysName = new JTextField(20);
 JTextField* userName = new JTextField(20);
 JLabel* sysNameLabel = new JLabel(tr("SystemName"));
 JLabel* userNameLabel = new JLabel(tr("UserName"));

 SpinnerNumberModel* numberToAddSpinnerNumberModel = new SpinnerNumberModel(1, 1, 100, 1); // maximum 100 items
 JSpinner* numberToAddSpinner = new JSpinner(numberToAddSpinnerNumberModel);
 JCheckBox* addRangeCheckBox = new JCheckBox(tr("Add a sequential range"));
 JCheckBox* _autoSystemNameCheckBox = new JCheckBox(tr("Automatically generate System Name"));
 JLabel* statusBar = new JLabel(tr("Enter a System Name and (optional) User Name."), JLabel::LEADING);
 /*private*/ JButton* newButton = nullptr;


 QComboBox* cur;// = new QComboBox*(curveOptions);
 JTextField* lengthField = new JTextField(7);
 JTextField* blockSpeed = new JTextField(7);
 QCheckBox* checkPerm = new QCheckBox(tr("Permissive"));

 UserPreferencesManager* pref;

 QComboBox* speeds = new QComboBox();
 QString systemNameAuto;// = this.getClass().getName() + ".AutoSystemName";
 static Logger* log;
 void handleCreateException(QString sysName);
 void deletePaths(JmriJFrame* f);
 JmriJFrame* finalF;

 // for icon state col
 bool _graphicState = false; // updated from prefs
 /*private*/ /*final*/ QRadioButton* inchBox = new QRadioButton(tr("Length in Inches")); // NOI18N
 /*private*/ /*final*/ QRadioButton* centimeterBox = new QRadioButton(tr("Length in Centimeters")); // NOI18N
 /*private*/ void initRadioButtons();
 /*private*/ void metricSelectionChanged(/*ActionEvent e*/);

protected:
 /*protected*/ void createModel() override;
 /*protected*/ void setTitle() override;
 /*protected*/ QString helpTarget() override;
 /*protected*/ Manager/*<Block>*/* getManager();

protected slots:
 /*protected*/ void addPressed(JActionEvent * /*e*/)override;
 /*protected*/ QString getClassName() override;

friend class BlockTableDataModel;
};
Q_DECLARE_METATYPE(BlockTableAction)



class BTActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 BlockTableAction* blockTableAction;
public:
 BTActionListener(BlockTableAction* blockTableAction) {this->blockTableAction = blockTableAction;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent* = 0)override
 {
     blockTableAction->okPressed();
 }
};
class BTCancelListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 BlockTableAction* blockTableAction;
public:
 BTCancelListener(BlockTableAction* blockTableAction) {this->blockTableAction = blockTableAction;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent* = 0) override
 {
     blockTableAction->cancelPressed();
 }
};

class ABWindowListener : public WindowAdapter
{
  Q_OBJECT
  BlockTableAction* blockTableAction;
 public:
  ABWindowListener(BlockTableAction* blockTableAction) {this->blockTableAction = blockTableAction;}
  void windowClosed(QCloseEvent */*e*/) override
  {
   blockTableAction->cancelPressed();
  }
  void windowClosing(QEvent*)override{}
};
#endif // BLOCKTABLEACTION_H
