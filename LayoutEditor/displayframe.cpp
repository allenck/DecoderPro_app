#include "displayframe.h"
#include "loggerfactory.h"
#include "editor.h"
#include "placewindow.h"
/**
 * Extended JmriJFrame that allows to add an InitEventListener for display of
 * a tabbed frame in the CPE Add Item {@link jmri.jmrit.display.palette.ItemPalette} pane.
 * <p>
 * <a href="doc-files/DisplayFrame-ClassDiagram.png"><img src="doc-files/DisplayFrame-ClassDiagram.png" alt="UML Class diagram" height="50%" width="50%"></a>
 *
 * @author Egbert Broerse Copyright (c) 2017
 */
/*
@startuml jmri/jmrit/display/doc-files/DisplayFrame-ClassDiagram.png

class jmri.util.JmriJFrame
class jmri.util.swing.ImagePanel {
-BufferedImage back
+setImage()
+paintComponent()
}
class jmri.jmrit.DisplayFrame  #88dddd {
-previewBgSet
#SetInitListener()
#setPreviewBg(i)
#getPreviewBg()
}
class jmri.jmrit.display.IconEditor

object AddItem_TabbedPane
AddItem_TabbedPane : Tab[1] = TurnoutTab
AddItem_TabbedPane : Tab[n] = IndicatorTab
object TurnoutItemPanel
TurnoutItemPanel : type = "Turnout"
object SignalMastItemPanel
SignalMastItemPanel : type = "SignalMast"
object xItemPanel
xItemPanel : type = "x"
object viewOnCombo
viewOnCombo : -int choice
viewOnCombo : +EventListener InitListener
object preview
preview : -image = 1
preview : +EventListener comboListener

AddItem_TabbedPane --> TurnoutItemPanel : show()
AddItem_TabbedPane --> SignalMastItemPanel : show()
AddItem_TabbedPane --> xItemPanel : show()
jmri.util.JmriJFrame --|> jmri.jmrit.DisplayFrame
jmri.jmrit.DisplayFrame *-- jmri.jmrit.display.IconEditor
SignalMastItemPanel *-- viewOnCombo
TurnoutItemPanel *-- viewOnCombo
xItemPanel *-- viewOnCombo
AddItem_TabbedPane ..> viewOnCombo: TabShown(i)
viewOnCombo ..> preview: SetImage[n]
jmri.jmrit.display.IconEditor *-- viewOnCombo
jmri.jmrit.DisplayFrame *-- AddItem_TabbedPane
jmri.util.swing.ImagePanel -- preview

@enduml
*/
///*public*/ class DisplayFrame extends JmriJFrame {

/**
 * Create a JmriJFrame with standard settings, optional save/restore of size
 * and position.
 *
 * @param saveSize     set true to save the last known size
 * @param savePosition set true to save the last known location
 */
/*public*/ DisplayFrame::DisplayFrame(bool saveSize, bool savePosition, QWidget* parent) : JmriJFrame(saveSize, savePosition, parent){
    //super(saveSize, savePosition);
 previewBgSet = 0;
}

/**
 * Create a JmriJFrame with with given name plus standard settings, including
 * optional save/restore of size and position.
 *
 * @param name         title of the Frame
 * @param saveSize     set true to save the last knowm size
 * @param savePosition set true to save the last known location
 */
/*public*/ DisplayFrame::DisplayFrame(QString name, bool saveSize, bool savePosition, QWidget* parent) : JmriJFrame(saveSize, savePosition, parent) {
    //super(name, saveSize, savePosition);
 previewBgSet = 0;
}

/**
 * Create a JmriJFrame with standard settings, including saving/restoring of
 * size and position.
 */
/*public*/ DisplayFrame::DisplayFrame(QWidget* parent) : JmriJFrame(true, true, parent){
    //this(true, true);
 previewBgSet = 0;
}

/**
 * Create a JmriJFrame with with given name plus standard settings, including
 * saving/restoring of size and position.
 *
 * @param name title of the JFrame
 */
/*public*/ DisplayFrame::DisplayFrame(QString name,QWidget* parent) : JmriJFrame(true, true, parent)
{
 //this(name, true, true);
 previewBgSet = 0;

}


/*public*/ void DisplayFrame::setPreviewBg(int index) {
    previewBgSet = index;
    log->debug(tr("prev set to %1").arg(index));
}

/*public*/ int DisplayFrame::getPreviewBg() {
    return previewBgSet;
}

/*public*/ void DisplayFrame::updateBackground0(BufferedImage* im) {
}

/**
 *
 * @param container Container to be resized
 * @param deltaDim Size difference of container with old contents
 * @param newDim Size of the new contents
 * @param ed panel editor
 */
/*public*/ void DisplayFrame::reSize(QWidget*container, QSize deltaDim, QSize newDim, Editor* ed) {
    QSize dim = QSize(deltaDim.width() + newDim.width() + 10,
            deltaDim.height() + newDim.height() + 10);
    container->resize(dim);
    if (log->isDebugEnabled())
        log->debug(tr(" deltaDim= (%1, %2) NewDim= (%3, %4) setPreferredSize to (%5, %6)" ).arg(
            deltaDim.width() ).arg( deltaDim.height() ).arg( newDim.width() ).arg( newDim.height() ).arg( dim.width(), dim.height()));
    pack();
    move(PlaceWindow::nextTo(ed, nullptr, this));
    if (log->isDebugEnabled()) {
        dim = container->size();
        log->debug(tr(" Resized to (%1, %2)" ).arg( dim.width() ).arg( dim.height()));
    }
}

/**
 * Register display of a different tab. Used on {@link jmri.jmrit.display.palette.ItemPanel}
 *
 * @param listener to attach
 */
/*public*/ void DisplayFrame::setInitEventListener(InitEventListener* listener) {
    log->debug("listener attached");
    this->listener = listener;
}

/*private*/ /*final*/ /*static*/ Logger* DisplayFrame::log = LoggerFactory::getLogger("DisplayFrame");
