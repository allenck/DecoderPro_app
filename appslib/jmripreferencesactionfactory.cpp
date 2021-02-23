#include "jmripreferencesactionfactory.h"
#include "jmriabstractaction.h"

JmriPreferencesActionFactory::JmriPreferencesActionFactory(QObject *parent) : QObject(parent)
{
 setProperty("InstanceManagerAutoDefault", "yes");
}
/**
 * This class provides a method to create an action that launches
 * preferences.  The default implementation provides a no-op action.
 * Applications that have a preferences interface should  install a
 * version of this factory in the InstanceManager that provides the
 * desired preferences action.
 *
 * @author Paul Bender Copyright (C) 2020
 */
// /*public*/ class JmriPreferencesActionFactory implements InstanceManagerAutoDefault {

    /*public*/ JmriAbstractAction* JmriPreferencesActionFactory::getDefaultAction() {
        return new JPAFJmriAbstractAction("No-op", this);
//        {
//            @Override
//            /*public*/ JmriPanel* makePanel() {
//                return null;
//            }
//        };
    }

    /*public*/ JmriAbstractAction* JmriPreferencesActionFactory::getNamedAction(QString name){
        return new JPAFJmriAbstractAction(name, this);
//        {
//            @Override
//            /*public*/ JmriPanel makePanel() {
//                return null;
//            }
//        };
    }

    /*public*/ JmriAbstractAction* JmriPreferencesActionFactory::getCategorizedAction(QString name, QString category){
        return new JPAFJmriAbstractAction(name, this);
//        {
//            @Override
//            /*public*/ JmriPanel* makePanel() {
//                return null;
//            }
//        };
    }

    /*public*/ JmriAbstractAction* JmriPreferencesActionFactory::getCategorizedAction(QString name, QString category,QString subCategory){
        return new JPAFJmriAbstractAction(name, this);
//        {
//            @Override
//            /*public*/ JmriPanel makePanel() {
//                return null;
//            }
//        };
    }
