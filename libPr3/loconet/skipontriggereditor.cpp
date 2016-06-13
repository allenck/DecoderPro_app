#include "skipontriggereditor.h"
#include "sdfmacro.h"
#include <QLabel>
#include <QLayout>

//SkipOnTriggerEditor::SkipOnTriggerEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the SKIP_ON_TRIGGER macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class SkipOnTriggerEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = -7444256530247471680L;

/*public*/ SkipOnTriggerEditor::SkipOnTriggerEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent){
   // super(inst);

    // remove default message from SdfMacroEditor
    this->removeAll();

    // and set up our own
    ((QLayout*)layout())->addWidget(new QLabel("No editor defined for this instruction yet."));
}
