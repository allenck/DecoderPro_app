#include "initiatesoundeditor.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include "sdfconstants.h"
#include "stringutil.h"
#include "initiatesound.h"

//InitiateSoundEditor::InitiateSoundEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the INITIATE_SOUND macro.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class InitiateSoundEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = -7107120240412402003L;

/*public*/ InitiateSoundEditor::InitiateSoundEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent)
{
    //super(inst);
 zap = new QCheckBox("Zap");
 run = new QCheckBox("Run while triggered");
 noprempt = new QCheckBox("No preemptive trigger");
 nottrig = new QCheckBox("Not triggered");

 // remove warning message from SdfMacroEditor
 //this->removeAll();
 QObjectList l = children();
 foreach(QObject* o, l)
 {
  if(qobject_cast<QWidget*>(o) != NULL)
  {
   layout()->removeWidget((QWidget*)o);
   delete o;
  }
 }
 delete layout();

 // and set up our own
 QVBoxLayout* thisLayout;
 this->setLayout(thisLayout=new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 QWidget* p = new QWidget();
 FlowLayout* pLayout;
 p->setLayout(pLayout = new FlowLayout());

 pLayout->addWidget(new QLabel("Start sequence when: "));
 box = new QComboBox(/*SdfConstants.editorTriggerNames*/);
 box->addItems(SdfConstants::editorTriggerNames);

 // find & set index of selected value
 update();

 pLayout->addWidget(box);
 thisLayout->addWidget(p);

 // check boxes
 thisLayout->addWidget(zap);
 thisLayout->addWidget(run);
 thisLayout->addWidget(noprempt);
 thisLayout->addWidget(nottrig);

 // change the instruction when the value is changed
// ActionListener l = new ActionListener() {
//     public void actionPerformed(java.awt.event.ActionEvent e) {
//         // have to convert back from string to
//         // trigger value
//         String trigger = (String) box.getSelectedItem();
//         int value = jmri.util.StringUtil.getStateFromName(trigger, SdfConstants.triggerCodes, SdfConstants.editorTriggerNames);
//         ((InitiateSound) InitiateSoundEditor.this.inst).setTrigger(value);
//         // buttons
//         int prempt = 0;
//         if (zap.isSelected()) {
//             prempt = prempt | SdfConstants.ZAP;
//         }
//         if (run.isSelected()) {
//             prempt = prempt | SdfConstants.RUN_WHILE_TRIG;
//         }
//         if (noprempt.isSelected()) {
//             prempt = prempt | SdfConstants.NO_PREEMPT_TRIG;
//         }
//         if (nottrig.isSelected()) {
//             prempt = prempt | SdfConstants.NOT_TRIG;
//         }
//         ((InitiateSound) InitiateSoundEditor.this.inst).setPrempt(prempt);
//         // tell the world
//         updated();
//     }
// };
 connect(box, SIGNAL(currentIndexChanged(int)), this, SLOT(on_action(int)));

 //box.addActionListener(l);
 //zap.addActionListener(l);
 connect(zap, SIGNAL(toggled(bool)), this, SLOT(on_action()));
 //run.addActionListener(l);
 connect(run, SIGNAL(toggled(bool)), this, SLOT(on_action()));
 //noprempt.addActionListener(l);
 connect(noprempt, SIGNAL(toggled(bool)), this, SLOT(on_action()));
 //nottrig.addActionListener(l);
 connect(nottrig, SIGNAL(toggled(bool)), this, SLOT(on_action()));
}

void InitiateSoundEditor::on_action(int)
{
 // have to convert back from string to
 // trigger value
 QString trigger =  box->currentText();
 int value = StringUtil::getStateFromName(trigger, SdfConstants::triggerCodes, SdfConstants::editorTriggerNames.toVector());
 ((InitiateSound*) InitiateSoundEditor::inst)->setTrigger(value);
 // buttons
 int prempt = 0;
 if (zap->isChecked()) {
     prempt = prempt | SdfConstants::ZAP;
 }
 if (run->isChecked()) {
     prempt = prempt | SdfConstants::RUN_WHILE_TRIG;
 }
 if (noprempt->isChecked()) {
     prempt = prempt | SdfConstants::NO_PREEMPT_TRIG;
 }
 if (nottrig->isChecked()) {
     prempt = prempt | SdfConstants::NOT_TRIG;
 }
 ((InitiateSound*) InitiateSoundEditor::inst)->setPrempt(prempt);
 // tell the world
 updated();

}

/*public*/ void InitiateSoundEditor::update()
{
 // find & set index of selected trigger
 InitiateSound* instruction = (InitiateSound*) inst;
 int trig = instruction->getTrigger();
 for (int i = 0; i < SdfConstants::triggerCodes.size(); i++)
 {
  if (SdfConstants::triggerCodes[i] == trig)
  {
   box->setCurrentIndex(i);
   break;
  }
 }
 // buttons
 int prempt = instruction->getPrempt();
 zap->setChecked((prempt & SdfConstants::ZAP) != 0);
 run->setChecked((prempt & SdfConstants::RUN_WHILE_TRIG) != 0);
 noprempt->setChecked((prempt & SdfConstants::NO_PREEMPT_TRIG) != 0);
 nottrig->setChecked((prempt & SdfConstants::NOT_TRIG) != 0);

}
