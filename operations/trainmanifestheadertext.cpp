#include "trainmanifestheadertext.h"
#include "xml.h"
#include "QString"

namespace Operations
{
/**
 * Loads and stores the manifest header text QStrings.
 *
 * @author Daniel Boudreau Copyright (C) 2014
 *
 */
///*public*/ class TrainManifestHeaderText {

 /*private*/ /*static*/ QString TrainManifestHeaderText::road = tr("Road"); // the supported message format options
 /*private*/ /*static*/ QString TrainManifestHeaderText::number = tr("Number");
 /*private*/ /*static*/ QString TrainManifestHeaderText::engine_number = tr("Number");
 /*private*/ /*static*/ QString TrainManifestHeaderText::type = tr("Type");
 /*private*/ /*static*/ QString TrainManifestHeaderText::model = tr("Model");
 /*private*/ /*static*/ QString TrainManifestHeaderText::length = tr("Length");
 /*private*/ /*static*/ QString TrainManifestHeaderText::_load = tr("Load");
 /*private*/ /*static*/ QString TrainManifestHeaderText::color = tr("Color");
 /*private*/ /*static*/ QString TrainManifestHeaderText::track = tr("Track");
 /*private*/ /*static*/ QString TrainManifestHeaderText::destination = tr("Destination");
 /*private*/ /*static*/ QString TrainManifestHeaderText::dest_track = tr("Dest&Track");
 /*private*/ /*static*/ QString TrainManifestHeaderText::final_dest = tr("Final_Dest");
 /*private*/ /*static*/ QString TrainManifestHeaderText::final_dest_track = tr("FD&Track");
 /*private*/ /*static*/ QString TrainManifestHeaderText::location = tr("Location");
 /*private*/ /*static*/ QString TrainManifestHeaderText::consist = tr("Consist");
 /*private*/ /*static*/ QString TrainManifestHeaderText::kernel = tr("Kernel");
 /*private*/ /*static*/ QString TrainManifestHeaderText::owner = tr("Owner");
 /*private*/ /*static*/ QString TrainManifestHeaderText::rwe = tr("RWE");
 /*private*/ /*static*/ QString TrainManifestHeaderText::comment = tr("Comment");
 /*private*/ /*static*/ QString TrainManifestHeaderText::drop_comment = tr("SetOut_Msg");
 /*private*/ /*static*/ QString TrainManifestHeaderText::pickup_comment = tr("PickUp_Msg");
 /*private*/ /*static*/ QString TrainManifestHeaderText::hazardous = tr("Hazardous");

 //TrainManifestHeaderText::TrainManifestHeaderText(){}


 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Road() {
     return road;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Road(QString s) {
     road = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Number() {
     return number;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Number(QString s) {
     number = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_EngineNumber() {
     return engine_number;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_EngineNumber(QString s) {
     engine_number = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Type() {
     return type;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Type(QString s) {
     type = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Model() {
     return model;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Model(QString s) {
     model = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Length() {
     return length;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Length(QString s) {
     length = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Load() {
     return _load;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Load(QString s) {
     _load = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Color() {
     return color;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Color(QString s) {
     color = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Track() {
     return track;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Track(QString s) {
     track = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Destination() {
     return destination;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Destination(QString s) {
     destination = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Dest_Track() {
     return dest_track;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Dest_Track(QString s) {
     dest_track = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Final_Dest() {
     return final_dest;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Final_Dest(QString s) {
     final_dest = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Final_Dest_Track() {
     return final_dest_track;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Final_Dest_Track(QString s) {
     final_dest_track = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Location() {
     return location;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Location(QString s) {
     location = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Consist() {
     return consist;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Consist(QString s) {
     consist = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Kernel() {
     return kernel;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Kernel(QString s) {
     kernel = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Owner() {
     return owner;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Owner(QString s) {
     owner = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_RWE() {
     return rwe;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_RWE(QString s) {
     rwe = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Comment() {
     return comment;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Comment(QString s) {
     comment = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Drop_Comment() {
     return drop_comment;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Drop_Comment(QString s) {
     drop_comment = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Pickup_Comment() {
     return pickup_comment;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Pickup_Comment(QString s) {
     pickup_comment = s;
 }

 /*public*/ /*static*/ QString TrainManifestHeaderText::getStringHeader_Hazardous() {
     return hazardous;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::setStringHeader_Hazardous(QString s) {
     hazardous = s;
 }

 // must synchronize changes with operation-config.dtd
 /*public*/ /*static*/ QDomElement TrainManifestHeaderText::store(QDomDocument doc) {
     QDomElement values;
     QDomElement e = doc.createElement(Xml::MANIFEST_HEADER_TEXT_STRINGS);
     // only save QStrings that have been modified
     if (getStringHeader_Road()!=(tr("Road"))) {
         e.appendChild(values = doc.createElement(Xml::ROAD));
         values.setAttribute(Xml::TEXT, getStringHeader_Road());
     }
     if (getStringHeader_Number()!=(tr("Number"))) {
         e.appendChild(values = doc.createElement(Xml::NUMBER));
         values.setAttribute(Xml::TEXT, getStringHeader_Number());
     }
     if (getStringHeader_EngineNumber()!=(tr("Number"))) {
         e.appendChild(values = doc.createElement(Xml::ENGINE_NUMBER));
         values.setAttribute(Xml::TEXT, getStringHeader_EngineNumber());
     }
     if (getStringHeader_Type()!=(tr("Type"))) {
         e.appendChild(values = doc.createElement(Xml::TYPE));
         values.setAttribute(Xml::TEXT, getStringHeader_Type());
     }
     if (getStringHeader_Model()!=(tr("Model"))) {
         e.appendChild(values = doc.createElement(Xml::MODEL));
         values.setAttribute(Xml::TEXT, getStringHeader_Model());
     }
     if (getStringHeader_Length()!=(tr("Length"))) {
         e.appendChild(values = doc.createElement(Xml::LENGTH));
         values.setAttribute(Xml::TEXT, getStringHeader_Length());
     }
     if (getStringHeader_Load()!=(tr("Load"))) {
         e.appendChild(values = doc.createElement(Xml::LOAD));
         values.setAttribute(Xml::TEXT, getStringHeader_Load());
     }
     if (getStringHeader_Color()!=(tr("Color"))) {
         e.appendChild(values = doc.createElement(Xml::COLOR));
         values.setAttribute(Xml::TEXT, getStringHeader_Color());
     }
     if (getStringHeader_Track()!=(tr("Track"))) {
         e.appendChild(values = doc.createElement(Xml::TRACK));
         values.setAttribute(Xml::TEXT, getStringHeader_Track());
     }
     if (getStringHeader_Destination()!=(tr("Destination"))) {
         e.appendChild(values = doc.createElement(Xml::DESTINATION));
         values.setAttribute(Xml::TEXT, getStringHeader_Destination());
     }
     if (getStringHeader_Dest_Track()!=(tr("Dest&Track"))) {
         e.appendChild(values = doc.createElement(Xml::DEST_TRACK));
         values.setAttribute(Xml::TEXT, getStringHeader_Dest_Track());
     }
     if (getStringHeader_Final_Dest()!=(tr("Final_Dest"))) {
         e.appendChild(values = doc.createElement(Xml::FINAL_DEST));
         values.setAttribute(Xml::TEXT, getStringHeader_Final_Dest());
     }
     if (getStringHeader_Final_Dest_Track()!=(tr("FD&Track"))) {
         e.appendChild(values = doc.createElement(Xml::FINAL_DEST_TRACK));
         values.setAttribute(Xml::TEXT, getStringHeader_Final_Dest_Track());
     }
     if (getStringHeader_Location()!=(tr("Location"))) {
         e.appendChild(values = doc.createElement(Xml::LOCATION));
         values.setAttribute(Xml::TEXT, getStringHeader_Location());
     }
     if (getStringHeader_Consist()!=(tr("Consist"))) {
         e.appendChild(values = doc.createElement(Xml::CONSIST));
         values.setAttribute(Xml::TEXT, getStringHeader_Consist());
     }
     if (getStringHeader_Kernel()!=(tr("Kernel"))) {
         e.appendChild(values = doc.createElement(Xml::KERNEL));
         values.setAttribute(Xml::TEXT, getStringHeader_Kernel());
     }
     if (getStringHeader_Owner()!=(tr("Owner"))) {
         e.appendChild(values = doc.createElement(Xml::OWNER));
         values.setAttribute(Xml::TEXT, getStringHeader_Owner());
     }
     if (getStringHeader_RWE()!=(tr("RWE"))) {
         e.appendChild(values = doc.createElement(Xml::RWE));
         values.setAttribute(Xml::TEXT, getStringHeader_RWE());
     }
     if (getStringHeader_Comment()!=(tr("Comment"))) {
         e.appendChild(values = doc.createElement(Xml::COMMENT));
         values.setAttribute(Xml::TEXT, getStringHeader_Comment());
     }
     if (getStringHeader_Drop_Comment()!=(tr("SetOut_Msg"))) {
         e.appendChild(values = doc.createElement(Xml::DROP_COMMENT));
         values.setAttribute(Xml::TEXT, getStringHeader_Drop_Comment());
     }
     if (getStringHeader_Pickup_Comment()!=(tr("PickUp_Msg"))) {
         e.appendChild(values = doc.createElement(Xml::PICKUP_COMMENT));
         values.setAttribute(Xml::TEXT, getStringHeader_Pickup_Comment());
     }
     if (getStringHeader_Hazardous()!=(tr("Hazardous"))) {
         e.appendChild(values = doc.createElement(Xml::HAZARDOUS));
         values.setAttribute(Xml::TEXT, getStringHeader_Hazardous());
     }

     return e;
 }

 /*public*/ /*/*static*/ void TrainManifestHeaderText::load(QDomElement e) {
     QDomElement emts = e.firstChildElement(Xml::MANIFEST_HEADER_TEXT_STRINGS);
     if (emts.isNull()) {
         return;
     }
     QString a;
     if (emts.firstChildElement(Xml::ROAD) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::ROAD).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Road(a);
         }
     }
     if (emts.firstChildElement(Xml::NUMBER) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::NUMBER).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Number(a);
         }
     }
     if (emts.firstChildElement(Xml::ENGINE_NUMBER) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::ENGINE_NUMBER).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_EngineNumber(a);
         }
     }
     if (emts.firstChildElement(Xml::TYPE) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::TYPE).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Type(a);
         }
     }
     if (emts.firstChildElement(Xml::MODEL) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::MODEL).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Model(a);
         }
     }
     if (emts.firstChildElement(Xml::LENGTH) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::LENGTH).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Length(a);
         }
     }
     if (emts.firstChildElement(Xml::LOAD) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::LOAD).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Load(a);
         }
     }
     if (emts.firstChildElement(Xml::COLOR) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::COLOR).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Color(a);
         }
     }
     if (emts.firstChildElement(Xml::TRACK) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::TRACK).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Track(a);
         }
     }
     if (emts.firstChildElement(Xml::DESTINATION) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::DESTINATION).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Destination(a);
         }
     }
     if (emts.firstChildElement(Xml::DEST_TRACK) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::DEST_TRACK).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Dest_Track(a);
         }
     }
     if (emts.firstChildElement(Xml::FINAL_DEST) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::FINAL_DEST).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Final_Dest(a);
         }
     }
     if (emts.firstChildElement(Xml::FINAL_DEST_TRACK) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::FINAL_DEST_TRACK).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Final_Dest_Track(a);
         }
     }
     if (emts.firstChildElement(Xml::LOCATION) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::LOCATION).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Location(a);
         }
     }
     if (emts.firstChildElement(Xml::CONSIST) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::CONSIST).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Consist(a);
         }
     }
     if (emts.firstChildElement(Xml::KERNEL) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::KERNEL).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Kernel(a);
         }
     }
     if (emts.firstChildElement(Xml::OWNER) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::OWNER).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Owner(a);
         }
     }
     if (emts.firstChildElement(Xml::RWE) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::RWE).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_RWE(a);
         }
     }
     if (emts.firstChildElement(Xml::COMMENT) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::COMMENT).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Comment(a);
         }
     }
     if (emts.firstChildElement(Xml::DROP_COMMENT) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::DROP_COMMENT).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Drop_Comment(a);
         }
     }
     if (emts.firstChildElement(Xml::PICKUP_COMMENT) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::PICKUP_COMMENT).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Pickup_Comment(a);
         }
     }
     if (emts.firstChildElement(Xml::HAZARDOUS) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::HAZARDOUS).attribute(Xml::TEXT)) != NULL) {
             setStringHeader_Hazardous(a);
         }
     }
 }
}
