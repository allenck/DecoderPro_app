#ifndef SIGNALGROUPMANAGER_H
#define SIGNALGROUPMANAGER_H

#include "abstractmanager.h"
#include "signalgroup.h"

/**
 * Interface for obtaining information about signal systems.
 * <p>
 * Each NamedBean here represents a single signal system.
 * The actual objects are SignalAspectTable objects; that's
 * a current anachronism, soon to be fixed.
 * <P>
 * See the common implementation for information on how loaded, etc.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author   Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 17977 $
 */
/*public*/ /*interface*/class LIBPR3SHARED_EXPORT SignalGroupManager : public AbstractManager
{
 Q_OBJECT
public:
    SignalGroupManager(QObject* parent = 0) : AbstractManager(parent) {}
    SignalGroupManager(SystemConnectionMemo*, QObject* parent = 0) : AbstractManager(memo, parent) {}
    ~SignalGroupManager() {}
    SignalGroupManager(const SignalGroupManager&) : AbstractManager() {}
    /*public*/ virtual SignalGroup* getSignalGroup(QString /*name*/) {return nullptr;}

    /*public*/ SignalGroup* getBySystemName(QString name)const {return (SignalGroup* ) AbstractManager::getBeanBySystemName(name);}


    /*public*/ SignalGroup* getByUserName(QString name)const {return (SignalGroup* )AbstractManager::getBeanByUserName(name);}

    /*public*/ virtual SignalGroup* newSignalGroup(QString /*sys*/) {return nullptr;}

    /*public*/ virtual SignalGroup* provideSignalGroup(QString /*systemName*/, QString /*userName*/) {return NULL;}

    /*public*/ QStringList getSystemNameList() override{ return AbstractManager::getSystemNameList();}

    virtual void deleteSignalGroup(SignalGroup* /*s*/) {}
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalGroup";
    }
    int getXMLOrder()const override
    {
     return Manager::SIGNALGROUPS;
    }

};
Q_DECLARE_METATYPE(SignalGroupManager)
#endif // SIGNALGROUPMANAGER_H
