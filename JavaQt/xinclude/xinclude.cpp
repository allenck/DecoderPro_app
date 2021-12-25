#include "xinclude.h"
#include <QUrl>
#include <QFile>
#include "exceptions.h"
#include "joptionpane.h"
#include "file.h"
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
#include "fileutil.h"

XInclude::XInclude(QObject *parent) : QObject(parent)
{
 reader = new QXmlStreamReader;
 writer = new QXmlStreamWriter;
}
bool XInclude::copyXml(QUrl *in, File* toFile, QWidget* who)
{
 this->who = who;
 try
 {
  QFile* fin = new QFile(in->path());
  if(!fin->exists())
   throw new IOException(tr("input file \"%1\" not found").arg(in->path()));
  if(!fin->open(QIODevice::ReadOnly))
   throw new IOException(tr("input file \"%1\" can not be opened").arg(in->path()));
  reader->setDevice(fin);

  FileUtil::createDirectory(toFile->getParent());

  QFile* fout = new QFile(toFile->getPath());
  if(!fout->open(QIODevice::WriteOnly)) throw new IOException(tr("File \"%1\" cannot be opened").arg(toFile->getPath()));
  writer->setDevice(fout);
  writer->setAutoFormatting(true);
  writer->setAutoFormattingIndent(2);
  if(reader->readNext() != QXmlStreamReader::StartDocument) throw new Exception(tr("No StartDocument"));
  writer->setCodec(reader->documentEncoding().toLocal8Bit());
  writer->writeStartDocument(reader->documentVersion().toString());
  QXmlStreamReader::TokenType type;
  QString typeString;
  while((type = reader->readNext()))
  {
   typeString = reader->tokenString();
   if(type == QXmlStreamReader::ProcessingInstruction)
   {
    writer->writeProcessingInstruction(reader->processingInstructionTarget().toString(), reader->processingInstructionData().toString());
    continue;
   }
   else if(type == QXmlStreamReader::DTD)
   {
    writer->writeDTD(reader->text().toString());
    continue;
   }
   else if(type == QXmlStreamReader::Comment)
   {
    writer->writeComment(reader->text().toString());
    continue;
   }
   else if(type == QXmlStreamReader::StartElement)
    break;
   //reader->raiseError(tr("unrecognized type %1").arg(type.tokenString()));
   throw new Exception(tr("unrecognized type %1").arg(typeString));
  }

  processStartElement(reader);

  writer->writeEndDocument();
  fout->flush();
  fout->close();
 }
 catch(IOException* ex)
 {
  JOptionPane::showMessageDialog(this->who, ex->getMessage(), tr("XML Error"), JOptionPane::ERROR_MESSAGE);
  return false;
 }
 catch(Exception* ex)
 {
  JOptionPane::showMessageDialog(this->who, ex->getMessage(), tr("XML Error"), JOptionPane::ERROR_MESSAGE);
  return false;
 }

 return true;
}

bool XInclude::processStartElement(QXmlStreamReader* reader)
{
 Q_ASSERT(reader->isStartElement());

 QString tagName = reader->name().toString();
 QString qualifiedName = reader->qualifiedName().toString();
 QXmlStreamAttributes attributes = reader->attributes();
 int cnt = attributes.count();
 QStringList sl;
 QStringList sv;
 for(int i=0; i < cnt; i++)
 {
  QXmlStreamAttribute sa = attributes.at(i);
  sl.append(sa.qualifiedName().toString());
  sv.append(sa.value().toString());
 }
 QString txt = reader->text().toString();
 QXmlStreamNamespaceDeclarations ns = reader->namespaceDeclarations();
 QStringList nsk;
 QStringList nsv;
 for(int i = 0; i < ns.count(); i++)
 {
  nsk.append(ns.at(i).prefix().toString());
  nsv.append( ns.at(i).namespaceUri().toString());
 }

 if(qualifiedName == "xi:include")
 {
  if(attributes.count() > 0 && sl.at(0) == "href")
  {
   QString href = sv.at(0);
   qDebug() << tr("Process xi:include href=\"%1\"").arg(sv.at(0));
   QUrl* url = new QUrl(href);
   if(!url->isValid())
    throw new Exception(tr("Invalid url: \"%1\"").arg(url->path()));
   processInclude(url);
   reader->skipCurrentElement();
   return true;
  }
 }

 if(qualifiedName == "")
   writer->writeStartElement(tagName);
 else
  writer->writeStartElement(qualifiedName);
 if(ns.count()>0)
 {
  for(int i = 0; i < ns.count(); i++)
  {
   writer->writeNamespace(nsv.at(i), nsk.at(i));
  }
 }
 if(attributes.count() > 0)
 {
  for(int i = 0; i < attributes.count(); i++)
  {
   writer->writeAttribute(attributes.at(i));
  }
 }
 if(txt != "")
 {
  writer->writeTextElement(qualifiedName, txt);
 }

 do
 {
  QXmlStreamReader::TokenType type = reader->readNext();
  Q_UNUSED(type);
  QString typeString = reader->tokenString();
  if(reader->isCharacters())
  {
   writer->writeCharacters(reader->text().toString());
   continue;
  }
  else if(reader->isEndElement())
  {
   writer->writeEndElement();
   return false;
  }
  if(reader->isStartElement())
   processStartElement(reader);
  else if(reader->isComment())
  {
  writer->writeComment(reader->text().toString());
  continue;
  }
  else if(reader->isEndDocument())
   return true;
  else    throw new Exception(tr("unrecognized type %1").arg(typeString));
 } while(!reader->atEnd());

 return true;
}

bool XInclude::processInclude(QUrl* href)
{
 this->href = href;
 QString hPath = href->path();
 if(hPath.startsWith("xml/") || hPath.startsWith("/xml/"))
 {
  qDebug() << href->path();
  QFile* fi = new QFile(FileUtil::getProgramPath()+ href->path());
  if(fi->exists())
  {
   QXmlStreamReader* reader = new QXmlStreamReader();
   if(fi->open(QIODevice::ReadOnly))
   {
    reader->setDevice(fi);
    writer->writeComment(tr("XInclude read from %1=%2").arg("href").arg(fi->fileName()));

    processIncludeBody(reader);
   }
  }
  return true;
 }

 QTimer timer;
 timer.setSingleShot(true);
 QEventLoop loop;
 connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)), &loop, SLOT(quit()));
 connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
 connect( &m_WebCtrl, SIGNAL (finished(QNetworkReply*)), this, SLOT (fileDownloaded(QNetworkReply*))   );
 QNetworkRequest request(*href);
 QNetworkReply* reply = m_WebCtrl.get(request);
 connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
 //connect(reply, SIGNAL(downloadProgress(qint64,qint64)), &loop, SLOT(quit()));
 timer.start(10000);
 loop.exec();
 if(!timer.isActive())
  throw new IOException(tr("failure reading %1").arg(href->path()));
 return true;
}

void XInclude::fileDownloaded(QNetworkReply* pReply)
{
  m_DownloadedData = pReply->readAll();
  //emit a signal
  pReply->deleteLater();
  if(m_DownloadedData.isEmpty())
   throw new IOException(tr("Failure reading %1; empty file returned").arg(href->path()));
//  qDebug() << m_DownloadedData;
  //emit downloaded();
  QXmlStreamReader* reader = new QXmlStreamReader(m_DownloadedData);
  writer->writeComment(tr("XInclude read from %1=%2").arg("href").arg(href->path()));

  processIncludeBody(reader);
}
void XInclude::processIncludeBody(QXmlStreamReader* reader)
{
 try
 {
  writer->writeComment(tr("XInclude read from %1=%2").arg("href").arg(href->path()));

  //reader->readNextStartElement();
  QString rootName = reader->qualifiedName().toString();
  reader->readNext();

  QXmlStreamReader::TokenType type;
  Q_UNUSED(type);
  QString typeString;
  do
  {
   type = reader->readNext();
   typeString = reader->tokenString();
   if(reader->isStartDocument())
   {
    continue;
   }
   if(reader->isProcessingInstruction())
   {
    continue;
   }
   else if(reader->isCharacters())
   {
    writer->writeCharacters(reader->text().toString());
    continue;
   }
   else if(reader->isComment())
   {
    writer->writeComment(reader->text().toString());
    continue;
   }
   else if(reader->isStartElement())
   {
    processStartElement(reader);
    continue;
   }
   else if(reader->isEndElement())
   {
    if(reader->name().toString() == rootName)
     return;
    writer->writeEndElement();
    continue;
   }
   else if(reader->isEndDocument())
   {
    return;
   }
   else    throw new Exception(tr("unrecognized type %1").arg(typeString));
  } while (!reader->atEnd());
 } catch (IOException* e)
 {
  qDebug() << e->getMessage();
  return ;
 }
}

void XInclude::error(QNetworkReply::NetworkError e)
{
 qDebug() << tr("Network error %1").arg(e);
 throw new Exception(tr("Network error %1").arg(e));
}
