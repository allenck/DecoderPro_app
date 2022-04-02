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
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionAudio"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionBlock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionClock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionDispatcher"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionEntryExit"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionLight"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionLightIntensity"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "ActionListenOnBeans"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "ActionListenOnBeansTable"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionLocalVariable"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionMemory"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionOBlock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionPower"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionReporter"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionScript"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionSensor"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionSignalHead"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionSignalMast"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionSound"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionThrottle"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "ActionTimer"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionTurnout"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionTurnoutLock"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ActionWarrant"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "DigitalCallModule"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "DoAnalogAction"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "DoStringAction"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "EnableLogix"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "ExecuteDelayed"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "For"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "IfThenElse"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "Logix"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "LogData"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "LogLocalVariables"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "DigitalMany"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "Sequence"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "ShutdownComputer"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "TableForEach"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "TriggerRoute"}});
        digitalActionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "WebBrowser"}});
        return digitalActionClasses;
    }
