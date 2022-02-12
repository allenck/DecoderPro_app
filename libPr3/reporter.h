#ifndef REPORTER_H
#define REPORTER_H

#include <QObject>
#include "abstractnamedbean.h"
#include "swingpropertychangesupport.h"
//#include "rfid/reportervariant.h"

class ReporterVariant;
class Reporter /*:  public AbstractNamedBean*/
{
    //Q_OBJECT
  //Q_INTERFACES(NamedBean)
public:
    //explicit Reporter(QObject *parent = 0);
//    Reporter(QObject* parent =0) : AbstractNamedBean(parent) {}
//    Reporter(QString systemName, QObject* parent) : AbstractNamedBean(systemName, parent) {}
//    Reporter(QString systemName, QString userName, QObject* parent) : AbstractNamedBean(systemName, userName, parent) {}

    /**
     * Represent a device that can report identification information.
     * <P>
     * Reporting devices might include:
     * <ul>
     *  <li>A DCC device that reports a locomotive number
     *      when it's in a particular location
     *  <LI>A device that reports something about the layout
     *      environment, e.g. the current drawn or light intensity
     *  <LI>A device that reacts to some happening on the layout
     *      with a complicated report
     *</UL>
     * <P>In contrast to Sensors, a Reporter provides more detailed
     * information. A Sensor provides a status of ACTIVE or INACTIVE, while
     * a Reporter returns an Object.  The real type of that object can
     * be whatever a particular Reporter finds useful to report.  Typical
     * values might be a String or Int, both of which can be displayed,
     * printed, equated, etc.
     * <P>
     * A Reporter might also not be able to report all the time.  The
     * previous value remains available, but it's also possible to
     * distinquish this case by using the getCurrentReport member function.
     * <P>
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
     * @author	Bob Jacobsen  Copyright (C) 2001
     * @author      Matthew Harris  Copyright (C) 2011
     * @version	$Revision: 17977 $
     * @see         jmri.Sensor
     * @see         jmri.ReporterManager
     * @see         jmri.InstanceManager
     */
//    virtual interface Reporter extends NamedBean {

        /**
         * Query the last report.  This will return a
         * value even if there's no current report available.
         * If there is a current report, both this and the
         * current report will be equal.  If nothing has ever
         * been reported, this will return a null object.
         */
        virtual ReporterVariant getLastReport()  =0; //{return QVariant();}

        /**
         * Query the current report.  If there is no current report
         * available (e.g. the reporting hardware says no information is
         * currently available) this will return a null object.
         */
        virtual ReporterVariant getCurrentReport() =0;//{return QVariant();}

        /**
         * Set the report to an arbitrary object.
         * <P>
         * A Reporter object will usually just "report"; its contents
         * usually come from the layout, and hence are only set by lower-level
         * implementation classes.  But there are occasionally reasons
         * to set it from inside the program, e.g. debugging via entering
         * values in the Reporter Table.  Hence provision of this method.
         */
        virtual void setReport(QVariant /*r*/)  {}
        /**
         * Provide an int form of the last report.
         *
         */
        virtual int getState()  {return 0;}
 //SwingPropertyChangeSupport* pcs;
  virtual QObject* self() =0;
signals:
    //void propertyChange(PropertyChangeEvent*);
public slots:
    
};
Q_DECLARE_INTERFACE(Reporter, "Reporter")
#endif // REPORTER_H
