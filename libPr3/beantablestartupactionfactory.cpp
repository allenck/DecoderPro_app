#include "beantablestartupactionfactory.h"

BeanTableStartupActionFactory::BeanTableStartupActionFactory(QObject *parent)
    : AbstractStartupActionFactory{parent}
{

}
/**
 * Factory for BeanTable startup actions.
 *
 * @author Randall Wood Copyright 2020
 */
//@ServiceProvider(service = StartupActionFactory)
// /*public*/ final class BeanTableStartupActionFactory extends AbstractStartupActionFactory {

    //@Override
    /*public*/ QString BeanTableStartupActionFactory::getTitle(QString clazz, QLocale locale) /*throws IllegalArgumentException*/ {
        if (clazz ==("AudioTableAction")) {
            return tr(/*locale,*/ "StartupAudioTableAction"); // NOI18N
        } else if (clazz ==("BlockTableAction")) {
            return tr(/*locale,*/ "StartupBlockTableAction"); // NOI18N
        } else if (clazz ==("IdTagTableAction")) {
            return tr(/*locale,*/ "StartupIdTagTableAction"); // NOI18N
        } else if (clazz ==("LightTableAction")) {
            return tr(/*locale,*/ "StartupLightTableAction"); // NOI18N
        } else if (clazz ==("ListedTableAction")) {
            return tr(/*locale,*/ "StartupListedTableAction"); // NOI18N
        } else if (clazz ==("LogixTableAction")) {
            return tr(/*locale,*/ "StartupLogixTableAction"); // NOI18N
        } else if (clazz ==("LogixNGTableAction")) {
            return tr(/*locale,*/ "StartupLogixNGTableAction"); // NOI18N
        } else if (clazz ==("LogixNGModuleTableAction")) {
            return tr(/*locale,*/ "StartupLogixNGModuleTableAction"); // NOI18N
        } else if (clazz ==("LogixNGTableTableAction")) {
            return tr(/*locale,*/ "StartupLogixNGTableTableAction"); // NOI18N
        } else if (clazz ==("LRouteTableAction")) {
            return tr(/*locale,*/ "StartupLRouteTableAction"); // NOI18N
        } else if (clazz ==("MemoryTableAction")) {
            return tr(/*locale,*/ "StartupMemoryTableAction"); // NOI18N
        } else if (clazz ==("OBlockTableAction")) {
            return tr(/*locale,*/ "StartupOBlockTableAction"); // NOI18N
        } else if (clazz ==("ReporterTableAction")) {
            return tr(/*locale,*/ "StartupReporterTableAction"); // NOI18N
        } else if (clazz ==("RouteTableAction")) {
            return tr(/*locale,*/ "StartupRouteTableAction"); // NOI18N
        } else if (clazz ==("SectionTableAction")) {
            return tr(/*locale,*/ "StartupSectionTableAction"); // NOI18N
        } else if (clazz ==("SensorTableAction")) {
            return tr(/*locale,*/ "StartupSensorTableAction"); // NOI18N
        } else if (clazz ==("SignalGroupTableAction")) {
            return tr(/*locale,*/ "StartupSignalGroupTableAction"); // NOI18N
        } else if (clazz ==("SignalHeadTableAction")) {
            return tr(/*locale,*/ "StartupSignalHeadTableAction"); // NOI18N
        } else if (clazz ==("SignalMastTableAction")) {
            return tr(/*locale,*/ "StartupSignalMastTableAction"); // NOI18N
        } else if (clazz ==("TransitTableAction")) {
            return tr(/*locale,*/ "StartupTransitTableAction"); // NOI18N
        } else if (clazz ==("TurnoutTableAction")) {
            return tr(/*locale,*/ "StartupTurnoutTableAction"); // NOI18N
        }
        throw new IllegalArgumentException(clazz/*.getName()*/ + " is not supported by " + this->metaObject()->className());
    }

    //@Override
    /*public*/ QList<QString> getActionClasses() {
        return QList<QString>{"AudioTableAction",
            "BlockTableAction",
            "IdTagTableAction",
            "LightTableAction",
            "ListedTableAction",
            "LogixTableAction",
            "LogixNGTableAction",
            "LogixNGModuleTableAction",
            "LogixNGTableTableAction",
            "LRouteTableAction",
            "MemoryTableAction",
            "OBlockTableAction",
            "ReporterTableAction",
            "RouteTableAction",
            "SectionTableAction",
            "SensorTableAction",
            "SignalGroupTableAction",
            "SignalHeadTableAction",
            "SignalMastTableAction",
            "TransitTableAction",
            "TurnoutTableAction"};
    }
