#include "sdfmacroeditor.h"
#include "sdfmacro.h"
#include <QLabel>
#include "defaultmutabletreenode.h"
#include "sdfeditorpane.h"
#include "logger.h"
#include "flowlayout.h"
#include "rosterentry.h"
#include "channelstarteditor.h"
#include "channelstart.h"
#include "sdlversion.h"
#include "sdlversioneditor.h"
#include "skemestart.h"
#include "skemestarteditor.h"
#include "initiatesound.h"
#include "initiatesoundeditor.h"
#include "generatetrigger.h"
#include "generatetriggereditor.h"
#include "loadmodifier.h"
#include "loadmodifiereditor.h"
#include "play.h"
#include "playeditor.h"
#include "maskcompare.h"
#include "maskcompareeditor.h"
#include "branchto.h"
#include "branchtoeditor.h"
#include "endsound.h"
#include "endsoundeditor.h"
#include "delaysound.h"
#include "delaysoundeditor.h"
#include "skipontrigger.h"
#include "skipontriggereditor.h"
#include "twobytemacro.h"
#include "twobytemacroeditor.h"
#include "fourbytemacro.h"
#include "fourbytemacroeditor.h"

//SdfMacroEditor::SdfMacroEditor(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * Common base for all the SDF macro editors.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ abstract class SdfMacroEditor extends JPanel {

/**
 *
 */
//private static final long serialVersionUID = 4518290766707658975L;

/*public*/ SdfMacroEditor::SdfMacroEditor(SdfMacro* inst, QWidget *parent) :
  QWidget(parent)
{
 treenode = NULL;
 editor = NULL;
 //log = new Logger("SdfMacroEditor");

 this->inst = inst;

 // add a default behavior
 FlowLayout* thisLayout = new FlowLayout;
 thisLayout->setObjectName("SdfMacroEditorLayout");
 setLayout(thisLayout);
 thisLayout->addWidget(new QLabel("This instruction has no options to set."));
}


/**
 * Update editor when it's reshown
 */
/*public*/ void SdfMacroEditor::update()
{
}

SdfMacro* SdfMacroEditor::getMacro()
{
 return inst;
}

/**
 * Notify that something has changed
 */
/*public*/ void SdfMacroEditor::updated()
{
 if (treenode != NULL)
 {
  treenode->setUserObject(VPtr<SdfMacroEditor>::asQVariant(this));
 }
 if (editor != NULL) {
     editor->updateSummary();
 }
}

/*public*/ QString SdfMacroEditor::toString() {
    return inst->toString();
}

/*public*/ QString SdfMacroEditor::oneInstructionString() {
    return inst->oneInstructionString();
}

/*public*/ QString SdfMacroEditor::allInstructionString(QString indent) {
    return inst->allInstructionString(indent);
}


/*public*/ void SdfMacroEditor::setNotify(DefaultMutableTreeNode* node, SdfEditorPane* pane) {
    treenode = node;
    editor = pane;
}

/**
 * Return an editor object for a SdfMacro type.
 */
/*static*/ /*public*/ SdfMacroEditor* SdfMacroEditor::attachEditor(SdfMacro* inst)
{
 Logger log("SdfMacroEditor");
    // full 1st byte decoder

 if (qobject_cast<ChannelStart*>(inst) != NULL)
 {
  return new ChannelStartEditor(inst);
 }
 else if(qobject_cast<SdlVersion*>(inst)!= NULL)
 {
  return new SdlVersionEditor(inst);
 }
 else if (qobject_cast<SkemeStart*>(inst) != NULL)
 {
  return new SkemeStartEditor(inst);
 }

 else if (qobject_cast<GenerateTrigger*>(inst) != NULL)
 {
  return new GenerateTriggerEditor(inst);
 }
 else if (qobject_cast<EndSound*>(inst) != NULL)
 {
  return new EndSoundEditor(inst);
 }
 else // 7 bit decode
 if (qobject_cast<DelaySound*>(inst) != NULL)
 {
     return new DelaySoundEditor(inst);
 }
 else // 6 bit decode
 if (qobject_cast<SkipOnTrigger*>(inst) != NULL) {
     return new SkipOnTriggerEditor(inst);
 }
 else // 5 bit decode
 if (qobject_cast<InitiateSound*>(inst) != NULL)
 {
  return new InitiateSoundEditor(inst);
 }
 else if (qobject_cast<MaskCompare*>(inst) != NULL) {
     return new MaskCompareEditor(inst);
 }
 else // 4 bit decode
 if (qobject_cast<LoadModifier*>(inst) != NULL)
 {
  return new LoadModifierEditor(inst);
 }
 else if (qobject_cast<BranchTo*>(inst) != NULL)
 {
  return new BranchToEditor(inst);
 }
 else // 2 bit decode
 if (qobject_cast<Play*>(inst) != NULL)
 {
  return new PlayEditor(inst);
 }
 else // generics
 if (qobject_cast<FourByteMacro*>(inst) != NULL)
 {
  return new FourByteMacroEditor(inst);
 }
 else if (qobject_cast<TwoByteMacro*>(inst) != NULL)
 {
  return new TwoByteMacroEditor(inst);
 }
 log.error("PANIC " + inst->name() );
 return new SdfMacroEditor(NULL);
}
void SdfMacroEditor::removeAll()
{
 QObjectList l = children();
 foreach(QObject* o, l)
 {
  if(qobject_cast<QWidget*>(o) != NULL)
  {
   layout()->removeWidget((QWidget*)o);
   delete o;
  }
 }
}
