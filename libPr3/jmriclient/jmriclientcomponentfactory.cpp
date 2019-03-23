#include "jmriclientcomponentfactory.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientmenu.h"
/**
 * Provide access to Swing components for the JMRI Network Client.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Paul Bender Copyright (C) 2010
 * @since 2.11.1
 */
///*public*/ class JMRIClientComponentFactory extends jmri.jmrix.swing.ComponentFactory {

/*public*/ JMRIClientComponentFactory::JMRIClientComponentFactory(JMRIClientSystemConnectionMemo* memo, QObject *parent)
: ComponentFactory(parent)
{
    this->memo = memo;
}


/**
 * Provide a menu with all items attached to this system connection
 */
//@Override
/*public*/ QMenu* JMRIClientComponentFactory::getMenu(QWidget* frame) {
    if (memo->getDisabled()) {
        return nullptr;
    }
    return new JMRIClientMenu(memo, this);
}
