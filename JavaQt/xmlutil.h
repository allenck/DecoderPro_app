#ifndef XMLUTIL_H
#define XMLUTIL_H

#include <QObject>
#include <QtXml>

class XMLUtil : public QObject
{
 Q_OBJECT
public:
 //explicit XMLUtil(QObject *parent = 0);
 /*public*/ static QDomElement findElement(QDomElement parent, QString name, QString _namespace);
 /*public*/ static void write(QDomDocument doc, QTextStream* out, QString enc); //throws IOException

signals:

public slots:
};

#endif // XMLUTIL_H
