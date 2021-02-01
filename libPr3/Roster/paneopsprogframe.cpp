#include "paneopsprogframe.h"

//PaneOpsProgFrame::PaneOpsProgFrame(QWidget *parent) :
//    PaneProgFrame(parent)
//{
//}
/**
 * Extend the PaneProgFrame to handle ops mode operations
 *
 * @author			Bob Jacobsen   Copyright (C) 2002, 2008
 * @version			$Revision: 17977 $
 */
// /*public*/ class PaneOpsProgFrame extends PaneProgFrame
//                 implements java.beans.PropertyChangeListener  {


/**
 * Provide programming-mode panel to the parent class.
 * <p>
 * In this case, provide just an empty JPanel; we
 * presently don't want a selection GUI to be
 * present when in ops mode.
 */
/*protected*/ JPanel* PaneOpsProgFrame::getModePane()
{
 if (modePane == NULL)
  modePane = new JPanel();
 return modePane;
}

/**
 * This invokes the parent ctor to do the real work. That will
 * call back to get the programming mode panel (none) and to
 * hear if there is read mode (no)
 *
 * @param decoderFile XML file defining the decoder contents
 * @param r RosterEntry for information on this locomotive
 * @param name
 * @param file
 */
/*public*/ PaneOpsProgFrame::PaneOpsProgFrame(DecoderFile* decoderFile, RosterEntry* r,
                        QString name, QString file, Programmer* p, QWidget* parent)
    : PaneProgFrame(decoderFile, r, name, file, p, true)

{
 //super(decoderFile, r, name, file, p, true);
 log = new Logger("PaneOpsProgFrame");
 if (log->isDebugEnabled()) log->debug("PaneOpsProgFrame \""+name
                                        +"\" constructed");
 modePane = NULL;
}

void PaneOpsProgFrame::addHelp()
{
 addHelpMenu("package.jmri.jmrit.symbolicprog.tabbedframe.PaneOpsProgFrame", true);
}

/*protected*/ void PaneOpsProgFrame::pickProgrammerMode(/*@NonNull*/ QDomElement programming)
{
 log->debug("Leaving mode as is, supposed to be ops mode");
}
/**
 * local dispose, which also invokes parent. Note that
 * we remove the components (removeAll) before taking those
 * apart.
 */
/*public*/ void PaneOpsProgFrame::dispose()
{
 if (log->isDebugEnabled()) log->debug("dispose local");

 //super.dispose();
 PaneProgFrame::dispose();
}

/*public*/ QString PaneOpsProgFrame::getClassName()
{
 return "jmri.jmrit.symbolicprog.tabbedframe.PaneOpsProgFrame";
}
