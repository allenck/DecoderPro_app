#ifndef DECODERINDEXFILE_H
#define DECODERINDEXFILE_H
#include "xmlfile.h"
#include <QStringList>
#include <QComboBox>
#include <QMutex>
#include <QHash>
#include "libPr3_global.h"
#include "abstractinstanceinitializer.h"

class DecoderFile;
class ComboBoxModel;
class LIBPR3SHARED_EXPORT DecoderIndexFile : public XmlFile
{
    Q_OBJECT
public:
    explicit DecoderIndexFile(QObject *parent = 0);
    /*public*/ int numDecoders();
    /*public*/ QStringList* getMfgNameList();
    /*public*/ QString mfgIdFromName(QString name);
    /*public*/ QString mfgNameFromId(QString name);
    /*public*/ QList<DecoderFile*>* matchingDecoderList(QString mfg, QString family, QString decoderMfgID, QString decoderVersionID, QString decoderProductID, QString model );
    /*public*/ QList<DecoderFile*> matchingDecoderList(QString mfg, QString family,
          QString decoderMfgID, QString decoderVersionID,
          QString decoderProductID, QString model, QString developerID, QString manufacturerID, QString productID);
  /*public*/ QComboBox* matchingComboBox(QString mfg, QString family, QString decoderMfgID, QString decoderVersionID, QString decoderProductID, QString model );
    static /*public*/ QComboBox* jComboBoxFromList(QList<DecoderFile*>* l);
    static /*public*/ ComboBoxModel* jComboBoxModelFromList(QList<DecoderFile*>* l);
    /*public*/ DecoderFile* fileFromTitle(QString title );
    /*public*/ bool checkEntry(int i, QString mfgName, QString family, QString mfgID, QString decoderVersionID, QString decoderProductID, QString model, QString developerID, QString manufacturerID, QString productID);
    static DecoderIndexFile* _instance;// = NULL;
    /*public*/ /*synchronized*/ static void resetInstance();
    /*public*/ /*synchronized*/ static DecoderIndexFile* instance();
    static bool updateIndexIfNeeded(QString name) throw (JDOMException, IOException);
    static /*public*/ void forceCreationOfNewIndex();
    static /*public*/ void forceCreationOfNewIndex(bool increment);
    void readFile(QString name) throw (JDOMException, IOException);
    void readMfgSection(QDomElement decoderIndex);
    void readFamilySection(QDomElement decoderIndex);
    void readFamily(QDomElement family);
    /*public*/ void writeFile(QString name, DecoderIndexFile* oldIndex, QStringList* files) throw (IOException);
signals:

public slots:

private:
    int fileVersion;// = -1;
    QMutex mutex;
    QString nmraListDate;// = NULL;
    QString updated;// = NULL;
    QString lastAdd;// = NULL;
 Logger* log;
protected:
    /*protected*/ QList<DecoderFile*>* decoderList;// = new QList<DecoderFile*>();
    // map mfg ID numbers from & to mfg names
    /*protected*/ QHash<QString,QString>* _mfgIdFromNameHash;// = new QHash<QString,QString>();
    /*protected*/ QHash<QString,QString>* _mfgNameFromIdHash;// = new QHash<QString,QString>();

    /*protected*/ QStringList* mMfgNameList;// = new QStringList();
    static /*final*/ /*protected*/ QString decoderIndexFileName;// = "decoderIndex.xml";
    /*protected*/ static QString defaultDecoderIndexFilename();

    static /*final*/ /*protected*/ QString DECODER_INDEX_FILE_NAME;// = "decoderIndex.xml";

};

#endif // DECODERINDEXFILE_H
