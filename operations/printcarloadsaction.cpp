#include "printcarloadsaction.h"
#include "carmanager.h"
#include "jframe.h"
#include "hardcopywriter.h"
#include "control.h"
#include <QHash>
#include <QList>
#include "cartypes.h"
#include "carload.h"
#include "carloads.h"
#include "instancemanager.h"

namespace Operations
 {
  /**
  * Action to print a summary of car loads ordered by car type.
  * <P>
  * This uses the older style printing, for compatibility with Java 1.1.8 in
  * Macintosh MRJ
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Dennis Miller Copyright (C) 2005
  * @author Daniel Boudreau Copyright (C) 2011
  * @version $Revision: 28795 $
  */
 ///*public*/ class PrintCarLoadsAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -7822254186432763396L;

  /*static*/ /*final*/ QString CarLoadPrintOption::TAB;// = "\t"; // NOI18N
  /*static*/ /*final*/ QString CarLoadPrintOption::NEW_LINE;// = "\n"; // NOI18N


 /*public*/ PrintCarLoadsAction::PrintCarLoadsAction(QString actionName, bool preview, QWidget* pWho)
   : AbstractAction(actionName, pWho)
 {
     //super(actionName);
     manager = ((CarManager*)InstanceManager::getDefault("CarManager"));

     isPreview = preview;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /**
  * Frame hosting the printing
  */

 /*public*/ void PrintCarLoadsAction::actionPerformed(ActionEvent* /*e*/) {
     new CarLoadPrintOption(this);
 }

     // no frame needed for now
     /*public*/ CarLoadPrintOption::CarLoadPrintOption(PrintCarLoadsAction* parent) {
         //super();
      this->parent = parent;
         printCars();
     }

     /*private*/ void CarLoadPrintOption::printCars() {

         // obtain a HardcopyWriter to do this
         HardcopyWriter* writer = NULL;
         JFrame* mFrame = new JFrame();
         //try {
             writer = new HardcopyWriter(mFrame, tr("Car Loads"), Control::reportFontSize, .5, .5, .5, .5, parent->isPreview);
//         } catch (HardcopyWriter.PrintCanceledException ex) {
//             log.debug("Print cancelled");
//             return;
//         }

         // Loop through the Roster, printing as needed
         QStringList carTypes = CarTypes::instance()->getNames();
         QHash<QString, QList<CarLoad*>*>* list = CarLoads::instance()->getList();
         //try {
             QString s = tr("Type") + TAB
                     + parent->tabString(tr("Load"), CarLoads::instance()->getMaxNameLength() + 1)
                     + tr("Type") + "  " + tr("Priority") + "  "
                     + tr("Load Pick Up Car Message") + "   " + tr("Load Set Out Car Message")
                     + NEW_LINE;
             writer->write(s);
             foreach (QString carType, carTypes) {
                 QList<CarLoad*>* carLoads = list->value(carType);
                 if (carLoads== NULL) {
                     continue;
                 }
                 bool printType = true;
                 foreach (CarLoad* carLoad, *carLoads) {
                     // don't print out default load or empty
                     if ((carLoad->getName()==(CarLoads::instance()->getDefaultEmptyName()) || carLoad->getName()
                             ==(CarLoads::instance()->getDefaultLoadName()))
                             && carLoad->getPickupComment()==(CarLoad::NONE)
                             && carLoad->getDropComment()==(CarLoad::NONE)
                             && carLoad->getPriority()==(CarLoad::PRIORITY_LOW)) {
                         continue;
                     }
                     // print the car type once
                     if (printType) {
                         writer->write(carType + NEW_LINE);
                         printType = false;
                     }
                     QString buf = "";//new StringBuffer(TAB);
                     buf.append(parent->tabString(carLoad->getName(), CarLoads::instance()->getMaxNameLength() + 1));
                     buf.append(parent->tabString(carLoad->getLoadType(), 6)); // load or empty
                     buf.append(parent->tabString(carLoad->getPriority(), 5)); // low or high
                     buf.append(parent->tabString(carLoad->getPickupComment(), 27));
                     buf.append(parent->tabString(carLoad->getDropComment(), 27));
                     writer->write(buf/*.toString()*/ + NEW_LINE);
                 }
             }
             // and force completion of the printing
             writer->close();
//         } catch (IOException we) {
//             log.error("Error printing car roster");
//         }
     }


 /*private*/ /*static*/ QString PrintCarLoadsAction::tabString(QString s, int fieldSize) {
     if (s.length() > fieldSize) {
         s = s.mid(0, fieldSize - 1);
     }
     QString buf = "";//new StringBuffer(s + " ");
     while (buf.length() < fieldSize) {
         buf.append(" ");
     }
     return buf/*.toString()*/;
 }

}
