#include "nceconsistrosterentry.h"
#include "nceconsistroster.h"

NceConsistRosterEntry::NceConsistRosterEntry(QObject *parent) :
    QObject(parent)
{
    init();
}
/**
 * ConsistRosterEntry represents a single element in a consist roster.
 * <P>
 * The ConsistRosterEntry is the central place to find information about a
 * consists configuration, including loco address, address type, loco's
 * direction, and consist number. Up to six consist locos are currently
 * tracked. ConsistRosterEntry handles persistency through the LocoFile
 * class. Creating a ConsistRosterEntry does not necessarily read the
 * corresponding file (which might not even exist), please see readFile(),
 * writeFile() member functions.
 * <P>
 * All the data attributes have a content, not NULL.
 * <P>
 * When the filePath attribute is non-NULL, the user has decided to organize the
 * roster into directories.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2002, 2004, 2005
 * @author Dennis Miller Copyright 2004
 * @author Daniel Boudreau (C) 2008
 * @version $Revision: 17977 $
 * @see NceConsistRoster
 *
 */
///*public*/ class NceConsistRosterEntry {

/**
 * Construct a blank object.
 *
 */
///*public*/ NceConsistRosterEntry() {
//}

/*public*/ NceConsistRosterEntry::NceConsistRosterEntry(NceConsistRosterEntry* pEntry, QString pID, QObject *parent) :
    QObject(parent) {
    //this();
    init();
    // The ID is different for this element
    _id = pID;

    // All other items are copied
    _roadName =     pEntry->_roadName;
    _roadNumber =   pEntry->_roadNumber;
    _model =   pEntry->_model;
    _consistNumber =   pEntry->_consistNumber;
    _loco1DccAddress =   pEntry->_loco1DccAddress;
    _isLoco1LongAddress = pEntry->_isLoco1LongAddress;
    _loco2DccAddress =   pEntry->_loco2DccAddress;
    _isLoco2LongAddress = pEntry->_isLoco2LongAddress;
    _loco3DccAddress =   pEntry->_loco3DccAddress;
    _isLoco3LongAddress = pEntry->_isLoco3LongAddress;
    _loco4DccAddress =   pEntry->_loco4DccAddress;
    _isLoco4LongAddress = pEntry->_isLoco4LongAddress;
    _loco5DccAddress =   pEntry->_loco5DccAddress;
    _isLoco5LongAddress = pEntry->_isLoco5LongAddress;
    _loco6DccAddress =   pEntry->_loco6DccAddress;
    _isLoco6LongAddress = pEntry->_isLoco6LongAddress;

    _comment =      pEntry->_comment;
}
void NceConsistRosterEntry::init()
{
    // members to remember all the info
    _fileName = "";

    _id = "";
    _consistNumber = "";
    _roadName = "";
    _roadNumber = "";
    _model = "";
    _loco1DccAddress = "";
    _isLoco1LongAddress = true;
    _loco1Direction = "";
    _loco2DccAddress = "";
    _isLoco2LongAddress = true;
    _loco2Direction = "";
    _loco3DccAddress = "";
    _isLoco3LongAddress = true;
    _loco3Direction = "";
    _loco4DccAddress = "";
    _isLoco4LongAddress = true;
    _loco4Direction = "";
    _loco5DccAddress = "";
    _isLoco5LongAddress = true;
    _loco5Direction = "";
    _loco6DccAddress = "";
    _isLoco6LongAddress = true;
    _loco6Direction = "";

    _comment = "";


}

/*public*/ void NceConsistRosterEntry::setId(QString s) {
    QString oldID = _id;
    _id = s;
    if (oldID!=(s))
        NceConsistRoster::instance()->entryIdChanged(this);
}
/*public*/ QString NceConsistRosterEntry::getId() { return _id; }

/*public*/ void   NceConsistRosterEntry::setConsistNumber(QString s) { _consistNumber = s; }
/*public*/ QString NceConsistRosterEntry::getConsistNumber() { return _consistNumber; }

/*public*/ void   NceConsistRosterEntry::setRoadName(QString s) { _roadName = s; }
/*public*/ QString NceConsistRosterEntry::getRoadName() { return _roadName; }

/*public*/ void   NceConsistRosterEntry::setRoadNumber(QString s) { _roadNumber = s; }
/*public*/ QString NceConsistRosterEntry::getRoadNumber() { return _roadNumber; }

/*public*/ void   NceConsistRosterEntry::setModel(QString s) { _model = s; }
/*public*/ QString NceConsistRosterEntry::getModel() { return _model; }

/*public*/ void   NceConsistRosterEntry::setLoco1DccAddress(QString s) { _loco1DccAddress = s; }
/*public*/ QString NceConsistRosterEntry::getLoco1DccAddress() { return _loco1DccAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco1LongAddress(bool b) { _isLoco1LongAddress = b; }
/*public*/ bool NceConsistRosterEntry::isLoco1LongAddress() { return _isLoco1LongAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco1Direction(QString s) { _loco1Direction = s; }
/*public*/ QString NceConsistRosterEntry::getLoco1Direction() { return _loco1Direction; }

/*public*/ void   NceConsistRosterEntry::setLoco2DccAddress(QString s) { _loco2DccAddress = s; }
/*public*/ QString NceConsistRosterEntry::getLoco2DccAddress() { return _loco2DccAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco2LongAddress(bool b) { _isLoco2LongAddress = b; }
/*public*/ bool NceConsistRosterEntry::isLoco2LongAddress() { return _isLoco2LongAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco2Direction(QString s) { _loco2Direction = s; }
/*public*/ QString NceConsistRosterEntry::getLoco2Direction() { return _loco2Direction; }

/*public*/ void   NceConsistRosterEntry::setLoco3DccAddress(QString s) { _loco3DccAddress = s; }
/*public*/ QString NceConsistRosterEntry::getLoco3DccAddress() { return _loco3DccAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco3LongAddress(bool b) { _isLoco3LongAddress = b; }
/*public*/ bool NceConsistRosterEntry::isLoco3LongAddress() { return _isLoco3LongAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco3Direction(QString s) { _loco3Direction = s; }
/*public*/ QString NceConsistRosterEntry::getLoco3Direction() { return _loco3Direction; }

/*public*/ void   NceConsistRosterEntry::setLoco4DccAddress(QString s) { _loco4DccAddress = s; }
/*public*/ QString NceConsistRosterEntry::getLoco4DccAddress() { return _loco4DccAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco4LongAddress(bool b) { _isLoco4LongAddress = b; }
/*public*/ bool NceConsistRosterEntry::isLoco4LongAddress() { return _isLoco4LongAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco4Direction(QString s) { _loco4Direction = s; }
/*public*/ QString NceConsistRosterEntry::getLoco4Direction() { return _loco4Direction; }

/*public*/ void   NceConsistRosterEntry::setLoco5DccAddress(QString s) { _loco5DccAddress = s; }
/*public*/ QString NceConsistRosterEntry::getLoco5DccAddress() { return _loco5DccAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco5LongAddress(bool b) { _isLoco5LongAddress = b; }
/*public*/ bool NceConsistRosterEntry::isLoco5LongAddress() { return _isLoco5LongAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco5Direction(QString s) { _loco5Direction = s; }
/*public*/ QString NceConsistRosterEntry::getLoco5Direction() { return _loco5Direction; }

/*public*/ void   NceConsistRosterEntry::setLoco6DccAddress(QString s) { _loco6DccAddress = s; }
/*public*/ QString NceConsistRosterEntry::getLoco6DccAddress() { return _loco6DccAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco6LongAddress(bool b) { _isLoco6LongAddress = b; }
/*public*/ bool NceConsistRosterEntry::isLoco6LongAddress() { return _isLoco6LongAddress; }

/*public*/ void   NceConsistRosterEntry::setLoco6Direction(QString s) { _loco6Direction = s; }
/*public*/ QString NceConsistRosterEntry::getLoco6Direction() { return _loco6Direction; }

/*public*/ void   NceConsistRosterEntry::setComment(QString s) { _comment = s; }
/*public*/ QString NceConsistRosterEntry::getComment() { return _comment; }

/**
 * Construct this Entry from XML. This member has to remain synchronized with the
 * detailed DTD in consist-roster-config.xml
 *
 * @param e  Consist XML element
 */
//@SuppressWarnings("unchecked")
/*public*/ NceConsistRosterEntry::NceConsistRosterEntry(QDomElement e) {
    log = new Logger("NceConsistRosterEntry");
    if (log->isDebugEnabled()) log->debug("ctor from element "+e.tagName());
    QString a;
    if ((a = e.attribute("id")) != "" )  _id = a;
    else log->warn("no id attribute in consist element when reading ConsistRoster");
    if ((a = e.attribute("consistNumber")) != NULL )  _consistNumber = a;
    if ((a = e.attribute("roadName")) != NULL )  _roadName = a;
    if ((a = e.attribute("roadNumber")) != NULL )  _roadNumber = a;
    if ((a = e.attribute("model")) != NULL )  _model = a;
    if ((a = e.attribute("comment")) != NULL )  _comment = a;

    QDomNodeList elementList = e.elementsByTagName("loco");

    for (int i = 0; i < elementList.size(); i++){
        QString locoName = "";
        QString locoMidNumber = "";
        if ((a  = ((elementList.at(i).toElement())).attribute("locoName"))!= NULL ) locoName  = a;
        if ((a  = ((elementList.at(i).toElement())).attribute("locoMidNumber")) != NULL ) locoMidNumber =a;

        if (locoName==("lead")){
            if ((a = ((elementList.at(i).toElement())).attribute("dccLocoAddress")) != NULL )  _loco1DccAddress = a;
            if ((a = ((elementList.at(i).toElement())).attribute("longAddress")) != NULL )  setLoco1LongAddress (a==("yes"));
            if ((a = ((elementList.at(i).toElement())).attribute("locoDir")) != NULL )  _loco1Direction = (a);
        }
        if (locoName==("rear")){
            if ((a = ((elementList.at(i).toElement())).attribute("dccLocoAddress")) != NULL )  _loco2DccAddress = a;
            if ((a = ((elementList.at(i).toElement())).attribute("longAddress")) != NULL )  setLoco2LongAddress (a==("yes"));
            if ((a = ((elementList.at(i).toElement())).attribute("locoDir")) != NULL )  _loco2Direction = (a);
        }
        if (locoName==("mid") && locoMidNumber== ("1")){
            if ((a = ((elementList.at(i).toElement())).attribute("dccLocoAddress")) != NULL )  _loco3DccAddress = a;
            if ((a = ((elementList.at(i).toElement())).attribute("longAddress")) != NULL )  setLoco3LongAddress (a==("yes"));
            if ((a = ((elementList.at(i).toElement())).attribute("locoDir")) != NULL )  _loco3Direction = (a);
        }
        if (locoName==("mid") && locoMidNumber== ("2")){
            if ((a = ((elementList.at(i).toElement())).attribute("dccLocoAddress")) != NULL )  _loco4DccAddress = a;
            if ((a = ((elementList.at(i).toElement())).attribute("longAddress")) != NULL )  setLoco4LongAddress (a==("yes"));
            if ((a = ((elementList.at(i).toElement())).attribute("locoDir")) != NULL )  _loco4Direction = (a);
        }
        if (locoName==("mid") && locoMidNumber== ("3")){
            if ((a = ((elementList.at(i).toElement())).attribute("dccLocoAddress")) != NULL )  _loco5DccAddress = a;
            if ((a = ((elementList.at(i).toElement())).attribute("longAddress")) != NULL )  setLoco5LongAddress (a==("yes"));
            if ((a = ((elementList.at(i).toElement())).attribute("locoDir")) != NULL )  _loco5Direction = (a);
        }
        if (locoName==("mid") && locoMidNumber== ("4")){
            if ((a = ((elementList.at(i).toElement())).attribute("dccLocoAddress")) != NULL )  _loco6DccAddress = a;
            if ((a = ((elementList.at(i).toElement())).attribute("longAddress")) != NULL )  setLoco6LongAddress (a==("yes"));
            if ((a = ((elementList.at(i).toElement())).attribute("locoDir")) != NULL )  _loco6Direction = (a);
        }
    }
    if (_loco1DccAddress==("")){
        log->warn("no lead loco attribute in consist element when reading ConsistRoster");
    }
    if (_loco2DccAddress==("")){
        log->warn("no rear loco attribute in consist element when reading ConsistRoster");
    }
}

/**
 * Create an XML element to represent this Entry. This member has to remain synchronized with the
 * detailed DTD in consist-roster-config.xml.
 * @return Contents in a JDOM Element
 */
QDomElement NceConsistRosterEntry::store(QDomDocument doc) {
    QDomElement e = doc.createElement("consist");
    e.setAttribute("id", getId());
    e.setAttribute("consistNumber",getConsistNumber());
    e.setAttribute("roadNumber",getRoadNumber());
    e.setAttribute("roadName",getRoadName());
    e.setAttribute("model",getModel());
    e.setAttribute("comment",getComment());

    QDomElement loco1 = doc.createElement("loco");
    loco1.setAttribute("locoName","lead");
    loco1.setAttribute("dccLocoAddress",getLoco1DccAddress());
    loco1.setAttribute("longAddress",isLoco1LongAddress()?"yes":"no");
    loco1.setAttribute("locoDir",getLoco1Direction());
    e.appendChild(loco1);

    QDomElement loco2 = doc.createElement("loco");
    loco2.setAttribute("locoName","rear");
    loco2.setAttribute("dccLocoAddress",getLoco2DccAddress());
    loco2.setAttribute("longAddress",isLoco2LongAddress()?"yes":"no");
    loco2.setAttribute("locoDir",getLoco2Direction());
    e.appendChild(loco2);

    if (getLoco3DccAddress()!=("")){
        QDomElement loco3 = doc.createElement("loco");
        loco3.setAttribute("locoName","mid");
        loco3.setAttribute("locoMidNumber","1");
        loco3.setAttribute("dccLocoAddress",getLoco3DccAddress());
        loco3.setAttribute("longAddress",isLoco3LongAddress()?"yes":"no");
        loco3.setAttribute("locoDir",getLoco3Direction());
        e.appendChild(loco3);
    }

    if (getLoco4DccAddress()!=("")){
        QDomElement loco4 = doc.createElement("loco");
        loco4.setAttribute("locoName","mid");
        loco4.setAttribute("locoMidNumber","2");
        loco4.setAttribute("dccLocoAddress",getLoco4DccAddress());
        loco4.setAttribute("longAddress",isLoco4LongAddress()?"yes":"no");
        loco4.setAttribute("locoDir",getLoco4Direction());
        e.appendChild(loco4);
    }

    if (getLoco5DccAddress()!=("")){
        QDomElement loco5 = doc.createElement("loco");
        loco5.setAttribute("locoName","mid");
        loco5.setAttribute("locoMidNumber","3");
        loco5.setAttribute("dccLocoAddress",getLoco5DccAddress());
        loco5.setAttribute("longAddress",isLoco5LongAddress()?"yes":"no");
        loco5.setAttribute("locoDir",getLoco5Direction());
        e.appendChild(loco5);
    }

    if (getLoco6DccAddress()!=("")){
        QDomElement loco6 = doc.createElement("loco");
        loco6.setAttribute("locoName","mid");
        loco6.setAttribute("locoMidNumber","4");
        loco6.setAttribute("dccLocoAddress",getLoco6DccAddress());
        loco6.setAttribute("longAddress",isLoco6LongAddress()?"yes":"no");
        loco6.setAttribute("locoDir",getLoco6Direction());
        e.appendChild(loco6);
    }

    return e;
}

/*public*/ QString NceConsistRosterEntry::titleString() {
    return getId();
}

/*public*/ QString NceConsistRosterEntry::toString() {
    QString out = "[ConsistRosterEntry: "
        +_id+" "
        +" "+_consistNumber
        +" "+_roadName
        +" "+_roadNumber
        +" "+_model
        +" "+_loco1DccAddress
        +" "+_loco2DccAddress
        +" "+_loco3DccAddress
        +" "+_loco4DccAddress
        +" "+_loco5DccAddress
        +" "+_loco6DccAddress
        +" "+_comment
        +"]";
    return out;
}
#if 0
/**
 *Prints the roster information. Updated to allow for multiline
 *comment field.
 *Created separate write statements for text and line feeds to work
 *around the HardcopyWriter bug that misplaces borders
 */
/*public*/ void NceConsistRosterEntry::printEntry(Writer w) {
    try {
        QString indent = "                      ";
        int indentWidth = indent.length();
        HardcopyWriter ww = (HardcopyWriter) w;
        int textSpace = ww.getCharactersPerLine() - indentWidth - 1;
        QString newLine = "\n";

        w.write(newLine, 0, 1);
        QString s = "   ID:                " + _id;
        w.write(s, 0, s.length());

        if (!(_consistNumber==(""))) {
            w.write(newLine, 0, 1);
            s = "   Consist number:    " + _consistNumber;
            w.write(s, 0, s.length());
        }
        if (!(_roadName==(""))) {
            w.write(newLine, 0, 1);
            s = "   Road name:         " + _roadName;
            w.write(s, 0, s.length());
        }
        if (!(_roadNumber==(""))) {
            w.write(newLine, 0, 1);
            s = "   Road number:       " + _roadNumber;
            w.write(s, 0, s.length());
        }
        if (!(_model==(""))) {
            w.write(newLine,0,1);
            s = "   Model:             " + _model;
            w.write(s,0,s.length());
        }
        if (!(_loco1DccAddress==(""))) {
            w.write(newLine, 0, 1);
            s = "   Lead Address:      " + _loco1DccAddress + "  " + _loco1Direction;
            w.write(s, 0, s.length());
        }
        if (!(_loco2DccAddress==(""))) {
            w.write(newLine, 0, 1);
            s = "   Rear Address:      " + _loco2DccAddress + "  " + _loco2Direction;
            w.write(s, 0, s.length());
        }
        if (!(_loco3DccAddress==(""))) {
            w.write(newLine, 0, 1);
            s = "   Mid1 Address:      " + _loco3DccAddress + "  " + _loco3Direction;
            w.write(s, 0, s.length());
        }
        if (!(_loco4DccAddress==(""))) {
            w.write(newLine, 0, 1);
            s = "   Mid2 Address:      " + _loco4DccAddress + "  " + _loco4Direction;
            w.write(s, 0, s.length());
        }
        if (!(_loco5DccAddress==(""))) {
            w.write(newLine, 0, 1);
            s = "   Mid3 Address:      " + _loco5DccAddress + "  " + _loco5Direction;
            w.write(s, 0, s.length());
        }
        if (!(_loco6DccAddress==(""))) {
            w.write(newLine, 0, 1);
            s = "   Mid4 Address:      " + _loco6DccAddress + "  " + _loco6Direction;
            w.write(s, 0, s.length());
        }

        // If there is a comment field, then wrap it using the new
        // wrapCommment
        // method and print it
        if (!(_comment==(""))) {
            Vector<QString> commentVector = wrapComment(_comment, textSpace);

            // Now have a vector of text pieces and line feeds that will all
            // fit in the allowed space. Print each piece, prefixing the
            // first one
            // with the label and indenting any remainding.
            int k = 0;
            w.write(newLine, 0, 1);
            s = "   Comment:           "
                + commentVector.elementAt(k);
            w.write(s, 0, s.length());
            k++;
            while (k < commentVector.size()) {
                QString token = commentVector.elementAt(k);
                if (!token==("\n"))
                    s = indent + token;
                else
                    s = token;
                w.write(s, 0, s.length());
                k++;
            }
        }
        w.write(newLine,0,1);
    } catch (IOException e) {
        log->error("Error printing ConsistRosterEntry: " + e);
    }
}

/**
 * Take a String comment field and perform line wrapping on it. String must
 * be non-NULL and may or may not have \n characters embedded. textSpace is
 * the width of the space to print for wrapping purposes. The comment is
 * wrapped on a word wrap basis
 *
 * This is exactly the same as RosterEntry.wrapComment
 */
/*public*/ QVector<QString> NceConsistRosterEntry::wrapComment(QString comment, int textSpace)
{
  // Tokenize the string using \n to separate the text on mulitple lines
  // and create a vector to hold the processed text pieces
  StringTokenizer commentTokens = new StringTokenizer (comment,"\n",true);
  Vector<QString> textVector = new Vector<QString>(commentTokens.countTokens());
  QString newLine = "\n";
  while (commentTokens.hasMoreTokens())
  {
    QString commentToken = commentTokens.nextToken();
    int startIndex = 0;
    int endIndex = textSpace;
    //Check each token to see if it needs to have a line wrap.
    //Get a piece of the token, either the size of the allowed space or
    //a shorter piece if there isn't enough text to fill the space
    if (commentToken.length() < startIndex+textSpace)
    {
      //the piece will fit.
      textVector.addElement(commentToken);
    }
    else
    {
      //Piece too long to fit. Extract a piece the size of the textSpace
      //and check for farthest right space for word wrapping.
      if (log->isDebugEnabled()) log->debug("token: /"+commentToken+"/");
      while (startIndex < commentToken.length())
      {
        QString tokenPiece = commentToken.substring(startIndex, startIndex + textSpace);
        if (log->isDebugEnabled()) log->debug("loop: /"+tokenPiece+"/ "+tokenPiece.lastIndexOf(" "));
        if (tokenPiece.lastIndexOf(" ") == -1)
        {
          //If no spaces, put the whole piece in the vector and add a line feed, then
          //increment the startIndex to reposition for extracting next piece
          textVector.addElement(tokenPiece);
          textVector.addElement(newLine);
          startIndex += textSpace;
        }
        else
        {
          //If there is at least one space, extract up to and including the
          //last space and put in the vector as well as a line feed
          endIndex = tokenPiece.lastIndexOf(" ") + 1;
          if (log->isDebugEnabled()) log->debug("/"+tokenPiece+"/ "+startIndex+" "+endIndex);
          textVector.addElement(tokenPiece.substring(0, endIndex));
          textVector.addElement(newLine);
          startIndex += endIndex;
        }
        //Check the remaining piece to see if it fits -Loco2rtIndex now points
        //to the start of the next piece
        if (commentToken.substring(startIndex).length() < textSpace)
        {
          //It will fit so just insert it, otherwise will cycle through the
          //while loop and the checks above will take care of the remainder.
          //Line feed is not required as this is the last part of the token.
          tokenPiece = commentToken.substring(startIndex);
          textVector.addElement(commentToken.substring(startIndex));
          startIndex += textSpace;
        }
      }
    }
  }
  return textVector;
}
#endif
