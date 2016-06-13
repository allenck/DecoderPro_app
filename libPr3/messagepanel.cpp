#include "messagepanel.h"
#include <QPushButton>
#include "jtextfield.h"
#include "flowlayout.h"
#include "loconetsystemconnectionmemo.h"
#include "lnmessagemanager.h"

//MessagePanel::MessagePanel(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * Panel for sending messages to throttles.
 *
 * @author	Bob Jacobsen Copyright (C) 2008, 2010
 * @version $Revision: 28746 $
 */
// /*public*/ class MessagePanel extends jmri.jmrix.loconet.swing.LnPanel {

/**
 *
 */
//private static final long serialVersionUID = -729914131632149918L;

/*public*/ MessagePanel::MessagePanel(QWidget *parent) :
 LnPanel(parent)
{
 //super();
 button = new QPushButton("Send");
 text = new JTextField(10);


 // general GUI config
 // install items in GUI
 FlowLayout* thisLayout;
 setLayout(thisLayout = new FlowLayout());
 thisLayout->addWidget(text);
 thisLayout->addWidget(button);
// button.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         memo.getLnMessageManager().sendMessage(text.getText());
//     }
// });
 connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

void MessagePanel::on_button_clicked()
{
 memo->getLnMessageManager()->sendMessage(text->text().trimmed());
}

/*public*/ QString MessagePanel::getHelpTarget() {
    return "package.jmri.jmrix.loconet.swing.throttlemsg.MessageFrame";
}

/*public*/ QString MessagePanel::getTitle() {
    return LnPanel::getTitle(tr("Send"));
}
