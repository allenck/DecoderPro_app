#include "enginestableaction.h"
#include "enginestableframe.h"

//EnginesTableAction::EnginesTableAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to create and register a EnginesTableFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 28746 $
 */
///*public*/ class EnginesTableAction extends AbstractAction {

    /**
     *
     */
    //private static final long serialVersionUID = 755025320493011103L;

    /*public*/ EnginesTableAction::EnginesTableAction(QString s, QObject *parent) :
  AbstractAction(s, parent) {
 common();
        //super(s);
    }

    /*public*/ EnginesTableAction::EnginesTableAction(QObject *parent) :
  AbstractAction(tr("Engines"),parent) {
        //this(tr("Engines")); // NOI18N
 common();
    }
void EnginesTableAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
    /*public*/ void EnginesTableAction::actionPerformed(JActionEvent * /*e*/) {
        // create a engine table frame
        new Operations::EnginesTableFrame();
    }
