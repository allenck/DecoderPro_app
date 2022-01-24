#ifndef HEXFILEFRAME_H
#define HEXFILEFRAME_H
#include "jmrijframe.h"
#include "libPr3_global.h"

class LnHexFilePort;
class JActionEvent;
class LnPacketizer;
class QPushButton;
class JTextField;
class QLabel;
class LIBPR3SHARED_EXPORT HexFileFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit HexFileFrame(QWidget *parent = 0);
    /*public*/ void initComponents(); //throw (Exception);
    /*public*/ void configure();
    /*public*/ void setAdapter(LnHexFilePort* adapter);
    /*public*/ LnHexFilePort* getAdapter();
    /*public*/ void dispose();
    /*public*/ QString getClassName();

signals:

public slots:
    /*public*/ void openHexFileButtonActionPerformed(JActionEvent* /*e*/ = 0);
    /*public*/ void filePauseButtonActionPerformed(JActionEvent* /*e*/ = 0);
    /*public*/ void jButton1ActionPerformed(JActionEvent* /*e*/ = 0);  // resume button
    /*public*/ void delayFieldActionPerformed(JActionEvent* /*e*/ = 0);

private:
    //private static final long serialVersionUID = -2625562807572301674L;
    // member declarations
    QPushButton* openHexFileButton;// = new QPushButton();
    QPushButton* filePauseButton;// = new jQPushButton();
    QPushButton* jButton1;// = new QPushButton();
    JTextField* delayField;// = new JTextField(5);
    QLabel* jLabel1;// = new QLabel();
    bool connected;// = false;
    LnPacketizer* packets;// = NULL;
    /*private*/ QThread* sourceThread;
    /*private*/ LnHexFilePort* port;// = NULL;
    Logger* log;
};

#endif // HEXFILEFRAME_H
