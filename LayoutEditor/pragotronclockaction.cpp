#include "pragotronclockaction.h"
#include "pragotronclockframe.h"

/**
 * Swing action to create and register a PragotronClockFrame object.
 *
 * @author Petr Sidlo Copyright (C) 2019
 *
 * Based on Nixie clock by Bob Jacobsen.
 */
 // /*public*/ class PragotronClockAction extends AbstractAction {

/*public*/ PragotronClockAction::PragotronClockAction(QObject* parent) : AbstractAction(tr("Pragotron Clock"), parent)
{
    //this("Pragotron Clock");
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent**/)));
}

/*public*/ PragotronClockAction::PragotronClockAction(QString s, QObject* parent) : AbstractAction(s, parent){
   //super(s);
   connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent**/)));
}

//@Override
/*public*/ void PragotronClockAction::actionPerformed(/*ActionEvent e*/) {

   PragotronClockFrame* f = new PragotronClockFrame();
   f->setVisible(true);
}

