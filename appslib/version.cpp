#include "version.h"
#include <QStringList>
Version::Version()
{
}

/**
 * Defines a simple place to get the JMRI version string.
 *<P>
 * These JavaDocs are for Version 3.3.2 of JMRI.
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
 * @author  Bob Jacobsen   Copyright 1997-2013
 * @version $Revision: 17977 $
 */

//public class Version {


/* The user who built this release */
/*static*/ /*final*/ const /*public*/ QString Version::buildUser = "allen";

/* The SVN revision ID for this release (if known) */
/*static*/ /*final*/ const /*public*/ QString Version::revisionId = "9ba259f0ab";

/* The date/time of this build */
/*static*/ /*final*/ const /*public*/ QString Version::buildDate = "201711260609";

/* Has this build been created as a possible "official" release? */
/*static*/ /*final*/ const /*public*/ bool Version::official = false;

/* Has this build been created from a branch in Subversion? */
/*static*/ /*final*/ const /*public*/ bool Version::branched = false;

/*public*/ /*static*/ QString Version::getModifier()
{
 QString modifier;

 if (test != 0)
 {
  modifier.append(".").append(QString::number(test));
 }

 if (branched && !official)
 {
  modifier.append("ish");
 }

 return modifier;
}


/**
 * Provide the current version string.
 * <P>
 * This string is built using various known build parameters, including
 * the release.{major,minor,build} values, the SVN revision ID (if known)
 * and the branched & release.official statuses.
 *
 * @return The current version string
 */
/*static*/ /*public*/ QString Version::name()
{
 QString releaseName;
 if (branched)
 {
  QString version = QString::number(major) + "." + QString::number(minor);
  if (test != 0) {
      version = version + "." + QString::number(test);
  }
  QString addOn;
  if ("unknown"==(revisionId))
  {
   addOn = buildDate + "-" + buildUser;
  }
  else
  {
   addOn = "r" + revisionId;
  }
  releaseName = major + "." + minor + getModifier() + "-" + addOn;
 }
 else if (revisionId==("unknown"))
 {
  releaseName = buildDate + "-" + buildUser;
 }
 else
 {
  releaseName = "r" + revisionId;
 }
 return releaseName;
}

/**
 * Tests that a string contains a canonical version string.
 * <p>
 * A canonical version string is a string in the form x.y.z and is different
 * than the version string displayed using {@link #name() }. The canonical
 * version string for a JMRI instance is available using {@link #getCanonicalVersion() }.
 *
 * @param version
 * @return true if version is a canonical version string
 */
/*static*/ /*public*/ bool Version::isCanonicalVersion(QString version)
{
 QStringList parts = version.split(QRegExp("\\."));
 if (parts.length() != 3)
 {
        return false;
 }
 foreach (QString part, parts)
 {
  if (part.isEmpty() || part.toInt() < 0)
  {
   return false;
  }
 }
 return true;
}

/**
 * Compares a canonical version string to the JMRI canonical version and returns
 * an integer indicating if the string is less than, equal to, or greater than the
 * JMRI canonical version.
 *
 * @param version
 * @return -1, 0, or 1 if version is less than, equal to, or greater than JMRI canonical version
 * @throws IllegalArgumentException if version is not a canonical version string
 * @see java.lang.Comparable#compareTo(java.lang.Object)
 */
/*static*/ /*public*/ int Version::compareCanonicalVersions(QString version) throw (IllegalArgumentException)
{
 return compareCanonicalVersions(version, getCanonicalVersion());
}

/**
 * Compares two canonical version strings and returns an integer indicating if
 * the first string is less than, equal to, or greater than the second string.
 *
 * @param version1 a canonical version string
 * @param version2 a canonical version string
 * @return -1, 0, or 1 if version1 is less than, equal to, or greater than version2
 * @throws IllegalArgumentException if either version string is not a canonical version string
 * @see java.lang.Comparable#compareTo(java.lang.Object)
 */
/*static*/ /*public*/ int Version::compareCanonicalVersions(QString version1, QString version2) throw (IllegalArgumentException)
{
    int result = 0;
    if (!isCanonicalVersion(version1)) {
        throw new IllegalArgumentException("Parameter version1 (" + version1 + ") is not a canonical version string.");
    }
    if (!isCanonicalVersion(version2)) {
        throw new IllegalArgumentException("Parameter version2 (" + version2 + ") is not a canonical version string.");
    }
    QStringList p1 = version1.split(QRegExp("\\."));
    QStringList p2 = version2.split(QRegExp("\\."));
    for (int i = 0; i < 3; i++)
    {
        result = p1[i]==(p2[i]);
        if (result != 0) {
            return result;
        }
    }
    return result;
}

/**
 * Return the version as a major.minor.test String.
 *
 * @return The version
 */
/*static*/ /*public*/ QString Version::getCanonicalVersion() {
    //return QString("%1").arg(major) + "." + QString("%1").arg(minor) + "." + QString("%1").arg(test);
    return QT_VERSION_STR;
}

/**
 * Return the application copyright as a String.
 *
 * @return The copyright
 */
/*static*/ /*public*/ QString Version::getCopyright()
{
    return "Copyright � 1997-2017 JMRI Community";
}

///**
// * Standalone print of version string and exit.
// *
// * This is used in the build.xml to generate parts of the installer release file name, so
// * take care in altering this code to make sure the ant recipes are also suitably modified.
// */
//static /*public*/ void main(String[] args) {
//    System.out.println(name());
//}
//}
