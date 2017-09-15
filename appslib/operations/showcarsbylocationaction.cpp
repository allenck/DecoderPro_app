#include "showcarsbylocationaction.h"
#include "carstableframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a CarsTableFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2009
  * @version $Revision: 28746 $
  */
 ///*public*/ class ShowCarsByLocationAction extends AbstractAction {

 /**
  *
  */
 // static final long serialVersionUID = -3383744212033518858L;

 /*public*/ ShowCarsByLocationAction::ShowCarsByLocationAction(QString s, QObject* parent)
     : AbstractAction(s, parent)
 {
   //super(s);
 }

 /*public*/ ShowCarsByLocationAction::ShowCarsByLocationAction(bool showAllCars, QString locationName, QString trackName, QObject* parent) : AbstractAction(tr("Show Cars"), parent) {
     //this(Bundle.getMessage("MenuItemShowCars"));
     this->showAllCars = showAllCars;
     this->locationName = locationName;
     this->trackName = trackName;
 }

void ShowCarsByLocationAction::common()
{
 showAllCars = true;
 locationName = "";
 trackName = "";
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

 /*public*/ void ShowCarsByLocationAction::actionPerformed(ActionEvent* /*e*/) {
     // create a car table frame
     new CarsTableFrame(showAllCars, locationName, trackName);
 }
}
