#include "playeditor.h"
#include "sdfmacro.h"
#include "play.h"
#include <QBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

//PlayEditor::PlayEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the PLAY macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class PlayEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = 6609198608813676953L;

/*public*/ PlayEditor::PlayEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent)
{
 //super(inst);
 handle = new QSpinBox(/*handleModel*/);
 handle->setMinimum(0);
 handle->setMaximum(63);
 handle->setValue(0);
 handle->setSingleStep(1);
 loop = new QComboBox(/*SdfConstants.loopNames*/);
 loop->addItems(SdfConstants::loopNames);
 wavbrk1 = new QCheckBox("Invert Loop Reason");
 wavbrk2 = new QCheckBox("Global Loop Reason");

 // remove warning message from SdfMacroEditor
 this->removeAll();

 // find & set selected values
 update();

 // set up GUI
 delete layout();
 QVBoxLayout* thisLayout;
 this->setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 // handle numbers
 QWidget* p = new QWidget();
 {
  QHBoxLayout* pLayout;
  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));

  pLayout->addWidget(new QLabel("Play handle number: "));
  pLayout->addWidget(handle);
  thisLayout->addWidget(p);
 }

 // loop control
 p = new QWidget();
 {
  QHBoxLayout* pLayout;
  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel("Loop control: "));
  pLayout->addWidget(loop);
  thisLayout->addWidget(p);
 }

 // loop control
 p = new QWidget();
 {
  QHBoxLayout* pLayout;
  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(wavbrk1);
  pLayout->addWidget(wavbrk2);
  thisLayout->addWidget(p);
 }

 // change the instruction when the value is changed
// ActionListener l = new ActionListener() {
//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         guiChanged();
//     }
// };

// loop->addActionListener(l);
 connect(loop, SIGNAL(currentIndexChanged(int)), this, SLOT(guiChanged()));
// wavbrk1.addActionListener(l);
// wavbrk2.addActionListener(l);
// ChangeListener c = new ChangeListener() {
//      /*public*/ void stateChanged(ChangeEvent e) {
//         guiChanged();
//     }
// };
// handle.addChangeListener(c);
}


/**
* update instruction if GUI changes
*/
void PlayEditor::guiChanged() {
 //Play* instruction = (Play*) PlayEditor.this.inst;
 Play* instruction = (Play*)inst;

 instruction->setHandle(handle->value());

 instruction->setBrk(loop->currentText());

 int flag = 0;
 if (wavbrk1->isChecked()) {
     flag |= 0x01;
 }
 if (wavbrk2->isChecked()) {
     flag |= 0x02;
 }
 instruction->setWaveBrkFlags(flag);

 // tell the world
 updated();
}

/*public*/ void PlayEditor::update()
{
 // find & set index of selected trigger
 Play* instruction = (Play*) inst;
 int handleVal = handle->value();
 instruction->setHandle(handleVal);

 // loop flag
 loop->setCurrentIndex(loop->findText(instruction->brkVal()));

 // wavbreak flags
 int flags = instruction->getWaveBrkFlags();
 wavbrk1->setChecked((flags & 0x01) != 0);
 wavbrk2->setChecked((flags & 0x02) != 0);
}
