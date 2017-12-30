#ifndef NODEIDENTITY_H
#define NODEIDENTITY_H

#include <QObject>
#include <QtXml>

class File;
class Logger;
class NodeIdentity : public QObject
{
 Q_OBJECT
public:
 //explicit NodeIdentity(QObject *parent = 0);
 /*synchronized*/ /*public*/ static QString identity();
 /*synchronized*/ /*public*/ QString getIdentity();
 /*public*/ QStringList getFormerIdentities();
 /*synchronized*/ /*public*/ static QList<QString> formerIdentities();

signals:

public slots:
private:
 Logger* log;
 /*private*/ /*final*/ QStringList* _formerIdentities;// = new ArrayList<>();
 /*private*/ QString _identity;// = null;

 /*private*/ static NodeIdentity* _instance;// = null;
// /*private*/ /*final*/ static Logger log = LoggerFactory.getLogger(NodeIdentity.class);

 /*private*/ /*final*/ static QString ROOT_ELEMENT;// = "nodeIdentityConfig"; // NOI18N
 /*private*/ /*final*/ static QString NODE_IDENTITY;// = "nodeIdentity"; // NOI18N
 /*private*/ /*final*/ static QString FORMER_IDENTITIES;// = "formerIdentities"; // NOI18N
 /*private*/ NodeIdentity();
 /*synchronized*/ /*private*/ void init();
 /*private*/ QString createIdentity(QByteArray mac);
 /*private*/ File* identityFile();
 /*synchronized*/ /*private*/ bool validateIdentity(QString identity);
 /*synchronized*/ /*private*/ void getIdentity(bool save);
 /*private*/ void saveIdentity();

};

#endif // NODEIDENTITY_H
