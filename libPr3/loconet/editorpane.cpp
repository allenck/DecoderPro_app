#include "editorpane.h"
#include "editorfilepane.h"
#include "loconetsystemconnectionmemo.h"
#include <QPushButton>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QFileDialog>
#include "fileutil.h"
#include "file.h"
#include "jframe.h"
#include "jmrijframe.h"
#include "joptionpane.h"

//EditorPane::EditorPane(QWidget *parent) :
//  LnPanel(parent)
//{
//}
/**
 * Frame for editing Digitrax SPJ files.
 *
 * This is just an enclosure for the EditorPane, which does the real work.
 *
 * This handles file read/write.
 *
 * @author	Bob Jacobsen Copyright (C) 2006, 2007, 2008, 2010
 * @version $Revision: 28746 $
 */
///*public*/ class EditorPane extends jmri.jmrix.loconet.swing.LnPanel {

/**
 *
 */
//private static final long serialVersionUID = 4382326277234572738L;



/*public*/ QString EditorPane::getHelpTarget() {
    return "package.jmri.jmrix.loconet.soundloader.EditorFrame";
}

/*public*/ QString EditorPane::getTitle() {
    return LnPanel::getTitle(tr("Sound Editor"));
}

/*public*/ EditorPane::EditorPane(QWidget *parent) :
  LnPanel(parent)
{
 //super();
 pane = NULL;

 // Its unfortunate that we have to read that bundle twice, but it's due to Java init order
 //res = ResourceBundle.getBundle("jmri.jmrix.loconet.soundloader.Editor");

 // general GUI config

 setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

 // add file button
 open = new QPushButton(tr("Open"));
//    open.addActionListener(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -6691600637263742650L;

//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            selectInputFile();
//        }
//    });
 connect(open, SIGNAL(clicked()), this, SLOT(selectInputFile()));

 save = new QPushButton(tr("Save"));
//    save.addActionListener(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -8592850250263713770L;

//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            selectSaveFile();
//        }
//    });
 connect(save, SIGNAL(clicked()), this, SLOT(selectSaveFile()));
 thisLayout->addWidget(save);
 save->setEnabled(false);

//    QWidget* p = new JPanel();
//    p.setLayout(new FlowLayout());
 setMinimumSize(100,80);
 FlowLayout* pLayout = new FlowLayout;
 pLayout->addWidget(open);
 pLayout->addWidget(save);
 thisLayout->addLayout(pLayout);

 // for now, for debugging, load the file
 // from a fixed name
 // pane = new EditorPane("ac4400.spj");
 // pane = new EditorPane("ac4400-silence.spj");
 // pane = new EditorPane("java/test/jmri/jmrix/loconet/spjfile/sd38_2.spj");
 //add(pane);
 //resize(800,80);
}

//static JFileChooser chooser;  // shared across all of these

void EditorPane::selectInputFile()
{
//    if (chooser == null) {
//        chooser = jmri.jmrit.XmlFile.userFileChooser();
//    }
//    chooser.rescanCurrentDirectory();
//    int retVal = chooser.showOpenDialog(this);
//    if (retVal != JFileChooser.APPROVE_OPTION) {
//        return;  // give up if no file selected
//    }
 QString fName = QFileDialog::getOpenFileName(this, tr("Select sound project file"), FileUtil::getUserFilesPath(), tr("Sound files (*.spj)"));
 if(fName == "") return;
    // success, open the file
 addFile(File(fName));
}

void EditorPane::selectSaveFile() {
//    if (chooser == null) {
//        chooser = new JFileChooser(System.getProperty("user.dir"));
//    }
//    int retVal = chooser.showSaveDialog(this);
//    if (retVal != JFileChooser.APPROVE_OPTION) {
//        return;  // give up if no file selected
//    }
 QString fName = QFileDialog::getSaveFileName(this, tr("Select save file name"), FileUtil::getUserFilesPath(), tr("Sound files (*.spj)"));
 if(fName == "") return;
 // success, open the file
 try {
     saveFile(fName);
 } catch (IOException e) {
     // failed, warn user
     JOptionPane::showMessageDialog(this, "Error during save: " + e.getMessage(),
             "Save failed!", JOptionPane::WARNING_MESSAGE);
 }
}

void EditorPane::addFile(File name)
{
 if (pane != NULL)
 {
  // already defined
  return;
 }
 pane = new EditorFilePane(File(name.getPath()));
 thisLayout->addWidget(pane);
 pane->setVisible(true);
 open->setEnabled(false);
 save->setEnabled(true);
    //revalidate();
 // major resize, repack
 resize(800, 400);
 if(qobject_cast<JmriJFrame*>(window())!= NULL)
 ((JmriJFrame*) window())->pack();
}

void EditorPane::saveFile(QString name) /*throws IOException*/ {
    pane->saveFile(name);
}

/*public*/ void EditorPane::dispose() {
    if (pane != NULL) {
        pane->dispose();
    }
    LnPanel::dispose();
}
/*public*/ QWidget* EditorPane::getTopLevelAncestor()
{
 QWidget* p = window();
  if(qobject_cast<JmriJFrame*>(p)!=NULL)
  {
   return (QWidget*)p;
  }
  //if(p instanceof Window || p instanceof Applet)
  if(qobject_cast<JmriPanel*>(p)!=NULL)
  {
   return (QWidget*)p;
  }
 return NULL;
}
