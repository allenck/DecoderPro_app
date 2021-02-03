#include "xmlinclude.h"
#include "filedownloader.h"
#include "QUrl"
#include <QTimer>

XmlInclude::XmlInclude()
{

}

QDomDocumentFragment XmlInclude::processInclude(QDomElement e, int level)
{
 if(e.tagName() != "xi:include") return QDomDocumentFragment();
 QString href = e.attribute("href");
 QUrl url = QUrl(href);
 FileDownloader* fd = new FileDownloader(url);
 QTimer timer;
 timer.setSingleShot(true);
 QEventLoop loop;
 connect(fd, SIGNAL(downloaded()), &loop, SLOT(quit()));
 connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
 timer.start(10000);
 loop.exec();
 QDomDocumentFragment frag;
 if(timer.isActive())
 {
  qDebug() << href << " level= " << QString::number(level) << " downloaded!";
  doc.setContent(fd->downloadedData());
  frag = doc.createDocumentFragment();
  QDomElement e = doc.documentElement(); // root element
  qDebug() << "included root tagname = " << e.tagName();
  if(e.tagName()!= "variables")
  {
   frag.appendChild(e);
   return frag;
  }
  //frag.appendChild(e);
  QDomNodeList nl = e.childNodes();
  qDebug() << "include " << QString::number(nl.count()) << " nodes";
  for(int i = 0; i < nl.count(); i++)
  {
   QDomElement e1 = nl.at(i).toElement();
   qDebug() << "include " << e1.tagName() << " CV= " << e1.attribute("CV");
   if(e1.tagName() == "xi:include")
   {
    QString href = e1.attribute("href");
    frag.appendChild(XmlInclude::processInclude(e1, level + 1));
   }
   else
    frag.appendChild( e1.cloneNode(true));
  }
 }

 return frag;
}

/*static*/ bool XmlInclude::scanForInclude(QDomElement e)
{
 QDomNodeList childNodes =  e.childNodes();
 for(int i = 0; i< childNodes.count(); i++)
 {
  QDomElement e = childNodes.at(i).toElement();
  if(e.tagName() == "xi:include")
   return true;
  if(scanForInclude(e))
   return true;
 }
 return false;
}


/*static*/ void XmlInclude::processIncludes(QDomElement e)
{
 QDomNodeList childNodes =  e.childNodes();
 QString tagName = e.tagName();
 for(int i = 0; i< childNodes.count(); i++)
 {
  QDomElement e1 = childNodes.at(i).toElement();
  QString tag = e1.tagName();
  if(e1.tagName() == "xi:include")
  {
   QString href = e1.attribute("href");
   QUrl url = QUrl(href);
   FileDownloader* fd = new FileDownloader(url);
   QTimer timer;
   timer.setSingleShot(true);
   QEventLoop loop;
   connect(fd, SIGNAL(downloaded()), &loop, SLOT(quit()));
   connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
   timer.start(10000);
   loop.exec();
   QDomDocumentFragment frag;
   if(timer.isActive())
   {
    qDebug() << href  << " downloaded!";
    QDomDocument newDoc = QDomDocument();
    newDoc.setContent(fd->downloadedData());
    frag = newDoc.createDocumentFragment();
    QDomElement e2 = newDoc.documentElement(); // root element
    qDebug() << "included file:" << href << " root tagname = " << e2.tagName();
    frag.appendChild(e2);
    e.replaceChild(frag,e1);
    processIncludes(e2);
   }
  }
  else
   processInclude(e1);
 }
}
