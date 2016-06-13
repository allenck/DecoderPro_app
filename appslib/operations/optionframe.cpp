#include "optionframe.h"
#include "optionpanel.h"

namespace Operations
{
/**
 * Frame for user edit of setup options
 *
 * @author Dan Boudreau Copyright (C) 2010, 2011, 2012, 2013
 * @version $Revision: 28746 $
 */
///*public*/ class OptionFrame extends OperationsFrame {

    /**
     *
     */
 //private static final long serialVersionUID = 6966221440054475425L;

 /*public*/ OptionFrame::OptionFrame(QWidget* parent)
     : OperationsFrame(tr("Options"), parent){
//        super(Bundle.getMessage("TitleOptions"), new OptionPanel());
  setContentPane(new OptionPanel(this));
 }

 //@Override
 /*public*/ void OptionFrame::initComponents() {
     OperationsFrame::initComponents();

     // build menu
     addHelpMenu("package.jmri.jmrit.operations.Operations_SettingsOptions", true); // NOI18N

     initMinimumSize();
 }
}
