#include "editorframe.h"
#include "sdfbuffer.h"
#include "sdfeditorpane.h"
#include <QBoxLayout>

//EditorFrame::EditorFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Frame for editing Digitrax SDF files.
 * <P>
 * This is just an enclosure for the EditorPane, which does the real work.
 * <P>
 * This handles file read/write.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class EditorFrame extends JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = 7106886649627618274L;


/*public*/ EditorFrame::EditorFrame(SdfBuffer* buff,QWidget *parent) :
  JmriJFrame(tr("Digitrax SDF Editor"), parent) {
    //super(ResourceBundle.getBundle("jmri.jmrix.loconet.sdfeditor.Editor").getString("Digitrax SDF Editor"));

    // Its unfortunate that we have to read that bundle twice, but it's due to Java init order
    //res = ResourceBundle.getBundle("jmri.jmrix.loconet.sdfeditor.Editor");

    // general GUI config
    //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 setCentralWidget(centralWidget);

 // add panel
 pane = new SdfEditorPane();  // should be SdfEditorPane
 pane->addSdf(buff);
 //getContentPane().add(pane);
 centralWidgetLayout->addWidget(pane);

 // add help menu to window
 addHelpMenu("package.jmri.jmrix.loconet.sdfeditor.EditorFrame", true);

 pack();

}

/*public*/ void EditorFrame::dispose()
{
 pane->dispose();
 JmriJFrame::dispose();
}
