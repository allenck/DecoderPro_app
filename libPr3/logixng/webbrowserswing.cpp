#include "webbrowserswing.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "webbrowser.h"

WebBrowserSwing::WebBrowserSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class WebBrowserSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void WebBrowserSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool WebBrowserSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* WebBrowserSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        WebBrowser* action = new WebBrowser(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void WebBrowserSwing::updateObject(/*@Nonnull*/ Base* /*object*/) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString WebBrowserSwing::toString() {
        return tr("WebBrowser");
    }

    //@Override
    /*public*/ void WebBrowserSwing::dispose() {
    }
