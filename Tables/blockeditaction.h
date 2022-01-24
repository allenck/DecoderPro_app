#ifndef BLOCKEDITACTION_H
#define BLOCKEDITACTION_H
#include "beaneditaction.h"
#include "abstractaction.h"
#include "namedbeancombobox.h"
#include "block.h"
#include <QCheckBox>

class QRadioButton;
class QComboBox;
class DecimalFormat;
class NamedBeanComboBox;
class BlockEditAction : public BeanEditAction
{
 Q_OBJECT
public:
 explicit BlockEditAction(QObject *parent = 0);
 /*public*/ QString helpTarget();
 /*public*/ QString getBeanType();
 /*public*/ NamedBean* getByUserName(QString name);

signals:

public slots:
 void on_reporterComboBox_currentIndexChanged(QString s);
 void on_setSaveItem();
 void on_setResetItem();

private:
 /*private*/ QString noneText;// = tr("None");
 /*private*/ QString gradualText;// = tr("Gradual");
 /*private*/ QString tightText;// = tr("Tight");
 /*private*/ QString severeText;// = tr("Severe");
 /*public*/ QStringList curveOptions;// = {noneText, gradualText, tightText, severeText};
 static /*final*/ QVector<QString> speedList;// = new QVector<QString>();

 /*private*/ DecimalFormat* twoDigit;// = new DecimalFormat("0.00");
 JTextField* userNameField;// = new JTextField(20);
 NamedBeanComboBox* reporterComboBox;
 QCheckBox* useCurrent;// = new JCheckBox();
 JTextArea* commentField;// = new JTextArea(3, 30);
 QScrollArea* commentFieldScroller;// = new JScrollPane(commentField);
 BeanItemPanel* reporterDetails();
 JTextField* lengthField = nullptr;// = new JTextField(20);
 QComboBox* curvatureField;// = new QComboBox<String>(curveOptions);
 QCheckBox* permissiveField;// = new QCheckBox();
 QComboBox* speedField;

 QRadioButton* inch;// = new JRadioButton(tr("Inches"));
 QRadioButton* cm;// = new JRadioButton(tr("Centimeters"));

 QString defaultBlockSpeedText;
 BeanItemPanel* physcialDetails();
 NamedBeanComboBox* sensorComboBox;
 BeanItemPanel* sensor();

private slots:
 /*private*/ void updateLength();


protected:
 /*protected*/ void initPanels();

 friend class SetResetItemAction;
 friend class SetSaveItemAction;
};

class SetResetItemAction : public AbstractAction
{
 Q_OBJECT
 BlockEditAction* act;
public:
 SetResetItemAction(BlockEditAction* act) {this->act = act;}
public slots:
 void actionPerformed()
 {
  act->reporterComboBox->setSelectedItem(((Block*) act->bean)->getReporter());
  act->useCurrent->setChecked(((Block*) act->bean)->isReportingCurrent());
 }
};

class SetSaveItemAction : public AbstractAction
{
 Q_OBJECT
 BlockEditAction* act;
public:
 SetSaveItemAction(BlockEditAction* act) {this->act = act;}
public slots:
 /*public*/ void actionPerformed() {
     Block* blk = (Block*) act->bean;
     blk->setReporter((Reporter*) act->reporterComboBox->getSelectedItem());
     blk->setReportingCurrent(act->useCurrent->isChecked());
 }
};
#endif // BLOCKEDITACTION_H
