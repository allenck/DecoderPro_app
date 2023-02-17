#ifndef TRANSPONDINGTAGMANAGER_H
#define TRANSPONDINGTAGMANAGER_H
#include "defaultidtagmanager.h"

class TranspondingTag;
class TranspondingTagManager : public DefaultIdTagManager
{
 Q_OBJECT
public:
 TranspondingTagManager(QObject* parent = nullptr);
 /*public*/ DefaultIdTag* newIdTag(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
 /*public*/ void writeIdTagDetails() const /*throw (IOException)*/override;
 /*public*/ void readIdTagDetails()override;
 /*public*/ QString getNamedBeanClass()const override {
     return "TranspondingTag";
 }

private:
 static Logger* log;
 /*final*/ void storeInstance();

protected:
 /*protected*/ NamedBean* createNewIdTag(QString systemName, QString userName)override;

};

#endif // TRANSPONDINGTAGMANAGER_H
