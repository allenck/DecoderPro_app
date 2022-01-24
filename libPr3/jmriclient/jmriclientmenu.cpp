#include "jmriclientmenu.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientmonaction.h"
#include "packetgenaction.h"
/**
 * Create a "JMRIClient" menu containing the system-specific tools.
 *
 * @author Bob Jacobsen Copyright 2008
 */
///*public*/ class JMRIClientMenu extends JMenu {

/*public*/ JMRIClientMenu::JMRIClientMenu(QString name, JMRIClientSystemConnectionMemo* memo, QWidget *parent) : QMenu(parent){
    common(memo);
    setTitle(name);
}

/*public*/ JMRIClientMenu::JMRIClientMenu(JMRIClientSystemConnectionMemo* memo, QWidget* parent) : QMenu(parent){
    common(memo);
}

void JMRIClientMenu::common(JMRIClientSystemConnectionMemo *memo)
{
    if (memo != nullptr) {
        setTitle(memo->getUserName());
    } else {
        setTitle(tr("JMRI Client"));
    }

    if (memo != nullptr) {
        addAction(new JMRIClientMonAction(this));
        addAction(new PacketGenAction(tr("Send Command"), memo, this));
    }
}
