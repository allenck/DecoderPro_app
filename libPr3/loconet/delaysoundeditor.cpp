#include "delaysoundeditor.h"
#include <QLayout>
#include "sdfmacro.h"
#include <QLabel>

//DelaySoundEditor::DelaySoundEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the DELAY_SOUND macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class DelaySoundEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = 8584517409405023951L;

/*public*/ DelaySoundEditor::DelaySoundEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent) {
    //super(inst);

    // remove default message from SdfMacroEditor
    this->removeAll();

    // and set up our own
    ((QLayout*)layout())->addWidget(new QLabel("No editor defined for this instruction yet."));
}
