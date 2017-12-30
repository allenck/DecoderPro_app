#ifndef XINCLUDE_H
#define XINCLUDE_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class QNetworkReply;
class File;
class XInclude : public QObject
{
 Q_OBJECT
public:
 explicit XInclude(QObject *parent = 0);
 bool copyXml(QUrl* in, File* toFile, QWidget* who);
signals:

public slots:
 void fileDownloaded(QNetworkReply* pReply);
 void error(QNetworkReply::NetworkError e);

private:
 QXmlStreamWriter* writer;
 QXmlStreamReader* reader;
 QWidget* who;
 QNetworkAccessManager m_WebCtrl;
 QByteArray m_DownloadedData;
 QUrl* href;
 bool processStartElement(QXmlStreamReader* reader);
 bool processInclude(QUrl* href);
 void processIncludeBody(QXmlStreamReader* reader);

};

#endif // XINCLUDE_H
