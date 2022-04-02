#ifndef ABSTRACTBASE_H
#define ABSTRACTBASE_H

#include <abstractnamedbean.h>
#include "base.h"
#include "namedbean.h"

class Logger;
class AbstractBase : public AbstractNamedBean, public virtual Base
{
  Q_OBJECT
  Q_INTERFACES(Base)
 public:
  /*public*/ AbstractBase(QObject* parent = nullptr) : AbstractNamedBean(parent) {}
  /*public*/ AbstractBase(QString sys, QObject* parent = nullptr) /*throw (BadSystemNameException)*/ ;
  /*public*/ AbstractBase(QString sys, QString user, QObject* parent = nullptr) /*throw (BadUserNameException, BadSystemNameException)*/;
  /*public*/ Base* deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/override;
  /*public*/ ConditionalNG* getConditionalNG()override;
  /*public*/ /*final*/ LogixNG* getLogixNG()override;
  /*public*/ /*final*/ Base* getRoot()override;
  /*public*/ /*final*/ bool setParentForAllChildren(QList<QString> errors)override;
  /*public*/ /*final*/ void registerListeners() override;
  /*public*/ /*final*/ void unregisterListeners()override;
  /*public*/ /*final*/ bool isActive() override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          QString currentIndent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  /*public*/ int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n)override;
  /*public*/ /*final*/ void dispose()override;
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list)override;

  QObject* self() override {return (QObject*)this;}

  //QString getSystemName() const override {return mSystemName;}
  //QString getUserName() const override {return AbstractNamedBean::getUserName();}
  QString getComment() override {return AbstractNamedBean::getComment();}
  //void setUserName(QString name) override {AbstractNamedBean::setUserName(name);}
  void setComment(QString name) override {AbstractNamedBean::setComment(name);}

  QString toString() override {return metaObject()->className();}
 private:
  static Logger* log;

 protected:
  /*protected*/ bool _listenersAreRegistered = false;
  /**
   * Register listeners if this object needs that.
   * <P>
   * Important: This method may be called more than once. Methods overriding
   * this method must ensure that listeners are not registered more than once.
   */
  /*abstract*/ virtual/*protected*/ void registerListenersForThisClass(){}

  /**
   * Unregister listeners if this object needs that.
   * <P>
   * Important: This method may be called more than once. Methods overriding
   * this method must ensure that listeners are not unregistered more than once.
   */
  /*abstract*/ virtual /*protected*/ void unregisterListenersForThisClass(){}
  /*protected*/ void printTreeRow(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString currentIndent,
          /*MutableInt*/int* lineNumber);
  /**
   * Dispose this class.
   * Listeners do not need to be unregistered by this method since they are
   * unregistered by dispose().
   */
  /*abstract*/virtual  /*protected*/ void disposeMe(){}
  /*protected*/ void assertListenersAreNotRegistered(Logger* log, QString method);

};

#endif // ABSTRACTBASE_H
