#ifndef RPSPOSITIONICON_H
#define RPSPOSITIONICON_H
#include "positionablelabel.h"
#include "abstractaction.h"

class Notifier;
class Measurement;
class RpsPositionIcon : public PositionableLabel
{
 Q_OBJECT
public:
 RpsPositionIcon(Editor*);
 /*public*/ NamedIcon* getActiveIcon();
 /*public*/ void setActiveIcon(NamedIcon* i);
 /*public*/ NamedIcon* getErrorIcon();
 /*public*/ void setErrorIcon(NamedIcon* i);
 /*public*/ QString getNameString();
 /*public*/ bool setEditIconMenu(QMenu* popup);
 /*public*/ bool showPopUp(QMenu* popup);
 /*public*/ void setScale(double s);
 /*public*/ void rotate(int deg);
 /*public*/ int maxHeight();
 /*public*/ int maxWidth();
 /*public*/ bool getMomentary();
 /*public*/ void setMomentary(bool m);
 /*public*/ bool isShowID();
 /*public*/ void setShowID(bool mode);
 /*public*/ void notify(Measurement* m);
 /*public*/ void setFilterPopup();
 /*public*/ void setFilter(QString val);
 /*public*/ QString getFilter();
 /*public*/ void dispose();
 /*public*/ void setRpsOrigin();
 /*public*/ double getXScale();
 /*public*/ double getYScale();
 /*public*/ int getXOrigin();
 /*public*/ int getYOrigin() ;
 /*public*/ void setTransform(double sxScale, double syScale, int sxOrigin, int syOrigin);
 /*public*/ void setRpsCurrentLocation();

private:
 // store coordinate system information
 Measurement* lastMeasurement;

 double sxScale, syScale;
 int sxOrigin, syOrigin;
 // display icon for a correct reading
 QString activeName;// = "resources/icons/smallschematics/tracksegments/circuit-occupied.gif";
 NamedIcon* active;// = new NamedIcon(activeName, activeName);

 // display icon if the last reading not OK
 QString errorName;// = "resources/icons/smallschematics/tracksegments/circuit-error.gif";
 NamedIcon* error;// = new NamedIcon(errorName, errorName);
 void displayState();
 // true if valid message received last
 bool state = false;
 QAction* showIdItem = nullptr;
 Notifier* _notify = nullptr;
 QAction* momentaryItem = nullptr;
 bool momentary = false;
 void toggleID(bool value);
 QString filterNumber;// = null;

protected:
 /*protected*/ void rotateOrthogonal();

 friend class Notifier;
};

class Notifier : public AbstractAction {
Q_OBJECT
 RpsPositionIcon* icon;
public:
    /*public*/ Notifier(RpsPositionIcon* icon);
    /*>(c) !=NULL)*/ void actionPerformed();
    void setPosition(int x, int y);
};

#endif // RPSPOSITIONICON_H
