#include "programmerfacadeselector.h"
#include "twoindexprogrammerfacade.h"
#include "accessoryopsmodeprogrammerfacade.h"
#include "addressedprogrammer.h"
#include "multiindexprogrammerfacade.h"
#include "addressedhighcvprogrammerfacade.h"
#include "loggerfactory.h"
#include "class.h"
#include "opsmodedelayedprogrammerfacade.h"
#include "offsethighcvprogrammerfacade.h"
#include "resettingoffsethighcvprogrammerfacade.h"

ProgrammerFacadeSelector::ProgrammerFacadeSelector(QObject *parent) :
    QObject(parent)
{
}
/**
 * Utility to load a specific ProgrammerFacade from an XML element
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2013
 * @version	$Revision: 27937 $
 */
// /*public*/ class ProgrammerFacadeSelector  {

/*public*/ /*static*/ Programmer* ProgrammerFacadeSelector::loadFacadeElements(
        QDomElement element, Programmer* programmer, bool allowCache, Programmer* baseProg)
{

 // iterate over any facades and add them
 QDomNodeList facades = element.elementsByTagName("capability");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(facades.size())+" capability elements");
 //for (QDomElement facade : facades)
 for(int i=0; i < facades.size(); i++)
 {
  QDomElement facade = facades.at(i).toElement();
  QString fname = facade.firstChildElement("name").text();
  if (log->isDebugEnabled()) log->debug("Process capability facade: "+fname);

  QDomNodeList parameters = facade.elementsByTagName("parameter");
  if (log->isDebugEnabled()) log->debug("Found "+QString::number(parameters.size())+" capability parameters");
  //for (QDomElement parameter : parameters)
  for(int j = 0; j < parameters.size(); j++)
  {
   QDomElement parameter = parameters.at(j).toElement();
   QString pval = parameter.text();
   if (log->isDebugEnabled()) log->debug("Process parameter value: "+pval);
  }

  if (fname==("High Access via Double Index"))
  {
   // going to create a specific one
   QString top          = parameters.at(0).toElement().text();
   QString addrCVhigh   = parameters.at(1).toElement().text();
   QString addrCVlow    = parameters.at(2).toElement().text();
   QString valueCV      = parameters.at(3).toElement().text();
   QString modulo       = parameters.at(4).toElement().text();

   AddressedHighCvProgrammerFacade* pf =
            new AddressedHighCvProgrammerFacade(programmer, top, addrCVhigh, addrCVlow, valueCV, modulo);

   log->debug("new programmer "+QString(pf->metaObject()->className()));
   programmer = (Programmer*)pf; // to go around and see if there are more

  }
  else if (fname==("High Access via Partial Index"))
  {
   // going to create a specific one
   QString top          = parameters.at(0).toElement().text();
   QString addrCV       = parameters.at(1).toElement().text();
   QString factor       = parameters.at(2).toElement().text();
   QString modulo       = parameters.at(3).toElement().text();

   OffsetHighCvProgrammerFacade* pf =
            new OffsetHighCvProgrammerFacade(programmer, top, addrCV, factor, modulo);

        log->debug("new programmer "+QString(pf->metaObject()->className()));
        programmer = pf; // to go around and see if there are more

    } else if (fname==("High Access via Partial Index with Reset")) {
        // going to create a specific one
        QString top          = parameters.at(0).toElement().text();
        QString addrCV       = parameters.at(1).toElement().text();
        QString factor       = parameters.at(2).toElement().text();
        QString modulo       = parameters.at(3).toElement().text();
        QString indicator    = parameters.at(4).toElement().text();

        ResettingOffsetHighCvProgrammerFacade* pf =
            new ResettingOffsetHighCvProgrammerFacade(programmer, top, addrCV, factor, modulo, indicator);

        log->debug(tr("new programmer ")+QString(pf->metaObject()->className()));
        programmer = pf; // to go around and see if there are more

    }
  else if (fname==("Indexed CV access"))
  {
   // going to create a specific one
   QString PI           = parameters.at(0).toElement().text();
   QString SI           = (parameters.size()>1) ? parameters.at(1).toElement().text() : "";
   bool cvFirst     = (parameters.size()>2) ? (parameters.at(2).toElement().text()==("false") ? false : true) : true;

   MultiIndexProgrammerFacade* pf =
            new MultiIndexProgrammerFacade(programmer, PI, SI, cvFirst);

   log->debug("new programmer "+QString(pf->metaObject()->className()));
   programmer = pf; // to go around and see if there are more

  }
  else if (fname==("TCS 4 CV access"))
  {

   TwoIndexTcsProgrammerFacade* pf =
            new TwoIndexTcsProgrammerFacade(programmer);

   log->debug("new programmer "+QString(pf->metaObject()->className()));
   programmer = pf; // to go around and see if there are more
  }
  else if(fname == "Ops Mode Accessory Programming")
  {
   //if ("AddressedProgrammer".isAssignableFrom(baseProg.getClass()))
   Class* clazz = Class::forName("AddressedProgrammer");
   if(clazz->isAssignableFrom(baseProg->metaObject()->className()))
   {  // create if relevant to current mode, otherwise silently ignore
    QString addrType = "decoder";
    int delay = 500;
    //for (QDomNode node : parameters)
    for(int i = 0; i < parameters.size(); i++)
    {
     QDomElement x = parameters.at(i).toElement();
     if(x.attribute("name")== "Address Type")
     {
      addrType = x.text();
     }
     else if( x.attribute("name") == "Delay")
     {
             delay = x.text().toInt();
     }
     else
     {
      log->error(tr("Unknown parameter \"%1\" for \"%2\"").arg(fname).arg(x.text()));
     }
    }
    log->debug(tr("\"%1\": addrType=\"%2\", delay=\"%3\", baseProg=\"%4\"").arg(fname).arg(addrType).arg(delay).arg(baseProg->metaObject()->className()));

    AccessoryOpsModeProgrammerFacade* pf
            = new AccessoryOpsModeProgrammerFacade(programmer, addrType, delay, (AddressedProgrammer*) baseProg);
    log->debug(tr("new programmer '%1' %2").arg(fname).arg(pf->metaObject()->className()));
    programmer = pf; // to go around and see if there are more
   }
  }
  else if(fname == "Ops Mode Delayed Programming")
  {
   Class* clazz = Class::forName("AddressedProgrammer");
//   if (AddressedProgrammer.class.isAssignableFrom(baseProg.getClass())) {  // create if relevant to current mode, otherwise silently ignore
   if(clazz->isAssignableFrom(baseProg->metaObject()->className()))
   {
    int delay = 500;
    for(int i=0; i < parameters.size(); i++)
    {
     QDomElement x = parameters.at(i).toElement();
     if(x.attribute("name")== "Delay")
     {
             delay = x.text().toInt();
     }
     else
     {
      log->error(tr("Unknown parameter \"%1\" for \"%2\"").arg(fname).arg(x.text()));
     }
    }
    log->debug(tr("\"%1\": delay=\"%2\"").arg(fname).arg(delay));
    OpsModeDelayedProgrammerFacade* pf
             = new OpsModeDelayedProgrammerFacade(programmer, delay);
    log->debug(tr("new programmer '%1' %2").arg(fname).arg(pf->metaObject()->className()));
    programmer = pf; // to go around and see if there are more
   }
  }
  else

  {
   log->error("Cannot create programmer capability named: "+fname);
  }

 }
 return programmer;
}

/*static*/ Logger* ProgrammerFacadeSelector::log = LoggerFactory::getLogger("ProgrammerFacadeSelector");
//}
