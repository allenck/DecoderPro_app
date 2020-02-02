#include "jemmyutil.h"
#include "jframeoperator.h"
#include "namecomponentchooser.h"
#include "sleeperthread.h"
#include "jdialog.h"
#include <QMetaObject>

JemmyUtil::JemmyUtil(QObject *parent) : QObject(parent)
{

}

/**
 * Utility Methods for Jemmy Tests.
 *
 * @author Paul Bender Copyright (C) 2018
 */

// /*public*/ class JemmyUtil {
    /*static*/ /*public*/ void JemmyUtil::pressDialogButton(JmriJFrame* f, QString buttonName) {
        JFrameOperator* jfo = new JFrameOperator(f);
        JDialogOperator* jdo = new JDialogOperator(jfo, 1); // wait for the first dialog.
        NameComponentChooser* bChooser = new NameComponentChooser(buttonName);
        JButtonOperator* jbo = new JButtonOperator(jdo, bChooser);
        // Click button
        jbo->push();
    }

    /*static*/ /*public*/ void JemmyUtil::pressDialogButton(QString dialogTitle, QString buttonName) {
//        JDialogOperator* jdo = new JDialogOperator(dialogTitle); // wait for the first dialog.
//        JButtonOperator* jbo = new JButtonOperator(jdo, buttonName);
//        // Click button
//        jbo->push();
      JemmyWait* wait = new JemmyWait(dialogTitle, buttonName);
    }
#if 0
    static /*public*/ void pressDialogButton(JmriJFrame f, String dialogTitle, String buttonName) {
        JFrameOperator jfo = new JFrameOperator(f);
        JDialogOperator jdo = new JDialogOperator(jfo, dialogTitle); // wait for the first dialog.
        JButtonOperator jbo = new JButtonOperator(jdo, buttonName);
        // Click button
        jbo.push();
    }

    static /*public*/ void enterClickAndLeave(JButton comp) {
        JButtonOperator jbo = new JButtonOperator(comp);
        jbo.push();
    }

    static /*public*/ void enterClickAndLeave(JCheckBox comp) {
        JCheckBoxOperator jbo = new JCheckBoxOperator(comp);
        jbo.doClick();
    }

    static /*public*/ void enterClickAndLeave(JRadioButton comp) {
        JRadioButtonOperator jbo = new JRadioButtonOperator(comp);
        jbo.doClick();
    }

    static /*public*/ void enterClickAndLeave(JToggleButton comp) {
        JToggleButtonOperator jtbo = new JToggleButtonOperator(comp);
        jtbo.doClick();
    }

    static /*public*/ void pressButton(WindowOperator frame, String text) {
        JButtonOperator jbo = new JButtonOperator(frame, text);
        jbo.push();
    }

    static /*public*/ void confirmJOptionPane(WindowOperator wo, String title, String message, String buttonLabel) {
        // the previous version of this message verified the text string
        // if the dialog matched the passed message value.  We need to
        // determine how to do that using Jemmy.
        JDialogOperator jdo = new JDialogOperator(wo, title);
        JButtonOperator jbo = new JButtonOperator(jdo, buttonLabel);
        jbo.push();
    }

    /*public*/ static Thread createModalDialogOperatorThread(String dialogTitle, String buttonText) {
        Thread t = new Thread(() -> {
            // constructor for jdo will wait until the dialog is visible
            JDialogOperator jdo = new JDialogOperator(dialogTitle);
            JButtonOperator jbo = new JButtonOperator(jdo, buttonText);
            jbo.pushNoBlock();
        });
        t.setName(dialogTitle + " Close Dialog Thread");
        t.start();
        return t;
    }

    static /*public*/ JLabel getLabelWithText(String frameName, String text) {
        // Find window by name
        JmriJFrame frame = JmriJFrame.getFrame(frameName);

        // find label within that
        JLabel jl = JLabelOperator.findJLabel(frame,new ComponentChooser(){
               /*public*/ boolean checkComponent(Component comp){
                   if(comp == null){
                      return false;
                   } else if (comp instanceof JLabel ) {
                      return ((JLabel)comp).getText().equals(text);
                   } else {
                      return false;
                   }
               }
               /*public*/ String getDescription(){
                  return "find JLabel with text: " + text;
               }
        });
        return jl;
    }
#endif

    JemmyWait::JemmyWait(QString dialogTitle, QString buttonName)
    {
     this->dialogTitle = dialogTitle;
     this->buttonName = buttonName;
     QThread* thread = new QThread();
     thread->setObjectName("JemmyWait");
     connect(thread, SIGNAL(started()), this, SLOT(process()));
     connect(this, SIGNAL(finished()), thread, SLOT(quit()));
     moveToThread(thread);
     thread->start(QThread::LowPriority);
    }

    void JemmyWait::process()
    {
     SleeperThread::msleep(500);
     bool bRunning = true;
     while(bRunning)
     {
      JDialog* dlg = JDialog::findDialog(dialogTitle);
      if(dlg)
      {
       QList<QPushButton*> list = dlg->findChildren<QPushButton*>();
       if(list.count()> 0)
       {
        foreach(QPushButton* b, list)
        {
         if(b->text() == buttonName)
         {
          if(!QMetaObject::invokeMethod(b, "click", Qt::AutoConnection))
           throw Exception(tr("Button '%1'click failed").arg(b->text()));
          bRunning = false;
          break;
         }
        }
       }
      }
      SleeperThread::msleep(500);
      counter++;
      if(counter > 15)
       break;
     }
     emit finished();
    }
