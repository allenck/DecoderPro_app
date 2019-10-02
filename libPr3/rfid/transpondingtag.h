#ifndef TRANSPONDINGTAG_H
#define TRANSPONDINGTAG_H
#include "../defaultidtag.h"

class TranspondingTag : public DefaultIdTag
{
 Q_OBJECT
public:
 TranspondingTag(QObject*parent = nullptr) : DefaultIdTag(parent) {}
 TranspondingTag(QString systemName, QObject*parent = nullptr);
 /*public*/ TranspondingTag(QString systemName, QString userName, QObject* parent= nullptr);
 QT_DEPRECATED/*public*/ QString toString();

private:

};
Q_DECLARE_METATYPE(TranspondingTag)
#endif // TRANSPONDINGTAG_H
