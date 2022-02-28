#ifndef LOGIXNG_DIGITALINSTANCEINITIALIZER_H
#define LOGIXNG_DIGITALINSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

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

/*public*/  class LogixNG_DigitalInstanceInitializer : public AbstractInstanceInitializer {
  Q_OBJECT
 public:
  LogixNG_DigitalInstanceInitializer(QObject* parent = nullptr) : AbstractInstanceInitializer(parent){}
  /*public*/  /*<T>*/ QObject* getDefault(QString type) const override;
  /*public*/  QSet</*Class<?>*/QString>* getInitalizes()override;
};

#endif // LOGIXNG_DIGITALINSTANCEINITIALIZER_H
