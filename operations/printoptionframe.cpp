#include "printoptionframe.h"
#include <QMenuBar>
#include <QMenu>
#include "printoptionpanel.h"
#include "editmanifesttextaction.h"
#include "editmanifestheadertextaction.h"
#include "editswitchlisttextaction.h"
#include "printmoreoptionaction.h"

namespace Operations
{
/**
 * Frame for user edit of manifest and switch list print options
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013
 * @version $Revision: 28746 $
 */
///*public*/ class PrintOptionFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -3366352601871116274L;

 /*public*/ PrintOptionFrame::PrintOptionFrame(QWidget* parent) : OperationsFrame(parent) {
     //super(Bundle.getMessage("TitlePrintOptions"), new PrintOptionPanel());
  setContentPane(new PrintOptionPanel(this));
 }

 //@Override
 /*public*/ void PrintOptionFrame::initComponents() {
     OperationsFrame::initComponents();

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new PrintMoreOptionAction(this));
     toolMenu->addAction(new EditManifestHeaderTextAction(this));
     toolMenu->addAction(new EditManifestTextAction(this));
     toolMenu->addAction(new EditSwitchListTextAction(this));

     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_PrintOptions", true); // NOI18N

     initMinimumSize();
 }

 /*public*/ QString PrintOptionFrame::getClassName()
 {
  return "jmri.jmrit.operations.setup.PrintOptionFrame";
 }

}
