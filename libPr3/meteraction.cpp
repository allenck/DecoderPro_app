#include "meteraction.h"
#include "meterframe.h"

/**
 * Swing action to create and register a AmpMeterFrame object.
 *
 * @author Ken Cameron        Copyright (C) 2007
 * @author Mark Underwood     Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2020
 *
 * This was a direct steal form the LCDClock code by Ken Cameron,
 * which was a direct steal from the Nixie clock code, ver 1.5.
 * Thank you Bob Jacobsen and Ken Cameron.
 */
// /*public*/ class MeterAction extends AbstractAction {

    /*public*/ MeterAction::MeterAction(QObject* parent) : AbstractAction(tr("Meter"), parent){
        //this(tr("Meter"));
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    /*public*/ MeterAction::MeterAction(QString s, QObject* parent) : AbstractAction(s, parent){
        //super(s);
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    //@Override
    /*public*/ void MeterAction::actionPerformed(/*ActionEvent e*/) {
        MeterFrame* f = new MeterFrame();
        f->initComponents();
        f->setVisible(true);
    }
