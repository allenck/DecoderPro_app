#include "analogclockaction.h"
#include "analogclockframe.h"

//AnalogClockAction::AnalogClockAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a AnalogClockFrame object Copied from
 * code for NixieClockAction by Bob Jacobsen
 *
 * @author	Dennis Miller Copyright (C) 2004
 * @version	$Revision: 28746 $
 */
///*public*/ class AnalogClockAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 4819621738581568597L;

/*public*/ AnalogClockAction::AnalogClockAction(QObject *parent) :
  AbstractAction(tr("Analog Clock"), parent) {
    //this("Analog Clock");
 common();
}

/*public*/ AnalogClockAction::AnalogClockAction(QString s, QObject *parent) :
  AbstractAction(s, parent) {
    //super(s);
 common();
}

void AnalogClockAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void AnalogClockAction::actionPerformed(ActionEvent* /*e*/) {

    AnalogClockFrame* f = new AnalogClockFrame();
    f->setVisible(true);

}
