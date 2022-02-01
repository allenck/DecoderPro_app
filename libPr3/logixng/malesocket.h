#ifndef MALESOCKET_H
#define MALESOCKET_H

#include <QObject>
#include "class.h"
//#include "base.h"
#include "debugable.h"
#include "symboltable.h"
#include "basemanager.h"


/**
 * A LogixNG male socket.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/ class MaleSocket : public Debugable
{
  Q_INTERFACES(Debugable)
 public:
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
         AbortExecution
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
            return "Show dialog box";
           case LogError:
           return "Log error";
           case LogErrorOnce:
           return "Log error once";
           case ThrowException:
            return "Throw exception";
           case AbortExecution:
           return "Abort execution";
          default:
           return "";
          }
        }
    };

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
    /*public*/ virtual bool getListen()=0;

    /**
     * Set whenether the node should listen to changes or not.
     * @param listen true if listen, false if not listen
     */
    /*public*/ virtual void setListen(bool listen);

    /**
     * Is the node locked?
     * @return true if locked, false otherwise
     */
    /*public*/ virtual bool isLocked();

    /**
     * Set if the node is locked or not.
     * @param locked true if locked, false otherwise
     */
    /*public*/ virtual void setLocked(bool locked);

    /**
     * Is the node a system node?
     * @return true if system, false otherwise
     */
    /*public*/ virtual bool isSystem();

    /**
     * Set if the node is system or not.
     * @param system true if system, false otherwise
     */
    /*public*/ virtual void setSystem(bool system);

    /**
     * Is the node catching AbortExecution or not?
     * @return true if catching, false otherwise
     */
    /*public*/ virtual bool getCatchAbortExecution()=0;

    /**
     * Set if the node should catch AbortExecution or not.
     * @param catchAbortExecution true if catch, false otherwise
     */
    /*public*/ virtual void setCatchAbortExecution(bool catchAbortExecution);

    /*public*/ virtual void addLocalVariable(
            QString name,
            SymbolTable::InitialValueType::TYPES initialValueType,
            QString initialValueData)=0;

    /*public*/ virtual void addLocalVariable(VariableData* variableData);

    /*public*/ virtual void clearLocalVariables()=0;

    /*public*/ virtual QSet<VariableData*> getLocalVariables()=0;

    /**
     * Get the error handling type for this socket.
     * @return the error handling type
     */
    /*public*/ virtual ErrorHandlingType::TYPES getErrorHandlingType()=0;

    /**
     * Set the error handling type for this socket.
     * @param errorHandlingType the error handling type
     */
    /*public*/ virtual void setErrorHandlingType(ErrorHandlingType::TYPES errorHandlingType)=0;

    /**
     * Get the object that this male socket holds.
     * This method is used when the object is going to be configured.
     *
     * @return the object this male socket holds
     */
    //@Nonnull
    /*public*/ virtual Base* getObject()=0;

    /**
     * Get the manager that stores this socket.
     * This method is used when the object is going to be configured.
     *
     * @return the manager
     */
    /*public*/ virtual BaseManager/*<NamedBean*>*/*/*<? extends NamedBean>*/* getManager()=0;

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

        Base* item = this;

        while ((static_cast< MaleSocket*>(item)) && !clazz->isInstance(item->self())) {
            item = item->getParent();
        }

        if (clazz->isInstance(item->self())) return (MaleSocket*)item;
        else return nullptr;
    }
  virtual QObject* self()=0;
   friend class Base;
};
#endif // MALESOCKET_H
