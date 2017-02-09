#include "catalogtree.h"
#include "abstractnamedbean.h"

CatalogTree::CatalogTree(QObject *parent) :
    TreeModel(parent)
{
//    IMAGE    = 'I';    // letter to filter for images/icons
//    SOUND    = 'S';    // letter to filter for sounds
//    SCRIPT   = 'T';    // letter to filter for scripts
//    NOFILTER = 'N';    // letter for unfiltered
//    FILESYS  = 'F';    // typeLetter for tree based on file system
//    XML      = 'X';    // typeLetter for index tree stored in XML file
 bean = new AbstractNamedBean(parent);
}
/**
 * Represents a CatalogTree, a tree displaying a taxonomy - e.g. a file system directory,
 * or an index of references or a table of contents built according to the user's
 * taxonomy.
 * <P>
 * Specific implementations are in the jmri.jmrit.catalog package.
 * <P>
 * The states  and names are Java Bean parameters, so that listeners can be
 * registered to be notified of any changes.
 * <P>
 * Each CatalogTree object has a two names.  The "user" name is entirely free form, and
 * can be used for any purpose.  The "system" name is provided by the purpose-specific
 * implementations.
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
 * @author	Pete Cressman  Copyright (C) 2009
 *
 */
///*public*/ interface CatalogTree extends NamedBean, TreeModel {

QString CatalogTree::getComment()
{
 bean->getComment();
}

void CatalogTree::setComment(QString comment)
{
 bean->setComment(comment);
}

QString CatalogTree::getDisplayName()
{
 bean->getDisplayName();
}

void CatalogTree::addPropertyChangeListener(PropertyChangeListener* l, const QString beanRef, QString listenerRef)
{
 bean->addPropertyChangeListener(l, beanRef, listenerRef);
}

void CatalogTree::addPropertyChangeListener(PropertyChangeListener* l)
{
 bean->addPropertyChangeListener(l);
}

/*public*/ QString CatalogTree::getSystemName() const  {bean->getSystemName();}
/*public*/ QString CatalogTree::getUserName() {return bean->getUserName();}
/*public*/ void CatalogTree::setUserName(QString s) { bean->setUserName(s);}

/*protected*/ void CatalogTree::firePropertyChange(QString p, QVariant old, QVariant n)
{
 bean->firePropertyChange(p, old, n);
}

/*public*/ void CatalogTree::dispose() {
 bean->dispose();
}
