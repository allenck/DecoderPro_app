#include "lcdclockaction.h"
#include "lcdclockframe.h"

//LcdClockAction::LcdClockAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a LcdClockFrame object
 *
 * @author	Ken Cameron Copyright (C) 2007
 * @version	$Revision: 28746 $
 *
 * This was a direct steal form the Nixie clock code, ver 1.5. Thank you Bob
 * Jacobsen.
 */
///*public*/ class LcdClockAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -2354784468892156228L;

/*public*/ LcdClockAction::LcdClockAction(QObject *parent) :
  QAction(tr("LCD Clock"),parent) {
 //this("LCD Clock");
 common();
}

/*public*/ LcdClockAction::LcdClockAction(QString s, QObject *parent) :
  QAction(s,parent){
    //super(s);
 common();
}
void LcdClockAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void LcdClockAction::actionPerformed(ActionEvent* e) {

    LcdClockFrame* f = new LcdClockFrame();
    f->setVisible(true);

}
