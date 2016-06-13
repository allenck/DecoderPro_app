#include "monitoringlabel.h"
#include "propertychangeevent.h"

//MonitoringLabel::MonitoringLabel(QWidget *parent) :
//  JTextArea(parent)
//{
//}
/**
 * Label which displays the contents of parameter messages.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version	$Revision: 28746 $
 */
// /*public*/ class MonitoringLabel extends javax.swing.JTextArea implements java.beans.PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = 266331403840457618L;

/*public*/ MonitoringLabel::MonitoringLabel(QWidget *parent) :
  JTextArea(parent)
{
 //super();
}

/*public*/ MonitoringLabel::MonitoringLabel(int row, int col, QWidget *parent)
 :  JTextArea(row, col, parent) {
 //super(row, col);
}

/**
 * Listening method, diplays results
 */
/*public*/ void MonitoringLabel::propertyChange(PropertyChangeEvent* evt)
{
 setText(evt->getNewValue().toString());
}
