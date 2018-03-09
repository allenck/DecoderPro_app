#include "locoseltreepane.h"
#include <QLabel>
#include "jtogglebutton.h"
#include "globalrosterentrycombobox.h"

LocoSelTreePane::LocoSelTreePane(QWidget *parent) :
    CombinedLocoSelTreePane(parent)
{
}
/**
 * Provide GUI controls to select a new decoder.
 * <P>
 * This is an extension of the CombinedLocoSelPane class to use
 * a JTree instead of a JComboBox for the decoder selection.
 * The loco selection (Roster manipulation) parts are unchanged.
 * <P>
 * The JComboBox implementation always had to have selected entries, so
 * we added dummy "select from .." items at the top & used those to
 * indicate that there was no selection in that box.
 * Here, the lack of a selection indicates there's no selection.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002, 2008
 * @version			$Revision: 21951 $
 */
///*public*/ class LocoSelTreePane extends CombinedLocoSelTreePane  {

/*public*/ LocoSelTreePane::LocoSelTreePane(QLabel* s, ProgModeSelector* selector, QWidget *parent)
    : CombinedLocoSelTreePane(s, selector, parent)
{
 //super(s);
}

///*public*/ LocoSelTreePane() {
//        super();
//}

// don't show the select-roster-entry box
/*protected*/ QWidget* LocoSelTreePane::layoutRosterSelection()
{
 locoBox->setVisible(false);
 return NULL;
}

/*protected*/ QWidget*  LocoSelTreePane::layoutDecoderSelection()
{
 QWidget* pan = CombinedLocoSelTreePane::layoutDecoderSelection();
 viewButtons->setVisible(false);
 return pan;
}

// don't show the Ident button
JToggleButton* LocoSelTreePane::addDecoderIdentButton()
{
 return NULL;
}
