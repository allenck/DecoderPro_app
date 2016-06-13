#include "twobytemacroeditor.h"
#include "sdfmacro.h"
#include <QLabel>
#include <QLayout>

//TwoByteMacroEditor::TwoByteMacroEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the generic two-byte macros from the Digitrax sound
 * definition language
 * <p>
 * In theory, this should never be invoked, because all the macros have specific
 * editors. But editors like this never keep up with changes to content of
 * underlying data, so we provide this as an escape claus for unrecognized
 * content.
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008
 * @version $Revision: 28746 $
 */
//class TwoByteMacroEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = 5363908602077121350L;

/*public*/ TwoByteMacroEditor::TwoByteMacroEditor(SdfMacro* inst, QWidget *parent)
 :  SdfMacroEditor(inst, parent) {
    //super(inst);

    // remove default message from SdfMacroEditor
    this->removeAll();

    // and set up our own
    ((QLayout*)layout())->addWidget(new QLabel("No editor defined for this instruction yet."));
}
