#include "skemestarteditor.h"

//SkemeStartEditor::SkemeStartEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the SKEME_START macro from the Digitrax sound definition
 * language.
 * <P>
 * This nests until the next SKEME_START.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class SkemeStartEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = 4488606516130401644L;

/*public*/ SkemeStartEditor::SkemeStartEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent)
{
 //super(inst);
 // No editor needed, leave default message in place.
}
