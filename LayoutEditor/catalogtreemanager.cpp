#include "catalogtreemanager.h"
#include "catalogtree.h"

//CatalogTreeManager::CatalogTreeManager(QObject *parent) :
//    QObject(parent)
//{
// setObjectName("CatalogTreeManager");
// setProperty("JavaClassName", "jmri.CatalogTreeManager");

// //registerSelf();
//}

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
//  /*public*/ interface CatalogTreeManager extends Manager {



//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY",
//            justification="with existing code structure, just have to accept these exposed arrays. Someday...")
/*static*/ /*final*/ QStringList CatalogTreeManager::IMAGE_FILTER = QStringList() <<"gif"<< "jpg"<< "jpeg"<< "png";

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_OOI_PKGPROTECT",
//            justification="with existing code structure, just have to accept these exposed arrays. Someday...")
/*static*/ /*final*/ QStringList CatalogTreeManager::SOUND_FILTER = QStringList() <<"wav";

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_OOI_PKGPROTECT",
//            justification="with existing code structure, just have to accept these exposed arrays. Someday...")
    /*static*/ /*final*/ QStringList CatalogTreeManager::SCRIPT_FILTER = QStringList() <<"py"<< "scpt";

/*public*/ SystemConnectionMemo* CatalogTreeManager::getMemo()
{
 throw new IllegalArgumentException();
}
