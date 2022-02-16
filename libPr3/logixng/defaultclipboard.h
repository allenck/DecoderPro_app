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
class MyDefaultFemaleAnySocket;
class DefaultClipboard;
class FemaleSocketListener;
class MyDefaultFemaleAnySocket : public DefaultFemaleAnySocket
{
  Q_OBJECT
  //Q_INTERFACES(FemaleAnySocket)

 public:
  MyDefaultFemaleAnySocket(DefaultClipboard* defaultClipboard, FemaleSocketListener* listener, QString name)
   : DefaultFemaleAnySocket((Base*)defaultClipboard, listener, name)
  {
  }
  QObject* self() override {return (QObject*)this;}
  //@Override
  /*public*/ void connected(FemaleSocket* socket) {
      // Do nothing
  }

  //@Override
  /*public*/ void disconnected(FemaleSocket* socket) {
      // Do nothing
  }

  QString getSystemName() const override {return AbstractFemaleSocket::getSystemName();}
  QString getUserName() const override {return AbstractFemaleSocket::getUserName();}
  QString getComment() override {return AbstractFemaleSocket::getComment();}
  void setUserName(QString name) override{AbstractFemaleSocket::setUserName(name);}
  /*public*/ Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/ override{}
  /*public*/ Base* deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames)  override{}
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list) override {return AbstractFemaleSocket::getListenerRefsIncludingChildren(list);}
  /*public*/ Base* getParent() const override {return AbstractFemaleSocket::getParent();}
  /*public*/ void setParent(/*@Nonnull*/ Base* parent)override{}
  /*public*/ bool setParentForAllChildren(QList<QString> errors)override{}
  /*public*/ void setComment(QString s)override{}
  /*public*/ /*final*/ LogixNG* getLogixNG()override {return AbstractFemaleSocket::getLogixNG();}
  /*public*/ /*final*/ Base* getRoot()override {return AbstractFemaleSocket::getRoot();}
  /*public*/ FemaleSocket* getChild(int index) override {return AbstractFemaleSocket::getChild(index);}
  /*public*/ int getChildCount() override {return AbstractFemaleSocket::getChildCount();}
  /*public*/ /*final*/ ConditionalNG* getConditionalNG()override {return AbstractFemaleSocket::getConditionalNG();}
  /*public*/ /*final*/ void dispose()override {AbstractFemaleSocket::dispose();}
   /*public*/ void registerListeners()override {AbstractFemaleSocket::registerListeners();}
   /*public*/ void unregisterListeners() override {AbstractFemaleSocket::unregisterListeners();}
   /*public*/ /*final*/ bool isActive()override {return AbstractFemaleSocket::isActive();}
  /*public*/ Category::TYPE getCategory() override {return AbstractFemaleSocket::getCategory();}
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
    /*MutableInt*/int*  lineNumber)override {return AbstractFemaleSocket::printTree(settings, writer, indent, lineNumber);}
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int*  lineNumber)override {return AbstractFemaleSocket::printTree(settings, locale,writer,indent, lineNumber );}
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          QString currentIndent,
          /*MutableInt*/int*  lineNumber)override {return AbstractFemaleSocket::printTree(settings, locale, writer,indent, lineNumber);}
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override
    {return AbstractFemaleSocket::getUsageTree(level,  bean, report, cdl);}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override
    {return AbstractFemaleSocket::getUsageDetail(level,  bean,  report,  cdl);}
  /*public*/ QString toString() override{AbstractFemaleSocket::toString();}

};
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
  /*public*/ bool add(MaleSocket* maleSocket, QList<QString> errors)override;
  /*public*/ MaleSocket* fetchTopItem()override;
  /*public*/ MaleSocket* getTopItem()override;
  /*public*/ AbstractFemaleSocket *getFemaleSocket()override;
  /*public*/ void moveItemToTop(MaleSocket* maleSocket)override;
  /*public*/ void setup()override;
  /*public*/ bool replaceClipboardItems(ClipboardMany* clipboardItems, QList<QString> errors);
  /*public*/ void setState(int s) /*throws JmriException*/override;
  /*public*/ int getState() override;
  /*public*/ QString getBeanType()override;
  /*public*/ Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;
  /*public*/ Base* getParent() const override;
  /*public*/ void setParent(Base* parent)override;
  /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/ int getChildCount() override;
  /*public*/ Category::TYPE getCategory()override;
  QObject* self() override {return (QObject*)this;}


 private:
  /*private*/ ClipboardMany* _clipboardItems = new ClipboardMany("", nullptr);
  DefaultClipboard* defaultClipboard;
  /*public*/ void connected(FemaleSocket* socket) {
              // Do nothing
          }
  //@Override
  /*public*/ void disconnected(FemaleSocket* socket) {
      // Do nothing
  }
  /*private*/ /*final*/ DefaultFemaleAnySocket* _femaleSocket = new MyDefaultFemaleAnySocket(this, new DCFemaleSocketListener(),"A");

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
        /*public*/ QString getComment() {
            return defaultClipboard->_clipboardItems->getComment();
        }

        //@Override
        /*public*/ void setComment(QString s) /*throws NamedBean.BadUserNameException*/ {
            throw new UnsupportedOperationException("Not supported");
        }
  };
#endif
#endif // DEFAULTCLIPBOARD_H
