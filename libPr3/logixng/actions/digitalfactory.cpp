#include "digitalfactory.h"
#include <QSet>

DigitalFactory::DigitalFactory(QObject *parent) : QObject(parent)
{

}
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = DigitalActionFactory.class)
// public class DigitalFactory implements DigitalActionFactory {

    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> DigitalFactory::getActionClasses() {
        QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> digitalActionClasses = QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>>();
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionAudio"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionBlock"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionClock"}});
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionDispatcher"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionEntryExit"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionLight"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionLightIntensity"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.ActionListenOnBeans"}});
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.ActionListenOnBeansTable"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionLocalVariable"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionMemory"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionOBlock"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionPower"}});
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionReporter"}});
#ifdef SCRIPTING_ENABLED
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionScript"}});
#endif
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionSensor"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionSignalHead"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionSignalMast"}});
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionSound"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionThrottle"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.ActionTimer"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionTurnout"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionTurnoutLock"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.ActionWarrant"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.DigitalCallModule"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.DoAnalogAction"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.DoStringAction"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.EnableLogix"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.ExecuteDelayed"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.For"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.IfThenElse"}});
//        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.Logix"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.LogData"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.LogLocalVariables"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.DigitalMany"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.Sequence"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.ShutdownComputer"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.TableForEach"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.TriggerRoute"}});
        digitalActionClasses.insert(QHash<Category, QString> {{Category::OTHER, "jmri.jmrit.logixng.actions.WebBrowser"}});
        return digitalActionClasses;
    }
