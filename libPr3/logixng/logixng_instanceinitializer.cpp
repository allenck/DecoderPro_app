#include "logixng_instanceinitializer.h"
#include "defaultconditionalngmanager.h"
#include "defaultfemalesocketmanager.h"
#include "defaultlogixnginitializationmanager.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixngpreferences.h"
#include "defaultnamedtablemanager.h"
#include "defaultmodulemanager.h"

/**
 * Provide the usual default implementations for the
 * {@link jmri.InstanceManager}.
 * <P>
 * Not all {@link jmri.InstanceManager} related classes are provided by this
 * class. See the discussion in {@link jmri.InstanceManager} of initialization
 * methods.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public/  License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public  License for more details.
 * <P>
 * @author Bob Jacobsen Copyright (C) 2001, 2008, 2014
 * @since 2.9.4
 */
//@ServiceProvider(service = InstanceInitializer.class)
// /*public*/  class LogixNG_InstanceInitializer extends AbstractInstanceInitializer {

    //@Override
    /*public*/  /*<T>*/ QObject* LogixNG_InstanceInitializer::getDefault(QString type) const {

        // In order for getDefault() to be called for a particular manager,
        // the manager also needs to be added to the method getInitalizes()
        // below.

        if (type == "ConditionalNG_Manager") {
            return new DefaultConditionalNGManager();
        }

        if (type == "FemaleSocketManager") {
            return new DefaultFemaleSocketManager();
        }

        if (type == "LogixNG_InitializationManager") {
            return new DefaultLogixNGInitializationManager();
        }

        if (type == "LogixNG_Manager") {
            return new DefaultLogixNGManager();
        }

        if (type == "LogixNGPreferences") {
            return new DefaultLogixNGPreferences();
        }

        if (type == "ModuleManager") {
            return new DefaultModuleManager();
        }

        if (type == "NamedTableManager") {
            return new DefaultNamedTableManager();
        }

        return AbstractInstanceInitializer::getDefault(type);
    }

    //@Override
    /*public*/  QSet<QString> LogixNG_InstanceInitializer::getInitalizes() {
        QSet<QString> set = AbstractInstanceInitializer::getInitalizes();
        set.fromList(QList<QString>() ={
                "ConditionalNG_Manager",
                "FemaleSocketManager",
                "LogixNG_InitializationManager",
                "LogixNG_Manager",
                "LogixNGPreferences",
                "ModuleManager",
                "NamedTableManager"
        });
        return set;
    }
