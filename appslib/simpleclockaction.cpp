#include "simpleclockaction.h"
#include "simpleclockframe.h"
#include "logger.h"

//SimpleClockAction::SimpleClockAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a SimpleClockFrame object
 *
 * @author	Dave Duchamp Copyright (C) 2004
 * @version	$Revision: 28746 $
 */
///*public*/ class SimpleClockAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -3576996090549666302L;

/*public*/ SimpleClockAction::SimpleClockAction(QString s,QObject *parent) :
  QAction(s, parent) {
    //super(s);
 common();
}

/*public*/ SimpleClockAction::SimpleClockAction(QObject *parent) :
  QAction(tr("Fast Clock Setup"), parent)
{
 //super("Fast Clock Setup");
 common();
}
void SimpleClockAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void SimpleClockAction::actionPerformed(ActionEvent* /*e*/) {

 SimpleClockFrame* f = new SimpleClockFrame();
 try {
     f->initComponents();
 } catch (Exception* E) {
  Logger::error("Exception in Simple Clock: " + E->getMessage());
 }
 f->setVisible(true);
}
