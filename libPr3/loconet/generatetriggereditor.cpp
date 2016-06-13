#include "generatetriggereditor.h"
#include <QLabel>
#include <QLayout>

//GenerateTriggerEditor::GenerateTriggerEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the GENERATE_TRIGGER macro from the Digitrax sound
 * definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class GenerateTriggerEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = -4809270548383400410L;

/*public*/ GenerateTriggerEditor::GenerateTriggerEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent)
{
 //super(inst);

 // remove default message from SdfMacroEditor
 this->removeAll();

 // and set up our own
 layout()->addWidget(new QLabel("No editor defined for this instruction yet."));
}
