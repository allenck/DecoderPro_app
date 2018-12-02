#include "rosterentry.h"
#include "roster.h"
#include "dcclocoaddress.h"
#include "dcclocoaddressxml.h"
#include "fileutil.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include <QMessageBox>
#include "imageicon.h"
#include <QImage>
#include "hardcopywriter.h"
#include "../../LayoutEditor/jlabel.h"
#include "rosterspeedprofile.h"
#include "rostergroup.h"

QString RosterEntry::_defaultOwner = "";
/*public*/ /*static*/ /*final*/ QString RosterEntry::ID = "id"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::FILENAME = "filename"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::ROADNAME = "roadname"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::MFG = "mfg"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::MODEL = "model"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::OWNER = "owner"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::DCC_ADDRESS = "dccaddress"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::LONG_ADDRESS = "longaddress"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::PROTOCOL = "protocol"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::COMMENT = "comment"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::DECODER_MODEL = "decodermodel"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::DECODER_FAMILY = "decoderfamily"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::DECODER_COMMENT = "decodercomment"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::IMAGE_FILE_PATH = "imagefilepath"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::ICON_FILE_PATH = "iconfilepath"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::URL = "url"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::DATE_UPDATED = "dateupdated"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::FUNCTION_IMAGE = "functionImage"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::FUNCTION_LABEL = "functionlabel"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::FUNCTION_LOCKABLE = "functionLockable"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::FUNCTION_SELECTED_IMAGE = "functionSelectedImage"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::ATTRIBUTE_UPDATED = "attributeUpdated:"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::ATTRIBUTE_DELETED = "attributeDeleted"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::MAX_SPEED = "maxSpeed"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::SHUNTING_FUNCTION = "IsShuntingOn"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::SPEED_PROFILE = "speedprofile"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString RosterEntry::SOUND_LABEL = "soundlabel"; // NOI18N
    /*public*/ /*final*/ /*static*/ int RosterEntry::MAXSOUNDNUM = 32;

RosterEntry::RosterEntry(QObject *parent) :
    BasicRosterEntry(parent)
{
 init();
}
/**
 * RosterEntry represents a single element in a locomotive roster, including
 * information on how to locate it from decoder information.
 * <P>
 * The RosterEntry is the central place to find information about a locomotive's
 * configuration, including CV and "programming variable" information.
 * RosterEntry handles persistency through the LocoFile class.  Creating
 * a RosterEntry does not necessarily read the corresponding file (which
 * might not even exist), please see readFile(), writeFile() member functions.
 * <P>
 * All the data attributes have a content, not NULL. FileName, however, is special.
 * A NULL value for it indicates that no physical file is (yet) associated with
 * this entry.
 * <P>
 * When the filePath attribute is non-NULL, the user has decided to
 * organize the roster into directories.
 * <P>
 * Each entry can have one or more "Attributes" associated with it.
 * These are (key, value) pairs.  The key has to be unique, and currently
 * both objects have to be QStrings.
 *<p>
 * All properties, including the "Attributes", are bound.
 *
 * @author    Bob Jacobsen   Copyright (C) 2001, 2002, 2004, 2005, 2009
 * @author    Dennis Miller Copyright 2004
 * @version   $Revision: 22547 $
 * @see       jmri.jmrit.roster.LocoFile
 *
 */
///*public*/ class RosterEntry implements jmri.BasicRosterEntry {

void RosterEntry::init()
{
 log = new Logger("RosterEntry");
 log->setDebugEnabled(true);
 pcs = new PropertyChangeSupport(this);
  _fileName = "";

 _id = "";
 _roadName = "";
 _roadNumber = "";
 _mfg = "";
 _owner = _defaultOwner;
 _model = "";
 _dccAddress = "3";
    ///*protected*/ bool _isLongAddress = false;
 _protocol = LocoAddress::DCC_SHORT;
  _comment = "";
  _decoderModel = "";
  _decoderFamily = "";
  _decoderComment = "";
  _dateUpdated = "";
  _maxSpeedPCT = 100;
  _isShuntingOn="";
  _rfidTag = 0;

 _imageFilePath = "";//FileUtil::getUserResourcePath() ; // at DndImagePanel init will
 _iconFilePath = "";//FileUtil::getUserResourcePath() ;  // force image copy to that folder
 _URL = "";
 _sp = NULL;
 loadedOnce = false;
 attributePairs = NULL;
 openCounter =0;
 functionLabels =  QVector<QString>(MAXFNNUM+1, "");
 functionSelectedImages = QVector<QString>(MAXFNNUM+1, "");
 functionImages = QVector<QString>(MAXFNNUM+1, "");
 functionLockables =  QVector<bool>(MAXFNNUM+1, true);
 blanks=0;
 textSpaceWithIcon=0;
 indent = "                      ";
 indentWidth = indent.length();
 newLine = "\n";

}

/**
 * Construct a blank object.
 *
 */
///*public*/ RosterEntry::RosterEntry() {
//    _owner = _defaultOwner;
//}

/*public*/ RosterEntry::RosterEntry(QString fileName, QObject *parent) : BasicRosterEntry(parent){
    //this();
    init();
    _fileName = fileName;
}

// copy constructor
/*public*/ RosterEntry::RosterEntry(RosterEntry* pEntry, QString pID, QObject *parent) : BasicRosterEntry(parent)
{
    //this();
    init();
    // The ID is different for this element
    _id = pID;

    // The filename is not set here, rather later
    _fileName = "";

    // All other items are copied
    _roadName =     pEntry->_roadName;
    _roadNumber =   pEntry->_roadNumber;
    _mfg =          pEntry->_mfg;
    _model =        pEntry->_model;
    _dccAddress =   pEntry->_dccAddress;
    _protocol =     pEntry->_protocol;
    _comment =      pEntry->_comment;
    _decoderModel = pEntry->_decoderModel;
    _decoderFamily =pEntry->_decoderFamily;
    _decoderComment=pEntry->_decoderComment;
    _owner =        pEntry->_owner;
    _imageFilePath =pEntry->_imageFilePath;
    _iconFilePath = pEntry->_iconFilePath;
    _URL =          pEntry->_URL;
    _maxSpeedPCT =  pEntry->_maxSpeedPCT;
    _isShuntingOn = pEntry->_isShuntingOn;

    for (int i=0; i<MAXFNNUM+1; i++)
    {
     if ((!pEntry->functionLabels.isEmpty()) && (!pEntry->functionLabels.at(i).isEmpty()))
     {
      functionLabels.replace(i, pEntry->functionLabels.at(i));
     }
     if ((!pEntry->functionSelectedImages.isEmpty()) && (pEntry->functionSelectedImages.at(i).isNull()))
     {
      functionSelectedImages.replace(i, pEntry->functionSelectedImages.at(i));
     }
     if ((!pEntry->functionImages.isEmpty()) && (!pEntry->functionImages.at(i).isEmpty()))
     {
      functionImages.replace(i,pEntry->functionImages.at(i));
     }
     if (!pEntry->functionLockables.isEmpty())
     {
      functionLockables.replace(i, pEntry->functionLockables.at(i));
     }
    }
}

/*public*/ void RosterEntry::setId(QString s) {
    QString oldID = _id;
    _id = s;
    if (!oldID.isEmpty() || oldID!=(s))
    {
        Roster::instance()->entryIdChanged(this);
//TODO:        firePropertyChange("id", oldID, s);
    }
}
/*public*/ QString RosterEntry::getId() { return _id; }

/*public*/ void   RosterEntry::setFileName(QString s) {
    QString oldName = _fileName;
    _fileName = s;
// TODO:    firePropertyChange("filename", oldName, s);
}
/*public*/ QString RosterEntry::getFileName() { return _fileName; }

/*public*/ QString RosterEntry::getPathName() {
    //return LocoFile.getFileLocation() + "/" + _fileName;
// TODO: implement LocoFile; for now, hard code it.
    return QDir::homePath()+"/.jmri/roster/" + _fileName;
}

/**
 * Ensure the entry has a valid filename. If none
 * exists, create one based on the ID string. Does _not_
 * enforce any particular naming; you have to check separately
 * for "&lt.none&gt." or whatever your convention is for indicating
 * an invalid name.  Does replace the space, period, colon, slash and
 * backslash characters so that the filename will be generally usable.
 */
/*public*/ void RosterEntry::ensureFilenameExists()
{
 // if there isn't a filename, store using the id
 if (getFileName().isEmpty()||getFileName()==(""))
 {

  QString newFilename = Roster::makeValidFilename(getId());

  // we don't want to overwrite a file that exists, whether or not
  // it's in the roster
  // TODO: QFile testFile (LocoFile.getFileLocation()+newFilename);
  QFile testFile(QDir::homePath()+"/.jmri/roster/"+newFilename);
  int count = 0;
  QString oldFilename = newFilename;
  while (testFile.exists())
  {
   // oops - change filename and try again
   newFilename = oldFilename.mid(0, oldFilename.length()-4)+count+".xml";
   count++;
   log->debug("try to use "+newFilename+" as filename instead of "+oldFilename);
    //testFile = new File(LocoFile.getFileLocation()+newFilename);
   testFile.setFileName(QDir::homePath()+"/.jmri/roster/"+newFilename);
  }
  setFileName(newFilename);
  log->debug("new filename: "+getFileName());
 }
}

/*public*/ void   RosterEntry::setRoadName(QString s) {
    QString old = _roadName;
    _roadName = s;
    firePropertyChange("roadname", old, s);
}
/*public*/ QString RosterEntry::getRoadName() { return _roadName; }

/*public*/ void   RosterEntry::setRoadNumber(QString s) {
    QString old = _roadNumber;
    _roadNumber = s;
    firePropertyChange("roadname", old, s);
}
/*public*/ QString RosterEntry::getRoadNumber() { return _roadNumber; }

/*public*/ void   RosterEntry::setMfg(QString s) {
    QString old = _mfg;
    _mfg = s;
    firePropertyChange("mfg", old, s);
}
/*public*/ QString RosterEntry::getMfg() { return _mfg; }

/*public*/ void   RosterEntry::setModel(QString s) {
    QString old = _model;
    _model = s;
    firePropertyChange("model", old, s);
}
/*public*/ QString RosterEntry::getModel() { return _model; }

/*public*/ void   RosterEntry::setOwner(QString s) {
    QString old = _owner;
    _owner = s;
    firePropertyChange("owner", old, s);
}
/*public*/ QString RosterEntry::getOwner() { return _owner; }

/*public*/ void   RosterEntry::setDccAddress(QString s)
{
 QString old = _dccAddress;
 _dccAddress = s;
 firePropertyChange("dccaddress", old, s);
}
/*public*/ QString RosterEntry::getDccAddress() { return _dccAddress; }

/*public*/ void RosterEntry::setLongAddress(bool b)
{
 bool old = false;
 if(_protocol==LocoAddress::DCC_LONG)
  old = true;
 if(b)
  _protocol=LocoAddress::DCC_LONG;
 else
  _protocol=LocoAddress::DCC_SHORT;
 firePropertyChange("longaddress", old, (b));
}

/*public*/ RosterSpeedProfile* RosterEntry::getSpeedProfile()
{
 return _sp;
}

/*public*/ void RosterEntry::setSpeedProfile(RosterSpeedProfile* sp)
{
 if (sp->getRosterEntry() != this)
 {
  log->error("Attempting to set a speed profile against the wrong roster entry");
  return;
 }
 RosterSpeedProfile* old = this->_sp;
 _sp = sp;
 this->firePropertyChange(RosterEntry::SPEED_PROFILE, VPtr<RosterSpeedProfile>::asQVariant(old), VPtr<RosterSpeedProfile>::asQVariant(this->_sp));
}
/*public*/ bool RosterEntry::isLongAddress() {
    if(_protocol==LocoAddress::DCC_LONG)
        return true;
    return false;
}

/*public*/ void RosterEntry::setProtocol(LocoAddress::Protocol protocol){
    LocoAddress::Protocol old = _protocol;
    _protocol = protocol;
    firePropertyChange("protocol", old, _protocol);
}

/*public*/ LocoAddress::Protocol RosterEntry::getProtocol(){
    return _protocol;
}

/*public*/ QString RosterEntry::getProtocolAsString(){
    return LocoAddress::getPeopleName(_protocol);
}

/*public*/ void   RosterEntry::setComment(QString s) {
    QString old = _comment;
    _comment = s;
    firePropertyChange("comment", old, s);
}
/*public*/ QString RosterEntry::getComment() { return _comment; }

/*public*/ void   RosterEntry::setDecoderModel(QString s) {
    QString old = _decoderModel;
    _decoderModel = s;
    firePropertyChange("decodermodel", old, s);
}
/*public*/ QString RosterEntry::getDecoderModel() { return _decoderModel; }

/*public*/ void   RosterEntry::setDecoderFamily(QString s) {
    QString old = _decoderFamily;
    _decoderFamily = s;
    firePropertyChange("decoderfamily", old, s);
}
/*public*/ QString RosterEntry::getDecoderFamily() { return _decoderFamily; }

/*public*/ void   RosterEntry::setDecoderComment(QString s) {
    QString old = _decoderComment;
    _decoderComment = s;
    firePropertyChange("decodercomment", old, s);
}
/*public*/ QString RosterEntry::getDecoderComment() { return _decoderComment; }

/*public*/ DccLocoAddress* RosterEntry::getDccLocoAddress() {
    int n;
    bool bOk;
    n = getDccAddress().toInt(&bOk);
    if(!bOk)
    {
     log->error("Illegal format for DCC address roster entry: \""+getId()+"\" value: \""+getDccAddress()+"\"");
     n = 0;
    }
    return new DccLocoAddress(n,_protocol);
}

/*public*/ void RosterEntry::setImagePath(QString s) {
    QString old = _imageFilePath;
    _imageFilePath = s;
    firePropertyChange("imagefilepath", old, s);
}
/*public*/ QString RosterEntry::getImagePath() { return _imageFilePath; }

/*public*/ void RosterEntry::setIconPath(QString s) {
    QString old = _iconFilePath;
    _iconFilePath = s;
    firePropertyChange("iconfilepath", old, s);
}
/*public*/ QString RosterEntry::getIconPath() { return _iconFilePath; }

/*public*/ void RosterEntry::setShuntingFunction(QString fn){
 QString old = this->_isShuntingOn;
 _isShuntingOn = fn;
 this->firePropertyChange(RosterEntry::SHUNTING_FUNCTION, old, this->_isShuntingOn);
}
/*public*/ QString RosterEntry::getShuntingFunction(){ return _isShuntingOn; }

/*public*/ void RosterEntry::setURL(QString s) {
    QString old = _URL;
    _URL = s;
    firePropertyChange("url", old, s);
}
/*public*/ QString RosterEntry::getURL() { return _URL; }

/*public*/ void RosterEntry::setDateModified(/*@Nonnull*/ QDateTime date) {
        QDateTime old = this->dateModified;
        this->dateModified = date;
        this->firePropertyChange(RosterEntry::DATE_UPDATED, old, date);
}

/**
 * Set the date modified given a string representing a date.
 * <p>
 * Tries ISO 8601 and the current Java defaults as formats for parsing a date.
 *
 * @param date the string to parse into a date
 * @throws ParseException if the date cannot be parsed
 */
/*public*/ void RosterEntry::setDateModified(/*@Nonnull*/ QString date) throw (ParseException) {
 try
 {
  // parse using ISO 8601 date format(s)
  QDateTime dt = QDateTime::fromString(date, Qt::ISODate);
  if(!dt.isValid()) throw ParseException(tr("error parsing date '%1'").arg(date));
  this->setDateModified(dt);
 }
 catch (ParseException ex)
 {
  log->debug("ParseException in setDateModified");
  // parse using defaults since thats how it was saved if saved
  // by earlier versions of JMRI
  QDateTime dt = QDateTime::fromString(date,"dddd, d MMMM yy hh:mm:ss");
  if(!dt.isValid()) throw IllegalArgumentException(tr("error parsing date '%1'").arg(date));
  this->setDateModified(dt);
 }
 catch (IllegalArgumentException ex2)
 {
  // warn that there's perhaps something wrong with the classpath
  log->error("IllegalArgumentException in RosterEntry.setDateModified - this may indicate a problem with the classpath, specifically multiple copies of the 'jackson` library. See release notes" );
  // parse using defaults since thats how it was saved if saved
  // by earlier versions of JMRI
  //this.setDateModified(DateFormat.getDateTimeInstance().parse(date));
 }
}

//@CheckForNull
/*public*/ QDateTime RosterEntry::getDateModified() {
    return this->dateModified;
}

/*public*/ void RosterEntry::setDateUpdated(QString s)
{
 QString old = _dateUpdated;
 _dateUpdated = s;
 try
 {
  this->setDateModified(s);
 }
 catch (ParseException ex) {
     log->warn(tr("Unable to parse \"%1\" as a date in roster entry \"%2\".").arg(s).arg(getId()));
     // property change is fired by setDateModified if s parses as a date
     firePropertyChange(RosterEntry::DATE_UPDATED, old, s);
 }
}
/*public*/ QString RosterEntry::getDateUpdated() { return _dateUpdated; }

//openCounter is used purely to indicate if the roster entry has been opened in an editing mode.
/*public*/ void RosterEntry::setOpen(bool boo){
    if(boo){
        openCounter++;
    } else {
        openCounter--;
    }
    if(openCounter<0){
        openCounter=0;
    }
}

/*public*/ bool RosterEntry::isOpen(){
    if(openCounter==0)
        return false;
    return true;
}

/**
 * Define label for a specific function
 * @param fn function number, starting with 0
 */
/*public*/ void RosterEntry::setFunctionLabel(int fn, QString label) {
//    if (functionLabels == NULL) functionLabels = new QString[MAXFNNUM+1]; // counts zero
//    functionLabels[fn] = label;
 if(functionLabels.isEmpty())
 {
  for(int i=0; i < MAXFNNUM+1; i ++)
   functionLabels.append("");
 }
 functionLabels.replace(fn,label);
}

/**
 * If a label has been defined for a specific function,
 * return it, otherwise return NULL.
 * @param fn function number, starting with 0
 */
/*public*/ QString RosterEntry::getFunctionLabel(int fn) {
//    if (functionLabels == NULL) return NULL;
//    if (fn <0 || fn >MAXFNNUM)
//        throw new IllegalArgumentException("number out of range: "+fn);
//    return functionLabels[fn];
  if(functionLabels.isEmpty()) return "";
  if (fn < 0 || fn > MAXFNNUM) {
   throw IllegalArgumentException("number out of range: " + QString::number(fn));
  }
  return functionLabels.at(fn);
}

/**
 * Define label for a specific sound
 *
 * @param fn    sound number, starting with 0
 * @param label
 */
/*public*/ void RosterEntry::setSoundLabel(int fn, QString label) {
    if (soundLabels.isEmpty()) {
        soundLabels = QVector<QString>(MAXSOUNDNUM + 1); // counts zero
    }
    QString old = this->soundLabels[fn];
    soundLabels.replace(fn, label);
    this->firePropertyChange(RosterEntry::SOUND_LABEL + fn, old, this->soundLabels[fn]);
}

/**
 * If a label has been defined for a specific sound, return it, otherwise
 * return null.
 *
 * @param fn sound number, starting with 0
 * @return sound label or null
 */
/*public*/ QString RosterEntry::getSoundLabel(int fn) {
    if (soundLabels.isEmpty()) {
     return "";
    }
    if (fn < 0 || fn > MAXSOUNDNUM) {
        throw IllegalArgumentException("number out of range: " + QString::number(fn));
    }
    return soundLabels[fn];
}
/*public*/ void RosterEntry::setFunctionImage(int fn, QString s)
{
 //if (functionImages == NULL) functionImages = new QString[MAXFNNUM+1]; // counts zero
 if(functionImages.isEmpty())
 {
  for(int i=0; i < MAXFNNUM+1; i ++)
   functionImages.append("");
 }

 QString old = functionImages.at(fn);
 functionImages.replace(fn, s);
 firePropertyChange("functionImage"+QString::number(fn), old, s);

 //QString dropFolder = FileUtil::getUserFilesPath();
 QString dropFolder = LocoFile::getFileLocation();
 File* source = new File(s);
 if(!source->exists())
 {
  log->error(tr("file %s does not exist").arg(source->getPath()));
 }
 File* dest = new File(s);
 if (dropFolder != NULL) {
     dest = new File(dropFolder + /*File::separatorChar +*/ source->getName());
     if (source->getParent().compare(dest->getParent()) != 0) {
         try {
             FileUtil::createDirectory(dest->getParentFile()->getPath());
             FileUtil::copy(source, dest);
         } catch (IOException ex) {
             log->error("filesDropped: error while copying new file, using original file");
             dest = source;
         }
     }
 }
 functionImages.replace(fn, dest->getPath());
}
/*public*/ QString RosterEntry::getFunctionImage(int fn)
{
 if ((!functionImages.isEmpty()) && (functionImages.at(fn) != ""))
  return functionImages.at(fn);
 return "";
}

/*public*/ void RosterEntry::setFunctionSelectedImage(int fn, QString s)
{
 //if (functionSelectedImages == NULL) functionSelectedImages = new QString[MAXFNNUM+1]; // counts zero
 if(functionSelectedImages.isEmpty())
 {
  for(int i=0; i < MAXFNNUM+1; i ++)
   functionSelectedImages.append("");
 }

 QString old = functionSelectedImages.at(fn);
 functionSelectedImages.replace(fn,s);
 firePropertyChange("functionSelectedImage"+QString::number(fn), old, s);

 //QString dropFolder = FileUtil::getUserFilesPath();
 QString dropFolder = LocoFile::getFileLocation();
 File* source = new File(s);
 File* dest = new File(s);
 if (dropFolder != NULL && source->getPath() != "")
 {
  dest = new File(dropFolder + /*File::separatorChar +*/ source->getName());
  if (source->getParent().compare(dest->getParent()) != 0)
  {
   try {
       FileUtil::createDirectory(dest->getParentFile()->getPath());
       FileUtil::copy(source, dest);
   } catch (IOException ex) {
       log->error("filesDropped: error while copying new file, using original file");
       dest = source;
   }
  }
 }
 functionSelectedImages.replace(fn, dest->getPath());
}

/*public*/ QString RosterEntry::getFunctionSelectedImage(int fn)
{
 if ((!functionSelectedImages.isEmpty()) && (functionSelectedImages.at(fn) != ""))
  return functionSelectedImages.at(fn);
 return "";
}

/**
 * Define whether a specific function is lockable.
 * @param fn function number, starting with 0
 */
/*public*/ void RosterEntry::setFunctionLockable(int fn, bool lockable)
{
 if (functionLockables.isEmpty())
 {
  //functionLockables = new bool[MAXFNNUM+1]; // counts zero
  //for (int i = 0; i < functionLockables.length; i++) functionLockables[i] = true;
  for(int i=0; i < MAXFNNUM+1; i++)
   functionLockables.append(true);
 }
 functionLockables.replace(fn,lockable);
}


/**
 * Return the lockable state of a specific function. Defaults to true.
 * @param fn function number, starting with 0
 */
/*public*/ bool RosterEntry::getFunctionLockable(int fn) {
    if (functionLockables.isEmpty()) return true;
    if (fn <0 || fn >MAXFNNUM)
        throw IllegalArgumentException("number out of range: "+QString::number(fn));
 return functionLockables.at(fn);
}

/**
 * Provide access to the set of attributes.  This
 * is directly backed access, so e.g. removing an item
 * from this Set removes it from the RosterEntry too.
 */
/*public*/ QSet<QString> RosterEntry::getAttributes()
{
 QSet<QString> newSet;
 if (attributePairs==NULL) return newSet;
 //return attributePairs->keys();
 foreach(QString s, attributePairs->keys())
  newSet.insert(s);
 return newSet;
}

/*public*/ QStringList RosterEntry::getAttributeList()
{
 QStringList newList;
 if (attributePairs->isEmpty()) return newList;
    return attributePairs->keys(); //.toArray(new QString[attributePairs->size()]);
}
/**
 * List the roster groups this entry is a member of, returning existing
 * {@link jmri.jmrit.roster.rostergroup.RosterGroup}s from the default
 * {@link jmri.jmrit.roster.Roster} if they exist.
 *
 * @return list of roster groups
 */
/*public*/ QList<RosterGroup*> RosterEntry::getGroups() {
    return this->getGroups(Roster::getDefault());
}

/**
 * List the roster groups this entry is a member of, returning existing
 * {@link jmri.jmrit.roster.rostergroup.RosterGroup}s from the specified
 * {@link jmri.jmrit.roster.Roster} if they exist.
 *
 * @param roster the roster to get matching groups from
 * @return list of roster groups
 */
/*public*/ QList<RosterGroup*> RosterEntry::getGroups(Roster* roster) {
    QList<RosterGroup*> groups = QList<RosterGroup*>();
    if (!this->getAttributes().isEmpty()) {
        foreach (QString attribute, this->getAttributes()) {
            if (attribute.startsWith(Roster::ROSTER_GROUP_PREFIX)) {
                QString name = attribute.mid(Roster::ROSTER_GROUP_PREFIX.length());
                if (roster->getRosterGroups().contains(name)) {
                    groups.append(roster->getRosterGroups().value(name));
                } else {
                    groups.append(new RosterGroup(name));
                }
            }
        }
    }
    return groups;
}

/*public*/ int RosterEntry::getMaxSpeedPCT() {
    return _maxSpeedPCT;
}

/*public*/ void RosterEntry::setMaxSpeedPCT(int maxSpeedPCT) {
    _maxSpeedPCT = maxSpeedPCT;
}

/**
 * Warn user that the roster entry needs to be resaved.
 */
/*protected*/ void RosterEntry::warnShortLong(QString id) {
    log->warn("Roster entry \""+id+"\" should be saved again to store the short/long address value");
}

/**
 * Create an XML element to represent this Entry. This member has to remain synchronized with the
 * detailed DTD in roster-config.xml.
 * @return Contents in a JDOM Element
 */
/*public*/ QDomElement RosterEntry::store(QDomDocument doc)
{
 QDomElement e = doc.createElement("locomotive");
 e.setAttribute("id", getId());
 e.setAttribute("fileName", getFileName());
 e.setAttribute("roadNumber",getRoadNumber());
 e.setAttribute("roadName",getRoadName());
 e.setAttribute("mfg",getMfg());
 e.setAttribute("owner",getOwner());
 e.setAttribute("model",getModel());
 e.setAttribute("dccAddress",getDccAddress());
 e.setAttribute("protocol",getProtocolAsString());
 e.setAttribute("comment",getComment());
 e.setAttribute("maxSpeed", getMaxSpeedPCT());
 // file path are saved without default xml config path
 //e.setAttribute("imageFilePath", getImagePath().mid( FileUtil::getUserResourcePath().length() ));
 e.setAttribute("imageFilePath", FileUtil::getPortableFilename(getImagePath(),false, false));
 e.setAttribute("iconFilePath", FileUtil::getPortableFilename(getIconPath(),false, false));
 e.setAttribute("URL", getURL());
 e.setAttribute("IsShuntingOn", getShuntingFunction());

 if (_dateUpdated!=(""))
  e.appendChild(createTextElement(doc, QString("dateUpdated"), getDateUpdated()));
 QDomElement d = doc.createElement("decoder");
 d.setAttribute("model",getDecoderModel());
 d.setAttribute("family",getDecoderFamily());
 d.setAttribute("comment",getDecoderComment());
 d.setAttribute("rfidtag", getRfidTag());

 e.appendChild(d);

 if (_dccAddress==(""))
 {
  //e.appendChild(new LocoAddressXml()).store(NULL));  // store a NULL address
  e.appendChild(storeLocoAddress(doc,NULL));
 }
 else
 {
  //e.appendChild(new LocoAddressXml()).store(new DccLocoAddress((_dccAddress), _protocol)));
  e.appendChild(storeLocoAddress(doc,new DccLocoAddress((_dccAddress.toInt()), _protocol)));
 }
#if 1
 if (!functionLabels.isEmpty())
 {
  d = doc.createElement("functionlabels");

  // loop to copy non-NULL elements
  for (int i = 0; i<MAXFNNUM+1; i++)
  {
   if (!functionLabels.at(i).isNull() && functionLabels.at(i)!=(""))
   {
    QDomElement fne = doc.createElement("functionlabel");
    fne.setAttribute("num", QString::number(i));
    bool lockable = false;
    if (!functionLockables.isEmpty()) lockable = functionLockables.at(i);
    fne.setAttribute("lockable", lockable ? QString("true"):QString("false"));

    if ((!functionImages.isEmpty()) && (functionImages.at(i)!=""))
    {
//     try
//     {
      fne.setAttribute("functionImage", FileUtil::getPortableFilename(functionImages[i]));
//     }
//     catch (StringIndexOutOfBoundsException eob)
//     {
//      fne.setAttribute("functionImage", "");
//     }
    }
    if ((!functionSelectedImages.isEmpty()) && (functionSelectedImages.at(i)!=""))
    {
//     try
//     {
      fne.setAttribute("functionImageSelected", FileUtil::getPortableFilename(functionSelectedImages[i]));
//     }
//     catch (QStringIndexOutOfBoundsException eob)
//     {
//      fne.setAttribute("functionImageSelected", "");
//     }
    }
    fne.appendChild(doc.createTextNode(functionLabels.at(i)));
    d.appendChild(fne);
   }
  }
  e.appendChild(d);
 }
#endif
 QSet<QString> keyset = getAttributes();
 if (!keyset.isEmpty())
 {
  //java.util.Iterator<QString> keys = keyset.iterator();
  QSetIterator<QString> keys(keyset);
  if (keys.hasNext())
  {
   d = doc.createElement("attributepairs");
   while (keys.hasNext())
   {
    QString key = keys.next();
    QString value = getAttribute(key);
//    d.appendChild(new Element("keyvaluepair")
//            .addContent(new Element("key")
//                .addContent(key)
//            )
//            .addContent(new Element("value")
//                .addContent(value)
//            )
//        );
    QDomElement keyvaluepair = doc.createElement("keyvaluepair");
    keyvaluepair.appendChild(createTextElement(doc,"key",key));
    keyvaluepair.appendChild(createTextElement(doc,"value",value));
    d.appendChild(keyvaluepair);
   }
   e.appendChild(d);
  }
 }
 if (_sp != NULL)
 {
  _sp->store(e);
 }

 return e;
}

///*public*/ QString RosterEntry::titleString() {
//    return getId();
//}

/*public*/ QString RosterEntry::toString() {
    QString out = "[RosterEntry: "+_id+" "
        +(_fileName!=NULL?_fileName:"<NULL>")
        +" "+_roadName
        +" "+_roadNumber
        +" "+_mfg
        +" "+_owner
        +" "+_model
        +" "+_dccAddress
        +" "+_comment
        +" "+_decoderModel
        +" "+_decoderFamily
        +" "+_decoderComment
        +"]";
    return out;
}

/**
 * Write the contents of this RosterEntry back to a file,
 * preserving all existing decoder content.
 * <p>
 * This writes the file back in place, with the same decoder-specific
 * content.
 */
/*public*/ void RosterEntry::updateFile()
{
#if 1
    LocoFile* df = new LocoFile();

    QString fullFilename = LocoFile::getFileLocation()+getFileName();

    // read in the content
    try {
        mRootElement = df->rootFromName(fullFilename);
    } catch (Exception e) { log->error("Exception while loading loco XML file: "+getFileName()+" exception: "+e.getMessage()); }

    try {
        QFile* f = new QFile(fullFilename);
        // do backup
        df->makeBackupFile(LocoFile::getFileLocation()+getFileName());

        // and finally write the file
        df->writeFile(f, mRootElement, this->store(QDomDocument("Roster") ));

    } catch (Exception e) {
        log->error("error during locomotive file output"/*, e*/);
//        try {
//            JOptionPane.showMessageDialog(NULL,
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getQString("ErrorSavingText")+"\n"+e.getMessage(),
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getQString("ErrorSavingTitle"),
//                    JOptionPane.ERROR_MESSAGE);
//        } catch (HeadlessException he) {
//            // silently ignore inability to display dialog
//        }
        QMessageBox::critical(0, tr("Error Saving Roster Entry"), tr("An error occurred writing the roster file, may not be complete: "));
    }
#endif
}
#if 1

/**
 * Write the contents of this RosterEntry to a file.
 * Information on the contents is passed through the parameters,
 * as the actual XML creation is done in the LocoFile class.
 *
 * @param cvModel  CV contents to include in file
 * @param variableModel Variable contents to include in file
 *
 */
/*public*/ void RosterEntry::writeFile(CvTableModel* cvModel, IndexedCvTableModel* iCvModel, VariableTableModel* variableModel) {
    LocoFile* df = new LocoFile();

    // do I/O
    FileUtil::createDirectory(LocoFile::getFileLocation());

    try {
        QString fullFilename = LocoFile::getFileLocation()+getFileName();
        QFile* f = new QFile(fullFilename);
        // do backup
        df->makeBackupFile(LocoFile::getFileLocation()+getFileName());

        // changed
        changeDateUpdated();

        // and finally write the file
        df->writeFile(f, cvModel, iCvModel, variableModel, this);

    } catch (Exception e) {
        log->error("error during locomotive file output"/*, e*/);
//        try {
//            JOptionPane.showMessageDialog(NULL,
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("ErrorSavingText")+"\n"+e.getMessage(),
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("ErrorSavingTitle"),
//                    JOptionPane.ERROR_MESSAGE);
//        } catch (HeadlessException he) {
//            // silently ignore inability to display dialog
//        }
        QMessageBox::critical(0, tr("Error Saving Roster Entry"), tr("An error occurred writing the roster file, may not be complete: "));
    }
}
#endif
/**
 * Mark the date updated, e.g. from storing this roster entry
 */
/*public*/ void RosterEntry::changeDateUpdated() 
{
//    java.text.DateFormat df = java.text.DateFormat.getDateTimeInstance();
//    setDateUpdated(df.format(new java.util.Date()));
    //setDateUpdated( QDateTime::currentDateTime().toString("MMM d, yyyy h:m:s AP"));
 setDateModified(QDateTime::currentDateTime());
}

/**
 * Load a pre-existing CvTableModel object with the CV contents
 * of this entry
 * @param cvModel Model to load, must exist
 */
/*public*/ void RosterEntry::loadCvModel(CvTableModel* cvModel, IndexedCvTableModel* iCvModel) {
    if (cvModel == NULL) log->error("loadCvModel must be given a non-NULL argument");
    if (mRootElement.isNull()) log->error("loadCvModel called before readFile() succeeded");
    try{
        LocoFile::loadCvModel(mRootElement.firstChildElement("locomotive"), cvModel, iCvModel);
    }
    catch (Exception ex)
    {
     log->error(tr("Error reading roster entry ")/*, ex.msg()*/);
//        try {
//            JOptionPane.showMessageDialog(NULL,
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getQString("ErrorReadingText"),
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getQString("ErrorReadingTitle"),
//                    JOptionPane.ERROR_MESSAGE);
//        } catch (HeadlessException he) {
//            // silently ignore inability to display dialog
//        }

    }
}

/*public*/ void RosterEntry::printEntry(HardcopyWriter* w)
{
 if (getIconPath()!=NULL)
 {
  ImageIcon* icon = new ImageIcon(getIconPath(),getIconPath());
  // we use an ImageIcon because it's guaranteed to have been loaded when ctor is complete
  //we set the imagesize to 150x150 pixels
  int imagesize = 150;

  QImage img = icon->getImage();
  int width = img.width();
  int height = img.height();
  double widthratio = (double) width/imagesize;
  double heightratio = (double) height/imagesize;
  double ratio = qMax(widthratio,heightratio);
  width = (int)(width/ratio);
  height = (int)(height/ratio);
  //QImage newImg = img.getScaledInstance(width, height, java.awt.Image.SCALE_SMOOTH);
  QImage newImg = img.scaled(width, height);

  ImageIcon* newIcon = new ImageIcon(newImg);
  w->writeNoScale(newIcon->getImage(), new JLabel());
  //Work out the number of line approx that the image takes up.
  //We might need to pad some areas of the roster out, so that things
  //look correct and text doesn't overflow into the image.
  blanks = (newImg.height()-w->getLineAscent())/w->getLineHeight();
  textSpaceWithIcon = w->getCharactersPerLine()-((newImg.width()/w->getCharWidth())) - indentWidth -1;
 }
 printEntryDetails(w);
}

/**
 *Prints the roster information. Updated to allow for multiline
 *comment and decoder comment fields.
 *Created separate write statements for text and line feeds to work
 *around the HardcopyWriter bug that misplaces borders
 */
/*public*/ void RosterEntry::printEntryDetails(HardcopyWriter* w)
{
 int linesadded = -1;
 QString title;
 try
 {
  //int indentWidth = indent.length();
  HardcopyWriter* ww = (HardcopyWriter*) w;
  int textSpace = ww->getCharactersPerLine() - indentWidth -1;
  title = "   ID:                ";
  if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
  {
    linesadded = writeWrappedComment(w, _id, title, textSpaceWithIcon) + linesadded;
  }
  else
  {
   linesadded = writeWrappedComment(w, _id, title, textSpace) + linesadded;
  }
  title = "   Filename:          ";
  if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
  {
   linesadded = writeWrappedComment(w, _fileName!=NULL?_fileName:"<NULL>", title, textSpaceWithIcon) + linesadded;
  }
  else
  {
   linesadded = writeWrappedComment(w, _fileName!=NULL?_fileName:"<NULL>", title, textSpace) + linesadded;
  }

  if (!(_roadName==("")))
  {
   title = "   Road name:         ";
   if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
   {
    linesadded = writeWrappedComment(w, _roadName, title, textSpaceWithIcon) + linesadded;
   }
   else
   {
    linesadded = writeWrappedComment(w, _roadName, title, textSpace) + linesadded;
   }
  }
  if (!(_roadNumber==("")))
  {
   title = "   Road number:       ";
   if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
   {
    linesadded = writeWrappedComment(w, _roadNumber, title, textSpaceWithIcon) + linesadded;
   }
   else
   {
    linesadded = writeWrappedComment(w, _roadNumber, title, textSpace) + linesadded;
   }
  }
  if (!(_mfg==("")))
  {
   title = "   Manufacturer:      ";
   if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
   {
    linesadded = writeWrappedComment(w, _mfg, title, textSpaceWithIcon) + linesadded;
   }
   else
   {
    linesadded = writeWrappedComment(w, _mfg, title, textSpace) + linesadded;
   }
  }
  if (!(_owner==("")))
  {
   title = "   Owner:             ";
  if ((textSpaceWithIcon!=0)&&(linesadded<blanks)){
    linesadded = writeWrappedComment(w, _owner, title, textSpaceWithIcon) + linesadded;
  } else {
    linesadded = writeWrappedComment(w, _owner, title, textSpace) + linesadded;
  }
}
if (!(_model==("")))
{
  title = "   Model:             ";
  if ((textSpaceWithIcon!=0)&&(linesadded<blanks)){
    linesadded = writeWrappedComment(w, _model, title, textSpaceWithIcon) + linesadded;
  } else {
    linesadded = writeWrappedComment(w, _model, title, textSpace) + linesadded;
  }
}
if (!(_dccAddress==("")))
{
  w->write(newLine,0,1);
  QString s = "   DCC Address:       " + _dccAddress;
  w->write(s,0,s.length());
  linesadded++;
}

//If there is a comment field, then wrap it using the new wrapCommment
//method and print it
if (!(_comment==("")))
{
    //Because the text will fill the width if the roster entry has an icon
    //then we need to add some blank lines to prevent the comment text going
    //through the picture.
    for(int i = 0; i<(blanks-linesadded); i++){
        w->write(newLine,0,1);
    }
    //As we have added the blank lines to pad out the comment we will
    //reset the number of blanks to 0.
    if (blanks!=0) blanks = 0;
    title = "   Comment:           ";
    linesadded = writeWrappedComment(w, _comment, title, textSpace) + linesadded;
 }
 if (!(_decoderModel==("")))
 {
  title = "   Decoder Model:     ";
  if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
  {
    linesadded = writeWrappedComment(w, _decoderModel, title, textSpaceWithIcon) + linesadded;
  } else {
    linesadded = writeWrappedComment(w, _decoderModel, title, textSpace) + linesadded;
  }
}
if (!(_decoderFamily==("")))
{
   title = "   Decoder Family:    ";
   if ((textSpaceWithIcon!=0)&&(linesadded<blanks))
   {
    linesadded = writeWrappedComment(w, _decoderFamily, title, textSpaceWithIcon) + linesadded;
   }
   else
   {
    linesadded = writeWrappedComment(w, _decoderFamily, title, textSpace) + linesadded;
   }
  }

  //If there is a decoderComment field, need to wrap it
  if (!(_decoderComment==("")))
  {
    //Because the text will fill the width if the roster entry has an icon
    //then we need to add some blank lines to prevent the comment text going
    //through the picture.
    for(int i = 0; i<(blanks-linesadded); i++){
    w->write(newLine,0,1);
   }
   //As we have added the blank lines to pad out the comment we will
   //reset the number of blanks to 0.
   if (blanks!=0) blanks = 0;
   title = "   Decoder Comment:   ";
   linesadded = writeWrappedComment(w, _decoderComment, title, textSpace) + linesadded;
  }
  w->write(newLine,0,1);
  for(int i = -1; i<(blanks-linesadded); i++)
  {
   w->write(newLine,0,1);
  }
 }
 catch (IOException e)
 {
  log->error("Error printing RosterEntry: "+e.getMessage());
 }
}

/*private*/ int RosterEntry::writeWrappedComment(HardcopyWriter* w, QString text, QString title, int textSpace)
{
 QVector<QString> commentVector = wrapComment(text, textSpace);

 //Now have a vector of text pieces and line feeds that will all
 //fit in the allowed space. Print each piece, prefixing the first one
 //with the label and indenting any remainding.
 QString s;
 int k = 0;
 try
 {
  w->write(newLine,0,1);
  s = title + commentVector.at(k);
  w->write(s,0,s.length());
  k++;
  while (k < commentVector.size())
  {
   QString token = commentVector.at(k);
   if (token!=("\n")) s = indent + token;
   else s = token;
   w->write(s,0,s.length());
   k++;
  }
 }
 catch (IOException e)
 {
  log->error("Error printing RosterEntry: "+e.getMessage());
 }
 return k;
}

/**
 * Take a QString comment field and perform line wrapping on it.
 * QString must be non-NULL and may or may not have \n
 * characters embedded.
 * textSpace is the width of the space to print for wrapping purposes.
 * The comment is wrapped on a word wrap basis
 */
/*public*/ QVector<QString> RosterEntry::wrapComment(QString comment, int textSpace)
{
 //Tokenize the string using \n to separate the text on multiple lines
 //and create a vector to hold the processed text pieces
 //QStringTokenizer commentTokens = new QStringTokenizer (comment,"\n",true);
 QStringList commentTokens = comment.split("\n");
 QVector<QString> textVector =  QVector<QString>(commentTokens.count());
 QString newLine = "\n";
 QStringListIterator iter(commentTokens);
 while (iter.hasNext())
 {
  QString commentToken = iter.next();
  int startIndex = 0;
  int endIndex = textSpace;
  //Check each token to see if it needs to have a line wrap.
  //Get a piece of the token, either the size of the allowed space or
  //a shorter piece if there isn't enough text to fill the space
  if (commentToken.length() < startIndex+textSpace)
  {
   //the piece will fit so extract it and put it in the vector
   textVector.append(commentToken);
  }
  else
  {
   //Piece too long to fit. Extract a piece the size of the textSpace
   //and check for farthest right space for word wrapping.
   if (log->isDebugEnabled()) log->debug("token: /"+commentToken+"/");
   while (startIndex < commentToken.length())
   {
    QString tokenPiece = commentToken.mid(startIndex, startIndex + textSpace);
    if (log->isDebugEnabled()) log->debug("loop: /"+tokenPiece+"/ "+tokenPiece.lastIndexOf(" "));
    if (tokenPiece.lastIndexOf(" ") == -1)
    {
     //If no spaces, put the whole piece in the vector and add a line feed, then
     //increment the startIndex to reposition for extracting next piece
     textVector.append(tokenPiece);
     textVector.append(newLine);
     startIndex += textSpace;
    }
    else
    {
     //If there is at least one space, extract up to and including the
     //last space and put in the vector as well as a line feed
     endIndex = tokenPiece.lastIndexOf(" ") + 1;
     if (log->isDebugEnabled()) log->debug("/"+tokenPiece+"/ "+startIndex+" "+endIndex);
     textVector.append(tokenPiece.mid(0, endIndex));
     textVector.append(newLine);
     startIndex += endIndex;
    }
    //Check the remaining piece to see if it fits - startIndex now points
    //to the start of the next piece
    if (commentToken.mid(startIndex).length() < textSpace)
    {
     //It will fit so just insert it, otherwise will cycle through the
     //while loop and the checks above will take care of the remainder.
     //Line feed is not required as this is the last part of the token.
     tokenPiece = commentToken.mid(startIndex);
     textVector.append(commentToken.mid(startIndex));
     startIndex += textSpace;
    }
   }
  }
 }
 return textVector;
}

/**
 * Read a file containing the contents of this RosterEntry.
 * This has to be done before a call to loadCvModel, for example.
 */
/*public*/ void RosterEntry::readFile() {
    if (getFileName() == NULL) {
        log->debug("readFiler file invoked with NULL filename");
        return;
    }
    else if (log->isDebugEnabled()) log->debug("readFile invoked with filename "+getFileName());

    LocoFile* lf = new LocoFile();  // used as a temporary
    try {
        mRootElement = lf->rootFromName(LocoFile::getFileLocation()+getFileName());
    } catch (Exception e) { log->error(tr("Exception while loading loco XML file: ")+getFileName()+tr(" exception: ")+e.getMessage()); }
}


/*public*/ /*synchronized*/ void RosterEntry::addPropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);
 if (pcs == NULL) pcs = new PropertyChangeSupport(this);
 pcs->addPropertyChangeListener(l);
}

/*protected*/ /*synchronized*/ void RosterEntry::firePropertyChange(QString p, QVariant old, QVariant n)
{
    QMutexLocker locker(&mutex);
    if (pcs == NULL) pcs = new PropertyChangeSupport(this);
    pcs->firePropertyChange(p,old,n);
    emit propertyChange(new PropertyChangeEvent(this, p, old,n));
}

/*public*/ /*synchronized*/ void RosterEntry::removePropertyChangeListener(PropertyChangeListener* l)
{
    QMutexLocker locker(&mutex);
    if (pcs == NULL) pcs = new PropertyChangeSupport(this);
    pcs->removePropertyChangeListener(l);
}

//// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(RosterEntry.class.getName());

//}

/**
* Construct this Entry from XML. This member has to remain synchronized with the
* detailed DTD in roster-config.xml
*
* @param e  Locomotive XML element
*/
/*public*/ RosterEntry::RosterEntry(QDomElement e)
{
 init();
 if (log->isDebugEnabled()) log->debug("ctor from element "+e.tagName());
  QString a;
  if ((a = e.attribute("id"))!="" )  _id = a;
  else log->warn("no id attribute in locomotive element when reading roster");
  if ((a = e.attribute("fileName")) != "" )  _fileName = a;
  if ((a = e.attribute("roadName")) != "" )  _roadName = a;
  if ((a = e.attribute("roadNumber")) != "" )  _roadNumber = a;
  if ((a = e.attribute("owner")) != "" )  _owner = a;
  if ((a = e.attribute("mfg")) != "" )  _mfg = a;
  if ((a = e.attribute("model")) != "" )  _model = a;
  if ((a = e.attribute("dccAddress")) != "" )  _dccAddress = a;

  // file path were saved without default xml config path
  if ((a = e.attribute("imageFilePath")) != "" )
  {
   try
   {
    if (FileUtil::getFile(a)->isFile())
    {
     _imageFilePath = FileUtil::getAbsoluteFilename(a);
    }
   }
   catch (FileNotFoundException ex)
   {
    if(a.contains(":"))
     a = a.mid(a.indexOf(":")+1);
    try
    {
     if(FileUtil::getFile(FileUtil::getUserResourcePath() + a)->isFile())
     {
      _imageFilePath = FileUtil::getUserResourcePath() + a;
     }
     QString p = FileUtil::locateFile(FileUtil::getProgramPath(), a);
     if(p != "" && FileUtil::getFile(p)->isFile())
      _imageFilePath = p;
    }
    catch (FileNotFoundException ex1)
    {
        _imageFilePath = "";
    }
   }
  }
  if ((a = e.attribute("iconFilePath")) != "" )
  {
   try
   {
    if (FileUtil::getFile(a)->isFile())
    {
        _iconFilePath = FileUtil::getAbsoluteFilename(a);
    }
   } catch (FileNotFoundException ex)
   {
    if(a.contains(":"))
     a = a.mid(a.indexOf(":")+1);
    try
    {
    if (FileUtil::getFile(FileUtil::getUserResourcePath() + a)->isFile())
    {
      _iconFilePath = FileUtil::getUserResourcePath() + a;
     }
    QString p = FileUtil::locateFile(FileUtil::getProgramPath(), a);
    if(p != "" && FileUtil::getFile(p)->isFile())
     _imageFilePath = p;
    }
    catch (FileNotFoundException ex1)
    {
     _iconFilePath = "";
    }
   }
  }
  if ((a = e.attribute("URL")) != "" )  _URL = a;
  if ((a = e.attribute("IsShuntingOn")) != "" )
   _isShuntingOn = a;
  if ((a = e.attribute("maxSpeed")) != "" )
       _maxSpeedPCT = a.toInt();
  QDomElement e3;
   if (!(e3 = e.firstChildElement("dateUpdated")).isNull())
   {
    _dateUpdated = e3.text();
   }
   if (!(e3 = e.firstChildElement("locoaddress")).isNull() )
   {
    DccLocoAddress* la = (DccLocoAddress*)(getAddress(e3));
    if (la!=NULL)
    {
     _dccAddress = QString::number(la->getNumber());
     _protocol = la->getProtocol();
    }
    else
    {
     _dccAddress = "";
     _protocol = LocoAddress::DCC_SHORT;
    }
   }
   else
   {// Did not find "locoaddress" element carrying the short/long, probably
           // because this is an older-format file, so try to use system default.
           // This is generally the best we can do without parsing the decoder file now
           // but may give the wrong answer in some cases (low value long addresses on NCE)

    ThrottleManager* tf = InstanceManager::throttleManagerInstance();
    int address =0;
    bool bOk;
    //try {
    address = _dccAddress.toInt(&bOk);
    if(!bOk) { address = 3;}  // ignore, accepting the default value
    if (tf!=NULL && tf->canBeLongAddress(address) && !tf->canBeShortAddress(address))
    {
     // if it has to be long, handle that
     _protocol = LocoAddress::DCC_LONG;
    }
    else if (tf!=NULL && !tf->canBeLongAddress(address) && tf->canBeShortAddress(address))
    {
     // if it has to be short, handle that
     _protocol = LocoAddress::DCC_SHORT;
    }
    else
    {
     // else guess short address
     // These people should resave their roster, so we'll warn them
     warnShortLong(_id);
     _protocol = LocoAddress::DCC_SHORT;

    }

   }
   if ((a = e.attribute("comment")) != "" )  _comment = a;
   QDomElement d = e.firstChildElement("decoder");
   if (!d.isNull())
   {
    if ((a = d.attribute("model")) != "" )  _decoderModel = a;
    if ((a = d.attribute("family")) != "" )  _decoderFamily = a;
    if ((a = d.attribute("comment")) != "" )  _decoderComment = a;
   }
   if((a = e.attribute("rfidtag")) != "" )_rfidTag = a.toInt();

   loadFunctions(e.firstChildElement("functionlabels"));
   // Temporarily ignore soundlabels in Roster Entry until  they are user-editable and resettable to defaults.
   // Needed to correct bad sound labels from ESU definitions - only ones used to date.
   //         loadSounds(e.getChild("soundlabels"), "RosterEntry");
   loadAttributes(e.firstChildElement("attributepairs").toElement());

   if (e.firstChildElement(RosterEntry::SPEED_PROFILE) != QDomElement())
   {
    _sp = new RosterSpeedProfile(this);
    _sp->load(e.firstChildElement(RosterEntry::SPEED_PROFILE));
   }
}

/**
* Loads function names from a
* JDOM element.  Does not change values that are already present!
*/
//@SuppressWarnings("unchecked")
/*public*/ void RosterEntry::loadFunctions(QDomElement e3)
{
 /*Load flag once, means that when the roster entry is edited only the first set of function labels are displayed
   ie those saved in the roster file, rather than those being left blank
   rather than being over-written by the defaults linked to the decoder def*/
 if(loadedOnce)
  return;
 if (!e3 .isNull())
 {
  // load function names
  //java.util.List<Element> l = e3.getChildren("functionlabel");
  QDomNodeList l = e3.childNodes();
  for (int i = 0; i < l.size(); i++)
  {
   QDomElement fn = l.at(i).toElement();
   int num = fn.attribute("num").toInt();
   QString lock = fn.attribute("lockable");
   QString functionImage = fn.attribute("functionImage");
   QString functionImageSelected = fn.attribute("functionImageSelected");
   QString val = fn.text();
   if (this->getFunctionLabel(num).isEmpty())
   {
    this->setFunctionLabel(num, val);
    this->setFunctionLockable(num, lock==("true"));
    QString a;
    if ((a = fn.attribute("functionImage")) != "")
     this->setFunctionImage(num, FileUtil::getAbsoluteFilename(a));
    if ((a = fn.attribute("functionImageSelected")) != "")
     this->setFunctionSelectedImage(num, FileUtil::getAbsoluteFilename(a));
   }
  }
 }
 loadedOnce = true;
}

/**
* Loads attribute key/value pairs from a
* JDOM element.
*/
//@SuppressWarnings("unchecked")
/*public*/ void RosterEntry::loadAttributes(QDomElement e3)
{
 if (!e3.isNull())
 {
  //java.util.List<Element> l = e3.getChildren("keyvaluepair");
  QDomNodeList l = e3.childNodes();

  for (int i = 0; i < l.size(); i++)
  {
   QDomElement fn = l.at(i).toElement();
   QString key = fn.firstChildElement("key").toElement().text();
   QString value = fn.firstChildElement("value").toElement().text();
   this->putAttribute(key, value);
  }
 }
}
/*public*/ LocoAddress* RosterEntry::getAddress(QDomElement element)
{
 if(!element.firstChildElement("dcclocoaddress").isNull())
 {
  DccLocoAddressXml* adapter = new DccLocoAddressXml();
  return adapter->getAddress(element.firstChildElement("dcclocoaddress"));
 }
 int addr = 0;
 bool bOk = false;
 addr = element.firstChildElement("number").text().toInt(&bOk);
 if(!bOk)
 {
  return NULL;
 }
 QString protocol = element.firstChildElement("protocol").text();
 LocoAddress::Protocol prot = LocoAddress::getByShortName(protocol);
 return new DccLocoAddress(addr, prot);
}
/*public*/ void RosterEntry::putAttribute(QString key, QString value)
{
 QString oldValue = getAttribute(key);
 if (attributePairs==NULL) attributePairs = new QMap<QString,QString>();
 attributePairs->insert(key, value);
 firePropertyChange("attributeUpdated:"+key, oldValue, value);
}
/*public*/ QString RosterEntry::getAttribute(QString key)
{
 if (attributePairs == NULL) return "";
  return attributePairs->value(key);
}

/*public*/ void RosterEntry::deleteAttribute(QString key)
{
 if (attributePairs!= NULL)
 {
  attributePairs->remove(key);
  firePropertyChange("attributeDeleted", key, 0);
 }
}
/*public*/ QString RosterEntry::titleString() {
    return getId();
}
QDomElement RosterEntry::createTextElement(QDomDocument doc, QString tagName, QString text)
{
 QDomElement eText = doc.createElement(tagName);
 QDomText t = doc.createTextNode(text);
 eText.appendChild(t);
 return eText;
}
QDomElement RosterEntry::storeLocoAddress(QDomDocument doc, LocoAddress* p)
{
 QDomElement element = doc.createElement("locoaddress");

 // include contents, we shall also store the old format for backward compatability
 DccLocoAddressXml* adapter = new DccLocoAddressXml();

 element.appendChild(adapter->store(p));

 if (p!=NULL)
 {
  element.appendChild(createTextElement(doc,QString("number"), QString("%1").arg(p->getNumber())));
  //element.appendChild(createTextElement(doc,QString("protocol"),QString("%1").arg(p->getProtocol().getShortName())));
  element.appendChild(createTextElement(doc,QString("protocol"),QString("%1").arg(LocoAddress::getShortName(p->getProtocol()))));
 }
 else
 {
  element.appendChild(createTextElement(doc,"number",""));
  element.appendChild(createTextElement(doc,"protocol",""));
 }

 return element;
}
qint32 RosterEntry::getRfidTag() {return _rfidTag;}
void RosterEntry::setRfidTag(QString tag)
{
 bool bOk;
 _rfidTag  = tag.toInt(&bOk, 16);
 if(!bOk)
     log->error(tr("'%1' is not a valid hexadecimal number!").arg(tag));
}
/*public*/ /*static*/ QString RosterEntry::getDefaultOwner() {
    return _defaultOwner;
}

/*public*/ /*static*/ void RosterEntry::setDefaultOwner(QString n) {
    _defaultOwner = n;
}
