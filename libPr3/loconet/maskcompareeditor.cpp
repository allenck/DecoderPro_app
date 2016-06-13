#include "maskcompareeditor.h"
#include "sdfmacro.h"
#include <QLabel>
#include <QLayout>

//MaskCompareEditor::MaskCompareEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the MASK_COMPARE macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class MaskCompareEditor extends SdfMacroEditor {

/**
 *
 */
//private static final long serialVersionUID = -1823359711169229533L;

/*public*/ MaskCompareEditor::MaskCompareEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent)
{
 //super(inst);

 // remove default message from SdfMacroEditor
 this->removeAll();

 // and set up our own
 ((QLayout*)layout())->addWidget(new QLabel("No editor defined for this instruction yet."));
}
