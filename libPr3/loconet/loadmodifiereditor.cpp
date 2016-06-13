#include "loadmodifiereditor.h"
#include <QLabel>
#include <QLayout>

//LoadModifierEditor::LoadModifierEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the LOAD_MODIFIER macro from the Digitrax sound definition
 * language
 *
 * Arg1: Upper 4 bits - math modifiers FMATH_LODE et al Arg2: Arg3:
 *
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class LoadModifierEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = 8107914840589271502L;

/*public*/ LoadModifierEditor::LoadModifierEditor(SdfMacro* inst, QWidget *parent) : SdfMacroEditor(inst, parent)
{
 //super(inst);

 // remove default message from SdfMacroEditor
 this->removeAll();

 // and set up our own
 layout()->addWidget(new QLabel("No editor defined for this instruction yet."));
}
