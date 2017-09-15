#include "printaction.h"
#include "paneprogframe.h"

//PrintAction::PrintAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Action to print the information in a VariableTable.
 * <P>
 * This uses the older style printing, for compatibility with Java 1.1.8 in
 * Macintosh MRJ
 *
 * @author		Bob Jacobsen   Copyright (C) 2003
 * @author      Dennis Miller  Copyright (C) 2005
 * @version             $Revision: 28013 $
 */
///*public*/ class PrintAction  extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -633211100496026121L;

/*public*/ PrintAction::PrintAction(QString actionName, PaneProgFrame* frame, bool preview) : QAction(actionName, frame)
{
 //super(actionName);
 mFrame = frame;
 isPreview = preview;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void PrintAction::actionPerformed(ActionEvent* /*e*/) {
 mFrame->printPanes(isPreview);
}
