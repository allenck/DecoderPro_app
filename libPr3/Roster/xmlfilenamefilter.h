#ifndef XMLFILENAMEFILTER_H
#define XMLFILENAMEFILTER_H

#include <QObject>

class QFile;
class XmlFilenameFilter : public QObject
{
    Q_OBJECT
public:
    explicit XmlFilenameFilter(QObject *parent = 0);
    /*public*/ bool accept(QFile* dir, QString name);

signals:

public slots:

};

#endif // XMLFILENAMEFILTER_H
