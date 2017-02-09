#include "twopanetbwindow.h"
#include "jmenuutil.h"
#include <QMenuBar>
#include "jtoolbarutil.h"
#include "box.h"
#include "jseparator.h"
#include <QToolBar>
#include "flowlayout.h"
#include <QLabel>

//TwoPaneTBWindow::TwoPaneTBWindow()
//{

//}
/**
 * MultiPane JMRI window with a "top" area over a single bottom lower pane,
 * optional toolbar and menu.
 *
 * @author Bob Jacobsen Copyright 2010
 * @since 2.13.1
 */
//abstract /*public*/ class TwoPaneTBWindow extends jmri.util.JmriJFrame {

/**
 * Create and initialize a multi-pane GUI window.
 */
/*public*/ TwoPaneTBWindow::TwoPaneTBWindow(QString name, QString menubarFile, QString toolbarFile, QWidget* parent) : JmriJFrame(name,parent)
{
    //super(name);
  top = new QWidget();

  bottom = new QWidget();

  statusBar = new QWidget();

  toolBar = new QToolBar();
  _hideBottomPane = false;
  menuBar = new QMenuBar();
  statusBoxIndex = 0;	// index to insert extra stuff
  /*
   The property change listener is located here so that the menus can interact with the front end
   */
  pcs = new PropertyChangeSupport(this);

    buildGUI(menubarFile, toolbarFile);
    pack();
}


/*public*/ QWidget* TwoPaneTBWindow::getTop() {
    return top;
}

/*public*/ QWidget* TwoPaneTBWindow::getBottom() {
    return bottom;
}

/*public*/ QWidget* TwoPaneTBWindow::getToolBar() {
    return toolBar;
}

/*public*/ QWidget* TwoPaneTBWindow::getSplitPane() {
    return upDownSplitPane;
}

/*protected*/ void TwoPaneTBWindow::buildGUI(QString menubarFile, QString toolbarFile) {
    configureFrame();
    addMainMenuBar(menubarFile);
    addMainToolBar(toolbarFile);
    addMainStatusBar();
}

/*protected*/ void TwoPaneTBWindow::configureFrame() {


    //rightTop.setBorder(BorderFactory.createLineBorder(Color.black));
    top->setLayout(new QHBoxLayout);//(top, BoxLayout.X_AXIS));
    bottom->setLayout(new QHBoxLayout);//(bottom, BoxLayout.X_AXIS));

//    upDownSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
//            top,
//            bottom);
    upDownSplitPane = new QSplitter(Qt::Vertical);
    upDownSplitPane->addWidget(top);
    upDownSplitPane->addWidget(bottom);
   //upDownSplitPane.setOneTouchExpandable(true);
    //upDownSplitPane.setResizeWeight(1.0);  // emphasize top part

    //add(upDownSplitPane, BorderLayout.CENTER);
    //((QVBoxLayout*)getContentPane()->layout())->addWidget(upDownSplitPane,0,Qt::AlignCenter);
    setCentralWidget(upDownSplitPane);
}

/*public*/ void TwoPaneTBWindow::resetTopToPreferredSizes() {
    //upDownSplitPane.resetToPreferredSizes();
}


/*public*/ void TwoPaneTBWindow::hideBottomPane(bool hide) {
    if (_hideBottomPane == hide) {
        return;
    }
    _hideBottomPane = hide;
    if (hide)
    {
        //upDownSplitPane.setDividerLocation(1.0d);
    }
    else
    {
        resetTopToPreferredSizes();
    }
}


/*protected*/ void TwoPaneTBWindow::addMainMenuBar(QString menuFile) {
    if (menuFile == "") {
        return;
    }

    menus = JMenuUtil::loadMenu(menuFile, (WindowInterface*)this, (QObject*)this);
    foreach (QMenu* j, menus) {
        menuBar->addMenu(j);
    }

    setMenuBar(menuBar);
}

/*public*/ QMenuBar* TwoPaneTBWindow::getMenu() {
    return menuBar;
}

/*protected*/ void TwoPaneTBWindow::addMainToolBar(QString toolBarFile) {
    if (toolBarFile == "") {
        return;
    }

    toolBar = JToolBarUtil::loadToolBar(toolBarFile, (WindowInterface*)this, (QObject*)this);

    // this takes up space at the top until pulled to floating
    //add(toolBar, BorderLayout.NORTH);
    addToolBar(toolBar);
}

/*abstract*/ /*public*/ void TwoPaneTBWindow::remoteCalls(QStringList args) {}

/*protected*/ void TwoPaneTBWindow::addMainStatusBar() {
//    statusBar.setLayout(new FlowLayout(FlowLayout.LEFT, 2, 0));
//    statusBar.setBorder(new BevelBorder(BevelBorder.LOWERED));

//    statusBox = Box.createHorizontalBox();
//    statusBox.add(Box.createHorizontalGlue());
//    statusBar.add(statusBox);
//    add(statusBar, BorderLayout.SOUTH);
}

/*public*/ void TwoPaneTBWindow::addToStatusBox(QLabel* title, QLabel* value)\
{
//    QWidget* statusItemPanel = new QWidget();
//    statusItemPanel->setLayout(new FlowLayout(FlowLayout::CENTER, 5, 0));
//    //Set the font size of the status bar text to be 1points less than the default configured, also set as plain
//    int fontSize = InstanceManager::getDefault("GuiLafPreferencesManager").getFontSize() - 1;
//    if (title != NULL) {
//        if (fontSize <= 4) {
//            fontSize = title.getFont().getSize() - 1;
//        }
//        title.setFont(title.getFont().deriveFont(Font.PLAIN, fontSize));
//        statusItemPanel.add(title);
//    }
//    if (value != null) {
//        if (fontSize <= 4) {
//            fontSize = value.getFont().getSize() - 1;
//        }
//        value.setFont(value.getFont().deriveFont(Font.PLAIN, fontSize));
//        statusItemPanel.add(value);
//    }
//    addToStatusBox(statusItemPanel);
}

/*static*/ /*final*/ int TwoPaneTBWindow::statusStrutWidth = 10;

/*public*/ void TwoPaneTBWindow::addToStatusBox(QWidget* comp) {
//    if (statusBoxIndex != 0) {
//        statusBox.add(Box::createHorizontalStrut(statusStrutWidth), statusBoxIndex);
//        ++statusBoxIndex;
//        statusBox.add(new JSeparator(javax.swing.SwingConstants.VERTICAL), statusBoxIndex);
//        ++statusBoxIndex;
//    }
//    statusBox.add(comp, statusBoxIndex);
    ++statusBoxIndex;
}

/**
 * Only close frame, etc, dispose() disposes of all cached panes
 */
/*public*/ void TwoPaneTBWindow::dispose() {
    JmriJFrame::dispose();
}


///*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
//    pcs.addPropertyChangeListener(l);
//}

///*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
//    pcs.removePropertyChangeListener(l);
//}

/*protected*/ void TwoPaneTBWindow::firePropertyChange(QString p, QVariant old, QVariant n) {
    if (pcs == NULL) {
        return;
    }
    pcs->firePropertyChange(p, old, n);
}
