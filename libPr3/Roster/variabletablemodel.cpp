#include "variabletablemodel.h"
#include "rosterentry.h"
#include "valuequalifier.h"
#include "compositevariablevalue.h"
#include "decvariablevalue.h"
#include "hexvariablevalue.h"
#include "longaddrvariablevalue.h"
#include "shortaddrvariablevalue.h"
#include "speedtablevarvalue.h"
#include "splitvariablevalue.h"
#include "constantvalue.h"
#include "qualifiercombiner.h"
#include "decoderfile.h"
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
/*public*/ VariableTableModel::VariableTableModel(JLabel* status, QStringList h, CvTableModel* cvModel, QObject *parent) :
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
/*public*/ int VariableTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return rowVector->size();
}
/*public*/ int VariableTableModel::getRowCount() const
{
 return rowCount(QModelIndex());
}
/*public*/ int VariableTableModel::columnCount(const QModelIndex &/*parent*/) const
{ return headers.length();}

/*public*/ QString VariableTableModel::getColumnName(int col) const {
    if (log->isDebugEnabled()) log->debug("getColumnName "+QString::number(col));
    return headers[col];
}

/*public*/ QString VariableTableModel::getColumnClass(int col) const {
    // if (log->isDebugEnabled()) log->debug("getColumnClass "+QString::number(col));
    if (headers[col]==("Value"))
        return "JTextField";
    else if (headers[col]==("Read"))
        return "JButton";
    else if (headers[col]==("Write"))
        return "JButton";
    else
        return "String";
}

/*public*/ bool VariableTableModel::isCellEditable(int row, int col) const {
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
/*public*/ void VariableTableModel::setRow(int row, QDomElement e, DecoderFile* df)
{
 // get the values for the VariableValue ctor
 _df = df;
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
 * If there's a "default" attribute, set that value to start
 * @return true if the value was set
 */
/*protected*/ bool VariableTableModel::setDefaultValue(QDomElement e, VariableValue* variable) {
    QString a;
    bool set = false;
    if ( (a = e.attribute("default")) != "") {
        QString val = a;
        variable->setIntValue(val.toInt());
        set = true;
    }
    // check for matching child
    QDomNodeList elements = e.elementsByTagName("defaultItem");
    //for (Element defaultItem : elements)
    for(int i=0; i < elements.size(); i++)
    {
     QDomElement defaultItem = elements.at(i).toElement();
        if (_df != nullptr && DecoderFile::isIncluded(defaultItem, _df->getProductID(), _df->getModel(), _df->getFamily(), "", "")) {
            log->debug(tr("element included by productID=%1 model=%2 family=%3").arg(_df->getProductID()).arg(_df->getModel()).arg(_df->getFamily()));
            variable->setValue(defaultItem.attribute("default"));
            return true;
        }
    }
    return set;
}


/*protected*/ VariableValue* VariableTableModel::processCompositeVal(QDomElement child, QString name, QString comment, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString CV, QString mask, QString item) {
 int count = 0;
 //IteratorIterable<Content> iterator = child.getDescendants();
 QDomNodeList content = child.childNodes();
 //while (iterator.hasNext()) {
 for(int i = 0; i<content.size(); i++)
 {
//     Object ex = iterator.next();
//     if (ex instanceof Element) {
  QDomElement ex = content.at(i).toElement();
  //       if (((Element) ex).getName().equals("compositeChoice")) {
  if(ex.tagName() == "compositChoice"){
             count++;
         }
     }
// }

 VariableValue* v;
 CompositeVariableValue* v1 = new CompositeVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, 0, count, _cvModel->allCvMap(), _status, item);
 v = v1; // v1 is of CompositeVariableType, so doesn't need casts

 v1->nItems(count);
 handleCompositeValChildren(child, v1);
 v1->lastItem();
 return v;
}

/**
 * Recursively walk the child compositeChoice elements, working through the
 * compositeChoiceGroup elements as needed.
 * <p>
 * Adapted from handleEnumValChildren for use in LocoIO Legacy tool.
 *
 * @param e Element that's source of info
 * @param var Variable to load
 */
/*protected*/ void VariableTableModel::handleCompositeValChildren(QDomElement e, CompositeVariableValue* var) {
    QDomNodeList local = e.childNodes();
    for (int k = 0; k < local.size(); k++) {
        QDomElement el = local.at(k).toElement();
        log->debug(tr("processing element='%1' name='%2' choice='%3' value='%4'").arg(el.tagName()).arg(/*LocaleSelector.*/el.attribute("name")).arg(el.attribute("choice")).arg(el.attribute("value")));
        if (_df != nullptr && !DecoderFile::isIncluded(el, _df->getProductID(), _df->getModel(), _df->getFamily(), "", "")) {
            log->debug(tr("element excluded by productID=%1 model=%2 family=%3").arg(_df->getProductID()).arg(_df->getModel()).arg(_df->getFamily()));
            continue;
        }
        if (el.tagName() == ("compositeChoice")) {
            // Create the choice
            QString choice = el.attribute("choice"); //el.attribute("choice");
            var->addChoice(choice);
            // for each choice, capture the settings
            QDomNodeList lSetting = el.elementsByTagName("compositeSetting");
            for (int n = 0; n < lSetting.size(); n++) {
                QDomElement settingElement = lSetting.at(n).toElement();
                QString varName = settingElement.attribute("label");//LocaleSelector.getAttribute(settingElement, "label");
                QString value = settingElement.attribute("value");
                var->addSetting(choice, varName, findVar(varName), value);
            }
        } else if (el.tagName() == ("compositeChoiceGroup")) {
            // no tree to manage as in enumGroup
            handleCompositeValChildren(el, var);
        }
        log->debug("element processed");
    }
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
 QDomNodeList local = e.childNodes();
 for (int k = 0; k < local.size(); k++) {
     QDomElement el = local.at(k).toElement();
     log->debug(tr("processing element='%1' name='%2' choice='%3' value='%4'").arg(el.tagName()).arg(el.attribute( "name")).arg(el.attribute( "choice")).arg(el.attribute("value")));
     if (_df != nullptr && !DecoderFile::isIncluded(el, _df->getProductID(), _df->getModel(), _df->getFamily(), "", "")) {
         log->debug(tr("element excluded by productID=%1 model=%2 family=%3").arg(_df->getProductID()).arg(_df->getModel()).arg(_df->getFamily()));
         continue;
     }
     if (el.tagName() == ("enumChoice")) {
         QString valAttr = el.attribute("value");
         if (valAttr == "") {
             var->addItem(el.attribute( "choice"));
         } else {
             var->addItem(el.attribute("choice"),
                     valAttr.toInt());
         }
     } else if (el.tagName() == ("enumChoiceGroup")) {
         var->startGroup(el.attribute("name"));
         handleENumValChildren(el, var);
         var->endGroup();
     }
     log->debug("element processed");
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
    QString highCV = "";

    if ((a = child.attribute("min")) != "") {
        minVal = a.toInt();
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
    QString extra3 = "0";
    if ((a = child.attribute("min")) != "") {
        extra3 = a;
    }
    QString extra4 = /*Long.toUnsignedString*/QString::number(~0);
    if ((a = child.attribute("max")) != "") {
        extra4 = a;
    }
    v = new SplitVariableValue(name, comment, "", readOnly, infoOnly, writeOnly, opsOnly, CV, mask, minVal, maxVal, _cvModel->allCvMap(), _status, item, highCV, factor, offset, uppermask, "", "", extra3, extra4);
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

/*public*/ void VariableTableModel::actionPerformed(JActionEvent* e) {
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

    _writeButtons->clear();
    _writeButtons = NULL;

    _readButtons->clear();
    _readButtons = NULL;

    _status = NULL;
}
