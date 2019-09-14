#ifndef REPORTABLE_H
#define REPORTABLE_H
#include <QString>
#include "abstractnamedbean.h"

/**
 * This interface specifies that an object provides a report value suitable
 * for display in an on-screen reporter.
 * <BR>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * </P><P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * </P>
 *
 * @author Paul Bender Copyright (C) 2019
 * @see jmri.Reporter
 * @since 4.15.3
 */
/*public*/ /*interface*/class Reportable : public AbstractNamedBean{
Q_OBJECT
public:
 Reportable(QObject* parent=nullptr) : AbstractNamedBean(parent) {}
 Reportable(QString sysName, QObject* parent=nullptr) : AbstractNamedBean(sysName, parent) {}
 Reportable(QString sysName, QString userName, QObject* parent=nullptr) : AbstractNamedBean(sysName, userName, parent) {}
 ~Reportable() {}
 Reportable(const Reportable&) : AbstractNamedBean() {}
     /**
      * Provide a string representation of the object, possibly including state
      * information, suitable for display in an on-screen reporter. A default
      * impelmentation provided here calls toString(), which may not be
      * appropriate in all cases.
      *
      * @return a report string representing the Object.
      */
 /*public*/ /*default*/ virtual QString toReportString() {return "";}

};
Q_DECLARE_METATYPE(Reportable)
#endif // REPORTABLE_H
