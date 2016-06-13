#include "application.h"
#include "exceptions.h"

Application::Application(QObject *parent) :
  QObject(parent)
{
}
/**
 * A lightweight class that provides a methods to retrieve the current JMRI
 * application name and icon.
 * <P>
 * The current name is set when a given JMRI application is launched.
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
 *
 * @author Matthew Harris Copyright (C) 2011
 * @version $Revision: 29216 $
 */
// /*public*/ class Application {

/*private*/ /*static*/ QString Application::name = NULL;
/*private*/ /*static*/ QString Application::logo = "resources/logo.gif";
/*private*/ /*static*/ QString Application::URL = "http://jmri.org";

/**
 * Return the current JMRI application name.
 *
 * @return String containing JMRI application name or "JMRI" if name has not
 *         been set.
 */
/*public*/ /*static*/ QString Application::getApplicationName() {
    if (Application::name == NULL) {
        return "JMRI";
    }
    return Application::name;
}

/**
 * Set the current JMRI application name.
 *
 * @param applicationName String containing the JMRI application name
 * @throws IllegalAccessException
 * @throws IllegalArgumentException
 */
/*public*/ /*static*/ void Application::setApplicationName(QString applicationName) /*throws IllegalAccessException, IllegalArgumentException */{
    if (Application::name == NULL) {
        if (applicationName != NULL) {
            Application::name = applicationName;
        } else {
            throw new IllegalArgumentException("Application name cannot be NULL.");
        }
    } else {
        throw new IllegalAccessException("Application name cannot be modified once set.");
    }
}

/**
 * Return the current JMRI application logo path. This path is relative to
 * the JMRI application installation path. If the application does not have
 * its own icon, return the JMRI default icon.
 *
 * @return String containing the application icon path
 */
/*public*/ /*static*/ QString Application::getLogo() {
    return logo;
}

/**
 * Set the current JMRI application logo path.
 *
 * @param logo String with the relative path to the JMRI application icon
 */
/*public*/ /*static*/ void Application::setLogo(QString logo) 
{
 if (logo == NULL) 
 {
  logo = "resources/logo.gif";
 }
 Application::logo = logo;
}

/**
 * @return the URL
 */
/*public*/ /*static*/ QString Application::getURL() {
    return Application::URL;
}

/**
 * @param URL the URL to set
 */
/*public*/ /*static*/ void Application::setURL(QString URL) {
    if (URL == NULL) {
        URL = "http://jmri.org";
    }
    Application::URL = URL;
}
