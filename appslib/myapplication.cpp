#include "myapplication.h"
#include <QDebug>
#include <QEvent>
#include "exceptions.h"

MyApplication::MyApplication(int &argc, char *argv[]):
    QApplication(argc, argv)
{

}

bool MyApplication::notify(QObject *receiver_, QEvent *event_)
{
 bool done = true;
 try
 {
  done = QApplication::notify( receiver_, event_ );
 }
 catch ( std::exception& e )
 {
  qDebug() << QString("caught std exception %1").arg(e.what());
 }
 catch (Exception& e)
 {
  //showAngryDialog( e );
  qDebug() << QString("caught unhandled exception, type = %1 %2").arg(event_->type()).arg(e.getMessage());
//  if(qobject_cast<Exception*>(&e) != NULL)

   //qDebug() << e.getMessage();
 }
 return done;
}
