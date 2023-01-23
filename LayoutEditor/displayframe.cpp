#include "displayframe.h"
#include "loggerfactory.h"
#include "editor.h"
#include "placewindow.h"
#include "drawsquares.h"
#include "bufferedimage.h"
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

/*static*/ QColor DisplayFrame::_grayColor = QColor(235, 235, 235);
/*static*/ QColor DisplayFrame::_darkGrayColor = QColor(150, 150, 150);
/*static*/ /*protected*/ QVector<QColor> DisplayFrame::colorChoice = QVector<QColor>() << Qt::white << DisplayFrame::_grayColor << DisplayFrame::_darkGrayColor; // panel bg color picked up directly


/**
 * Create a JmriJFrame with standard settings, optional save/restore of size
 * and position.
 *
 * @param saveSize     set true to save the last known size
 * @param savePosition set true to save the last known location
 */
/*public*/ DisplayFrame::DisplayFrame(bool saveSize, bool savePosition, QWidget* parent)
 : JmriJFrame(saveSize, savePosition, parent){
    //super(saveSize, savePosition);
 setFrameRef(getClassName());
 previewBgSet = 0;
 makeBackgrounds();
}

/**
 * Create a JmriJFrame with with given name plus standard settings, including
 * optional save/restore of size and position.
 *
 * @param name         title of the Frame
 * @param saveSize     set true to save the last knowm size
 * @param savePosition set true to save the last known location
 */
/*public*/ DisplayFrame::DisplayFrame(QString name, bool saveSize, bool savePosition, QWidget* parent)
 : JmriJFrame(saveSize, savePosition, parent) {
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
/*public*/ DisplayFrame::DisplayFrame(QString name, Editor* editor, QWidget* parent) : JmriJFrame(true, true, parent)
{
 //this(name, true, true);
 previewBgSet = 0;
 _editor = editor;
 makeBackgrounds();

}


/*public*/ void DisplayFrame::setPreviewBg(int index) {
    previewBgSet = index;
    log->debug(tr("prev set to %1").arg(index));
}

/*public*/ int DisplayFrame::getPreviewBg() {
    return previewBgSet;
}

/*public*/ BufferedImage* DisplayFrame::getPreviewBackground() {
    return _backgrounds->at(previewBgIndex);
}
/**
 *
 * @return the color of the background of editor display panel
 */
/*public*/ QColor DisplayFrame::getCurrentColor() {
    // should be _editor.getTargetPanel().getBackground()
    return _panelBackground;
}

/*public*/ BufferedImage* DisplayFrame::getBackground(int index) {
    return _backgrounds->at(index);
}
/**
 * Called when the background of the display panel is changed.
 * @param ed the editor of the display panel
 */
/*public*/ void DisplayFrame::updateBackground(Editor* ed) {
 if (ed == nullptr) {
       log->error("updateBackground called for a null editor!");
       return;
   }
   _editor = ed;
   QColor color = ed->getTargetPanel()->getBackground();
   if (color !=(_panelBackground)) {
       _backgrounds->replace(0, DrawSquares::getImage(500, 400, 10, color, color));
       _panelBackground = color;
       if (previewBgIndex == 0) {
           setPreviewBg(0);    // notify children
       }
   }
}

/*public*/ Editor* DisplayFrame::getEditor() {
   return _editor;
}

/**
* Make an array of background BufferedImages for the PreviewPanels
*/
/*private*/ void DisplayFrame::makeBackgrounds() {
   _panelBackground = _editor->getTargetPanel()->getBackground(); // start using Panel background color
   if (_backgrounds == nullptr) { // reduces load but will not redraw for new size
       _backgrounds = new QVector<BufferedImage*>(5);
       for (int i = 1; i <= 3; i++) {
           _backgrounds->replace(i, DrawSquares::getImage(500, 400, 10, colorChoice[i - 1], colorChoice[i - 1]));
           // [i-1] because choice 0 is not in colorChoice[]
       }
       _backgrounds->replace(4, DrawSquares::getImage(500, 400, 10, Qt::white, _grayColor));
   }
   // always update background from Panel Editor
   _backgrounds->replace(0, DrawSquares::getImage(500, 400, 10, _panelBackground, _panelBackground));
   log->debug(tr("makeBackgrounds backgrounds[0] = %1").arg(_backgrounds->at(0)->text()));
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
/*public*/ QString DisplayFrame::getClassName()
{
 return "jmri.jmrit.display.DisplayFrame";
}

/*private*/ /*final*/ /*static*/ Logger* DisplayFrame::log = LoggerFactory::getLogger("DisplayFrame");
