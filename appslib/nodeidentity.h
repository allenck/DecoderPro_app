#ifndef NODEIDENTITY_H
#define NODEIDENTITY_H

#include <QObject>
#include <QtXml>

class Profile;
class File;
class Logger;
class NodeIdentity : public QObject
{
 Q_OBJECT
public:
 //explicit NodeIdentity(QObject *parent = 0);
 // /*synchronized*/ /*public*/ static QString identity();
 // /*synchronized*/ /*public*/ QString getIdentity();
 /*public*/ QStringList getFormerIdentities();
 /*synchronized*/ /*public*/ static QList<QString> formerIdentities();
 /*public*/ static bool copyFormerIdentity(File* oldPath, File* newPath);
 /*public*/ static /*synchronized*/ QString networkIdentity();
 /*public*/ static /*synchronized*/ QString storageIdentity();
 /*public*/ static /*synchronized*/ QString storageIdentity(Profile* profile);

signals:

public slots:
private:
 static Logger* log;
 /*private*/ /*final*/ QStringList _formerIdentities;// = new ArrayList<>();
 /*private*/ QString _identity;// = null;
 /*private*/ QUuid uuid;// = null;
 /*private*/ QString _networkIdentity;
 /*private*/ QString _storageIdentity;
 /*private*/ /*final*/ QMap<Profile*, QString> profileStorageIdentities;// = new HashMap<>();

 /*private*/ static NodeIdentity* _instance;// = null;
// /*private*/ /*final*/ static Logger log = LoggerFactory.getLogger(NodeIdentity.class);

 /*private*/ /*final*/ static QString ROOT_ELEMENT;// = "nodeIdentityConfig"; // NOI18N
 /*private*/ static /*final*/ QString UUID_ELEMENT;// = "uuid"; // NOI18N
 /*private*/ /*final*/ static QString NODE_IDENTITY;// = "nodeIdentity"; // NOI18N
 /*private*/ static /*final*/ QString STORAGE_IDENTITY;// = "storageIdentity"; // NOI18N
 /*private*/ /*final*/ static QString FORMER_IDENTITIES;// = "formerIdentities"; // NOI18N
 /*private*/ static /*final*/ QString IDENTITY_PREFIX;// = "jmri-";

 /*private*/ NodeIdentity(QObject *parent = nullptr);
 /*synchronized*/ /*private*/ void init();
 /*private*/ QString createIdentity(QByteArray mac);
 /*private*/ File* identityFile();
// /*synchronized*/ /*private*/ bool validateIdentity(QString identity);
// /*synchronized*/ /*private*/ void getIdentity(bool save);
 /*private*/ void saveIdentity();
 /*private*/ static NodeIdentity* instance;// = nullptr;
 /*private*/ /*synchronized*/ bool validateNetworkIdentity(QString identity);
 /*private*/ /*synchronized*/ void getNetworkIdentity(bool save);
 /*private*/ QString createNetworkIdentity(QByteArray mac);
 /*private*/ /*synchronized*/ QString getNetworkIdentity();
 /*private*/ /*synchronized*/ QString getStorageIdentity();
 /*private*/ /*synchronized*/ void getStorageIdentity(bool save);

protected:
 /*protected*/ static QString uuidToCompactString(QUuid uuid);
 /*protected*/ static QUuid uuidFromCompactString(QString compact);
 /*protected*/ static /*final*/ QString URL_SAFE_CHARACTERS;

};

#endif // NODEIDENTITY_H
