#include "rosterframestartupactionfactory.h"

RosterFrameStartupActionFactory::RosterFrameStartupActionFactory(QObject* parent)
{

}
/**
 * {@link apps.startup.StartupActionFactory} for the
 * {@link jmri.jmrit.roster.swing.RosterFrameAction}.
 *
 * @author Randall Wood Copyright (C) 2016
 */
//@ServiceProvider(service = StartupActionFactory.class)
///*public*/ class RosterFrameStartupActionFactory extends AbstractStartupActionFactory {

    //@Override
    /*public*/ QString RosterFrameStartupActionFactory::getTitle(/*Class<?>*/QString clazz, QLocale locale) throw (IllegalArgumentException) {
        if (clazz !=("RosterFrameAction")) {
            throw  IllegalArgumentException();
        }
        return tr("RosterFrameAction"); // NOI18N
    }

    //@Override
    /*public*/ /*Class<?>*/QStringList RosterFrameStartupActionFactory::getActionClasses() {
        return QStringList() << "RosterFrameAction";
    }

//}
