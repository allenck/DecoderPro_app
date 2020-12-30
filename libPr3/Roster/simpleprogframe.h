#ifndef SIMPLEPROGFRAME_H
#define SIMPLEPROGFRAME_H
#include "../../LayoutEditor/jmrijframe.h"
#include "libPr3_global.h"

class JActionEvent;
class JToggleButton;
class JTextField;
class ProgModePane;
class QButtonGroup;
class QRadioButton;
class QLabel;
class LIBPR3SHARED_EXPORT SimpleProgFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SimpleProgFrame(QWidget *parent = 0);
 /*public*/ QString getClassName();

signals:

public slots:
    /*public*/ void programmingOpReply(int value, int status);
    /*public*/ void readPushed(JActionEvent* e = 0);
    /*public*/ void writePushed(JActionEvent* e = 0);
    /*public*/ void decHexButtonChanged(JActionEvent* e = 0);
    /*public*/ void dispose();
    void On_read_programmerException(QString);
    void On_write_programmerException(QString);

private:
    // GUI member declarations
    JToggleButton* readButton;// 	= new JToggleButton();
    JToggleButton* writeButton;// 	= new JToggleButton();
    JTextField*  addrField;//      = new JTextField(4);
    JTextField*  valField;//       = new JTextField(4);

    ProgModePane* modePane;//      = new ProgModePane(BoxLayout.Y_AXIS);

    QButtonGroup* radixGroup;//    = new ButtonGroup();
    QRadioButton* hexButton;//    	= new QRadioButton();
    QRadioButton* decButton;//   	= new QRadioButton();

    QLabel* resultsField;//   = new JLabel(" ");
    /*private*/ int getNewVal() ;
    /*private*/ QString getNewAddr();
    /*private*/ QString statusCode(int status);


};

#endif // SIMPLEPROGFRAME_H
