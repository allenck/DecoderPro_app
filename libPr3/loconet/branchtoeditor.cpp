#include "branchtoeditor.h"
#include "sdfmacro.h"
#include <QLayout>
#include <QLabel>

//BranchToEditor::BranchToEditor(QWidget *parent) :
//  SdfMacroEditor(parent)
//{
//}
/**
 * Editor panel for the BRANCH_TO macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
//class BranchToEditor extends SdfMacroEditor {

 /**
  *
  */
 //private static final long serialVersionUID = -7625740509332461282L;

 /*public*/ BranchToEditor::BranchToEditor(SdfMacro* inst, QWidget *parent) :
  SdfMacroEditor(inst, parent)
{
 //super(inst);

 // remove default message from SdfMacroEditor
 this->removeAll();

 // and set up our own
 ((QLayout*)layout())->addWidget(new QLabel("No editor defined for this instruction yet."));
}
