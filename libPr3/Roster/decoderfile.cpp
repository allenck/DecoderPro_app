#include "decoderfile.h"
#include "variabletablemodel.h"
#include "resettablemodel.h"
#include "fileutil.h"
#include "xmlinclude.h"
#include "loggerfactory.h"

QString DecoderFile::fileLocation = tr("decoders")+QDir::separator();
//QString DecoderFile::fileLocation = "/home/allen/NetBeansProjects/jmri/xml/decoders/";

DecoderFile::DecoderFile(QObject *parent) :
    XmlFile(parent)
{

}
/**
 * Represents and manipulates a decoder definition, both as a file and
 * in memory.  The internal storage is a JDOM tree.
 *<P>
 * This object is created by DecoderIndexFile to represent the
 * decoder identification info _before_ the actual decoder file is read.
 *
 * @author    Bob Jacobsen   Copyright (C) 2001
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 21273 $
 * @see       jmri.jmrit.decoderdefn.DecoderIndexFile
 */
///*public*/ class DecoderFile extends XmlFile {

//    /*public*/ DecoderFile() {}

/*public*/ DecoderFile::DecoderFile(QString mfg, QString mfgID, QString model, QString lowVersionID, QString highVersionID, QString family, QString filename, int numFns, int numOuts, QDomElement decoder, QObject *parent) : XmlFile(parent)
{
 log->setDebugEnabled(true);

 _mfg = mfg;
 _mfgID = mfgID;
 _model = model;
 _family = family;
 _filename = filename;
 _numFns = numFns;
 _numOuts = numOuts;
 _element = decoder;
 //QDir::setCurrent(FileUtil::getProgramPath());

 versions = new QVector<bool>(256,false);
 // store the default range of version id's
 setVersionRange(lowVersionID, highVersionID);
}
/*public*/ DecoderFile::DecoderFile(QString mfg, QString mfgID, QString model, QString lowVersionID,
        QString highVersionID, QString family, QString filename,
        int numFns, int numOuts, QDomElement decoder, QString replacementModel, QString replacementFamily) {
//    this(mfg, mfgID, model, lowVersionID,
//            highVersionID, family, filename,
//            numFns, numOuts, decoder);
 _mfg = mfg;
 _mfgID = mfgID;
 _model = model;
 _family = family;
 _filename = filename;
 _numFns = numFns;
 _numOuts = numOuts;
 _element = decoder;
 _replacementModel = replacementModel;
 _replacementFamily = replacementFamily;
}

/*public*/ void DecoderFile::setOneVersion(int i) { versions->replace(i, true); }
/*public*/ void DecoderFile::setVersionRange(int low, int high) {
    for (int i=low; i<=high; i++) versions->replace(i, true);
}
/*public*/ void DecoderFile::setVersionRange(QString lowVersionID, QString highVersionID)
{
 if (lowVersionID!="")
 {
  // lowVersionID is not NULL; check high version ID
  if (highVersionID!="")
  {
   // low version and high version are not NULL
   setVersionRange((lowVersionID).toInt(),
                            (highVersionID).toInt());
  }
  else
  {
   // low version not NULL, but high is NULL. This is
   // a single value to match
   setOneVersion((lowVersionID).toInt());
  }
 }
 else
 {
  // lowVersionID is NULL; check high version ID
  if (highVersionID!="")
  {
   // low version NULL, but high is not NULL
   setOneVersion((highVersionID).toInt());
   }
  else
  {
   // both low and high version are NULL; do nothing
  }
 }
}

/**
 * Test for correct decoder version number
 * @param i
 * @return true if decoder version matches id
 */
/*public*/ bool DecoderFile::isVersion(int i) { return versions->at(i); }

/**
 * return array of versions
 *
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<bool>* DecoderFile::getVersions() { return(versions); }

/*public*/ QString DecoderFile::getVersionsAsString()
{
 QString ret = "";
 int partStart = -1;
 QString part = "";
 for (int i = 0; i < 256; i++)
 {
  if (partStart >= 0)
  {
   /* working on part, found end of range */
   if (!versions->at(i))
   {
    if (i - partStart > 1)
    {
     part = QString::number(partStart) + "-" + QString::number(i - 1);
    }
    else
    {
     part = QString::number(i - 1);
    }
    if (ret == "")
    {
     ret = part;
    }
    else
    {
     ret = "," + part;
    }
    partStart = -1;
   }
  }
  else
  {
   /* testing for new part */
   if (versions->at(i))
   {
    partStart = i;
   }
  }
 }
 if (partStart >= 0)
 {
  if (partStart != 255)
  {
   part = QString::number(partStart) + "-" + QString::number(255);
  }
  else
  {
   part = QString::number(partStart);
  }
  if (ret != "")
  {
   ret = ret + "," + part;
  }
  else
  {
   ret = part;
  }
 }
 return(ret);
}


/*public*/ QString DecoderFile::getMfg()       { return _mfg; }
/*public*/ QString DecoderFile::getMfgID()     { return _mfgID; }
/**
 * Get the SV2 "Developer ID" number.
 *
 * This value is assigned by the device
 * manufacturer and is an 8-bit number.
 * @return the developerID number
 */
/*public*/ QString DecoderFile::getDeveloperID() {
    return _developerID;
}

/**
 * Get the SV2 "Manufacturer ID" number.
 *
 * This value typically matches the NMRA
 * manufacturer ID number and is an 8-bit number.
 *
 * @return the manufacturer number
 */
/*public*/ QString DecoderFile::getManufacturerID() {
    return _manufacturerID;
}

/*public*/ QString DecoderFile::getModel()     { return _model; }
/*public*/ QString DecoderFile::getFamily()    { return _family; }
/*public*/ QString DecoderFile::getReplacementModel() {
    return _replacementModel;
}

/*public*/ QString DecoderFile::getReplacementFamily() {
    return _replacementFamily;
}

/*public*/ QString DecoderFile::getFileName()  { return _filename; }
/*public*/ int DecoderFile::getNumFunctions() { return _numFns; }
/*public*/ int DecoderFile::getNumOutputs()   { return _numOuts; }

/*public*/ QString DecoderFile::getModelComment() { return _element.attribute("comment"); }

/*public*/ QString DecoderFile::getFamilyComment()
{
 return ((QDomElement)_element.parentNode().toElement()).attribute("comment");
}
/*public*/ QString DecoderFile::getProductID() {
   _productID = _element.attribute("productID");
   return _productID;
}

/*public*/ QDomElement DecoderFile::getModelElement() { return _element; }

// static service methods - extract info from a given Element
/*public*/ /*static*/ QString DecoderFile::getMfgName(QDomElement decoderElement) {
    return decoderElement.firstChildElement("family").attribute("mfg");
}


/*public*/ QList<LocoAddress::Protocol>* DecoderFile::getSupportedProtocols(){
    if(protocols==NULL)
        setSupportedProtocols();
    //return protocols->toArray(new LocoAddress::Protocol[protocols->size()]);
    return protocols;
}

/*private*/ void DecoderFile::setSupportedProtocols(){
    protocols = new QList<LocoAddress::Protocol>();
    if(!_element.firstChildElement("protocols").isNull()){
        //@SuppressWarnings("unchecked")
        QDomNodeList protocolList = _element.firstChildElement("protocols").elementsByTagName("protocol");
        for(int i = 0; i <  protocolList.size(); i++)
        {
         QDomElement e = protocolList.at(i).toElement();
            protocols->append(LocoAddress::getByShortName(e.text()));
        }
    }
}

bool DecoderFile::isProductIDok(QDomElement e, QString extraInclude, QString extraExclude) {
        return isIncluded(e, _productID, _model, _family, extraInclude, extraExclude);
    }

/**
 * @param e XML element with possible "include" and "exclude" attributes to be checked
 * @param productID the specific ID of the decoder being loaded, to check against include/exclude conditions
 * @param modelID the model ID of the decoder being loaded, to check against include/exclude conditions
 * @param familyID the family ID of the decoder being loaded, to check against include/exclude conditions
 * @param extraInclude additional "include" terms
 * @param extraExclude additional "exclude" terms
 */
/*public*/ /*static*/ bool DecoderFile::isIncluded(QDomElement e, QString productID, QString modelID, QString familyID, QString extraInclude, QString extraExclude)
{
 QString include = e.attribute("include");
 if (include != "") include = include+","+extraInclude;
    else include = extraInclude;
    // if there are any include clauses, then it has to match
    if (include!=("") && !(isInList(productID, include)||isInList(modelID, include)||isInList(familyID, include)) ) {
        //if (log.isTraceEnabled()) log.trace("include not in list of OK values: /"+include+"/ /"+productID+"/ /"+modelID+"/");
        return false;
    }

    QString exclude = e.attribute("exclude");
    if (exclude != "") exclude = exclude+","+extraExclude;
    else exclude = extraExclude;
    // if there are any include clauses, then it cannot match
    if ( exclude!=("") && (isInList(productID, exclude)||isInList(modelID, exclude)||isInList(familyID, exclude)) ) {
//        if (log.isTraceEnabled()) log.trace("exclude match: /"+exclude+"/ /"+productID+"/ /"+modelID+"/");
        return false;
    }

    return true;
}

/*private*/ /*static*/ bool DecoderFile::isInList(QString include, QString productID) {
    QString test = ","+productID+",";
    return test.contains(","+include+",");
}

// use the decoder Element from the file to load a VariableTableModel for programming.
//@SuppressWarnings("unchecked")
/*public*/ void DecoderFile::loadVariableModel(QDomElement decoderElement,
                              VariableTableModel* variableModel)
{
  nextCvStoreIndex = 0;

  processVariablesElement(decoderElement.firstChildElement("variables"), variableModel, "", "");

  variableModel->configDone();

 }
/*public*/ void DecoderFile::processVariablesElement(QDomElement variablesElement,
                              VariableTableModel* variableModel, QString extraInclude, QString extraExclude)
{

 // handle include, exclude on this element
 extraInclude = extraInclude +(variablesElement.attribute("include")!="" ? ","+variablesElement.attribute("include") : "");
 extraExclude = extraExclude +(variablesElement.attribute("exclude")!="" ? ","+variablesElement.attribute("exclude") : "");
 log->debug(tr("extraInclude /%1/, extraExclude /%2/").arg(extraInclude).arg(extraExclude));

// load variables to table
//    Iterator<QDomElement> iter = decoderElement.firstChildElement("variables")
//                                .getDescendants(new ElementFilter("variable"));
 QDomNodeList list = variablesElement.elementsByTagName("variable");

 int index = 0;
//    while (iter.hasNext()) {
//        QDomElement e = iter.next();
 for(int i=0; i < list.size(); i++)
 {
  QDomElement e = list.at(i).toElement();
  log->debug(tr("processing variable CV=%1, item='%2' ").arg(e.attribute("CV")).arg(e.attribute("item")));
  try
  {
   // if its associated with an inconsistent number of functions,
   // skip creating it
   if (getNumFunctions() >= 0 && e.attribute("minFn") != ""
       && getNumFunctions() < (e.attribute("minFn")).toInt() )
       continue;
   // if its associated with an inconsistent number of outputs,
   // skip creating it
   if (getNumOutputs() >= 0 && e.attribute("minOut") != ""
       && getNumOutputs() < (e.attribute("minOut")).toInt() )
       continue;
   // if not correct productID, skip
   if (!isProductIDok(e, extraInclude, extraExclude)) continue;
  } catch (Exception ex) {
      log->warn("Problem parsing minFn or minOut in decoder file, variable "
               +e.attribute("item")+" exception: "/*+ex*/);
  }
  // load each row
  variableModel->setRow(nextCvStoreIndex++, e, _element.isNull() ? nullptr : this);
 }
 // load constants to table
//    iter = decoderElement.getChild("variables")
//                                .getDescendants(new ElementFilter("constant"));
 list = variablesElement.elementsByTagName("constant");
 index = 0;
//    while (iter.hasNext()) {
//        QDomElement e = iter.next();
 for(int i=0; i < list.size(); i++)
 {
  QDomElement e = list.at(i).toElement();
     try {
         // if its associated with an inconsistent number of functions,
         // skip creating it
   bool bOk;
         if (getNumFunctions() >= 0 && e.attribute("minFn") != NULL
             && getNumFunctions() < (e.attribute("minFn")).toInt(&bOk) )
             continue;
         if(!bOk) throw Exception();
         // if its associated with an inconsistent number of outputs,
         // skip creating it
         if (getNumOutputs() >= 0 && e.attribute("minOut") != NULL
             && getNumOutputs() < (e.attribute("minOut")).toInt(&bOk) )
             continue;
         if(!bOk) throw Exception();
         // if not correct productID, skip
         if (!isProductIDok(e, extraInclude, extraExclude)) continue;
     } catch (Exception ex) {
         log->warn("Problem parsing minFn or minOut in decoder file, variable "
                  +e.attribute("item")+" exception: "+ex.getMessage());
     }
     // load each row
     variableModel->setConstant(e);
 }
//    iter = decoderElement.getChild("variables")
//                                .getDescendants(new ElementFilter("ivariable"));
 list = variablesElement.elementsByTagName("ivariable");
 index = 0;
 int row = 0;
//    while (iter.hasNext()) {
//        QDomElement e = iter.next();
 for(int i=0; i < list.count(); i++)
 {
  QDomElement e = list.at(i).toElement();
  try
  {
   if (log->isDebugEnabled()) log->debug("process iVar "+e.attribute("CVname"));
   // if its associated with an inconsistent number of functions,
   // skip creating it
   bool bOk = true;
   if (getNumFunctions() >= 0 && e.attribute("minFn") != ""
       && (getNumFunctions() < (e.attribute("minFn")).toInt(&bOk)) && bOk)
   {
    log->debug("skip due to num functions");
    continue;
   }
   if(!bOk) throw Exception();
   // if its associated with an inconsistent number of outputs,
   // skip creating it
   if (getNumOutputs() >= 0 && e.attribute("minOut") != NULL
       && (getNumOutputs() < (e.attribute("minOut")).toInt(&bOk)) && bOk )
   {
       log->debug("skip due to num outputs");
       continue;
   }
   if(!bOk) throw Exception();
  }
  catch (Exception ex) {
   log->warn("Problem parsing minFn or minOut in decoder file, variable "
            +e.attribute("item")+" exception: "+ex.getMessage());
  }

 }
 //for (Element e : variablesElement.getChildren("variables")) {
 QDomNodeList nl1 = variablesElement.elementsByTagName("variables");
 for(int i=0; i < nl1.count(); i++)
 {
  QDomElement e = nl1.at(i).toElement();
  processVariablesElement(e, variableModel, extraInclude, extraExclude);
 }

 log->debug("iVarList done, now row = "+row);
 variableModel->configDone();
}

// use the decoder Element from the file to load a VariableTableModel for programming.
//@SuppressWarnings("unchecked")
/*public*/ void DecoderFile::loadResetModel(QDomElement decoderElement,
                           ResetTableModel* resetModel)
{

    if (!decoderElement.firstChildElement("resets").isNull()) {
     QDomNodeList resetList = decoderElement.firstChildElement("resets").elementsByTagName("factReset");
     for (int i = 0; i < resetList.size(); i++) {
         QDomElement e = resetList.at(i).toElement();
         resetModel->setRow(i, e, decoderElement.firstChildElement("resets"), _model);
     }
 }
}

/**
 * Convert to a cannonical text form for ComboBoxes, etc.
 * <P>
 * Must distinquish identical models in different families.
 */
/*public*/ QString DecoderFile::titleString() {
    return titleString(getModel(), getFamily());
}

/*static*/ /*public*/ QString DecoderFile::titleString(QString model, QString family) {
    return model+" ("+family+")";
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_SHOULD_BE_FINAL") // script access
/*private*/ /*final*/ /*static*/ Logger* DecoderFile::log = LoggerFactory::getLogger("DecoderFile");
