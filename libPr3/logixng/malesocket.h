#ifndef MALESOCKET_H
#define MALESOCKET_H

#include <QObject>
#include "class.h"
//#include "base.h"
#include "debugable.h"
#include "symboltable.h"
//#include "basemanager.h"

class BaseManager;
/**
 * A LogixNG male socket.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
class ErrorHandlingType : public QObject
{
  Q_OBJECT
     public:
//        Default(Bundle.getMessage("ErrorHandling_Default")),
//        ShowDialogBox(Bundle.getMessage("ErrorHandling_ShowDialogBox")),
//        LogError(Bundle.getMessage("ErrorHandling_LogError")),
//        LogErrorOnce(Bundle.getMessage("ErrorHandling_LogErrorOnce")),
//        ThrowException(Bundle.getMessage("ErrorHandling_ThrowException")),
//        AbortExecution(Bundle.getMessage("ErrorHandling_AbortExecution"));
     enum TYPES
     {
      Default,
      ShowDialogBox,
      LogError,
      LogErrorOnce,
      ThrowException,
      AbortExecution,
      None
     };
private:
     /*private*/ /*final*/ QString _description;

     /*private*/ ErrorHandlingType(QString description) {
         _description = description;
     }
public:
     //@Override
     /*public*/ static QString toString(TYPES t) {
       switch(t)
       {
        case Default:
         return tr("Use default");
        case ShowDialogBox:
         return tr("Show dialog box");
        case LogError:
        return tr("Log error");
        case LogErrorOnce:
        return tr("Log error once");
        case ThrowException:
         return tr("Throw exception");
        case AbortExecution:
        return tr("Abort execution");
       default:
        return "";
       }
     }
     /*public*/ static TYPES  valueOf(QString s)
     {
      if(s == tr("Use default")) return  Default;
      if(s ==tr("Show dialog box")) return ShowDialogBox;
      if(s ==tr("Log error") ) return LogError;
      if(s == tr("Log error once")) return  LogErrorOnce;
      if(s == tr("Throw exception")) return ThrowException;
      if(s == tr("Abort execution")) return AbortExecution;
      return None;
     }
     /*public*/ static QList<TYPES> values()
     {
      return QList<TYPES> {Default, ShowDialogBox, LogError, LogErrorOnce,ThrowException, AbortExecution} ;
     }
 };
/*public*/ /*interface*/ class MaleSocket : /*public QObject,*/ public Debugable
{
  //Q_OBJECT
  Q_INTERFACES(Debugable)
 public:
//MaleSocket(QObject* parent=nullptr) : QObject(parent){}

    /**
     * Set whenether this male socket is enabled or disabled.
     * <P>
     * This method must call registerListeners() / unregisterListeners().
     *
     * @param enable true if this male socket should be enabled, false otherwise
     */
    /*public*/ virtual void setEnabled(bool enable)=0;

    /**
     * Set whenether this male socket is enabled or disabled, without activating
     * the male socket. This is used when loading the xml file and when copying
     * an item.
     * <P>
     * This method must call registerListeners() / unregisterListeners().
     *
     * @param enable true if this male socket should be enabled, false otherwise
     */
    /*public*/ virtual void setEnabledFlag(bool enable)=0;

    /**
     * Determines whether this male socket is enabled.
     *
     * @return true if the male socket is enabled, false otherwise
     */
    //@Override
    /*public*/ virtual bool isEnabled()=0;

    /**
     * Get whenether the node should listen to changes or not.
     * @return true if listen, false if not listen
     */
  /*public*/ virtual bool getListen() {return false;}

    /**
     * Set whenether the node should listen to changes or not.
     * @param listen true if listen, false if not listen
     */
  /*public*/ virtual void setListen(bool /*listen*/) {}

    /**
     * Is the node locked?
     * @return true if locked, false otherwise
     */
    /*public*/ virtual bool isLocked(){return false;}

    /**
     * Set if the node is locked or not.
     * @param locked true if locked, false otherwise
     */
  /*public*/ virtual void setLocked(bool locked) {}

    /**
     * Is the node a system node?
     * @return true if system, false otherwise
     */
    /*public*/ virtual bool isSystem(){return false;}

    /**
     * Set if the node is system or not.
     * @param system true if system, false otherwise
     */
  /*public*/ virtual void setSystem(bool /*system*/) {}

    /**
     * Is the node catching AbortExecution or not?
     * @return true if catching, false otherwise
     */
    /*public*/ virtual bool getCatchAbortExecution(){return false;}

    /**
     * Set if the node should catch AbortExecution or not.
     * @param catchAbortExecution true if catch, false otherwise
     */
  /*public*/ virtual void setCatchAbortExecution(bool catchAbortExecution){}

    /*public*/ virtual void addLocalVariable(
            QString name,
            InitialValueType::TYPES initialValueType,
    QString initialValueData){}

  /*public*/ virtual void addLocalVariable(VariableData* variableData) {}

  /*public*/ virtual void clearLocalVariables() {}

  /*public*/ virtual QSet<VariableData*> getLocalVariables() {return QSet<VariableData*>();}

    /**
     * Get the error handling type for this socket.
     * @return the error handling type
     */
  /*public*/ virtual ErrorHandlingType::TYPES getErrorHandlingType() {return ErrorHandlingType::None;}

    /**
     * Set the error handling type for this socket.
     * @param errorHandlingType the error handling type
     */
  /*public*/ virtual void setErrorHandlingType(ErrorHandlingType::TYPES errorHandlingType){}

    /**
     * Get the object that this male socket holds.
     * This method is used when the object is going to be configured.
     *
     * @return the object this male socket holds
     */
    //@Nonnull
    /*public*/ virtual Base* getObject(){return nullptr;}

    /**
     * Get the manager that stores this socket.
     * This method is used when the object is going to be configured.
     *
     * @return the manager
     */
    /*public*/ virtual BaseManager/*<NamedBean*>*//*<? extends NamedBean>*/* getManager(){return nullptr;}

    /** {@inheritDoc} */
    //@Override
    /*default*/ /*public*/  void setup() {
        getObject()->setup();
    }

    /**
     * Find a male socket of a particular type.
     * Male sockets can be stacked and this method travels thru the stacked
     * male sockets to find the desired male socket.
     * @param clazz the type of the male socket we are looking for
     * @return the found male socket or null if not found
     */
    /*public*/  /*default*/ MaleSocket* find(QString className) {
    Class* clazz =Class::forName(className);

//        if (! MaleSocket::isAssignableFrom(clazz)) {
//            throw  IllegalArgumentException("clazz is not a MaleSocket");
//        }
        if(!clazz->isAssignableFrom("MaleSocket"))
          throw  IllegalArgumentException("clazz is not a MaleSocket");
        Base* item = this;

//        while ((static_cast<MaleSocket*>(item)) && !clazz->isInstance(item->self())) {
//            item = item->getParent();
//        }
        while(((Class*)item)->isAssignableFrom("MaleSocket"))
        {
          item = item->getParent();
        }

        if (clazz->isInstance(item->bself())) return (MaleSocket*)item->bself();
        else return nullptr;
    }
  /*public*/ virtual QString getClassName() =0;//{return "jmri.jmrit.logixng.MaleSocket";}
  //virtual QObject* bself()=0;
  //QObject* bself() override{return (QObject*)this;}

   friend class Base;
};
Q_DECLARE_INTERFACE(MaleSocket, "MaleSocket")
#endif // MALESOCKET_H
