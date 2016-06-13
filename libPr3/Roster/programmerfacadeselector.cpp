#include "programmerfacadeselector.h"
#include "twoindexprogrammerfacade.h"
#include "accessoryopsmodeprogrammerfacade.h"
#include "addressedprogrammer.h"
#include "multiindexprogrammerfacade.h"
#include "addressedhighcvprogrammerfacade.h"

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

/*public*/ /*static*/ Programmer* ProgrammerFacadeSelector::loadFacadeElements(QDomElement element, Programmer* programmer)
{
 Logger* log = new Logger("ProgrammerFacadeSelector");

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
#if 0
  else if (fname==("High Access via Partial Index"))
  {
   // going to create a specific one
   QString top          = parameters.at(0).toElement().text();
   QString addrCV       = parameters.at(1).toElement().text();
   QString factor       = parameters.at(2).toElement().text();
   QString modulo       = parameters.at(3).toElement().text();

   OffsetHighCvProgrammerFacade pf =
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

        ResettingOffsetHighCvProgrammerFacade pf =
            new ResettingOffsetHighCvProgrammerFacade(programmer, top, addrCV, factor, modulo, indicator);

        log->debug("new programmer "+QString(pf->metaObject()->className()));
        programmer = pf; // to go around and see if there are more

    } else
#endif
  if (fname==("Indexed CV access"))
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
  else
  //if (programmer instanceof AddressedProgrammer && fname==("Ops Mode Accessory Programming"))
  if(qobject_cast<AddressedProgrammer*>(programmer) != NULL)
  {

   AccessoryOpsModeProgrammerFacade* pf =
            new AccessoryOpsModeProgrammerFacade((AddressedProgrammer*)programmer);

   log->debug("new programmer "+QString(pf->metaObject()->className()));
   programmer = pf; // to go around and see if there are more
  }
  else

  {
   log->error("Cannot create programmer capability named: "+fname);
  }
 }

 return programmer;
}

//    static Logger log = LoggerFactory.getLogger(ProgrammerFacadeSelector.class.getName());
//}
