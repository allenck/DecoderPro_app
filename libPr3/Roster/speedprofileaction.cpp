#include "speedprofileaction.h"
#include "windowinterface.h"
#include "speedprofileframe.h"

//SpeedProfileAction::SpeedProfileAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register the Add Entry Exit Pair
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 1.4 $
 */
// /*public*/ class SpeedProfileAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 7900417672370349395L;

/*public*/ SpeedProfileAction::SpeedProfileAction(QString s, WindowInterface* wi)
 : QAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ SpeedProfileAction::SpeedProfileAction(QString s, QIcon i, WindowInterface* wi)  : QAction(i, s, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ SpeedProfileAction::SpeedProfileAction(QString s, QObject *parent) :
   QAction(s,parent)
{
 //super(s);
 common();
}
void SpeedProfileAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void SpeedProfileAction::actionPerformed(ActionEvent* /*e*/)
{
 SpeedProfileFrame* f = new SpeedProfileFrame();
//    try {
     f->initComponents();
//    } catch (Exception* ex) {
//        log.error("Exception: " + ex.toString());
//        ex.printStackTrace();
//    }
 f->setVisible(true);
}
