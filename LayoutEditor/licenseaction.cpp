#include "licenseaction.h"
#include <QHBoxLayout>
#include <QScrollArea>
#include "jtextpane.h"
#include "fileutil.h"
//#include "inputstreamreader.h"
//#include "bufferedreader.h"
/**
 * Swing action to display the JMRI license
 *
 * @author Bob Jacobsen Copyright (C) 2004, 2010
 */
///*public*/ class LicenseAction extends jmri.util.swing.JmriAbstractAction {

    /*public*/ LicenseAction::LicenseAction(QObject* parent) : JmriAbstractAction("License", parent) {
        //super("License");
    }

    /*public*/ LicenseAction::LicenseAction(QString s, QIcon i, WindowInterface* w) : JmriAbstractAction(s, i, w){
        //super(s, i, w);
    }

    /*public*/ LicenseAction::LicenseAction(QString s, WindowInterface* w) : JmriAbstractAction(s, w) {
        //super(s, w);
    }

    //@Override
    /*public*/ JmriPanel* LicenseAction::makePanel() {
        JmriPanel* p = new JmriPanel();
        p->setLayout(new QHBoxLayout());//p, BoxLayout.X_AXIS));

        QScrollArea* jScrollPane = new QScrollArea();
        JTextPane* textPane = new JTextPane();

        // get the file
        QTextStream* is = FileUtil::findInputStream("resources/COPYING", FileUtil::Location::INSTALLED); // NOI18N

        QString t;

//        try (   InputStreamReader isr = new InputStreamReader(is, "US-ASCII");    // file stored as ASCII // NOI18N
//                BufferedReader r = new BufferedReader(isr);
//            ){
//            StringBuilder buf = new StringBuilder();
//            while (r.ready()) {
//                buf.append(r.readLine());
//                buf.append("\n");
//            }
//            t = buf.toString();
//        } catch (IOException ex) {
//            t = "JMRI is distributed under a license. For license information, see the JMRI website http://jmri.org";
//        }
        while(!is->atEnd())
        {
         t.append(is->readLine());
         t.append("\n");
        }
        textPane->setText(t);

        // set up display
        textPane->setEditable(false);
        //jScrollPane.getViewport().add(textPane);
        jScrollPane->setWidget(textPane);
        p->layout()->addWidget(jScrollPane);

        // start scrolled to top
#if 0
        JScrollBar b = jScrollPane.getVerticalScrollBar();
        b.setValue(b.getMaximum());
#endif
        return p;
    }
