#include "dualdecoderselectframe.h"
#include "dualdecoderselectpane.h"

//DualDecoderSelectFrame::DualDecoderSelectFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Frame for user dual-decoder select too. This allows the user (person) to
 * select an active decoder from multiple ones in a loco
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @version $Revision: 28746 $
 */
///*public*/ class DualDecoderSelectFrame extends jmri.util.JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = 1029903266811472795L;

///*public*/ DualDecoderSelectFrame() {
//    this("Multi-Decoder Control");
//}

/*public*/ DualDecoderSelectFrame::DualDecoderSelectFrame(QString title, QWidget *parent) :
  JmriJFrame(title, parent)
{
 //super(title);


 //getContentPane()->addWidget(new DualDecoderSelectPane());
 setCentralWidget(new DualDecoderSelectPane());

 // add help menu to window
 addHelpMenu("package.jmri.jmrit.dualdecoder.DualDecoderSelectFrame", true);

 adjustSize();
}
/*public*/ QString DualDecoderSelectFrame::getClassName()
{
 return "jmri.jmrit.dualdecoder.DualDecoderSelectFrame";
}
