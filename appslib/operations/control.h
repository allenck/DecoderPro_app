#ifndef OCONTROL_H
#define OCONTROL_H

#include <QObject>
#include "appslib_global.h"

class QDomElement;
class QDomDocument;
namespace Operations
{
 class APPSLIBSHARED_EXPORT Control : public QObject
 {
  Q_OBJECT
 public:
  //explicit Control(QObject *parent = 0);
  // debug flags
  /*public*/ static /*final*/ bool showProperty; //=false;
  /*public*/ static /*final*/ bool showInstance; //=false;

  // Default panel width
  /*public*/ static /*final*/ int panelWidth1025; //=1025;
  /*public*/ static /*final*/ int panelWidth700; //=700;
  /*public*/ static /*final*/ int panelWidth600; //=600;
  /*public*/ static /*final*/ int panelWidth500; //=500;
  /*public*/ static /*final*/ int panelWidth400; //=400;
  /*public*/ static /*final*/ int panelWidth300; //=300;

  // Default panel height
  /*public*/ static /*final*/ int panelHeight600; //=600;
  /*public*/ static /*final*/ int panelHeight500; //=500;
  /*public*/ static /*final*/ int panelHeight400; //=400;
  /*public*/ static /*final*/ int panelHeight300; //=300;
  /*public*/ static /*final*/ int panelHeight250; //=250;
  /*public*/ static /*final*/ int panelHeight200; //=200;
  /*public*/ static /*final*/ int panelHeight100; //=100;

  /*
   static Dimension screenSize; //=Toolkit.getDefaultToolkit().getScreenSize();
   // Maximum panel height
  public static final int panelMaxHeight=screenSize.height;
  */

  // Default panel edit locations
  /*public*/ static /*final*/ int panelX; //=0;
  /*public*/ static /*final*/ int panelY; //=0;

  // Train build parameters
  //@//edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value; //="MS_SHOULD_BE_FINAL") // allow access for testing
  /*public*/ static bool fullTrainOnly; //=false;

  // Car and Engine attribute maximum string length
  /*public*/ static int max_len_string_attibute; //=12;

  // Car and Engine number maximum string length
  /*public*/ static int max_len_string_road_number; //=10;

  // Car and Engine number maximum string length when printing
  /*public*/ static int max_len_string_print_road_number; //=6;

  // Location name maximum string length
  /*public*/ static int max_len_string_location_name; //=25;

  // Track name maximum string length
  /*public*/ static int max_len_string_track_name; //=25;

  // Track length maximum string length
  /*public*/ static int max_len_string_track_length_name; //=5;

  // Car and Engine length maximum string length
  /*public*/ static int max_len_string_length_name; //=4;

  // Car weight maximum string length
  /*public*/ static int max_len_string_weight_name; //=4;

  // Car and Engine built date maximum string length
  /*public*/ static int max_len_string_built_name; //=5;

  // Train name maximum string length
  /*public*/ static int max_len_string_train_name; //=25;

  // Route name maximum string length
  /*public*/ static int max_len_string_route_name; //=25;

  // Backward compatibility for xml saves (pre 2013 releases)
  // backward compatibility to false in 2014
  /*public*/ static bool backwardCompatible; //=false;

  /*public*/ static int reportFontSize; //=10;
  /*public*/ static QString reportFontName; //=""; // use default

  /*public*/ static QDomElement store();
  /*public*/ static void load(QDomElement e);
  /*public*/ static void setDoc(QDomDocument doc);

 signals:

 public slots:
 private:
  static QDomDocument doc;

 };
}
#endif // OCONTROL_H
