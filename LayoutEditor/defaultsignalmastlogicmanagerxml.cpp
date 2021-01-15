#include "defaultsignalmastlogicmanagerxml.h"
#include "instancemanager.h"
#include "signalmastlogicmanager.h"
#include "signalmastlogic.h"
#include "block.h"
#include "sensor.h"
#include "signalmast.h"
#include "blockmanager.h"
#include "defaultsignalmastmanager.h"
#include "defaultsignalmastlogic.h"
#include "defaultsignalmastlogicmanager.h"
#include "signalmastlogicmanager.h"

DefaultSignalMastLogicManagerXml::DefaultSignalMastLogicManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
    log = new Logger("DefaultSignalMastLogicManagerXml");
    nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
}
/**
 *
 * @author kevin
 */
///*public*/ class DefaultSignalMastLogicManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {
//    /*public*/ DefaultSignalMastLogicManagerXml(){
//        debug = log->isDebugEnabled();
//    }



/*public*/ QDomElement DefaultSignalMastLogicManagerXml::store(QObject* o)
{
 QDomElement signalMastLogic = doc.createElement("signalmastlogics");
 setStoreElementClass(signalMastLogic);
 SignalMastLogicManager* smlm = (SignalMastLogicManager*) o;
 QDomElement e1;
 signalMastLogic.appendChild(e1=doc.createElement("logicDelay"));
 e1.appendChild(doc.createTextNode(QString::number(((DefaultSignalMastLogicManager*)smlm)->getSignalLogicDelay())));
 QList<SignalMastLogic*> sml = ((DefaultSignalMastLogicManager*)smlm)->getSignalMastLogicList();
 for(int i = 0; i<sml.size(); i++)
 {
  SignalMastLogic* sm = sml.at(i);
  QDomElement source = doc.createElement("signalmastlogic");
  QDomElement e2;
  source.appendChild(e2=doc.createElement("sourceSignalMast"));
  e2.appendChild(doc.createTextNode(sm->getSourceMast()->getDisplayName()));
  QList<SignalMast*> destination = sm->getDestinationList();
  if(destination.size()!=0)
  {
   for (int k = 0; k<destination.size(); k++)
   {
    SignalMast* dest = destination.at(k);
    if(sml.at(i)->getStoreState(dest)!=SignalMastLogic::STORENONE)
    {
     QDomElement elem = doc.createElement("destinationMast");
     QDomElement e1;
     elem.appendChild(e1 = doc.createElement("destinationSignalMast"));
     e1.appendChild(doc.createTextNode(dest->getDisplayName()));
     QDomElement e2;
     elem.appendChild(e2 =doc.createElement("comment"));
     e2.appendChild(doc.createTextNode(sm->getComment(dest)));
     QDomElement e3;
     if(sm->isEnabled(dest))
     {
      elem.appendChild(e3 =doc.createElement("enabled"));
      e3.appendChild(doc.createTextNode("yes"));
     }
     else
     {
      elem.appendChild(e3 = doc.createElement("enabled"));
      e3.appendChild(doc.createTextNode("no"));
     }

     QDomElement e4;
     if(((DefaultSignalMastLogic*)sm)->allowAutoMaticSignalMastGeneration(dest))
     {
      elem.appendChild(e4 =doc.createElement("allowAutoMaticSignalMastGeneration"));
      e4.appendChild(doc.createTextNode("yes"));
     }
     else
     {
      elem.appendChild(e4=doc.createElement("allowAutoMaticSignalMastGeneration"));
      e4.appendChild(doc.createTextNode("no"));
     }

     QDomElement e5;
     if(((DefaultSignalMastLogic*)sm)->useLayoutEditor(dest))
     {
      elem.appendChild(e5 = doc.createElement("useLayoutEditor"));
      e5.appendChild(doc.createTextNode("yes"));
     }
     else
     {
      elem.appendChild(e5 =  doc.createElement("useLayoutEditor"));
      e5.appendChild(doc.createTextNode("no"));
     }

     QDomElement e6;
     if(((DefaultSignalMastLogic*)sm)->useLayoutEditorTurnouts(dest))
     {
      elem.appendChild(e6 =doc.createElement("useLayoutEditorTurnouts"));
      e6.appendChild(doc.createTextNode("yes"));
     }
     else
     {
      elem.appendChild(e6=doc.createElement("useLayoutEditorTurnouts"));
      e6.appendChild(doc.createTextNode("no"));
     }

     QDomElement e7;
     if(((DefaultSignalMastLogic*)sm)->useLayoutEditorBlocks(dest))
     {
      elem.appendChild(e7=doc.createElement("useLayoutEditorBlocks"));
      e7.appendChild(doc.createTextNode("yes"));
     }
     else
     {
      elem.appendChild(e7=doc.createElement("useLayoutEditorBlocks"));
      e7.appendChild(doc.createTextNode("no"));
     }
     QDomElement e7a;
     if (sm->getAssociatedSection(dest) != nullptr)
     {
      elem.appendChild(e7a = doc.createElement("associatedSection"));
      e7a.appendChild(doc.createTextNode(sm->getAssociatedSection(dest)->getDisplayName()));
     }
     QDomElement e8;
     if(((DefaultSignalMastLogic*)sm)->isTurnoutLockAllowed(dest))
     {
      elem.appendChild(e8=doc.createElement("lockTurnouts"));
      e8.appendChild(doc.createTextNode("yes"));
     }
     else
     {
      elem.appendChild(e8=doc.createElement("lockTurnouts"));
      e8.appendChild(doc.createTextNode("no"));
     }

     if(((DefaultSignalMastLogic*)sml.at(i))->getStoreState(dest)==SignalMastLogic::STOREALL)
     {
      QList<Block*> blocks = ((DefaultSignalMastLogic*)sm)->getBlocks(dest);
      if (blocks.size()>0)
      {
       QDomElement blockElement = doc.createElement("blocks");
       for(int j = 0; j<blocks.size(); j++)
       {
        QDomElement bloc = doc.createElement("block");
        QDomElement b1;
        bloc.appendChild(b1=doc.createElement("blockName"));
        b1.appendChild(doc.createTextNode(blocks.at(j)->getDisplayName()));
        QString blkState = "anyState";
        if (((DefaultSignalMastLogic*)sm)->getBlockState(blocks.at(j), dest)==Block::OCCUPIED)
            blkState = "occupied";
        else if (((DefaultSignalMastLogic*)sm)->getBlockState(blocks.at(j), dest)==Block::UNOCCUPIED)
            blkState = "unoccupied";
        QDomElement b2;
        bloc.appendChild(b2 =doc.createElement("blockState"));
        b2.appendChild(doc.createTextNode(blkState));
        blockElement.appendChild(bloc);
       }
       elem.appendChild(blockElement);
      }
      QList<NamedBeanHandle<Turnout*>* > turnouts = ((DefaultSignalMastLogic*)sm)->getNamedTurnouts(dest);
      if (turnouts.size()>0)
      {
       QDomElement turnoutElement = doc.createElement("turnouts");
       for(int j = 0; j<turnouts.size(); j++)
       {
        QDomElement turn = doc.createElement("turnout");
        QDomElement t1;
        turn.appendChild(t1=doc.createElement("turnoutName"));
        t1.appendChild(doc.createTextNode(turnouts.at(j)->getName()));
        QString turnState = "thrown";
        if (((DefaultSignalMastLogic*)sm)->getTurnoutState(turnouts.at(j)->getBean(),dest)==Turnout::CLOSED)
         turnState = "closed";
        QDomElement t2;
        turn.appendChild(t2=doc.createElement("turnoutState"));
        t2.appendChild(doc.createTextNode(turnState));
        turnoutElement.appendChild(turn);
       }
       elem.appendChild(turnoutElement);
      }
      QList<NamedBeanHandle<Sensor*>* > sensors = ((DefaultSignalMastLogic*)sm)->getNamedSensors(dest);
      if (sensors.size()>0)
      {
       QDomElement sensorElement = doc.createElement("sensors");
       for(int j = 0; j<sensors.size(); j++)
       {
        QDomElement sensor= doc.createElement("sensor");
        QDomElement s1;
        sensor.appendChild(s1 =doc.createElement("sensorName"));
        s1.appendChild(doc.createTextNode(sensors.at(j)->getName()));
        QString sensorState = "inActive";
        if (((DefaultSignalMastLogic*)sm)->getSensorState(sensors.at(j)->getBean(), dest)==Sensor::ACTIVE)
         sensorState = "active";
        QDomElement s2;
        sensor.appendChild(s2=doc.createElement("sensorState"));
        s2.appendChild(doc.createTextNode(sensorState));
            sensorElement.appendChild(sensor);
       }
       elem.appendChild(sensorElement);
      }
      QList<SignalMast*> masts = ((DefaultSignalMastLogic*)sm)->getSignalMasts(dest);
      if (masts.size()>0)
      {
       QDomElement mastElement = doc.createElement("masts");
       for(int j = 0; j<masts.size(); j++)
       {
        QDomElement mast= doc.createElement("mast");
        QDomElement m1;
        mast.appendChild(m1=doc.createElement("mastName"));
        m1.appendChild(doc.createTextNode(masts.at(j)->getDisplayName()));
        QDomElement m2;
        mast.appendChild(m2 = doc.createElement("mastState"));
        m2.appendChild(doc.createTextNode(((DefaultSignalMastLogic*)sm)->getSignalMastState(masts.at(j), dest)));
        mastElement.appendChild(mast);
       }
       elem.appendChild(mastElement);
      }
     }
     source.appendChild(elem);
    }
   }
   signalMastLogic.appendChild(source);
  }
 }
 return signalMastLogic;
}

/*public*/ void DefaultSignalMastLogicManagerXml::setStoreElementClass(QDomElement signalMastLogic) {
    signalMastLogic.setAttribute("class","jmri.managers.configurexml.DefaultSignalMastLogicManagerXml");
}

/*public*/ void DefaultSignalMastLogicManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/*public*/ bool DefaultSignalMastLogicManagerXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException){
    // load individual Transits
    loadSignalMastLogic(shared);
    return true;
}

//@SuppressWarnings("unchecked")
/*public*/ bool DefaultSignalMastLogicManagerXml::loadSignalMastLogic(QDomElement signalMastLogic)
{
 QDomNodeList logicList = signalMastLogic.elementsByTagName("signalmastlogic");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(logicList.size())+" signal mast logics");

 SignalMastManager* sm = (SignalMastManager*)InstanceManager::getDefault("SignalMastManager");
 SignalMastLogicManager* smlm = (SignalMastLogicManager*) InstanceManager::getDefault("SignalMastLogicManager");
 try
 {
     QString logicDelay = signalMastLogic.firstChildElement("logicDelay").text();
     ((DefaultSignalMastLogicManager*)smlm)->setSignalLogicDelay((logicDelay.toLong()));
 }
 catch (NullPointerException e){
     //Considered normal if it doesn't exists
 }
 bool loadOk = true;
 for(int i=0; i < logicList.size(); i++)
 {
  QDomElement sml = logicList.at(i).toElement();
  QString source = sml.firstChildElement("sourceSignalMast").text();
  SignalMast* sourceMast = sm->getSignalMast(source);
  if(sourceMast != nullptr)
  {
   SignalMastLogic* logic = smlm->newSignalMastLogic(sourceMast);

   QDomNodeList destList = sml.elementsByTagName("destinationMast");
   for (int i=0; i <  destList.count(); i++)
   {
    QDomElement d = destList.at(i).toElement();
    QString destination = d.firstChildElement("destinationSignalMast").text();
    SignalMast* dest = sm->getSignalMast(destination);
    if(dest != nullptr)
    {
     ((DefaultSignalMastLogic*)logic)->setDestinationMast(dest);
     if(!d.firstChildElement("comment").isNull())
     {
      ((DefaultSignalMastLogic*)logic)->setComment(d.firstChildElement("comment").text(), dest);
     }
     if(!d.firstChildElement("enabled").isNull())
     {
      if (d.firstChildElement("enabled").text()==("yes"))
       ((DefaultSignalMastLogic*)logic)->setEnabled(dest);
      else
       ((DefaultSignalMastLogic*)logic)->setDisabled(dest);
     }

     if(!d.firstChildElement("allowAutoMaticSignalMastGeneration").isNull())
     {
      if (d.firstChildElement("allowAutoMaticSignalMastGeneration").text()==("no"))
       ((DefaultSignalMastLogic*)logic)->allowAutoMaticSignalMastGeneration(false, dest);
      else
       ((DefaultSignalMastLogic*)logic)->allowAutoMaticSignalMastGeneration(true , dest);
     }

     bool useLayoutEditorTurnout = true;
     bool useLayoutEditorBlock = true;
     if(!d.firstChildElement("useLayoutEditorTurnouts").isNull())
     {
      if (d.firstChildElement("useLayoutEditorTurnouts").text()==("no"))
       useLayoutEditorTurnout=false;
     }

     if(!d.firstChildElement("useLayoutEditorBlocks").isNull())
     {
      if (d.firstChildElement("useLayoutEditorBlocks").text()==("no"))
       useLayoutEditorBlock=false;
     }
     try
     {
      ((DefaultSignalMastLogic*)logic)->useLayoutEditorDetails(useLayoutEditorTurnout, useLayoutEditorBlock, dest);
     }
     catch (JmriException ex)
     {

     }

     if(!d.firstChildElement("useLayoutEditor").isNull())
     {
      try
      {
       if (d.firstChildElement("useLayoutEditor").text()==("yes"))
        ((DefaultSignalMastLogic*)logic)->useLayoutEditor(true, dest);
       else
        ((DefaultSignalMastLogic*)logic)->useLayoutEditor(false, dest);
      }
      catch (JmriException e)
      {
       //Considered normal if layout editor hasn't yet been set up.
      }
     }

     if (!d.firstChildElement("associatedSection").isNull())
     {
      Section* sect = ((SectionManager*)InstanceManager::getDefault("SectionManager"))->getSection(d.firstChildElement("associatedSection").text());
      logic->setAssociatedSection(sect, dest);
     }

     QDomElement turnoutElem = d.firstChildElement("turnouts");
     if(!turnoutElem.isNull())
     {
      QDomNodeList turnoutList = turnoutElem.elementsByTagName("turnout");
      if (turnoutList.size()>0)
      {
       QHash<NamedBeanHandle<Turnout*>*, int> list =  QHash<NamedBeanHandle<Turnout*>*, int>();
       for (int i=0; i <  turnoutList.count(); i ++)
       {
        QDomElement t = turnoutList.at(i).toElement();
        QString turnout = t.firstChildElement("turnoutName").text();
        QString state = t.firstChildElement("turnoutState").text();
        int value = Turnout::CLOSED;
        if (state==("thrown"))
            value = Turnout::THROWN;
        Turnout* turn = ((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(turnout);
        if(turn!=NULL){
            NamedBeanHandle<Turnout*>* namedTurnout = nbhm->getNamedBeanHandle(turnout, turn);
            list.insert(namedTurnout, value);
        } else if (debug)
            log->debug("Unable to add Turnout " + turnout + " as it does not exist in the panel file");
       }
       ((DefaultSignalMastLogic*)logic)->setTurnouts(list, dest);
      }
     }
     QDomElement sensorElem = d.firstChildElement("sensors");
     if(!sensorElem.isNull())
     {
      QDomNodeList sensorList = sensorElem.elementsByTagName("sensor");
      if (sensorList.size()>0)
      {
       QHash<NamedBeanHandle<Sensor*>*, int> list =  QHash<NamedBeanHandle<Sensor*>*, int>();
       for (int i=0; i <  sensorList.count(); i++)
       {
        QDomElement sl = sensorList.at(i).toElement();
        QString sensorName = sl.firstChildElement("sensorName").text();
        QString state = sl.firstChildElement("sensorState").text();
        int value = Sensor::INACTIVE;
        if (state==("active"))
            value = Sensor::ACTIVE;

        Sensor* sen = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sensorName);
        if(sen!=NULL)
        {
         NamedBeanHandle<Sensor*>* namedSensor = nbhm->getNamedBeanHandle(sensorName, sen);
         list.insert(namedSensor, value);
        }
        else if (debug)
         log->debug("Unable to add sensor " + sensorName + " as it does not exist in the panel file");

       }
       ((DefaultSignalMastLogic*)logic)->setSensors(list, dest);
      }
     }
     QDomElement blockElem = d.firstChildElement("blocks");
     if(!blockElem.isNull())
     {
      QDomNodeList blockList = blockElem.elementsByTagName("block");
      if (blockList.size()>0)
      {
       QHash<Block*, int> list =  QHash<Block*, int>();
       for (int i=0; i < blockList.count(); i++)
       {
           QDomElement b = blockList.at(i).toElement();
           QString block = b.firstChildElement("blockName").text();
           QString state = b.firstChildElement("blockState").text();
           int value = 0x03;
           if (state==("occupied"))
               value = Block::OCCUPIED;
           else if (state==("unoccupied"))
               value = Block::UNOCCUPIED;

           Block* blk = ((BlockManager*)((BlockManager*)InstanceManager::getDefault("BlockManager")))->getBlock(block);
           if (blk!=NULL)
               list.insert(blk, value);
           else if (debug)
               log->debug("Unable to add Block " + block + " as it does not exist in the panel file");
       }
       ((DefaultSignalMastLogic*)logic)->setBlocks(list, dest);
      }
     }
     QDomElement mastElem = d.firstChildElement("masts");
     if(!mastElem.isNull())
     {
      QDomNodeList mastList = mastElem.elementsByTagName("mast");
      if (mastList.size()>0)
      {
       QHash<SignalMast*, QString> list =  QHash<SignalMast*, QString>();
       for (int i=0; i < mastList.count(); i++)
       {
           QDomElement m = mastList.at(i).toElement();
           QString mast = m.firstChildElement("mastName").text();
           QString state = m.firstChildElement("mastState").text();
           SignalMast* mst = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(mast);
           if(mst!=NULL)
               list.insert(mst, state);
           else if (debug)
               log->debug("Unable to add Signal Mast  " + mast + " as it does not exist in the panel file");

       }
       ((DefaultSignalMastLogic*)logic)->setMasts(list, dest);
      }
     }
    }
    else
    {
     log->error(tr("Destination Mast %1 not found, logic not loaded").arg(destination));
     loadOk = false;
    }
   }
  }
  else
  {
   log->error(tr("Source Mast %1 Not found, logic not loaded").arg(source));
   loadOk = false;
  }
 }
 ((DefaultSignalMastLogicManager*)smlm)->initialise();
 return loadOk;
}

/*public*/ int DefaultSignalMastLogicManagerXml::loadOrder() const
{
    return ((DefaultSignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getXMLOrder();
}
