#ifndef DEFAULTCLIPBOARD_H
#define DEFAULTCLIPBOARD_H
#include "abstractbase.h"
#include "clipboard.h"
#include "clipboardmany.h"
#include "defaultfemaleanysocket.h"
#include "femalesocketlistener.h"
#include "abstractmalesocket.h"

#if 1
class DCFemaleSocketListener;
class DefaultClipboard;
class FemaleSocketListener;

class DCFemaleSocketListener : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
  DefaultClipboard* defaultClipboard;
 public:
  DCFemaleSocketListener() : QObject() {}
  QObject* self() override {return (QObject*)this;}
  protected:
  //@Override
  /*public*/ void connected(FemaleSocket* socket) override {
      // Do nothing
  }

  //@Override
  /*public*/ void disconnected(FemaleSocket* socket) override{
      // Do nothing
  }
};

class DefaultClipboard : public AbstractBase, public Clipboard
{
  Q_OBJECT
  Q_INTERFACES(Clipboard)
 public:
  DefaultClipboard(QObject* parent = nullptr);
  /*public*/ bool isEmpty()override;
  /*public*/ bool add(MaleSocket* maleSocket, QList<QString> *errors)override;
  /*public*/ MaleSocket* fetchTopItem()override;
  /*public*/ MaleSocket* getTopItem()override;
  /*public*/ FemaleSocket *getFemaleSocket()override;
  /*public*/ void moveItemToTop(MaleSocket* maleSocket)override;
  /*public*/ void setup()override;
  /*public*/ bool replaceClipboardItems(ClipboardMany* clipboardItems, QList<QString> *errors);
  /*public*/ void setState(int s) /*throws JmriException*/override;
  /*public*/ int getState() override;
  /*public*/ QString getBeanType()override;
  /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;
  /*public*/ Base* getParent() const override;
  /*public*/ void setParent(Base* parent)override;
  /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/ int getChildCount() override;
  /*public*/ Category getCategory()override;
  /*public*/ QString getClassName() {return "jmri.jmrit.logixng.tools.debugger.DefaultClipboard";}

  QObject* self() override {return (QObject*)this;}
 QObject* bself() override {return (QObject*)this;}

 /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
  AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
 }
 /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                   QString name, QString listenerRef) override {
  AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
 }
 /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
 /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
 /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
 /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
 /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
 /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
  return AbstractNamedBean::getPropertyChangeListenersByReference(name);
 }

 private:
  /*private*/ ClipboardMany* _clipboardItems = nullptr; //new ClipboardMany("", nullptr);
  DefaultClipboard* defaultClipboard;
  /*public*/ void connected(FemaleSocket* socket) {
              // Do nothing
  }
  //@Override
  /*public*/ void disconnected(FemaleSocket* socket) {
      // Do nothing
  }
  /*private*/ /*final*/ FemaleAnySocket* _femaleSocket = new DefaultFemaleAnySocket(this, new DCFemaleSocketListener(),"A");

 protected:
  /*protected*/ void registerListenersForThisClass()override;
  /*protected*/ void unregisterListenersForThisClass()override;
  /*protected*/ void disposeMe()override;
 friend class MaleRootSocket;
};



/*private*/ class MaleRootSocket : public AbstractMaleSocket {
  DefaultClipboard* defaultClipboard;
  Q_OBJECT
public:
        /*public*/ MaleRootSocket(BaseManager/*<? extends NamedBean>*/* manager, DefaultClipboard* defaultClipboard)
   : AbstractMaleSocket(manager, defaultClipboard->_clipboardItems) {
            //super(manager, _clipboardItems);
   this->defaultClipboard = defaultClipboard;
        }
  /*public*/ bool add(MaleSocket* maleSocket, QList<QString> errors);
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.MaleRootSocket";}

 protected:
        //@Override
        /*protected*/ void registerListenersForThisClass() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*protected*/ void unregisterListenersForThisClass() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*protected*/ void disposeMe() {
            defaultClipboard->_clipboardItems->dispose();
        }
public:
        //@Override
        /*public*/ void setEnabled(bool enable) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ void setEnabledFlag(bool enable) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ bool isEnabled() {
            return defaultClipboard->_clipboardItems->isEnabled();
        }

        //@Override
        /*public*/ void setDebugConfig(DebugConfig* config) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ DebugConfig* getDebugConfig() {
            return nullptr;
        }

        //@Override
        /*public*/ DebugConfig* createDebugConfig() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/ QString getComment() override {
            return defaultClipboard->_clipboardItems->AbstractNamedBean::getComment();
        }

        //@Override
        /*public*/ void setComment(QString s) /*throws NamedBean.BadUserNameException*/ {
            throw new UnsupportedOperationException("Not supported");
        }
  };
#endif
#endif // DEFAULTCLIPBOARD_H
