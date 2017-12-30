#ifndef METADATA_H
#define METADATA_H
#include <QtCore>

class Metadata
{
public:
 /*public*/ static /*final*/ QString JMRIVERSION;// = "JMRIVERSION"; // NOI18N
 /*public*/ static /*final*/ QString JMRIVERCANON;// = "JMRIVERCANON"; // NOI18N
 /*public*/ static /*final*/ QString JMRIVERMAJOR;// = "JMRIVERMAJOR"; // NOI18N
 /*public*/ static /*final*/ QString JMRIVERMINOR;// = "JMRIVERMINOR"; // NOI18N
 /*public*/ static /*final*/ QString JMRIVERTEST;// = "JMRIVERTEST"; // NOI18N
 /*public*/ static /*final*/ QString JVMVERSION;// = "JVMVERSION"; // NOI18N
 /*public*/ static /*final*/ QString JVMVENDOR;// = "JVMVENDOR"; // NOI18N
 /*public*/ static QString getBySystemName(QString name);
 /*public*/ static QStringList getSystemNameArray();
 /*public*/ static QList<QString> getSystemNameList();

private:
 Metadata();
};

#endif // METADATA_H
