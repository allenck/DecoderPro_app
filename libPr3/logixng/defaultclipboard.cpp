#include "defaultclipboard.h"
#include "runtimeexception.h"
#include "defaultfemaleanysocket.h"

/**
 * Default implementation of the clipboard
 *
 * @author Daniel Bergqvist (C) 2020
 */
///*public*/ class DefaultClipboard extends AbstractBase implements Clipboard {


//    /*private*/ /*final*/ FemaleAnySocket* _femaleSocket = new DefaultFemaleAnySocket(this, new FemaleSocketListener(),"A") ;
//        //@Override
//        /*public*/ void connected(FemaleSocket socket) {
//            // Do nothing
//        }

//        //@Override
//        /*public*/ void disconnected(FemaleSocket socket) {
//            // Do nothing
//        }
//    }, "A");


    /*public*/ DefaultClipboard::DefaultClipboard(QObject* parent ) : AbstractBase("IQClipboard", parent) {
        //super("IQClipboard");

        // Listeners should never be enabled for the clipboard
        _femaleSocket->setEnableListeners(false);

        try {
            _femaleSocket->_connect(new MaleRootSocket(nullptr, this));
        } catch (SocketAlreadyConnectedException* ex) {
            // This should never happen
            throw new RuntimeException("Program error", ex);
        }
        if (!_femaleSocket->setParentForAllChildren(QList<QString>())) {
            throw new RuntimeException("Failed to set parent for all children");
        }
        _clipboardItems->setParent(_femaleSocket->getConnectedSocket());
    }

    //@Override
    /*public*/ bool DefaultClipboard::isEmpty() {
        return _clipboardItems->getChildCount() == 0;
    }

    //@Override
    /*public*/ bool DefaultClipboard::add(MaleSocket* maleSocket, QList<QString> errors) {
        _clipboardItems->ensureFreeSocketAtTop();
        try {
            _clipboardItems->getChild(0)->_connect(maleSocket);
            return _clipboardItems->setParentForAllChildren(errors);
        } catch (SocketAlreadyConnectedException* ex) {
            throw new RuntimeException("Cannot add socket", ex);
        }
    }

    //@Override
    /*public*/ MaleSocket* DefaultClipboard::fetchTopItem() {
        if (!isEmpty()) {
            MaleSocket* maleSocket = _clipboardItems->getChild(0)->getConnectedSocket();
            _clipboardItems->getChild(0)->_disconnect();
            return maleSocket;
        } else {
            return nullptr;
        }
    }

    //@Override
    /*public*/ MaleSocket* DefaultClipboard::getTopItem() {
        if (!isEmpty()) {
            return _clipboardItems->getChild(0)->getConnectedSocket();
        } else {
            return nullptr;
        }
    }

    //@Override
    /*public*/ FemaleSocket* DefaultClipboard::getFemaleSocket() {
        return _femaleSocket;
    }

    //@Override
    /*public*/ void DefaultClipboard::moveItemToTop(MaleSocket* maleSocket) {
        _clipboardItems->ensureFreeSocketAtTop();
        if (maleSocket->getParent() != nullptr) {
            if (!(qobject_cast<AbstractFemaleSocket*>(maleSocket->getParent()->bself()))) {
                throw new UnsupportedOperationException("maleSocket.parent() is not a female socket");
            }
            ((AbstractFemaleSocket*)maleSocket->getParent()->bself())->_disconnect();
        }
        try {
            _clipboardItems->getChild(0)->_connect(maleSocket);
        } catch (SocketAlreadyConnectedException* ex) {
            throw new UnsupportedOperationException("Cannot move item to clipboard", ex);
        }
    }

    //@Override
    /*public*/ void DefaultClipboard::setup() {
        _clipboardItems->setup();
    }

    /*public*/ bool DefaultClipboard::replaceClipboardItems(ClipboardMany* clipboardItems, QList<QString> errors) {
        _clipboardItems = clipboardItems;

        _femaleSocket->_disconnect();

        try {
            _femaleSocket->_connect(new MaleRootSocket(nullptr, this));
        } catch (SocketAlreadyConnectedException* ex) {
            // This should never happen
            throw new RuntimeException("Program error", ex);
        }
        bool result = _femaleSocket->setParentForAllChildren(errors);
        _clipboardItems->setParent(_femaleSocket->getConnectedSocket());
        return result;
    }

    //@Override
    /*protected*/ void DefaultClipboard::registerListenersForThisClass() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*protected*/ void DefaultClipboard::unregisterListenersForThisClass() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*protected*/ void DefaultClipboard::disposeMe() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ void DefaultClipboard::setState(int s) /*throws JmriException*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ int DefaultClipboard::getState() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ QString DefaultClipboard::getBeanType() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ Base* DefaultClipboard::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ QString DefaultClipboard::getShortDescription(QLocale locale) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ QString DefaultClipboard::getLongDescription(QLocale locale) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ Base* DefaultClipboard::getParent() const {
        return nullptr;
    }

    //@Override
    /*public*/ void DefaultClipboard::setParent(Base* parent) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ FemaleSocket* DefaultClipboard::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ int DefaultClipboard::getChildCount() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ Category *DefaultClipboard::getCategory() {
        throw new UnsupportedOperationException("Not supported");
    }

#if 0
    private class MaleRootSocket extends AbstractMaleSocket {

        /*public*/ MaleRootSocket(BaseManager<? extends NamedBean> manager) {
            super(manager, _clipboardItems);
        }

        //@Override
        protected void registerListenersForThisClass() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        protected void unregisterListenersForThisClass() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        protected void disposeMe() {
            _clipboardItems.dispose();
        }

        //@Override
        /*public*/ void setEnabled(boolean enable) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ void setEnabledFlag(boolean enable) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ boolean isEnabled() {
            return _clipboardItems.isEnabled();
        }

        //@Override
        /*public*/ void setDebugConfig(DebugConfig config) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ DebugConfig getDebugConfig() {
            return null;
        }

        //@Override
        /*public*/ DebugConfig createDebugConfig() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ QString getComment() {
            return _clipboardItems.getComment();
        }

        //@Override
        /*public*/ void setComment(String s) throws NamedBean.BadUserNameException {
            throw new UnsupportedOperationException("Not supported");
        }

    }
#endif
