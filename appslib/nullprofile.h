#ifndef NULLPROFILE_H
#define NULLPROFILE_H
#include "profile.h"

class NullProfile : public Profile
{
public:
    NullProfile();
    /*public*/ NullProfile(/*@Nonnull*/ File* path, QObject* parent = nullptr) throw (IOException);
    /*public*/ NullProfile(/*@Nonnull*/ File *path, /*@Nonnull*/ QString id, QObject* parent = nullptr) throw (IOException);
    /*public*/ NullProfile(QString name, QString id, /*@Nonnull*/ File* path, QObject* parent=nullptr) throw (IOException, IllegalArgumentException);
    /*public*/ QString toString();
//    /*public*/ int hashCode();
    /*public*/ bool equals(QObject* obj);
    /*public*/ bool isComplete();
    /*public*/ QString getUniqueId();


};

#endif // NULLPROFILE_H
