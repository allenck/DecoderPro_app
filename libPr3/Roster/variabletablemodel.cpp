#include "variabletablemodel.h"
#include "rosterentry.h"
#include "valuequalifier.h"
#include "compositevariablevalue.h"
#include "decvariablevalue.h"
#include "hexvariablevalue.h"
#include "indexedenumvariablevalue.h"
#include "indexedvariablevalue.h"
#include "longaddrvariablevalue.h"
#include "shortaddrvariablevalue.h"
#include "speedtablevarvalue.h"
#include "splitvariablevalue.h"
#include "constantvalue.h"
#include "qualifiercombiner.h"
#include "decoderfile.h"
#include "indexedpairvariablevalue.h"
#include "speedtablevarvalue.h"
#include "qualifieradder.h"
#include "xmlinclude.h"

VariableTableModel::VariableTableModel(QObject *parent) :
    AbstractTableModel(parent)
{
}
/**
 * Table data model for display of variables in symbolic programmer.
 * Also responsible for loading from the XML file...
 *
 * @author      Bob Jacobsen        Copyright (C) 2001, 2006, 2010
 * @author      Howard G. Penny     Copyright (C) 2005
 * @author      Daniel Boudreau     Copyright (C) 2007
 * @author      Dave Heap           Copyright (C) 2012 Added support for Marklin mfx style speed table
 * @version     $Revision: 22629 $
 */
//public class VariableTableModel extends AbstractTableModel implements ActionListener, PropertyChangeListener {


/** Defines the columns; values understood are:
 *  "Name", "Value", "Range", "Read", "Write", "Comment", "CV", "Mask", "State"
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // OK until Java 1.6 allows cheap array copy
/*public*/ VariableTableModel::VariableTableModel(QLabel* status, QStringList h, CvTableModel* cvModel, QObject *parent) :
AbstractTableModel(parent)
{
//super();
log = new Logger("VariableTableModel");
//log->setDebugEnabled(true);
_status = status;
_cvModel = cvModel;
//_indxCvModel = iCvModel;
headers = h;
rowVector = new QVector<VariableValue*>();
_writeButtons = new QVector<QPushButton*>();
_readButtons = new QVector<QPushButton*>();
}

// basic methods for AbstractTableModel implementation
/*public*/ int VariableTableModel::rowCount(const QModelIndex &parent) const
{
    return rowVector->size();
}

/*public*/ int VariableTableModel::columnCount(const QModelIndex &parent) const
{ return headers.length();}

/*public*/ QString VariableTableModel::getColumnName(int col) {
    if (log->isDebugEnabled()) log->debug("getColumnName "+QString::number(col));
    return headers[col];
}

/*public*/ QString VariableTableModel::getColumnClass(int col) {
    // if (log->isDebugEnabled()) log->debug("getColumnClass "+QString::number(col));
    if (headers[col]==("Value"))
        return "QLineEdit";
    else if (headers[col]==("Read"))
        return "QPushButton";
    else if (headers[col]==("Write"))
        return "QPushButton";
    else
        return "QString";
}

/*public*/ bool VariableTableModel::isCellEditable(int row, int col) {
    if (log->isDebugEnabled()) log->debug("isCellEditable "+QString::number(col));
    if (headers[col]==("Value"))
        return true;
    else if (headers[col]==("Read"))
        return true;
    else if (headers[col]==("Write")
             && !((rowVector->at(row)))->getReadOnly())
        return true;
    else
        return false;
}

/*public*/ VariableValue* VariableTableModel::getVariable(int row) {
    return (rowVector->at(row));
}

/*public*/ QString VariableTableModel::getLabel(int row) {
    return (rowVector->at(row))->label();
}

/*public*/ QString VariableTableModel::getItem(int row) {
    return (rowVector->at(row))->item();
}

/*public*/ QString VariableTableModel::getCvName(int row) {
    return (rowVector->at(row))->cvName();
}

/*public*/ QString VariableTableModel::getValString(int row) {
    return (rowVector->at(row))->getValueString();
}

/*public*/ void VariableTableModel::setIntValue(int row, int val) {
    (rowVector->at(row))->setIntValue(val);
}

/*public*/ void VariableTableModel::setState(int row, int val) {
    if (log->isDebugEnabled()) log->debug("setState row: "+QString::number(row)+" val: "+QString::number(val));
    (rowVector->at(row))->setState(val);
}

/*public*/ int VariableTableModel::getState(int row) {
    return (rowVector->at(row))->getState();
}

/*
 * Request a "unique representation", e.g. something we can show
 * for the row-th variable.
 */
/*public*/ QWidget* VariableTableModel::getRep(int row, QString format) {
    VariableValue* v = rowVector->at(row);
//    if(qobject_cast<DecVariableValue*>(v) != NULL)
//        return ((DecVariableValue*)v)->getNewRep(format);
//    else
//    if(qobject_cast<EnumVariableValue*>(v) != NULL)
//        return ((EnumVariableValue*)v)->getNewRep(format);
//    else
//    if(qobject_cast<ShortAddrVariableValue*>(v) != NULL)
//        return ((ShortAddrVariableValue*)v)->getNewRep(format);
//    else
//    if(qobject_cast<LongAddrVariableValue*>(v) != NULL)
//        return ((LongAddrVariableValue*)v)->getNewRep(format);
//    else
//    if(qobject_cast<SpeedTableVarValue*>(v) != NULL)
//     return ((SpeedTableVarValue*)v)->getNewRep(format);
//    else
    return v->getNewRep(format);
}

/*public*/ QVariant VariableTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
    // if (log->isDebugEnabled()) log->debug("getValueAt "+row+" "+col);
    if (row >= rowVector->size()){
        log->debug("row greater than row vector");
        return "Error";
    }
    VariableValue* v = rowVector->at(row);
    if (v == NULL){
        log->debug("v is NULL!");
        return "Error value";
    }
    if (headers[col]==("Value"))
        return VPtr<QWidget>::asQVariant(v->getCommonRep());
    else if (headers[col]==("Read"))
        return VPtr<QPushButton>::asQVariant(_readButtons->at(row));
    else if (headers[col]==("Write"))
        return VPtr<QPushButton>::asQVariant(_writeButtons->at(row));
    else if (headers[col]==("CV"))
        return v->getCvNum();
    else if (headers[col]==("Name"))
        return v->label();
    else if (headers[col]==("Comment"))
        return v->getComment();
    else if (headers[col]==("Mask"))
        return v->getMask();
    else if (headers[col]==("State")) {
        int state = v->getState();
        switch (state) {
        case CvValue::UNKNOWN:  return "Unknown";
        case CvValue::READ:     return "Read";
        case CvValue::EDITED:   return "Edited";
        case CvValue::STORED:   return "Stored";
        case CvValue::FROMFILE: return "From file";
        default: return "inconsistent";
        }
    }
    else if (headers[col]==("Range"))
        return v->rangeVal();
 }
 return QVariant();
}

/*public*/ bool VariableTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
    if (log->isDebugEnabled()) log->debug("setvalueAt "+QString::number(row)+" "+QString::number(col)+" "+value.toString());
    setFileDirty(true);
    return true;
}

/**
 * Load one row in the VariableTableModel,
 * by reading in the Element containing its
 * definition.
 * <p>
 * Invoked from DecoderFile
 * @param row number of row to fill
 * @param e Element of type "variable"
 */
/*public*/ void VariableTableModel::setRow(int row, QDomElement e)
{
 // get the values for the VariableValue ctor
 //QString name = LocaleSelector.attribute(e, "label"); 	// Note the name variable is actually the label attribute
 QString name = e.attribute("label");
 if (log->isDebugEnabled()) log->debug("Starting to setRow \""+name+"\"");
 QString item = ( e.attribute("item")!="" ?
                    e.attribute("item") :
                "");
 // as a special case, if no item, use label
 if (item == "")
 {
  item = e.attribute("label");
  log->debug("no item attribute for \""+item+"\"");
 }
 // as a special case, if no label, use item
 if (name == "")
 {
  name = item;
  if(log->isDebugEnabled()) log->debug("no label attribute for \""+item+"\"");
 }

 QString comment = "";
 if (e.attribute("comment") != "")
  comment = e.attribute("comment");
 QString CV = "";
 if (e.attribute("CV") != "")
  CV = e.attribute("CV");
 QString mask = NULL;
 if (e.attribute("mask") != "")
  mask = e.attribute("mask");
 else
 {
  mask ="VVVVVVVV";
 }

 bool readOnly = e.attribute("readOnly")!="" ? e.attribute("readOnly")==("yes") : false;
 bool infoOnly = e.attribute("infoOnly")!="" ? e.attribute("infoOnly")==("yes") : false;
 bool writeOnly = e.attribute("writeOnly")!="" ? e.attribute("writeOnly")==("yes") : false;
 bool opsOnly = e.attribute("opsOnly")!="" ?e.attribute("opsOnly")==("yes") : false;

 // Ops mode doesn't allow reads, therefore we must disable read buttons
 if (_cvModel->getProgrammer() != NULL
            && !_cvModel->getProgrammer()->getCanRead())
 {
  // can't read, so adjust
  if (readOnly)
  {
   readOnly = false;
   infoOnly = true;
  }
  if (!infoOnly)
  {
   writeOnly = true;
  }
 }


 QPushButton* bw = new QPushButton("Write");
 _writeButtons->append(bw);
 QPushButton* br = new QPushButton("Read");
 _readButtons->append(br);
 setButtonsReadWrite(readOnly, infoOnly, writeOnly, bw, br, row);

 if (_cvModel == NULL)
 {
  log->error("CvModel reference is NULL; cannot add variables");
        return;
 }
 if (CV>0)   // some variables have no CV per se

 _cvModel->addCV(CV, readOnly, infoOnly, writeOnly);

 // decode and handle specific types
 QDomElement child;
 VariableValue* v = NULL;
// if(!(child=e.firstChildElement("xi:include")).isNull())
// {
//  e.replaceChild(XmlInclude::processInclude(child), child);
// }
 if ( !(child = e.firstChildElement("decVal")).isNull())
 {
  v = processDecVal(child, name, comment, readOnly, infoOnly, writeOnly, opsOnly, CV, mask, item);

 }
 else if ( !(child = e.firstChildElement("hexVal")).isNull())
 {
  v = processHexVal(child, name, comment, readOnly, infoOnly, writeOnly, opsOnly, CV, mask, item);

 }
 else if ( !(child = e.firstChildElement("enumVal")).isNull())
 {
  v = processEnumVal(child, name, comment, readOnly, infoOnly, writeOnly, opsOnly, CV, mask, item);

 }
 else if ( !(child = e.firstChildElement("compositeVal")).isNull())
 {
  // loop over the choices
  v = processCompositeVal(child, name, comment, readOnly, infoOnly, writeOnly, opsOnly, CV, mask, item);

 }
 else if ( !(child = e.firstChildElement("speedTableVal")).isNull())
 {
  v = processSpeedTableVal(child, CV, readOnly, infoOnly, writeOnly, name, comment, opsOnly, mask, item);

 }
 else if ( !(child = e.firstChildElement("longAddressVal")).isNull())
 {
  v = processLongAddressVal(CV, readOnly, infoOnly, writeOnly, name, comment, opsOnly, mask, item);

 }
 else if ( !(child = e.firstChildElement("shortAddressVal")).isNull())
 {
  v = processShortAddressVal(name, comment, readOnly, infoOnly, writeOnly, opsOnly, CV, mask, item, child);
 }
 else if ( !(child = e.firstChildElement("splitVal")).isNull())
 {
  v = processSplitVal(child, CV, readOnly, infoOnly, writeOnly, name, comment, opsOnly, mask, item);
 }
 else
 {
  log->error(tr("VariableTableModel: variable type %1 is not valid").arg(e.firstChild().toElement().tagName()));
  reportBogus();
  return;
 }

 processModifierElements(e,v);

 setToolTip(e, v);

 // record new variable, update state, hook up listeners
 rowVector->append(v);
 v->setState(VariableValue::FROMFILE);
 v->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(v->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 // set to default value if specified (CV load may later override this)
 if (setDefaultValue(e, v))
 {
  _cvModel->getCvByNumber(CV)->setState(VariableValue::FROMFILE);  // correct for transition to "edited"
 }
}

/**
 * If there are any modifier elements, process them
 * by e.g. setting attributes on the VariableValue
 */
/*protected*/ void VariableTableModel::processModifierElements(QDomElement e, VariableValue* v)
{
 VTQualifierAdder* qa = new VTQualifierAdder(v);
 // {
 //                protected Qualifier createQualifier(VariableValue var, String relation, String value) {
 //                    return new ValueQualifier(v, var, Integer.parseInt(value), relation);
 //                }
 //                protected void addListener(java.beans.PropertyChangeListener qc) {
 //                    v.addPropertyChangeListener(qc);
 //                }
 //            };

 qa->processModifierElements(e, this);
}
VTQualifierAdder::VTQualifierAdder(VariableValue *v) { this->v = v;}
/*protected*/ Qualifier* VTQualifierAdder::createQualifier(VariableValue* var, QString relation, QString value)
{
 return new ValueQualifier(v, var, value.toInt(), relation);
}
/*protected*/ void VTQualifierAdder::addListener(PropertyChangeListener* qc) {
//    v->addPropertyChangeListener(qc);
//    connect(v, SIGNAL(notifyPropertyChange(PropertyChangeEvent*)), this, SLOT());
}

/**
 * Create an IndexedVariableValue object of a specific
 * type from a describing element.
 * @return NULL if no valid element
 * @throws java.lang.NumberFormatException
 */
/*protected*/ VariableValue* VariableTableModel::createIndexedVariableFromElement(QDomElement e, int row, QString name, QString comment, QString cvName, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString cv, QString mask, QString item, QString productID) throw (NumberFormatException)
{
 VariableValue* iv = NULL;
 QDomElement child;
 if (!(child = e.firstChildElement("indexedVal")).isNull())
 {
  iv = processIndexedVal(child, row, name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, item);
 }
 else if (!(child = e.firstChildElement("ienumVal")).isNull())
 {
  iv = processIEnumVal(child, row, name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, item, productID);
 }
 else if (!(child = e.firstChildElement("indexedPairVal")).isNull())
 {
  iv = processIndexedPairVal(child, row, readOnly, infoOnly, writeOnly, name, comment, cvName, opsOnly, cv, mask, item);
 }
 return iv;
}

/**
 * If there's a "default" attribute, set that value to start
 * @return true if the value was set
 */
/*protected*/ bool VariableTableModel::setDefaultValue(QDomElement e, VariableValue* v) {
    QString a;
    if ( (a = e.attribute("default")) != "") {
        QString val = a;
        v->setIntValue(val.toInt());
        return true;
    }
    return false;
}
/*public*/ QString VariableTableModel::piCv() {return _piCv;}
/*public*/ QString VariableTableModel::siCv() {return _siCv;}

/**
 * Load one row in the IndexedVariableTableModel,
 * by reading in the Element containing its
 * definition.
 * <p>
 * Invoked from DecoderFile
 * @param row number of row to fill
 * @param e Element of type "variable"
 */
/*public*/ int VariableTableModel::setIndxRow(int row, QDomElement e, QString productID)
{
// if (DecoderFile::isIncluded(e, productID) == false)
// {
//  if (log->isDebugEnabled()) log->debug("include not match, return row - 1 ="+(row-1));
//   return row - 1;
// }

 // get the values for the VariableValue ctor
 //QString name = LocaleSelector.attribute(e, "label"); 	// Note the name variable is actually the label attribute
 QString name = e.attribute("label");
 if (log->isDebugEnabled()) log->debug("Starting to setIndexedRow \""+name+"\"");
    QString cvName = e.attribute("CVname");
    QString item = ( e.attribute("item")!="" ?
                    e.attribute("item") :
                "");
    QString comment = "";
    if (e.attribute("comment") != NULL)
        comment = e.attribute("comment");
    int piVal = e.attribute("PI").toInt();
    int siVal = ( e.attribute("SI") != NULL ?
                  e.attribute("SI").toInt() :
                  -1);
    QString cv = e.attribute("CV");
    QString mask = NULL;
    if (e.attribute("mask") != "")
        mask = e.attribute("mask");
    else {
        mask ="VVVVVVVV";
    }

    bool readOnly = e.attribute("readOnly")!=NULL ?
                            e.attribute("readOnly")==("yes") : false;
    bool infoOnly = e.attribute("infoOnly")!=NULL ?
                            e.attribute("infoOnly")==("yes") : false;
    bool writeOnly = e.attribute("writeOnly")!=NULL ?
                            e.attribute("writeOnly")==("yes") : false;
    bool opsOnly = e.attribute("opsOnly")!=NULL ?
                            e.attribute("opsOnly")==("yes") : false;


    QPushButton* br = new QPushButton("Read");
    _readButtons->append(br);
    QPushButton* bw = new QPushButton("Write");
    _writeButtons->append(bw);

    setButtonsReadWrite(readOnly, infoOnly, writeOnly, bw, br, row);

    if (_indxCvModel == NULL) {
        log->error("IndexedCvModel reference is NULL; can not add variables");
        return -1;
    }

    // add the information to the CV model
    int _newRow = _indxCvModel->addIndxCV(cvName, _piCv, piVal, _siCv, siVal, cv, readOnly, infoOnly, writeOnly);
    if( _newRow != row) {
        row = _newRow;
        if (log->isDebugEnabled()) log->debug("new row is "+QString::number(_newRow)+", row was "+QString::number(row));
    }

    // Find and process the specific content types
    VariableValue* iv;
    iv = createIndexedVariableFromElement(e, row, name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, item, productID);

    if (iv == NULL) {
       // trouble reporting
     log->error("createIndexedVariableFromElement is null");
       reportBogus();
        return -1;
    }

    processModifierElements(e,iv);

    setToolTip(e, iv);

    // record new variable, update state, hook up listeners
    rowVector->append(iv);
    iv->setState(VariableValue::FROMFILE);
    iv->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(iv->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    // set to default value if specified (CV load may later override this)
    QString a;
    if ((a = e.attribute("default")) != "") {
        QString val = a;
        if (log->isDebugEnabled()) log->debug("Found default value: "+val+" for "+name);
        iv->setIntValue(val.toInt());
        if (_indxCvModel->getCvByRow(row)->getInfoOnly()) {
            _indxCvModel->getCvByRow(row)->setState(VariableValue::READ);
        } else {
            _indxCvModel->getCvByRow(row)->setState(VariableValue::FROMFILE); // correct for transition to "edited"
        }
    } else {
        _indxCvModel->getCvByRow(row)->setState(VariableValue::UNKNOWN);
    }
    return row;
}

/*protected*/ VariableValue* VariableTableModel::processCompositeVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) {
    VariableValue* v;
    //@SuppressWarnings("unchecked")
    QDomNodeList lChoice = child.elementsByTagName("compositeChoice");
    CompositeVariableValue* v1 = new CompositeVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, 0, lChoice.size() - 1, _indxCvModel->allIndxCvMap(), _status, item);
    v = v1; // v1 is of CompositeVariableType, so doesn't need casts
    // loop over the choices
    for (int k = 0; k < lChoice.size(); k++) {
        // Create the choice
        QDomElement choiceElement = lChoice.at(k).toElement();
        //QString choice = LocaleSelector.attribute(choiceElement, "choice");
        QString choice = choiceElement.attribute("choice");
        v1->addChoice(choice);
        // for each choice, capture the settings
        //@SuppressWarnings("unchecked")
        QDomNodeList lSetting = choiceElement.elementsByTagName("compositeSetting");
        for (int n = 0; n < lSetting.size(); n++) {
            QDomElement settingElement = lSetting.at(n).toElement();
            //QString varName = LocaleSelector.attribute(settingElement, "label");
            QString varName = settingElement.attribute("label");
            QString value = settingElement.attribute("value");
            v1->addSetting(choice, varName, findVar(varName), value);
        }
    }
    v1->lastItem();
    return v;
}

/*protected*/ VariableValue* VariableTableModel::processDecVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) throw (NumberFormatException) {
    VariableValue* v;
    QString a;
    int minVal = 0;
    int maxVal = 255;
    if ((a = child.attribute("min")) != "") {
        minVal = a.toInt();
    }
    if ((a = child.attribute("max")) != "") {
        maxVal = a.toInt();
    }
    v = new DecVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, item);
    return v;
}


/*protected*/ VariableValue* VariableTableModel::processEnumVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) throw (NumberFormatException)
{
 int count = 0;
 //IteratorIterable<Content> iterator = child.getDescendants();
 QDomNodeList nl = child.childNodes();
 //while (iterator.hasNext())
 for(int i = 0; i < nl.count(); i++)
 {
  //Object ex = iterator.next();
  QDomNode node = nl.at(0);
  //if (ex instanceof Element)
  if(!node.toElement().isNull())
  {
   //if (((Element) ex).getName().equals("enumChoice"))
   if(node.toElement().tagName() == "enumChoice")
   {
    count++;
   }
  }
 }

 VariableValue* v;
 EnumVariableValue* v1 = new EnumVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, 0, count, _cvModel->allCvMap(), _status, item);
 v = v1; // v1 is of EnunVariableValue type, so doesn't need casts

 v1->nItems(count);
 handleENumValChildren(child, v1);
 v1->lastItem();
 return v;
}

/**
 * Recursively walk the child enumChoice elements, working through the
 * enumChoiceGroup elements as needed.
 */
/*protected*/ void VariableTableModel::handleENumValChildren(QDomElement e, EnumVariableValue* var)
{
    //List<Element> local = e.getChildren();
 QDomNodeList local = e.childNodes();
 for (int k = 0; k < local.size(); k++)
 {
     //Element el = local.get(k);
  QDomElement el = local.at(k).toElement();
  if (el.tagName()==("enumChoice"))
  {
   QString valAttr = el.attribute("value");
   if (valAttr == "")
   {
       //var->addItem(LocaleSelector.getAttribute(el, "choice"));
    var->addItem(el.attribute("choice"));
   }
   else
   {
//                var->addItem(LocaleSelector.getAttribute(el, "choice"),
//                        Integer.parseInt(valAttr.getValue()));
    var->addItem(el.attribute("choice"),el.text().toInt());
   }
  }
  else if (el.tagName()==("enumChoiceGroup"))
  {
      //var->startGroup(LocaleSelector.getAttribute(el, "name"));
   var->startGroup(el.attribute("name"));
   handleENumValChildren(el, var);
   var->endGroup();
  }
 }
}

/*protected*/ VariableValue* VariableTableModel::processHexVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) throw (NumberFormatException) {
    VariableValue* v;
    QString a;
    int minVal = 0;
    int maxVal = 255;
    if ((a = child.attribute("min")) != "") {
        minVal = a.toInt(0,16);
    }
    if ((a = child.attribute("max")) != NULL) {
        maxVal =a.toInt(0,16);
    }
    v = new HexVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, item);
    return v;
}

/*protected*/ VariableValue* VariableTableModel::processIEnumVal(QDomElement child, int row, QString name, QString comment, QString cvName, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString cv, QString mask, QString item, QString productID) throw (NumberFormatException) {
    VariableValue* iv;
    //@SuppressWarnings("unchecked")
    QDomNodeList l = child.elementsByTagName("ienumChoice");
    IndexedEnumVariableValue* v1 = new IndexedEnumVariableValue(row, name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, _indxCvModel->allIndxCvMap(), _status, item);
    iv = v1;
    for (int x = 0; x < l.size(); x++) {
        QDomElement ex = l.at(x).toElement();
//        if (DecoderFile::isIncluded(ex, productID) == false) {
//            l.remove(x);
//            x--;
//        }
    }
    v1->nItems(l.size());
    for (int k = 0; k < l.size(); k++) {
        QDomElement enumChElement = l.at(k).toElement();
        // is a value specified?
        QString valAttr = enumChElement.attribute("value");
        if (valAttr == "") {
            //v1->addItem(LocaleSelector.attribute(enumChElement, "choice"));
            v1->addItem(enumChElement.attribute("choice"));
        } else {
            //            v1->addItem(LocaleSelector.attribute(enumChElement, "choice"),
            //                        Integer.parseInt(valAttr.getValue()));
            v1->addItem(enumChElement.attribute("choice"),valAttr.toInt());
        }
    }
    v1->lastItem();
    return iv;
}

/*protected*/ VariableValue* VariableTableModel::processIndexedPairVal(QDomElement child, int row, bool readOnly, bool infoOnly, bool writeOnly, QString name, QString comment, QString cvName, bool opsOnly, QString cv, QString mask, QString item) throw (NumberFormatException)
{
    VariableValue* iv;
    int minVal = 0;
    int maxVal = 255;
    QString a;
    if ((a = child.attribute("min")) != "") {
        minVal =a.toInt();
    }
    if ((a = child.attribute("max")) != "") {
        maxVal = a.toInt();
    }
    int factor = 1;
    if ((a = child.attribute("factor")) != "") {
        factor = a.toInt();
    }
    int offset = 0;
    if ((a = child.attribute("offset")) != "") {
        offset = a.toInt();
    }
    QString uppermask = "VVVVVVVV";
    if ((a = child.attribute("upperMask")) != "") {
        uppermask = a;
    }
    QString highCVname = "";
    QString highCVnumber = "";
    int highCVpiVal = -1;
    int highCVsiVal = -1;
    if ((a = child.attribute("highCVname")) != "")
    {
     highCVname = a;
     int x = highCVname.indexOf('.');
     highCVnumber = highCVname.mid(0, x);
     int y = highCVname.indexOf('.', x + 1);
     if (y > 0)
     {
      highCVpiVal = highCVname.mid(x + 1, y).toInt();
      x = highCVname.lastIndexOf('.');
      highCVsiVal = highCVname.mid(x + 1).toInt();
     }
     else
     {
      x = highCVname.lastIndexOf('.');
      highCVpiVal = highCVname.mid(x + 1).toInt();
     }
    }
// ensure highCVnumber indexed CV exists
if (log->isDebugEnabled()) log->debug("Add high indexed CV "+highCVname);
_indxCvModel->addIndxCV(highCVname, _piCv, highCVpiVal, _siCv, highCVsiVal, highCVnumber, readOnly, infoOnly, writeOnly);

// order
bool upperFirst = false;
if ((a = child.attribute("order")) != "") {
if (a==("highFirst")) upperFirst = true;
}

iv = new IndexedPairVariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, minVal, maxVal, _indxCvModel->allIndxCvMap(), _status, item, highCVname, factor, offset, uppermask, upperFirst);
return iv;
}

/*protected*/ VariableValue* VariableTableModel::processIndexedVal(QDomElement child, int row, QString name, QString comment, QString cvName, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString cv, QString mask, QString item) throw (NumberFormatException) {
VariableValue* iv;
int minVal = 0;
int maxVal = 255;
QString a;
if ((a = child.attribute("min")) != "") {
minVal = a.toInt();
}
if ((a = child.attribute("max")) != "") {
maxVal = a.toInt();
}
iv = new IndexedVariableValue(row, name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, minVal, maxVal, _indxCvModel->allIndxCvMap(), _status, item);

    if ((a = child.attribute("min")) != "") {
        minVal = a.toInt();
    }
    if ((a = child.attribute("max")) != "") {
        maxVal = a.toInt();
    }
    iv = new IndexedVariableValue(row, name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cv, mask, minVal, maxVal, _indxCvModel->allIndxCvMap(), _status, item);
    return iv;
}

/*protected*/ VariableValue* VariableTableModel::processLongAddressVal(QString CV, bool readOnly, bool infoOnly, bool writeOnly, QString name, QString comment, bool opsOnly, QString mask, QString item) {
    VariableValue* v;
    int minVal = 0;
    int maxVal = 255;
    _cvModel->addCV(QString::number(CV.toInt() + 1), readOnly, infoOnly, writeOnly); // ensure 2nd CV exists
    v = new LongAddrVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, item);
    return v;
}

/*protected*/ VariableValue* VariableTableModel::processShortAddressVal(QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item, QDomElement child) {
    VariableValue* v;
    ShortAddrVariableValue* v1 = new ShortAddrVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, _cvModel->allCvMap(), _status, item);
    v = v1;
    // get specifics if any
    //@SuppressWarnings("unchecked")
    QDomNodeList l = child.elementsByTagName("shortAddressChanges");
    for (int k = 0; k < l.size(); k++) {
        try {
            v1->setModifiedCV(l.at(k).toElement().attribute("cv"));
        } catch (DataConversionException e1) {
            log->error("invalid cv attribute in short address element of decoder file");
        }
    }
    return v;
}

/*protected*/ VariableValue* VariableTableModel::processSpeedTableVal(QDomElement child, QString CV, bool readOnly,
                                                                      bool infoOnly, bool writeOnly, QString name,
                                                                      QString comment, bool opsOnly, QString mask,
                                                                      QString item) throw (NumberFormatException)
{
 VariableValue* v;
 QString a;
 int minVal = 0;
 int maxVal = 255;
 if ((a = child.attribute("min")) != "")
 {
  minVal = a.toInt();
 }
 if ((a = child.attribute("max")) != "")
 {
  maxVal = a.toInt();
 }
 QString entriesAttr = child.attribute("entries");
 int entries = 28;
 try
 {
  if (entriesAttr != NULL)
  {
   entries = entriesAttr.toInt();
  }
 }
 catch (DataConversionException e1)
 {
 }
 QString ESUAttr = child.attribute("mfx");
 bool mfxFlag = false;
 try
 {
  if (ESUAttr != "")
  {
   //mfxFlag = (ESUAttr()==QString("true")?true:false);
   if(ESUAttr == "true")
    mfxFlag = true;
   else
    mfxFlag = false;
  }
 }
 catch (DataConversionException e1)
 {
 }
 // ensure all CVs exist
 for (int i = 0; i < entries; i++)
 {
  _cvModel->addCV(QString::number(CV.toInt()+i), readOnly, infoOnly, writeOnly);
 }
 if (mfxFlag)
 {
  _cvModel->addCV(QString::number(2), readOnly, infoOnly, writeOnly);
  _cvModel->addCV(QString::number (5), readOnly, infoOnly, writeOnly);
 }
 v = new SpeedTableVarValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, item, entries, mfxFlag);
 return v;
}

/*protected*/ VariableValue* VariableTableModel::processSplitVal(QDomElement child, QString CV, bool readOnly, bool infoOnly, bool writeOnly, QString name, QString comment, bool opsOnly, QString mask, QString item) throw (NumberFormatException) {
    VariableValue* v;
    QString a;
    int minVal = 0;
    int maxVal = 255;
    if ((a = child.attribute("min")) != "") {
        minVal = a.toInt();
    }
    if ((a = child.attribute("max")) != "") {
        maxVal = a.toInt();
    }
    int highCV = CV.toInt() + 1;
    if ((a = child.attribute("highCV")) != "") {
        highCV = a.toInt();
    }
    int factor = 1;
    if ((a = child.attribute("factor")) != "") {
        factor = a.toInt();
    }
    int offset = 0;
    if ((a = child.attribute("offset")) != "") {
        offset = a.toInt();
    }
    QString uppermask = "VVVVVVVV";
    if ((a = child.attribute("upperMask")) != "") {
        uppermask = a;
    }
    _cvModel->addCV(QString::number(highCV), readOnly, infoOnly, writeOnly); // ensure 2nd CV exists
    v = new SplitVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, item, highCV, factor, offset, uppermask);
    return v;
}

/*protected*/ void VariableTableModel::setButtonsReadWrite(bool readOnly, bool infoOnly, bool writeOnly, QPushButton* bw, QPushButton* br, int /*row*/) {
    if (readOnly || infoOnly) {
        // readOnly or infoOnly, config write, read buttons
        if (writeOnly) {
            bw->setEnabled(true);
//            bw->setActionCommand("W" + row);
//            bw->addActionListener(this);
        } else {
            bw->setEnabled(false);
        }
        if (infoOnly) {
            br->setEnabled(false);
        } else {
//            br->setActionCommand("R" + row);
//            br->addActionListener(this);
        }
    } else {
        // not readOnly or infoOnly, config write, read buttons
//        bw->setActionCommand("W" + row);
//        bw->addActionListener(this);
        if (writeOnly) {
            br->setEnabled(false);
        } else {
//            br->setActionCommand("R" + row);
//            br->addActionListener(this);
        }
    }
}

/*protected*/ void VariableTableModel::setToolTip(QDomElement e, VariableValue* v) {
    // back to general processing
    // add tooltip text if present
    {
        QString a;
        if ((a = e.attribute("tooltip")) != "") {
            v->setToolTipText(a);
        }
    }
}

void VariableTableModel::reportBogus() {
    log->error("Did not find a valid variable type");
}

/**
 * Configure from a constant.  This is like setRow (which processes
 * a variable Element).
 */
/*public*/ void VariableTableModel::setConstant(QDomElement e) {
    // get the values for the VariableValue ctor
    QString stdname = e.attribute("item");
    if (log->isDebugEnabled()) log->debug("Starting to setConstant \""+stdname+"\"");

    //QString name = LocaleSelector.attribute(e, "label");
    QString name = e.attribute("label");
    if (name == NULL || name==("")) name = stdname;

    //QString comment = LocaleSelector.attribute(e, "comment");
    QString comment = e.attribute("comment");

    QString mask = "";

    // intrinsically readOnly, so use just that branch
    QPushButton* bw = new QPushButton();
    _writeButtons->append(bw);

    // config read button as a dummy - there's really nothing to read
    QPushButton* br = new QPushButton("Read");
    _readButtons->append(br);

    // no CV references are added here

    // have to handle various value types, see "snippet"
    QString a;

    // set to default value if specified (CV load will later override this)
    int defaultVal = 0;
    if ( (a = e.attribute("default")) != "") {
        QString val = a;
        if (log->isDebugEnabled()) log->debug("Found default value: "+val+" for "+stdname);
        defaultVal = val.toInt();
        if ( stdname.compare("PICV") == 0 ) {
            _piCv = val.toInt();
        } else if ( stdname.compare("SICV") == 0 ) {
            _siCv =val.toInt();
        }
    }

    // create the specific object

    ConstantValue* v = new ConstantValue(name, comment, "", true, true, false, false,
                                        0, mask, defaultVal, defaultVal,
                                        _cvModel->allCvMap(), _status, stdname);

    // record new variable, update state, hook up listeners
    rowVector->append(v);
    v->setState(VariableValue::FROMFILE);
    v->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(v->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    // set to default value if specified (CV load will later override this)
    if ( (a = e.attribute("default")) != "") {
        QString val = a;
        if (log->isDebugEnabled()) log->debug("Found default value: "+val+" for "+name);
        v->setIntValue(defaultVal);
    }
}

/*public*/ void VariableTableModel::newDecVariableValue(QString name, QString CV, QString mask,
                                bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly) {
    setFileDirty(true);
    QString comment = "";
    int minVal = 0;
    int maxVal = 255;
    _cvModel->addCV(""+CV, readOnly, infoOnly, writeOnly);

    //int row = getRowCount();

    // config write button
    QPushButton* bw = new QPushButton("Write");
//    bw->setActionCommand("W"+row);
//    bw->addActionListener(this);
    _writeButtons->append(bw);

    // config read button
    QPushButton* br = new QPushButton("Read");
//    br->setActionCommand("R"+row);
//    br->addActionListener(this);
    _readButtons->append(br);

    VariableValue* v = new DecVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly,
                                           CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, NULL);
    rowVector->append(v);
    v->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(v->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void VariableTableModel::actionPerformed(ActionEvent* e) {
    if (log->isDebugEnabled()) log->debug("action performed,  command: "+e->getActionCommand());
    setFileDirty(true);
    QChar b = e->getActionCommand().at(0);
    int row = e->getActionCommand().mid(1).toInt();
    if (log->isDebugEnabled()) log->debug("event on "+QString(&b)+" row "+QString::number(row));
    if (b=='R') {
        // read command
        read(row);
    } else {
        // write command
        write(row);
    }
}

/**
 * Command reading of a particular variable
 * @param i row number
 */
/*public*/ void VariableTableModel::read(int i) {
    VariableValue* v = rowVector->at(i);
    v->readAll();
}

/**
 * Command writing of a particular variable
 * @param i row number
 */
/*public*/ void VariableTableModel::write(int i) {
    VariableValue* v = rowVector->at(i);
    v->writeAll();
}

/*public*/ void VariableTableModel::propertyChange(PropertyChangeEvent* e)
{
 if (log->isDebugEnabled())
 {
  log->debug("prop changed "+e->getPropertyName()
                  +" new value: "+e->getNewValue().toString()
                  +(e->getPropertyName()==("State") ? (" ("+VariableValue::stateNameFromValue((e->getNewValue()).toInt())+") "):" ")
                  +" Source "+e->getSource()->metaObject()->className());
 }
 if (e->getNewValue().isNull() )
 {
  log->error("new value of "+e->getPropertyName()+" should not be NULL!");
//        (new Exception()).printStackTrace();
 }
 // set dirty only if edited or read
 if (e->getPropertyName()==("State")
            && ( e->getNewValue()).toInt() == CvValue::READ
            || e->getPropertyName()==("State")
            && ( e->getNewValue()).toInt() == CvValue::EDITED)
    {
        setFileDirty(true);

    }
    fireTableDataChanged();
}

/*public*/ void VariableTableModel::configDone() {
    fireTableDataChanged();
}

/**
 * Represents any change to values, etc, hence rewriting the
 * file is desirable.
 */
/*public*/ bool VariableTableModel::fileDirty() {
    return _fileDirty;
}
/*public*/ void VariableTableModel::setFileDirty(bool b) {
    _fileDirty = b;
}

/**
 * Check for change to values, etc, hence rewriting the
 * decoder is desirable.
 */
/*public*/ bool VariableTableModel::decoderDirty() {
    int len = rowVector->size();
    for (int i=0; i< len; i++) {
        if (((rowVector->at(i)))->getState() == CvValue::EDITED ) return true;
    }
    return false;
}

/*public*/ void VariableTableModel::resetStatus(int newStatus)
{
 int len = rowVector->size();
 for (int i=0; i< len; i++)
 {
  if (((rowVector->at(i)))->getState() == CvValue::EDITED )
  {
   rowVector->at(i)->setState(newStatus);
  }
 }
 _cvModel->resetDecoderDirty(newStatus);

}

/*public*/ VariableValue* VariableTableModel::findVar(QString name) {
    for (int i=0; i<rowCount(QModelIndex()); i++) {
        if (name==(getItem(i)))  return getVariable(i);
        if (name==(getLabel(i))) return  getVariable(i);
    }
    return NULL;
}

/*public*/ int VariableTableModel::findVarIndex(QString name)
{
 for (int i=0; i<rowCount(QModelIndex()); i++)
 {
        if (name==(getItem(i))) return i;
        if (name==(getLabel(i))) return i;
        if (name==("CV"+getCvName(i))) return i;
//            try {
//                if (name==("CV"+((IndexedEnumVariableValue)rowVector->at(i)).cvName())) return i;
//            } catch (Exception e){}
    }
    return -1;
}

/*public*/ void VariableTableModel::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");

    // remove buttons
//        for (int i = 0; i<_writeButtons.size(); i++) {
//            _writeButtons->at(i).removeActionListener(this);
//        }
//        for (int i = 0; i<_readButtons.size(); i++) {
//            _readButtons->at(i).removeActionListener(this);
//        }

    // remove variables listeners
    for (int i = 0; i<rowVector->size(); i++) {
        VariableValue* v = rowVector->at(i);
        v->removePropertyChangeListener((PropertyChangeListener*)this);
        v->dispose();
    }

    headers = QStringList();

    rowVector->clear();
    rowVector = NULL;

    _cvModel = NULL;
    _indxCvModel = NULL;

    _writeButtons->clear();
    _writeButtons = NULL;

    _readButtons->clear();
    _readButtons = NULL;

    _status = NULL;
}
