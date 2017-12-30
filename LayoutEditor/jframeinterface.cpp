#include "jframeinterface.h"
#include "jframe.h"

//JFrameInterface::JFrameInterface(QWidget *parent) :
//  WindowInterface(parent)
//{
//}
/**
 * A simple WindowInterface for a JFrame. This really does nothing but wrap the
 * WindowInterface interface around a JFrame, so that menu items that expect the
 * WindowInterface can rely on it's presence.
 *
 * @author rhwood
 */
// /*public*/ class JFrameInterface implements WindowInterface {

    //protected JFrame frame = null;

/*public*/ JFrameInterface::JFrameInterface(JFrame* frame, QWidget *parent) :
  WindowInterface(parent)
{
 this->frame = frame;
}

//@Override
/*public*/ void JFrameInterface::show(JmriPanel* child, QAction* action) {
    //throw new UnsupportedOperationException("Not supported yet.");
}

//@Override
/*public*/ void JFrameInterface::show(JmriPanel* child, QAction* action, WindowInterface::Hint hint) {
    //throw new UnsupportedOperationException("Not supported yet.");
}

//@Override
/*public*/ bool JFrameInterface::multipleInstances() {
    return false;
}

//@Override
/*public*/ JFrame* JFrameInterface::getFrame() {
    return this->frame;
}

//@Override
/*public*/ void JFrameInterface::dispose() {

}
