#ifndef IMAGEICON_H
#define IMAGEICON_H

#include <QUrl>
#include <QImage>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT ImageIcon : public QObject
{
    Q_OBJECT
public:
    explicit ImageIcon(QObject *parent = nullptr);
    /*public*/ ImageIcon(QString filename, QString description ="", QObject *parent = nullptr);
    /*public*/ ImageIcon(QUrl location, QString description="",QObject *parent = nullptr);
    /*public*/ ImageIcon(QImage image, QString description, QObject *parent = nullptr);
    /*public*/ ImageIcon(QImage image, QObject *parent = nullptr);
    /*public*/ QString toString();
    QString location();
    QString description();
    /*public*/ QImage getImage();
    /*public*/ void setImage(QImage image);
    /*public*/ QString getDescription();
    /*public*/ void setDescription(QString description);
    /*public*/ int getIconWidth() ;
    /*public*/ int getIconHeight();

signals:
    
public slots:
private:
    QString filename;
    QUrl _location;

    QImage image;
    int loadStatus;
//    ImageObserver imageObserver;
    QString _description;
protected:
    // Fields for twisted backward compatibility only. DO NOT USE.
//    static Component component;
//    static MediaTracker tracker;
    /**
     * Id used in loading images from MediaTracker.
     */
    /*private*/ static int mediaTrackerID;

    /*private*/ /*final*/ static QObject TRACKER_KEY;// = new QStringBuilder("TRACKER_KEY");

    int width;// = -1;
    int height;// = -1;
    void init();
    
};

#endif // IMAGEICON_H
