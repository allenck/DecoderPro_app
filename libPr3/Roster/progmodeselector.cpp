#include "progmodeselector.h"
#include "programmer.h"

ProgModeSelector::ProgModeSelector(QWidget *parent) :
    JPanel(parent)
{
}
/**
 * Provide a JPanel to configure the programming mode.
 * <P>
 * The using code should get a configured programmer with getProgrammer.
 * <P>
 * This pane will only display ops mode options if ops mode is available,
 * as evidenced by an attempt to get an ops mode programmer at startup time.
 * <P>
 * For service mode, you can get the programmer either from here
 * or direct from the instance manager.  For ops mode, you have to
 * get it from here.
 * <P>
 * Note that you should call the dispose() method when you're really done, so that
 * a ProgModeSelector object can disconnect its listeners.
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 17977 $
 */
// /*public*/ abstract class ProgModeSelector extends javax.swing.JPanel {

/**
 * Get the configured programmer
 */
/*abstract*/ /*public*/ Programmer*  ProgModeSelector::getProgrammer() { return NULL;}

/**
 * Does this object have sufficient selection information to
 * provide a programmer?
 * @return true if a programmer is available
 */
/*abstract*/ /*public*/ bool ProgModeSelector::isSelected() {return false;}

/**
 * Enable/Disable the selection aspect of whatever
 * GUI is presented
 * <p>
 * Default beavior is to do nothing.
 * @param enabled false disables GUI user changes
 */
/*public*/ void ProgModeSelector::setEnabled(bool enabled) {}

/**
 * Clean up when done. Required.
 */
/*abstract*/ /*public*/ void ProgModeSelector::dispose() {}
