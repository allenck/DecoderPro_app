#include "metadata.h"
#include <QString>
#include "system.h"
#include "version.h"

Metadata::Metadata()
{

}
/**
 * Meta data concerning the JMRI application.
 * <P>
 * Meta data is static information concerning the JMRI application. This class
 * provides a single container for listing and storing JMRI meta data. This
 * class is used by the DefaultXmlIOServer object.
 *
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
 * @author	Randall Wood Copyright (C) 2011
 */
///*public*/ class Metadata {

/*public*/ /*static*/ /*final*/ QString Metadata::JMRIVERSION = "JMRIVERSION"; // NOI18N
/*public*/ /*static*/ /*final*/ QString Metadata::JMRIVERCANON = "JMRIVERCANON"; // NOI18N
/*public*/ /*static*/ /*final*/ QString Metadata::JMRIVERMAJOR = "JMRIVERMAJOR"; // NOI18N
/*public*/ /*static*/ /*final*/ QString Metadata::JMRIVERMINOR = "JMRIVERMINOR"; // NOI18N
/*public*/ /*static*/ /*final*/ QString Metadata::JMRIVERTEST = "JMRIVERTEST"; // NOI18N
/*public*/ /*static*/ /*final*/ QString Metadata::JVMVERSION = "JVMVERSION"; // NOI18N
/*public*/ /*static*/ /*final*/ QString Metadata::JVMVENDOR = "JVMVENDOR"; // NOI18N

/**
 * Return the value of the named meta data, or any valid system property.
 *
 * @param name name of meta data or property to return
 * @return String value of requested data or null
 */
/*public*/ /*static*/ QString Metadata::getBySystemName(QString name) {
    if (QString::compare(name,JMRIVERSION,Qt::CaseInsensitive)==0) {
        return Version::name();
    } else if ( QString::compare(name,JMRIVERCANON,Qt::CaseInsensitive)==0) {
        return Version::getCanonicalVersion();
    } else if ( QString::compare(name,JMRIVERMAJOR,Qt::CaseInsensitive)==0) {
        return QString::number(Version::major);
    } else if ( QString::compare(name,JMRIVERMINOR,Qt::CaseInsensitive)==0) {
        return QString::number(Version::minor);
    } else if ( QString::compare(name,JMRIVERTEST,Qt::CaseInsensitive)==0) {
        return QString::number(Version::test);
    } else if ( QString::compare(name,JVMVERSION,Qt::CaseInsensitive)==0) {
        return System::getProperty("java.version", "<unknown>"); // NOI18N
    } else if ( QString::compare(name,JVMVENDOR,Qt::CaseInsensitive)==0) {
        return System::getProperty("java.vendor", "<unknown>"); // NOI18N
    }
    // returns null if name is not a system property
    return System::getProperty(name);
}

/**
 * An array of known meta data names.
 *
 * @return String[]
 */
/*public*/ /*static*/ QStringList Metadata::getSystemNameArray() {
    QStringList names = QStringList() << JMRIVERSION <<
        JMRIVERCANON <<
        JMRIVERMAJOR <<
        JMRIVERMINOR <<
        JMRIVERTEST <<
        JVMVERSION<<
        JVMVENDOR;
    return names;
}

/**
 * Get the list of known meta-data names.
 * @return the list of names
 */
/*public*/ /*static*/ QList<QString> Metadata::getSystemNameList() {
    return (Metadata::getSystemNameArray());
}

