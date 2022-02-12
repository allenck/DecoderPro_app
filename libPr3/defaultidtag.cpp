#include "defaultidtag.h"
#include "instancemanager.h"
#include "defaultidtagmanager.h"
#include "rosterentry.h"
#include "clockcontrol.h"

/**
 * Concrete implementation of the {@link jmri.IdTag} interface
 * for the Internal system.
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
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 22227 $
 * @since       2.11.4
 */
///*public*/ class DefaultIdTag extends AbstractIdTag {


/*public*/ DefaultIdTag::DefaultIdTag(QString systemName, QObject *parent)
    : AbstractIdTag(systemName.toUpper(), parent)
{
        //super(systemName.toUpperCase());
    init();
        setWhereLastSeen(nullptr);
    }

/*public*/ DefaultIdTag::DefaultIdTag(QString systemName, QString userName, QObject *parent)
    : AbstractIdTag(systemName.toUpper(), userName, parent)
{
        //super(systemName.toUpperCase(), userName);
 init();
    setWhereLastSeen(nullptr);
}

void DefaultIdTag::init()
{
 _currentState = UNKNOWN;
 _rosterId = 0;
}

//@Override
/*public*/ /*final*/ void DefaultIdTag::setWhereLastSeen(Reporter* r)
{
 Reporter* oldWhere = this->_whereLastSeen;
 QDateTime oldWhen = this->_whenLastSeen;
 this->_whereLastSeen = r;
 if (r!=nullptr)
 {
  this->_whenLastSeen = ((DefaultIdTagManager*)InstanceManager::getDefault("DefaultIdTagManager"))->isFastClockUsed()?
  ((ClockControl*)InstanceManager::getDefault("ClockControl"))->getTime():
  QDateTime::currentDateTime();
 }
 else
 {
  this->_whenLastSeen = QDateTime();
 }
 setCurrentState(r!=nullptr?IdTag::SEEN:IdTag::UNSEEN);
 firePropertyChange("whereLastSeen", VPtr<Reporter>::asQVariant(oldWhere), VPtr<Reporter>::asQVariant(this->_whereLastSeen)); //NOI18N
 emit propertyChange(new PropertyChangeEvent(this, "whereLastSeen", VPtr<Reporter>::asQVariant(oldWhere), VPtr<Reporter>::asQVariant(this->_whereLastSeen))); //NOI18N

 firePropertyChange("whenLastSeen", QVariant(oldWhen), QVariant(this->_whenLastSeen));    //NOI18N
 emit propertyChange(new PropertyChangeEvent(this, "whenLastSeen", QVariant(oldWhen), QVariant(this->_whenLastSeen)));    //NOI18N

}

/*private*/ void DefaultIdTag::setCurrentState(int state) {
    try {
        setState(state);
    } catch (JmriException* ex) {
        log.warn("Problem setting state of IdTag " + getSystemName());
    }
}

//@Override
/*public*/ void DefaultIdTag::setState(int s) /*throw (JmriException)*/ {
    this->_currentState = s;
}

//@Override
/*public*/ int DefaultIdTag::getState() {
    return this->_currentState;
}

//@Override
/*public*/ QDomElement DefaultIdTag::store(QDomDocument doc, bool storeState)
{
 QDomElement e = doc.createElement("idtag"); //NOI18N
 // e.setAttribute("systemName", this.mSystemName); // not needed from 2.11.1
 QDomElement e1;
 e.appendChild(e1 = doc.createElement("systemName"));
 e1.appendChild(doc.createTextNode(this->mSystemName)); //NOI18N
 if (this->mUserName!=nullptr && this->mUserName.length()>0)
 {
  // e.setAttribute("userName", this.mUserName); // not needed from 2.11.1
  e.appendChild(e1 = doc.createElement("userName"));
  e1.appendChild(doc.createTextNode(this->mUserName)); //NOI18N
 }
 if (this->getComment()!=nullptr && this->getComment().length()>0)
 {
  e.appendChild(e1 = doc.createElement("comment"));
  e1.appendChild(doc.createTextNode(this->getComment())); //NOI18N
 }
 if (this->getWhereLastSeen()!=nullptr && storeState)
 {
  e.appendChild(e1 = doc.createElement("whereLastSeen"));
  e1.appendChild(doc.createTextNode(((AbstractNamedBean*)this->getWhereLastSeen())->getSystemName())); //NOI18N
 }
 if (!this->getWhenLastSeen().isNull() && storeState)
 {
  e.appendChild(e1=doc.createElement("whenLastSeen"));
  e1.appendChild(doc.createTextNode(this->getWhenLastSeen().toString())); //NOI18N
 }
 if(this->rosterId() != 0)
 {
  e.appendChild(e1 = doc.createElement("rosterId"));
  e1.appendChild(doc.createTextNode(QString("%1").arg(_rosterId)));
 }
 return e;
}

//@Override
/*public*/ void DefaultIdTag::load(QDomElement e)
{
 if (e.tagName()==("idtag"))
 { //NOI18N
  if (log.isDebugEnabled())
    log.debug("Load IdTag element for " + this->getSystemName());
  if (!e.firstChildElement("userName").isNull()) //NOI18N
   this->setUserName(e.firstChildElement("userName").text()); //NOI18N
  if (!e.firstChildElement("comment").isNull()) //NOI18N
   this->setComment(e.firstChildElement("comment").text()); //NOI18N
  if (!e.firstChildElement("whereLastSeen").isNull())
  { //NOI18N
   this->setWhereLastSeen(((ProxyReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter(                        e.firstChildElement("whereLastSeen").text())); //NOI18N
   this->_whenLastSeen = QDateTime();
  }
  if (!e.firstChildElement("whenLastSeen").isNull())
  { //NOI18N
   log.debug("When Last Seen: " + e.firstChildElement("whenLastSeen").text());
   try
   {
    this->_whenLastSeen = QDateTime::fromString(e.firstChildElement("whenLastSeen").text()); //NOI18N
   }
   catch (ParseException* ex)
   {
    log.warn("Error parsing when last seen: " + ex->getMessage());
   }
  }
  if (!e.firstChildElement("rosterid").isNull()) //NOI18N
   this->setRosterId(e.firstChildElement("rosterid").text().toInt()); //NOI18N

 }
 else
 {
  log.error("Not an IdTag element: " + e.tagName());
 }
}

//private static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultIdTag.class.getName());

//}
void DefaultIdTag::setRosterId(int id)
{
  IdTagManagerXml::instance()->setDirty(true);
 _rosterId = id;
}
int DefaultIdTag::rosterId() { return _rosterId;}
