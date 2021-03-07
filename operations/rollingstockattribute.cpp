#include "rollingstockattribute.h"
#include <QVector>
#include "stringutil.h"
#include "jcombobox.h"
#include "logger.h"
#include "propertychangesupport.h"
#include <QtXml>
#include "control.h"
#include "xml.h"

//RollingStockAttribute::RollingStockAttribute(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations {
/**
 * Represents an attribute a rolling stock can have. Some attributes are length,
 * color, type, load, road, owner, model etc.
 *
 * @author Daniel Boudreau Copyright (C) 2014
 * @version $Revision: 25735 $
 */
///*public*/ class RollingStockAttribute {

 /*protected*/ /*static*/ /*final*/ int RollingStockAttribute::MIN_NAME_LENGTH = 4;

 /*public*/ RollingStockAttribute::RollingStockAttribute(QObject *parent) :
  PropertyChangeSupport(this, parent)
 {
  list = QStringList();
  maxNameLength = 0;
  log = new Logger("RollingStockAttribute");
 }

 /*public*/ /*synchronized*/ void RollingStockAttribute::dispose()
 {
  list.clear();
     //TODO The removal of listeners causes the tests to fail.
     // Need to reload all listeners for the tests to work.
     // Only tests currently call dispose()
     // remove all listeners
//		for (java.beans.PropertyChangeListener p : pcs.getPropertyChangeListeners())
//			pcs.removePropertyChangeListener(p);
 }


 /*public*/ QStringList RollingStockAttribute::getNames()
 {
  if (list.size() == 0)
  {
   foreach (QString name, getDefaultNames().split(","))
   {
    list.append(name);
   }
  }
  QVector<QString> names = QVector<QString>(list.size());
  for (int i = 0; i < list.size(); i++)
  {
   names.replace(i,list.at(i));
  }
  return names.toList();
 }

 /*protected*/ QString RollingStockAttribute::getDefaultNames() {
     return "Error"; //  NOI18N overridden
 }

 /*public*/ void RollingStockAttribute::setNames(QStringList names) {
 if (names.length() == 0) {
         return;
     }
     StringUtil::sort(names);
     foreach (QString name, names) {
         if (!list.contains(name)) {
             list.append(name);
         }
     }
 }

 /**
  * Performs number sort before adding to list
  *
  * @param lengths
  */
 /*public*/ void RollingStockAttribute::setValues(QStringList lengths) {
 if (lengths.length() == 0) {
         return;
     }
     //try {
         StringUtil::numberSort(lengths);
//     } catch (NumberFormatException e) {
//         log->error("lengths are not all numeric, list:");
//         for (int i = 0; i < lengths.length; i++) {
//             bool ok;
//                 lengths.at(i).toInt(&ok);
//                 log->error("length " + i + " = " + lengths[i]);
//                 if(!ok)
//                 {
//                 log->error("length " + i + " = " + lengths[i] + " is not a valid number!");
//             }
//         }
//     }
     foreach (QString length, lengths) {
         if (!list.contains(length)) {
             list.append(length);
         }
     }
 }

 /*public*/ void RollingStockAttribute::addName(QString name) {
 if (name == "") {
         return;
     }
     // insert at start of list, sort later
     if (list.contains(name)) {
         return;
     }
     list.insert(0, name);
     maxNameLength = 0; // reset maximum name length
 }

 /*public*/ void RollingStockAttribute::deleteName(QString name) {
     list.removeOne(name);
     maxNameLength = 0; // reset maximum name length
 }

 /*public*/ bool RollingStockAttribute::containsName(QString name) {
     return list.contains(name);
 }

 /*public*/ JComboBox* RollingStockAttribute::getComboBox() {
     JComboBox* box = new JComboBox();
     updateComboBox(box);
     return box;
 }

 /*public*/ void RollingStockAttribute::updateComboBox(JComboBox *box)
 {
  box->clear();
  foreach (QString name, getNames())
  {
   box->addItem(name);
  }
 }


 /*public*/ int RollingStockAttribute::getMaxNameLength() {
     if (maxNameLength == 0) {
      maxName = "";
         maxNameLength = MIN_NAME_LENGTH;
         foreach (QString name, getNames()) {
             if (name.length() > maxNameLength) {
                 maxName = name;
                 maxNameLength = name.length();
             }
         }
     }
     return maxNameLength;
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  *
  */
 /*public*/ void RollingStockAttribute::store(QDomElement root, QString eNames, QString eName, QString oldName, QDomDocument doc)
 {
     if (Control::backwardCompatible) {
        QDomElement values = doc.createElement(oldName);
//      QDomElement values = QDomElement();
//      values.setTagName(oldName);
      QString content;
         foreach (QString name, getNames())
         {
             //values.addContent(name + "%%"); // NOI18N
          if(content != "")
           content.append("%%");
          content.append(name);
         }
         QDomText t = QDomText();
         t.setData(content);
         root.appendChild(t);
     }
     // new format using elements
     QDomElement names = doc.createElement(eNames);
//     QDomElement names = QDomElement();
//     names.setTagName(eNames);
     foreach (QString name, getNames())
     {
        QDomElement e = doc.createElement(eName);
//      QDomElement e = QDomElement();
//      e.setTagName(eName);
         if (eName==(Xml::LENGTH)) {
             e.setAttribute(Xml::VALUE, name);
         } else {
             e.setAttribute(Xml::NAME, name);
         }
         names.appendChild(e);
     }
     root.appendChild(names);
 }

 /*public*/ void RollingStockAttribute::load(QDomElement root, QString eNames, QString eName, QString oldName) {
     // new format using elements starting version 3.3.1
 if (root.firstChildElement(eNames) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList l = root.firstChildElement(eNames).elementsByTagName(eName);
         QString a;
         QVector<QString> names = QVector<QString>(l.size());
         for (int i = 0; i < l.size(); i++) {
             QDomElement name = l.at(i).toElement();
             if ((a = name.attribute(Xml::NAME)) != "") {
                 names.replace(i, a);
             }
             // lengths use "VALUE"
             if ((a = name.attribute(Xml::VALUE)) != "") {
              names.replace(i, a);

             }

         }
         setNames(names.toList());
     } // try old format
 else if (root.firstChildElement(oldName) != QDomElement()) {
         QStringList names = root.firstChildElement(oldName).text().split("%%"); // NOI18N
         setNames(names);
     }
 }
}
