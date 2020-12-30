#include "addentryexitpairaction.h"
#include "layouteditor.h"
#include "addentryexitpairframe.h"

//AddEntryExitPairAction::AddEntryExitPairAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to create and register the Add Entry Exit Pair
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 1.4 $
 */
///*public*/ class AddEntryExitPairAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -2153517492240562949L;

/*public*/ AddEntryExitPairAction::AddEntryExitPairAction(QString /*s*/, LayoutEditor* panel, QObject *parent)
 : AbstractAction(parent)
{
 //super(s);
 this->panel = panel;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void AddEntryExitPairAction::actionPerformed(JActionEvent* /*e*/)
{
 AddEntryExitPairFrame* f = new AddEntryExitPairFrame();
 try
 {
  f->initComponents(panel);
 }
 catch (Exception ex)
 {
  Logger::error("Exception: " + ex.getMessage());
  //ex.printStackTrace();
 }
  f->setVisible(true);
}
