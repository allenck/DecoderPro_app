#ifndef CATALOGTREEMANAGER_H
#define CATALOGTREEMANAGER_H
#include "manager.h"
#include "catalogtree.h"

class CatalogTreeManager :  public Manager
{
    Q_OBJECT
public:
    explicit CatalogTreeManager(QObject *parent = 0);
    CatalogTreeManager(const char *, QObject *parent = 0);
    /**
     * Locate a CatalogTree object representing some specific information.
     *<P>
     * CatalogTree objects are obtained from a CatalogTreeManager, which in turn is generally located
     * from the InstanceManager.
     * <P>
     * Much of the book-keeping is implemented in the AbstractCatalogTreeManager class, which
     * can form the basis for a system-specific implementation.
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
     * @author			Pete Cressman Copyright (C) 2009
     *
     */
    //public interface CatalogTreeManager extends Manager {


        /**
         * Locate via user name, then system name if needed.
         * If that fails, return null
         *
         * @param name
         * @return null if no match found
         */
        virtual CatalogTree* getCatalogTree(QString name);

        /**
         * Locate an instance based on a system name.  Returns null if no
         * instance already exists.
         * @return requested CatalogTree object or null if none exists
         */
        virtual CatalogTree* getBySystemName(QString systemName);

        /**
         * Locate an instance based on a user name.  Returns null if no
         * instance already exists.
         * @return requested CatalogTree object or null if none exists
         */
        virtual CatalogTree* getByUserName(QString userName);

        /**
         * Return an instance with the specified system and user names.
         * Note that two calls with the same arguments will get the same instance;
         * there is only one CatalogTree object representing a given physical CatalogTree
         * and therefore only one with a specific system or user name.
         *<P>
         * This will always return a valid object reference; a new object will be
         * created if necessary. In that case:
         *<UL>
         *<LI>If a null reference is given for user name, no user name will be associated
         *    with the CatalogTree object created; a valid system name must be provided
         *<LI>If both names are provided, the system name defines the
         *    hardware access of the desired CatalogTree, and the user address
         *    is associated with it. The system name must be valid.
         *</UL>
         * Note that it is possible to make an inconsistent request if both
         * addresses are provided, but the given values are associated with
         * different objects.  This is a problem, and we don't have a
         * good solution except to issue warnings.
         * This will mostly happen if you're creating CatalogTree objects when you should
         * be looking them up.
         * @return requested CatalogTree object (never null)
         */
        virtual CatalogTree* newCatalogTree(QString systemName, QString userName);

        /**
         * Get a list of all CatalogTree objects' system names.
         */
        virtual QStringList getSystemNameList();

//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY",
//                justification="with existing code structure, just have to accept these exposed arrays. Someday...")
        QStringList IMAGE_FILTER;

//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_OOI_PKGPROTECT",
//                justification="with existing code structure, just have to accept these exposed arrays. Someday...")
        QStringList SOUND_FILTER;

//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_OOI_PKGPROTECT",
//                justification="with existing code structure, just have to accept these exposed arrays. Someday...")
        QStringList SCRIPT_FILTER;

signals:
    
public slots:
    
};

#endif // CATALOGTREEMANAGER_H
