#include "logixng_analoginstanceinitializer.h"
#include "defaultanalogactionmanager.h"
#include "defaultanalogexpressionmanager.h"

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
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 * @author Bob Jacobsen Copyright (C) 2001, 2008, 2014
 * @since 2.9.4
 */
//@ServiceProvider(service = InstanceInitializer.class)
// /*public*/  class LogixNG_AnalogInstanceInitializer extends AbstractInstanceInitializer {

    //@Override
    /*public*/  /*<T>*/ QObject* LogixNG_AnalogInstanceInitializer::getDefault(QString  type) const {

        // In order for getDefault() to be called for a particular manager,
        // the manager also needs to be added to the method getInitalizes()
        // below.

        if (type == "AnalogActionManager") {
            return new DefaultAnalogActionManager();
        }

        if (type == "AnalogExpressionManager") {
            return new DefaultAnalogExpressionManager();
        }

        return AbstractInstanceInitializer::getDefault(type);
    }

    //@Override
    /*public*/  QSet</*Class<?>*/QString> LogixNG_AnalogInstanceInitializer::getInitalizes() {
        QSet</*Class<?>*/QString> set = AbstractInstanceInitializer::getInitalizes();
//        set.addAll(Arrays.asList(
//                "AnalogActionManager",
//                "AnalogExpressionManager"
//        ));
        set.insert("AnalogActionManager");
        set.insert("AnalogExpressionManager");

        return set;
    }
