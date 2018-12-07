#include "rostericonfactory.h"
#include "roster.h"
#include "rosterentry.h"

RosterIconFactory::RosterIconFactory(QObject *parent) :
    QObject(parent)
{
 iconHeight = 19; // OS X, because of Apple look'n feel constraints, ComboBox cannot be higher than this 19pixels
}
RosterIconFactory::RosterIconFactory(int h, QObject *parent) : QObject(parent)
{
 iconHeight = h;
 setProperty("InstanceManagerAutoDefault", "yes");

}
/*static*/ RosterIconFactory* RosterIconFactory::_instance = NULL;

/*
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
* @author	Lionel Jeanson   Copyright (C) 2009
* @version	$$
*/

//public class RosterIconFactory {
//	HashMap<String,ImageIcon> icons = new HashMap<String,ImageIcon>();


//	public RosterIconFactory() {
//		iconHeight = 19; // OS X, because of Apple look'n feel constraints, ComboBox cannot be higher than this 19pixels
//	}

ImageIcon* RosterIconFactory::getIcon(QString id) {
    if (id == "") return NULL;
    RosterEntry* re = Roster::getDefault()->entryFromTitle(id);
    if (re==NULL) return NULL;
    return getIcon(re);
}

/*public*/ ImageIcon* RosterIconFactory::getIcon(RosterEntry* re) {
    if ((re==NULL) || (re->getIconPath()==NULL)) return NULL;

    ImageIcon* icon = icons.value(re->getIconPath());
    if (icon == NULL) {
        icon = new ImageIcon( re->getIconPath(), re->getId());
        /* icon can not be NULL
        if (icon==NULL)
            return NULL;
        */
        //icon->setImage( icon->getImage().getScaledInstance( -1, iconHeight, java.awt.Image.SCALE_FAST ));
        icon->setImage(icon->getImage().scaled(-1,iconHeight,Qt::KeepAspectRatio));
        icons.insert(re->getIconPath(), icon);
    }
    return icon;
}

/*static*/ RosterIconFactory* RosterIconFactory::instance()
{
 if (_instance == NULL)
 {
  _instance = new RosterIconFactory();
 }
 return _instance;
}

