#include "lnpanel.h"
#include "loconetsystemconnectionmemo.h"

LnPanel::LnPanel(QWidget *parent) :
    JmriPanel(parent)
{
}
/**
 * JPanel extension to handle automatic creation
 * of window title and help reference for LocoNet panels
 * <p>
 * For use with JmriAbstractAction, etc
 *
 * @author Bob Jacobsen  Copyright 2010
 * @since 2.9.4
 * @version $Revision: 28013 $
 */

// abstract /*public*/ class LnPanel extends jmri.util.swing.JmriPanel implements LnPanelInterface {


/**
 *
 */
//private static final long serialVersionUID = 9092473563938799253L;

/*public*/ void LnPanel::initComponents(LocoNetSystemConnectionMemo* memo)
{
 this->memo = memo;
 setWindowTitle(getTitle());
}

QString LnPanel::getTitle() { return "";}

/*public*/ void LnPanel::initContext(QObject* context)
{
 if (qobject_cast<LocoNetSystemConnectionMemo*>(context) != NULL )
 {
  initComponents((LocoNetSystemConnectionMemo*) context);
 }
}

/*public*/ QString LnPanel::getTitle(QString menuTitle)
{
 QString uName = "";
 if (memo!=NULL)
 {
  uName = memo->getUserName();
  // string "LocoNet" is hard coded
  if ("LocoNet"!=(uName))
  {
   uName = uName+": ";
  }
  else
  {
   uName = "";
  }
 }
 return uName + menuTitle;
}
