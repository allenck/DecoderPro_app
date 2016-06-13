#ifndef TRAINMANIFESTHEADERTEXT_H
#define TRAINMANIFESTHEADERTEXT_H

#include <QObject>
#include <QtXml>
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT TrainManifestHeaderText : QObject
 {
  Q_OBJECT
 public:
  //TrainManifestHeaderText();
  /*public*/ static QString getStringHeader_Road();
  /*public*/ static void setStringHeader_Road(QString s);
  /*public*/ static QString getStringHeader_Number();
  /*public*/ static void setStringHeader_Number(QString s);
  /*public*/ static QString getStringHeader_EngineNumber();
  /*public*/ static void setStringHeader_EngineNumber(QString s);
  /*public*/ static QString getStringHeader_Type() ;
  /*public*/ static void setStringHeader_Type(QString s);
  /*public*/ static QString getStringHeader_Model();
  /*public*/ static void setStringHeader_Model(QString s);
  /*public*/ static QString getStringHeader_Length();
  /*public*/ static void setStringHeader_Length(QString s) ;
  /*public*/ static QString getStringHeader_Load() ;
  /*public*/ static void setStringHeader_Load(QString s);
  /*public*/ static QString getStringHeader_Color();
  /*public*/ static void setStringHeader_Color(QString s) ;
  /*public*/ static QString getStringHeader_Track();
  /*public*/ static void setStringHeader_Track(QString s);
  /*public*/ static QString getStringHeader_Destination();
  /*public*/ static void setStringHeader_Destination(QString s);
  /*public*/ static QString getStringHeader_Dest_Track() ;
  /*public*/ static void setStringHeader_Dest_Track(QString s);
  /*public*/ static QString getStringHeader_Final_Dest();
  /*public*/ static void setStringHeader_Final_Dest(QString s) ;
  /*public*/ static QString getStringHeader_Final_Dest_Track();
  /*public*/ static void setStringHeader_Final_Dest_Track(QString s);
  /*public*/ static QString getStringHeader_Location();
  /*public*/ static void setStringHeader_Location(QString s);
  /*public*/ static QString getStringHeader_Consist();
  /*public*/ static void setStringHeader_Consist(QString s);
  /*public*/ static QString getStringHeader_Kernel() ;
  /*public*/ static void setStringHeader_Kernel(QString s);
  /*public*/ static QString getStringHeader_Owner();
  /*public*/ static void setStringHeader_Owner(QString s);
  /*public*/ static QString getStringHeader_RWE();
  /*public*/ static void setStringHeader_RWE(QString s);
  /*public*/ static QString getStringHeader_Comment();
  /*public*/ static void setStringHeader_Comment(QString s);
  /*public*/ static QString getStringHeader_Drop_Comment() ;
  /*public*/ static void setStringHeader_Drop_Comment(QString s) ;
  /*public*/ static QString getStringHeader_Pickup_Comment();
  /*public*/ static void setStringHeader_Pickup_Comment(QString s);
  /*public*/ static QString getStringHeader_Hazardous();
  /*public*/ static void setStringHeader_Hazardous(QString s);
  // must synchronize changes with operation-config.dtd
  /*public*/ static QDomElement store(QDomDocument doc);
  /*public*/ static void load(QDomElement e);
   private:
   /*private*/ static QString road;//= tr("Road"); // the supported message format options
   /*private*/ static QString number;//= tr("Number");
   /*private*/ static QString engine_number;//= tr("Number");
   /*private*/ static QString type;//= tr("Type");
   /*private*/ static QString model;//= tr("Model");
   /*private*/ static QString length;//= tr("Length");
   /*private*/ static QString _load;//= tr("Load");
   /*private*/ static QString color;//= tr("Color");
   /*private*/ static QString track;//= tr("Track");
   /*private*/ static QString destination;//= tr("Destination");
   /*private*/ static QString dest_track;//= tr("Dest&Track");
   /*private*/ static QString final_dest;//= tr("Final_Dest");
   /*private*/ static QString final_dest_track;//= tr("FD&Track");
   /*private*/ static QString location;//= tr("Location");
   /*private*/ static QString consist;//= tr("Consist");
   /*private*/ static QString kernel;//= tr("Kernel");
   /*private*/ static QString owner;//= tr("Owner");
   /*private*/ static QString rwe;//= tr("RWE");
   /*private*/ static QString comment;//= tr("Comment");
   /*private*/ static QString drop_comment;//= tr("SetOut_Msg");
   /*private*/ static QString pickup_comment;//= tr("PickUp_Msg");
   /*private*/ static QString hazardous;//= tr("Hazardous");

 };
}
#endif // TRAINMANIFESTHEADERTEXT_H
