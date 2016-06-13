#include "myapplication.h"
#include <QDebug>
#include <QEvent>

MyApplication::MyApplication(int &argc, char *argv[]):
    QApplication(argc, argv)
{

}
bool MyApplication::notify(QObject *receiver_, QEvent *event_)
{
 try
 {
  return QApplication::notify( receiver_, event_ );
 }
 catch ( std::exception& e )
 {
  //showAngryDialog( e );
  qDebug() << QString("caught exception, type = %1").arg(event_->type());
 }
 return false;
}
