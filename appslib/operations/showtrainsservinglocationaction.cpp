#include "showtrainsservinglocationaction.h"
#include "showtrainsservinglocationframe.h"

namespace Operations
{
 /**
  * Action to create the ShowTrainsServingLocationFrame.
  *
  * @author Daniel Boudreau Copyright (C) 2014
  * @version $Revision: 22219 $
  */
 ///*public*/ class ShowTrainsServingLocationAction extends AbstractAction {

  /**
   *
   */
  //private static final long serialVersionUID = -3320805739334775139L;

  /*public*/ ShowTrainsServingLocationAction::ShowTrainsServingLocationAction(QString title, Location* location, Track* track, QObject* parent)
    : AbstractAction(title, parent)
  {
      //super(title);
      _location = location;
      _track = track;
      setEnabled(_location != NULL);
  }


  /*public*/ void ShowTrainsServingLocationAction::actionPerformed(ActionEvent* e) {
      if (_frame != NULL) {
          _frame->dispose();
      }
      _frame = new ShowTrainsServingLocationFrame();
      _frame->initComponents(_location, _track);
  }
}
