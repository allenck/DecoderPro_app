#ifndef PROFILEPROPERTIES_H
#define PROFILEPROPERTIES_H
#include "auxiliaryproperties.h"

class Profile;
class File;
class Logger;
class ProfileProperties : public AuxiliaryProperties
{
public:
 /*public*/ ProfileProperties(Profile* project, QObject* parent= 0);
 /*public*/ ProfileProperties(File* path, QObject* parent = 0);
 QT_DEPRECATED /*public*/ QString get(QString key, bool shared);
 QT_DEPRECATED /*public*/ QList<QString> listKeys(bool shared);
 QT_DEPRECATED /*public*/ void put(QString key, QString value, bool shared);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("ProfileProperties");
 /*private*/ /*final*/ File* path;

};

#endif // PROFILEPROPERTIES_H
