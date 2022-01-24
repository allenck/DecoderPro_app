#include "editorframeoperator.h"

EditorFrameOperator::EditorFrameOperator(QObject *parent) : QObject(parent)
{

}
/**
 * Jemmy Operator for Editor panels swing interfaces.
 *
 * @author	Bob Jacobsen Copyright 2009, 2010
 * @author  Paul Bender Copyright 2017
 */
///*public*/ class EditorFrameOperator extends JFrameOperator {

/*public*/ EditorFrameOperator::EditorFrameOperator(QString title){
   //super(title);
}

/*public*/ EditorFrameOperator::EditorFrameOperator(JFrame* frame){
   //super(frame);
this->frame = frame;
}

/*public*/ void EditorFrameOperator::closeFrameWithConfirmations(){
    // if OK to here, close window
    //this->requestClose();
frame->close();

    dismissClosingDialogs();
}

/*public*/ void EditorFrameOperator::deleteViaFileMenuWithConfirmations(){
#if 0
    JMenuOperator jmo = new JMenuOperator(this,Bundle.getMessage("MenuFile"));
    jmo.pushMenuNoBlock(Bundle.getMessage("MenuFile") +"/"+ Bundle.getMessage("DeletePanel"), "/");
    dismissClosingDialogs();
#endif

}

/*private*/ void EditorFrameOperator::dismissClosingDialogs(){
    // the reminder dialog doesn't appear every time we close, so put
    // pressing the button in that dialog into a thread by itself.  If
    // the dialog appears, it will get clicked, but it's not an error
    // if it doesn't appear.
#if 0
    Thread t = new Thread( () -> {
       try {
          JDialogOperator d = new JDialogOperator(Bundle.getMessage("ReminderTitle"));
          // Find the button that deletes the panel
          JButtonOperator bo = new JButtonOperator(d,Bundle.getMessage("ButtonDeletePanel"));

          // Click button to delete panel and close window
          bo.push();
          } catch (Exception* e) {
              // exceptions in this thread are not considered an error.
              return;
          }
    });
    t.setName("Reminder Dialog Close Thread");
    t.start();

    // that pops dialog, find and press Yes - Delete
    JDialogOperator d = new JDialogOperator(Bundle.getMessage("DeleteVerifyTitle"));

    // Find the button that deletes the panel
    JButtonOperator bo = new JButtonOperator(d,Bundle.getMessage("ButtonYesDelete"));

    // Click button to delete panel and close window
    bo.push();

    // join t
   /* try {
        t.join();
    } catch( java.lang.InterruptedException ie) {
       // do nothing, this isn't an error in this test.
       return;
    }*/
#endif
}
