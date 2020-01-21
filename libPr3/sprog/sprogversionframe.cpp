#include "sprogversionframe.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "sprogversion.h"
#include "sprogversionquery.h"

using namespace Sprog;
/**
 * Display the firmware version of the attached SPROG hardware.
 *
 * @author	Andrew Crosland Copyright (C) 2008
 */
///*public*/ class SprogVersionFrame extends jmri.util.JmriJFrame implements SprogVersionListener {


/*public*/ SprogVersionFrame::SprogVersionFrame(SprogSystemConnectionMemo* memo, QWidget* parent): JmriJFrame(parent) {
    //super();
    _memo = memo;
}

/**
 * {@inheritDoc}
 */
//@Override
/*synchronized*/ /*public*/ void SprogVersionFrame::initComponents() {
    setTitle(tr("Sprog Version"));

    // add help menu to window
    addHelpMenu("package.jmri.jmrix.sprog.update.SprogVersionFrame", true);

    // Start the query
    SprogVersionQuery* query = _memo->getSprogVersionQuery();
    query->requestVersion((SprogVersionListener*)this);
}

/**
 * {@inheritDoc}
 */
//@Override
/*synchronized*/ /*public*/ void SprogVersionFrame::notifyVersion(SprogVersion* v) {
    log->debug(tr("Version %1 notified").arg(v->toString()));
    JOptionPane::showMessageDialog(NULL, tr("SPROG version: {%1}").arg( v->toString()),
            tr("Sprog Version"), JOptionPane::INFORMATION_MESSAGE);
    setVisible(false);
    dispose();
}
/*public*/ QString SprogVersionFrame::getClassName()
{
 return "jmri.jmrix.sprog.update.SprogVersionFrame";
}

/*private*/ /*final*/ /*static*/ Logger* SprogVersionFrame::log = LoggerFactory::getLogger("SprogVersionFrame");
