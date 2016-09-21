#ifndef NODEIDENTITY_H
#define NODEIDENTITY_H

#include <QObject>
#include <QStringList>

class Logger;
class File;
class NodeIdentity : public QObject
{
 Q_OBJECT
public:
 explicit NodeIdentity(QObject *parent = 0);
 /*synchronized*/ /*public*/ static QString identity();
 /*synchronized*/ /*public*/ static QStringList formerIdentities();
 /*public*/ QStringList getFormerIdentities();
 /*synchronized*/ /*public*/ QString getIdentity();

signals:

public slots:
private:
 Logger* log;
 /*private*/ /*final*/ QStringList _formerIdentities;// = new ArrayList<>();
 /*private*/ QString _identity;// = null;

 /*private*/ static NodeIdentity* instance;// = null;
 /*private*/ /*final*/ static QString ROOT_ELEMENT;// = "nodeIdentityConfig"; // NOI18N
 /*private*/ /*final*/ static QString NODE_IDENTITY;// = "nodeIdentity"; // NOI18N
 /*private*/ /*final*/ static QString FORMER_IDENTITIES;// = "formerIdentities"; // NOI18N
 /*synchronized*/ /*private*/ void init();
 /*synchronized*/ /*private*/ bool validateIdentity(QString identity);
 /*synchronized*/ /*private*/ void getIdentity(bool save);
 /*private*/ void saveIdentity();
 /*private*/ QString createIdentity(QString mac);
 /*private*/ File* identityFile();

};

#endif // NODEIDENTITY_H
