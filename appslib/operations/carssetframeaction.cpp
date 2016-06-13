#include "carssetframeaction.h"
#include "carssetframe.h"

namespace Operations
{
/**
 * Swing action to create and register a CarsSetFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2010
 * @version $Revision: 28746 $
 */
///*public*/ class CarsSetFrameAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -3263490494828511284L;

 /*public*/ CarsSetFrameAction::CarsSetFrameAction(QString s, QObject* parent) : AbstractAction(parent) {
     //(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
   _carsTable = NULL;
 }

 /*public*/ CarsSetFrameAction::CarsSetFrameAction(JTable* carsTable, QObject* parent)
     : AbstractAction(tr("Set Cars"), parent)
{
     //this(Bundle.getMessage("TitleSetCars"));
     _carsTable = carsTable;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void CarsSetFrameAction::actionPerformed(ActionEvent* e) {
     // create a car table frame
     CarsSetFrame* csf = new CarsSetFrame();
     csf->initComponents(_carsTable);
 }
}
