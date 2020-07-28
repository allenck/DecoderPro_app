#ifndef SYSTEMTYPE_H
#define SYSTEMTYPE_H

#include <QObject>

class Logger;
class SystemType : public QObject
{
    Q_OBJECT
public:
    static /*final*/ /*public*/ const int MACCLASSIC = 1; // no longer supported - latest JVM is 1.1.8
    static /*final*/ /*public*/ const int MACOSX = 2;
    static /*final*/ /*public*/ const int WINDOWS = 4;
    static /*final*/ /*public*/ const int LINUX = 5;
    static /*final*/ /*public*/ const int OS2 = 6;
    static /*final*/ /*public*/ const int UNIX = 7;
    static int type;// = 0;
    static bool isSet;// = false;

    static QString osName;
    /*public*/ static int getType();
    /*public*/ static QString getOSName();
    /*public*/ static bool isMacOSX();
    /*public*/ static bool isLinux();
    /*public*/ static bool isWindows();
    /*public*/ static bool isOS2();
    /*public*/ static bool isUnix() ;

private:
    static void setType();
    static Logger* log;
signals:

public slots:

protected:
    explicit SystemType(QObject *parent = nullptr);

};

#endif // SYSTEMTYPE_H
