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
    /*public*/ QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> DigitalFactory::getActionClasses() {
        QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> digitalActionClasses = QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>>();
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionAudio"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionBlock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionClock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionDispatcher"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionEntryExit"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionLight"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionLightIntensity"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.ActionListenOnBeans"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.ActionListenOnBeansTable"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionLocalVariable"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionMemory"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionOBlock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionPower"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionReporter"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionScript"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionSensor"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionSignalHead"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionSignalMast"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionSound"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionThrottle"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.ActionTimer"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionTurnout"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionTurnoutLock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.ActionWarrant"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.DigitalCallModule"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.DoAnalogAction"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.DoStringAction"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.EnableLogix"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.ExecuteDelayed"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.For"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.IfThenElse"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.Logix"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.LogData"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.LogLocalVariables"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.DigitalMany"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.Sequence"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.ShutdownComputer"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.TableForEach"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.TriggerRoute"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, ".jmri.jmrit.logixng.WebBrowser"}});
        return digitalActionClasses;
    }
