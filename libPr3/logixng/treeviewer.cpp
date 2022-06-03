#include "treeviewer.h"
#include "treepane.h"
#include <QMenuBar>
#include <QMenu>
#include "jmenuitem.h"
#include <QSize>

/**
 * Show the action/expression tree.
 * <P>
 * Base class for ConditionalNG editors
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/ class TreeViewer extends JmriJFrame {

    /*private*/ /*static*/ /*final*/ int TreeViewer::panelWidth = 500;
    /*private*/ /*static*/ /*final*/ int TreeViewer::panelHeight = 300;


    /**
     * Construct a ConditionalEditor.
     *
     * @param femaleRootSocket the root of the tree
     */
    /*public*/ TreeViewer::TreeViewer(AbstractFemaleSocket* femaleRootSocket, QWidget* parent): JmriJFrame((parent)) {
        _treePane = new TreePane(femaleRootSocket);
    }

    //@Override
    /*public*/ void TreeViewer::initComponents() {
        JmriJFrame::initComponents();

        // build menu
        QMenuBar* menuBar = new QMenuBar();
        QMenu* fileMenu = new QMenu(tr("File"));
        JMenuItem* closeWindowItem = new JMenuItem(tr("Close window"),this);
        connect(closeWindowItem, &JMenuItem::triggered, [=] {
            dispose();
        });
        fileMenu->addAction(closeWindowItem);
        menuBar->addMenu(fileMenu);

        setMenuBar(menuBar);
//        addHelpMenu("package.jmri.jmrit.operations.Operations_Settings", true); // NOI18N

        _treePane->initComponents();

        // add panels
        getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));
        getContentPane()->layout()->addWidget(_treePane);

        initMinimumSize(QSize(panelWidth, panelHeight));
    }

    /*public*/ void TreeViewer::initMinimumSize(QSize dimension) {
        setMinimumSize(dimension);
        pack();
        setVisible(true);
    }

    /*public*/ bool TreeViewer::getRootVisible() {
        return _rootVisible;
    }

    /*public*/ void TreeViewer::setRootVisible(bool rootVisible) {
        _rootVisible = rootVisible;
    }

    //@Override
    /*public*/ void TreeViewer::dispose() {
        _treePane->dispose();
        JmriJFrame::dispose();
    }


//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(TreeViewer.class);
