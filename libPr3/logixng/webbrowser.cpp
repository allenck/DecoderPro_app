#include "webbrowser.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/defaultstringexpressionmanager.h"
#include "logixng/femalestringexpressionsocket.h"

/**
 * Executes an string action with the result of an string expression.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/ class WebBrowser
//        extends AbstractDigitalAction
//        implements FemaleSocketListener {


    /*public*/ WebBrowser::WebBrowser(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent) {
        //super(sys, user);
        _urlExpressionSocket = ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))
                ->createFemaleSocket(this, this, "E");
    }

    //@Override
    /*public*/ Base* WebBrowser::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        WebBrowser* copy = new WebBrowser(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category WebBrowser::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void WebBrowser::execute() /*throws JmriException*/ {
        QString url = _urlExpressionSocket->evaluate();
#if 0 // TODO:

        try {
            QUrl* uri = new QUrl(url);
            HttpURLConnection* request = (HttpURLConnection*) uri.toURL().openConnection();
            request.setRequestMethod("GET");
            request.connect();
            if (request.getResponseCode() != 200) {
                throw new JmriException(String.format(
                        "Failed to connect to web page: %d, %s",
                        request.getResponseCode(), request.getResponseMessage()));
            }
            if ( Desktop.getDesktop().isSupported( Desktop.Action.BROWSE) ) {
                // Open browser to URL with draft report
                Desktop.getDesktop().browse(uri);
            } else {
                throw new JmriException(String.format(
                        "Failed to connect to web page. java.awt.Desktop doesn't suppport Action.BROWSE"));
            }
        } catch (IOException | URISyntaxException e) {
            throw new JmriException(String.format(
                    "Failed to connect to web page. Exception thrown: %s",
                    e.getMessage()), e);
        }
#endif
    }

    //@Override
    /*public*/ FemaleSocket* WebBrowser::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        switch (index) {
            case 0:
                return _urlExpressionSocket;

            default:
                throw new IllegalArgumentException(
                        tr("index has invalid value: %1").arg(index));
        }
    }

    //@Override
    /*public*/ int WebBrowser::getChildCount() {
        return 1;
    }

    //@Override
    /*public*/ void WebBrowser::connected(FemaleSocket* socket) {
        if (socket == _urlExpressionSocket) {
            _urlExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/ void WebBrowser::disconnected(FemaleSocket* socket) {
        if (socket == _urlExpressionSocket) {
            _urlExpressionSocketSystemName = nullptr;
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/ QString WebBrowser::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "WebBrowser");
    }

    //@Override
    /*public*/ QString WebBrowser::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Web browser. Open web page %1").arg(_urlExpressionSocket->getName());
    }

    /*public*/ FemaleStringExpressionSocket* WebBrowser::getStringExpressionSocket() {
        return _urlExpressionSocket;
    }

    /*public*/ QString WebBrowser::getStringExpressionSocketSystemName() {
        return _urlExpressionSocketSystemName;
    }

    /*public*/ void WebBrowser::setStringExpressionSocketSystemName(QString systemName) {
        _urlExpressionSocketSystemName = systemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void WebBrowser::setup() {
        try {
            if (_urlExpressionSocket->isConnected()
                    || _urlExpressionSocket->getConnectedSocket()->getSystemName()
                             != (_urlExpressionSocketSystemName)) {

                QString socketSystemName = _urlExpressionSocketSystemName;

                _urlExpressionSocket->_disconnect();

                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (AbstractMaleSocket*)
                            ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))
                            ->getBySystemName(socketSystemName)->self();
                    if (maleSocket != nullptr) {
                        _urlExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error(tr("cannot load string expression ") + socketSystemName);
                    }
                }
            } else {
                _urlExpressionSocket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void WebBrowser::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void WebBrowser::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void WebBrowser::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* WebBrowser::log = LoggerFactory::getLogger("WebBrowser");
