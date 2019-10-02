#ifndef TRANSPONDINGTAGMANAGER_H
#define TRANSPONDINGTAGMANAGER_H
#include "defaultidtagmanager.h"

class TranspondingTag;
class TranspondingTagManager : public DefaultIdTagManager
{
 Q_OBJECT
public:
 TranspondingTagManager(QObject* parent = nullptr);
 /*public*/ IdTag* newIdTag(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName);
 /*public*/ void writeIdTagDetails() throw (IOException);
 /*public*/ void readIdTagDetails();
private:
 static Logger* log;

protected:
 /*protected*/ IdTag* createNewIdTag(QString systemName, QString userName);

};

#endif // TRANSPONDINGTAGMANAGER_H
