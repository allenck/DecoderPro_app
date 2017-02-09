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
  QDomElement e = doc.documentElement();
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
