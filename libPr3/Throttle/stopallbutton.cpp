#include "stopallbutton.h"
#include "namedicon.h"
#include "throttleframemanager.h"
#include "throttleslistpanel.h"

//StopAllButton::StopAllButton()
//{

//}
// /*public*/ class StopAllButton extends JButton {

/*public*/ StopAllButton::StopAllButton() {
    //   	stop.setText(Bundle.getMessage("ThrottleToolBarStopAll"));
    setIcon(QIcon(":resources/icons/throttles/estop.png")); //new NamedIcon("resources/icons/throttles/estop.png", "resources/icons/throttles/estop.png"));
    setToolTip(tr("EStop all JMRI managed throttles"));
//    setVerticalTextPosition(JButton.BOTTOM);
//    setHorizontalTextPosition(JButton.CENTER);
//    addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            Iterator<ThrottleFrame> tpi = jmri.jmrit.throttle.ThrottleFrameManager.instance().getThrottlesListPanel().getTableModel().iterator();
//            while (tpi.hasNext()) {
//                DccThrottle th = tpi.next().getAddressPanel().getThrottle();
//                if (th != null) {
//                    th.setSpeedSetting(-1);
//                }
//            }
//        }
//    });
    connect(this, SIGNAL(clicked()), this, SLOT(actionPerformed()));
}
/*public*/ void StopAllButton::actionPerformed(JActionEvent* e)
{
#if 0
    Iterator<ThrottleFrame*> tpi = ThrottleFrameManager::instance()->getThrottlesListPanel()->getTableModel().iterator();
    while (tpi.hasNext()) {
        DccThrottle* th = tpi.next().getAddressPanel().getThrottle();
        if (th != NULL) {
            th.setSpeedSetting(-1);
        }
    }
#endif
}
