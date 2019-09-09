#ifndef DECODERFILE_H
#define DECODERFILE_H
#include "xmlfile.h"
#include "locoaddress.h"

class LocoAddress;
class VariableTableModel;
class ResetTableModel;
class LIBPR3SHARED_EXPORT DecoderFile : public XmlFile
{
    Q_OBJECT
public:
    explicit DecoderFile(QObject *parent = 0);
    /*public*/ DecoderFile(QString mfg, QString mfgID, QString model, QString lowVersionID,
                       QString highVersionID, QString family, QString filename,
                       int numFns, int numOuts, QDomElement decoder, QObject *parent = 0);
 /*public*/ DecoderFile(QString mfg, QString mfgID, QString model, QString lowVersionID,
         QString highVersionID, QString family, QString filename,
         int numFns, int numOuts, QDomElement decoder, QString replacementModel, QString replacementFamily);
    /*public*/ void setOneVersion(int i);
    /*public*/ void setVersionRange(int low, int high);
    /*public*/ void setVersionRange(QString lowVersionID, QString highVersionID);
    /*public*/ bool isVersion(int i);
    /*public*/ QVector<bool>* getVersions();
    /*public*/ QString getVersionsAsString();
    /*public*/ QString getMfg();
    /*public*/ QString getMfgID();
    /*public*/ QString getModel();
    /*public*/ QString getFamily();
    /*public*/ QString getReplacementModel() ;
    /*public*/ QString getReplacementFamily();
    /*public*/ QString getFileName();
    /*public*/ int getNumFunctions();
    /*public*/ int getNumOutputs();
    /*public*/ QString getModelComment();
    /*public*/ QString getFamilyComment();
    /*public*/ QString getProductID();
    /*public*/ QDomElement getModelElement();
    /*public*/ QList<LocoAddress::Protocol>* getSupportedProtocols();
    bool isProductIDok(QDomElement e, QString extraInclude, QString extraExclude);
    /*public*/ static bool isIncluded(QDomElement e, QString productID, QString modelID, QString familyID, QString extraInclude, QString extraExclude);
    // static service methods - extract info from a given Element
    /*public*/ static QString getMfgName(QDomElement decoderElement);
    /*public*/ void loadVariableModel(QDomElement decoderElement,
                                  VariableTableModel* variableModel);
    /*public*/ void loadResetModel(QDomElement decoderElement,
                               ResetTableModel* resetModel);
    /*public*/ QString titleString();
    static /*public*/ QString titleString(QString model, QString family);

    static /*public*/ QString fileLocation;// = "decoders"+QDir::separator();
    /*public*/ void processVariablesElement(QDomElement variablesElement,
                                  VariableTableModel* variableModel, QString extraInclude, QString extraExclude);

signals:

public slots:
 private:
    // store acceptable version numbers
    QVector<bool>* versions;// = new boolean[256];
    // store indexing information
    QString _mfg;//       = null;
    QString _mfgID;//     = null;
    QString _model;//     = null;
    QString _family;//    = null;
    QString _replacementFamily;
    QString _replacementModel;
    QString _filename;//  = null;
    QString _productID;// = null;
    int _numFns;//  = -1;
    int _numOuts;//  = -1;
    QDomElement _element;// = null;
    QList<LocoAddress::Protocol>* protocols;// = null;
    /*private*/ void setSupportedProtocols();
    /*private*/ static bool isInList(QString include, QString productID);
    Logger* log;
    int nextCvStoreIndex;// = 0;
    int nextICvStoreIndex;// = 0;

};

#endif // DECODERFILE_H
