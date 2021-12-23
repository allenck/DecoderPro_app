#include "abstractpowerserver.h"
#include "loggerfactory.h"
#include "powermanager.h"
#include "instancemanager.h"
#include "propertychangeevent.h"

/**
 * Abstract interface between the JMRI power manager and a network connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
//abstract /*public*/ class AbstractPowerServer implements PropertyChangeListener {

/*public*/ AbstractPowerServer::AbstractPowerServer(QObject *parent) : QObject(parent) {

    // Check to see if the Power Manger has a current status
/*        if(mgrOK()) {
     try {
     sendStatus(p.getPower());
     } catch (JmriException* ex) {
     try {
     sendErrorStatus();
     } catch (IOException ie) {
     } catch (java.lang.NullPointerException je) {
     }
     } catch(IOException ie2) {
     } catch (java.lang.NullPointerException je2) {
     }
     }*/
}

/*protected*/ bool AbstractPowerServer::mgrOK()
{
 if (p == nullptr)
 {
  p = static_cast<PowerManager*>(InstanceManager::getNullableDefault("PowerManager"));
  if (p == nullptr)
  {
      log->error("No power manager instance found");
      try {
          sendErrorStatus();
      }
      catch (IOException ie) {
      }
      return false;
  }
  else {
      //p.addPropertyChangeListener(this);
   connect(p->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }
 return true;
}

/*public*/ void AbstractPowerServer::setOnStatus() {
    if (mgrOK()) {
        try {
            p->setPower(PowerManager::ON);
        } catch (JmriException* e) {
            log->error("Exception trying to turn power on " + e->getMessage());
            try {
                sendErrorStatus();
            } catch (IOException ie) {
            }
        }
    }
}

/*public*/ void AbstractPowerServer::setOffStatus() {
    if (mgrOK()) {
        try {
            p->setPower(PowerManager::OFF);
        } catch (JmriException* e) {
            log->error("Exception trying to turn power off " + e->getMessage());
            try {
                sendErrorStatus();
            } catch (IOException ie) {
            }
        }
    }
}

//@Override
/*public*/ void AbstractPowerServer::propertyChange(PropertyChangeEvent* /*ev*/)
{
 try
 {
  sendStatus(p->getPower());
 }
 catch (JmriException* ex)
 {
  try
  {
   sendErrorStatus();
  }
  catch (IOException ie)
  {
  }
 }
 catch (IOException ie2)
 {
 }
}

/*public*/ void AbstractPowerServer::dispose() {
    if (p != nullptr) {
//        p.removePropertyChangeListener(this);
     connect(p->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
}


/*
 * Protocol Specific Abstract Functions
 */
//abstract /*public*/ void sendStatus(int Status) throws IOException;

//abstract /*public*/ void sendErrorStatus() throws IOException;

//abstract /*public*/ void parseStatus(String statusString) throws JmriException, IOException;

/*private*/ /*final*/ /*static*/ Logger* AbstractPowerServer::log = LoggerFactory::getLogger("AbstractPowerServer");

