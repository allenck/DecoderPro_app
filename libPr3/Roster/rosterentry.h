#ifndef ROSTERENTRY_H
#define ROSTERENTRY_H

#include <QObject>
#include "locoaddress.h"
#include <QMap>
#include "logger.h"
#include <QStringList>
#include <QDir>
#include <QtXml>
#include "dcclocoaddress.h"
#include "propertychangesupport.h"
#include "Roster/cvtablemodel.h"
#include "Roster/locofile.h"
#include "basicrosterentry.h"
#include "arbitrarybean.h"
#include "rosterobject.h"

class Roster;
class RosterGroup;
class RosterSpeedProfile;
class HardcopyWriter;
class PropertyChangeEvent;
class CvTableModel;
class IndexedCvTableModel;
class VariableTableModel;
class LIBPR3SHARED_EXPORT RosterEntry : public ArbitraryBean, public BasicRosterEntry, public RosterObject
{
 Q_OBJECT
 Q_INTERFACES(BasicRosterEntry RosterObject)
public:
 /*public*/ static /*final*/ QString ID;// = "id"; // NOI18N
     /*public*/ static /*final*/ QString FILENAME;// = "filename"; // NOI18N
     /*public*/ static /*final*/ QString ROADNAME;// = "roadname"; // NOI18N
     /*public*/ static /*final*/ QString MFG;// = "mfg"; // NOI18N
     /*public*/ static /*final*/ QString MODEL;// = "model"; // NOI18N
     /*public*/ static /*final*/ QString OWNER;// = "owner"; // NOI18N
     /*public*/ static /*final*/ QString DCC_ADDRESS;// = "dccaddress"; // NOI18N
     /*public*/ static /*final*/ QString LONG_ADDRESS;// = "longaddress"; // NOI18N
     /*public*/ static /*final*/ QString PROTOCOL;// = "protocol"; // NOI18N
     /*public*/ static /*final*/ QString COMMENT;// = "comment"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_MODEL;// = "decodermodel"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_DEVELOPERID;// = "developerID"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_MANUFACTURERID;// = "manufacturerID"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_PRODUCTID;// = "productID"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_FAMILY;// = "decoderfamily"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_COMMENT;// = "decodercomment"; // NOI18N
     /*public*/ static /*final*/ QString DECODER_MAXFNNUM;// = "decodermaxFnNum"; // NOI18N
     /*public*/ static /*final*/ QString DEFAULT_MAXFNNUM;// = "28"; // NOI18N
     /*public*/ static /*final*/ QString IMAGE_FILE_PATH;// = "imagefilepath"; // NOI18N
     /*public*/ static /*final*/ QString ICON_FILE_PATH;// = "iconfilepath"; // NOI18N
     /*public*/ static /*final*/ QString URL;// = "url"; // NOI18N
     /*public*/ static /*final*/ QString DATE_UPDATED;// = "dateupdated"; // NOI18N
     /*public*/ static /*final*/ QString FUNCTION_IMAGE;// = "functionImage"; // NOI18N
     /*public*/ static /*final*/ QString FUNCTION_LABEL;// = "functionlabel"; // NOI18N
     /*public*/ static /*final*/ QString FUNCTION_LOCKABLE;// = "functionLockable"; // NOI18N
     /*public*/ static /*final*/ QString FUNCTION_SELECTED_IMAGE;// = "functionSelectedImage"; // NOI18N
     /*public*/ static /*final*/ QString ATTRIBUTE_UPDATED;// = "attributeUpdated:"; // NOI18N
     /*public*/ static /*final*/ QString ATTRIBUTE_DELETED;// = "attributeDeleted"; // NOI18N
     /*public*/ static /*final*/ QString MAX_SPEED;// = "maxSpeed"; // NOI18N
     /*public*/ static /*final*/ QString SHUNTING_FUNCTION;// = "IsShuntingOn"; // NOI18N
     /*public*/ static /*final*/ QString SPEED_PROFILE;// = "speedprofile"; // NOI18N
     /*public*/ static /*final*/ QString SOUND_LABEL;// = "soundlabel"; // NOI18N
     /*public*/ /*final*/ static int MAXSOUNDNUM;// = 32;
    explicit RosterEntry(QObject *parent = 0);
    ~RosterEntry() {}
    RosterEntry(const RosterEntry& /*e*/, QObject* parent = 0 ) : ArbitraryBean(parent) {}
    QT_DEPRECATED /*final*/const static int MAXFNNUM = 28;

    /*public*/ int getMAXFNNUM() { return MAXFNNUM; }
    /**
     * Construct a blank object.
     *
     */
//    /*public*/ RosterEntry() ;
    /*public*/ RosterEntry(QString fileName,QObject *parent = 0);
    /*public*/ RosterEntry(RosterEntry* pEntry, QString pID,QObject *parent = 0);
    /*public*/ void setId(QString s);
    /*public*/ QString getId();
    /*public*/ void   setFileName(QString s);
    /*public*/ QString getFileName();
    /*public*/ QString getPathName();
    /**
     * Ensure the entry has a valid filename. If none
     * exists, create one based on the ID string. Does _not_
     * enforce any particular naming; you have to check separately
     * for "&lt.none&gt." or whatever your convention is for indicating
     * an invalid name.  Does replace the space, period, colon, slash and
     * backslash characters so that the filename will be generally usable.
     */
    /*public*/ void ensureFilenameExists();
    /*public*/ RosterEntry(QDomElement e, QObject *parent = 0);
//    /*public*/ LocoAddress* getAddress(QDomElement element);
    /*public*/ void loadFunctions(QDomElement e3);
    /*public*/ void loadFunctions(QDomElement e3, QString source);
    /*public*/ void loadAttributes(QDomElement e3);
    /*public*/ void loadSounds(QDomElement e3, QString source);
    /*public*/ void putAttribute(QString key, QString value);
    /*public*/ QString getAttribute(QString key) ;
    /*public*/ QString titleString();
    /*public*/ void deleteAttribute(QString key);
    /*public*/ QList<QString> getAttributes();
    /*public*/ QStringList getAttributeList();
    /*public*/ int getMaxSpeedPCT();
    /*public*/ void setMaxSpeedPCT(int maxSpeedPCT);
    /*protected*/ virtual void warnShortLong(QString id);
    /*public*/ QDomElement store(QDomDocument doc);
    /*public*/ QString toString();
    /*public*/ void updateFile();
    /*public*/ void   setRoadName(QString s);
    /*public*/ QString getRoadName();
    /*public*/ void   setRoadNumber(QString s);
    /*public*/ QString getRoadNumber();
    /*public*/ void   setMfg(QString s);
    /*public*/ QString getMfg();
    /*public*/ void   setModel(QString s);
    /*public*/ QString getModel();
    /*public*/ void   setOwner(QString s);
    /*public*/ QString getOwner();
    /*public*/ void   setDccAddress(QString s);
    /*public*/ QString getDccAddress();
    /*public*/ void setLongAddress(bool b);
    /*public*/ RosterSpeedProfile* getSpeedProfile();
    /*public*/ void setSpeedProfile(RosterSpeedProfile* sp);
    /*public*/ bool isLongAddress();
    /*public*/ void setProtocol(LocoAddress::Protocol protocol);
    /*public*/ LocoAddress::Protocol getProtocol();
    /*public*/ QString getProtocolAsString();
    /*public*/ void   setComment(QString s);
    /*public*/ QString getComment();
    /*public*/ void   setDecoderModel(QString s);
    /*public*/ QString getDecoderModel();
    /*public*/ void   setDecoderFamily(QString s);
    /*public*/ void setDeveloperID(QString s);
    /*public*/ QString getDeveloperID();
    /*public*/ void setManufacturerID(QString s);
    /*public*/ QString getManufacturerID();
    /*public*/ void setProductID(QString s);
    /*public*/ QString getProductID();
    /*public*/ QString getDecoderFamily();
    /*public*/ void   setDecoderComment(QString s);
    /*public*/ QString getDecoderComment();
    /*public*/ void setMaxFnNum(QString s);
    /*public*/ QString getMaxFnNum();
    /*public*/ DccLocoAddress* getDccLocoAddress();
    /*public*/ void setImagePath(QString s) ;
    /*public*/ QString getImagePath();
    /*public*/ void setIconPath(QString s);
    /*public*/ QString getIconPath();
    /*public*/ void setShuntingFunction(QString fn);
    /*public*/ QString getShuntingFunction();
    /*public*/ void setURL(QString s);
    /*public*/ QString getURL();
    /*public*/ void setDateModified(/*@Nonnull*/ QDateTime date);
    /*public*/ void setDateModified(/*@Nonnull*/ QString date) throw (ParseException) ;
    /*public*/ QDateTime getDateModified();
    QT_DEPRECATED /*public*/ void setDateUpdated(QString s);
    /*public*/ QString getDateUpdated();
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*protected*/ /*synchronized*/ void firePropertyChange(QString p, QVariant old, QVariant n);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    qint32 getRfidTag();
    void setRfidTag(QString tag);
    /*public*/ void setFunctionLabel(int fn, QString label);
    /*public*/ QString getFunctionLabel(int fn);
    /*public*/ void setSoundLabel(int fn, QString label);
    /*public*/ QString getSoundLabel(int fn);
    /*public*/ void setFunctionImage(int fn, QString s);
    /*public*/ QString getFunctionImage(int fn);
    /*public*/ void setFunctionSelectedImage(int fn, QString s);
    /*public*/ QString getFunctionSelectedImage(int fn);
    /*public*/ void setFunctionLockable(int fn, bool lockable);
    /*public*/ bool getFunctionLockable(int fn);
    /*public*/ void loadCvModel(VariableTableModel* varModel, CvTableModel* cvModel);
    /*public*/ void writeFile(CvTableModel* cvModel, /*IndexedCvTableModel* iCvModel,*/ VariableTableModel* variableModel);
    /*public*/ void changeDateUpdated();
    /*public*/ void setOpen(bool boo);
    /*public*/ bool isOpen();
    /*public*/ void readFile();
    /*public*/ void printEntry(HardcopyWriter* w);
    /*public*/ void printEntryDetails(HardcopyWriter* w);
    /*public*/ QVector<QString> wrapComment(QString comment, int textSpace);
    /*public*/ static QString getDefaultOwner() ;
    /*public*/ static void setDefaultOwner(QString n);
    /*public*/ QList<RosterGroup*> getGroups();
    /*public*/ QList<RosterGroup*> getGroups(Roster* roster);
    /*public*/ static RosterEntry* fromFile(/*@Nonnull*/ File* file) throw (JDOMException, IOException);
    /*public*/ QString getDisplayName();


signals:
 void propertyChange(PropertyChangeEvent*);
    
public slots:
private:
    static /*private*/ QString _defaultOwner;// = "";
    void init();
    static Logger* log;
    bool loadedOnce;// = false;
    /**
     * Store the root element of the JDOM tree representing this
     * RosterEntry.
     */
    /*private*/ QDomElement mRootElement;// = NULL;
    PropertyChangeSupport* pcs;
    int openCounter;// =0;
    QMutex mutex;
    /*private*/ int blanks;//=0;
    /*private*/ int textSpaceWithIcon;//=0;
    QString indent;// = "                      ";
    int indentWidth;// = indent.length();
    QString newLine;// = "\n";
    /*private*/ int writeWrappedComment(HardcopyWriter* w, QString text, QString title, int textSpace);
    QDateTime dateModified;
    bool soundLoadedOnce = false;

protected:
    // members to remember all the info
    /*protected*/ QString _fileName;// = null;

    /*protected*/ QString _id;// = "";
    /*protected*/ QString _roadName;// = "";
    /*protected*/ QString _roadNumber;// = "";
    /*protected*/ QString _mfg;// = "";
    /*protected*/ QString _owner;// = _defaultOwner;
    /*protected*/ QString _model;// = "";
    /*protected*/ QString _dccAddress;// = "3";
    ///*protected*/ bool _isLongAddress = false;
    /*protected*/ LocoAddress::Protocol _protocol;// = LocoAddress::DCC_SHORT;
    /*protected*/ QString _comment;// = "";
    /*protected*/ QString _decoderModel;// = "";
    /*protected*/ QString _decoderFamily;// = "";
    /*protected*/ QString _decoderComment;// = "";
    /*protected*/ QString _maxFnNum = DEFAULT_MAXFNNUM;
    /*protected*/ QString _dateUpdated;// = "";
    /*protected*/ int _maxSpeedPCT = 100;
    /*protected*/ QString _developerID = "";
    /*protected*/ QString _manufacturerID = "";
    /*protected*/ QString _productID = "";
    /*protected*/ QMap<int, QString> functionLabels;
    /*protected*/ QMap<int, QString> soundLabels;
    /*protected*/ QMap<int, QString> functionSelectedImages;
    /*protected*/ QMap<int, QString> functionImages;
    /*protected*/ QMap<int, bool> functionLockables;
    /*protected*/ QString _isShuntingOn;//="";
    qint32 _rfidTag;


    QMap<QString,QString>* attributePairs;

    /*protected*/ QString _imageFilePath = nullptr;// = FileUtil.getUserResourcePath() ; // at DndImagePanel init will
    /*protected*/ QString _iconFilePath = nullptr;// = FileUtil.getUserResourcePath() ;  // force image copy to that folder
    /*protected*/ QString _URL = "";
    /*protected*/ RosterSpeedProfile* _sp = nullptr;
    QDomElement createTextElement(QDomDocument doc, QString tagName, QString text);
 friend class RosterFrame;
 friend class JsonRosterSocketService;
};
Q_DECLARE_METATYPE(RosterEntry)

#ifndef VPTR_H
#define VPTR_H
template <class T> class VPtr
{
public:
    static T* asPtr(QVariant v)
    {
    return  (T *) v.value<void *>();
    }

    static QVariant asQVariant(T* ptr)
    {
    return qVariantFromValue((void *) ptr);
    }
};
#endif
Q_DECLARE_METATYPE (QList<RosterEntry*>*)
#endif // ROSTERENTRY_H
