#include "nixieclockaction.h"
#include "nixieclockframe.h"

//NixieClockAction::NixieClockAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a NixieClockFrame object
 *
 * @author	Bob Jacobsen Copyright (C) 2004
 * @version	$Revision: 28746 $
 */
///*public*/ class NixieClockAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -5653182277242573672L;

/*public*/ NixieClockAction::NixieClockAction(QObject *parent) :
  QAction(tr("Nixie Clock"), parent) {
    //this("Nixie Clock");
 common();
}

/*public*/ NixieClockAction::NixieClockAction(QString s, QObject *parent) :
  QAction(s, parent) {
  //super(s);
 common();
}
void NixieClockAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void NixieClockAction::actionPerformed(ActionEvent* /*e*/) {

    NixieClockFrame* f = new NixieClockFrame();
    f->setVisible(true);

}
