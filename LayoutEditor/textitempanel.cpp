#include "textitempanel.h"
#include "decoratorpanel.h"
#include "itempalette.h"
#include <QVBoxLayout>
#include "flowlayout.h"
#include "loggerfactory.h"
#include "decoratorpanel.h"
#include <QPushButton>
#include "editor.h"
#include "positionablepopuputil.h"

//TextItemPanel::TextItemPanel(QWidget *parent) :
//    ItemPanel(parent)
//{
//}
/**
*  ItemPanel for text labels
*/
///*public*/ class TextItemPanel extends ItemPanel /*implements ActionListener */{

//    JTextField _text;

/*public*/ TextItemPanel::TextItemPanel(ItemPalette* parentFrame, QString  type, Editor* editor, QWidget *parent) : ItemPanel(parentFrame, type, editor,parent) {
        //super(parentFrame,  type, family, editor);
        setToolTip(tr("Drag the label from the Preview panel to add it to the control panel"));
        setObjectName("TextItemPanel");
    }

/*public*/ void TextItemPanel::init() {
    if (!_initialized) {
        QThread::yieldCurrentThread();
        QWidget* panel = new QWidget();
        panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
        panel->layout()->addWidget(new JLabel(tr("Enter text and choose attributes for the label in the Preview panel.  Then")));
        panel->layout()->addWidget(new JLabel(tr("Drag the label from the Preview panel to add it to the control panel")));
        QWidget* p = new QWidget();
        p->setLayout(new FlowLayout);
        p->layout()->addWidget(panel);
        thisLayout->addWidget(p);
        DragDecoratorLabel* sample = new DragDecoratorLabel(tr("sample"), _editor, this);
        _decorator = new DecoratorPanel(_editor, _paletteFrame);
        _decorator->initDecoratorPanel(sample);
        thisLayout->addWidget(_decorator);
        _paletteFrame->pack();
        ItemPanel::init();
    }
    log->debug(tr("init panel '%1', layout %2 contains %3 items, objectName = %4").arg("TextItemPanel").arg(thisLayout == nullptr?"null layout": thisLayout->metaObject()->className()).arg(thisLayout->children().size()).arg(thisLayout->objectName()));
}

//@Override
/*protected*/ void TextItemPanel::updateBackground0(BufferedImage* im) {
    if (_decorator != nullptr) {
        _decorator->_bgColorBox->setCurrentIndex(_paletteFrame->getPreviewBg());
    }
}

//@Override
/*protected*/ void TextItemPanel::setPreviewBg(int index) {
    if (_decorator != nullptr) {
        _decorator->_bgColorBox->setCurrentIndex(_paletteFrame->getPreviewBg());
    }
}

/*protected*/ QWidget* TextItemPanel::makeDoneButtonPanel(ActionListener* doneAction) {
    QWidget* panel = new QWidget();
    FlowLayout* panelLayout = new FlowLayout(panel);
    QPushButton* updateButton = new QPushButton(tr("Update")); // custom update label
    //updateButton.addActionListener(doneAction);
    connect(updateButton, SIGNAL(clicked(bool)), doneAction, SLOT(actionPerformed(/*ActionEvent**/)));
    updateButton->setToolTip(tr("Select an item from the table and an icon set to update the Panel"));
    panelLayout->addWidget(updateButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            closeDialogs();
//        }
//    });
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeDialogs()));
    panel->layout()->addWidget(cancelButton);
    return panel;
}

//@Override
/*protected*/ void TextItemPanel::setEditor(Editor* ed) {
    ItemPanel::setEditor(ed);
    if (_decorator != nullptr) {
        QColor panelBackground;// = _editor.getTargetPanel().getBackground();
        QBrush br = _editor->getTargetPanel()->backgroundBrush();
        panelBackground = br.color();
        // set Panel background color
        _decorator->setBackgrounds(makeBackgrounds(_decorator->getBackgrounds(), panelBackground));
        _decorator->_bgColorBox->setCurrentIndex(_paletteFrame->getPreviewBg());
    }
}

/*public*/ void TextItemPanel::updateAttributes(PositionableLabel* l) {
    _decorator->setAttributes(l);
    PositionablePopupUtil* util = _decorator->getPositionablePopupUtil();
    l->setPopupUtility(util->clone(l, l->getTextComponent()));
//    l->setFont(util->getFont().deriveFont(util.getFontStyle()));
    if (util->hasBackground()) { // unrotated
        l->setOpaque(true);
    }
}

//@Override
/*public*/ void TextItemPanel::closeDialogs() {
    if (_decorator != nullptr) {
        _decorator->setSuppressRecentColor(false);
    }
    ItemPanel::closeDialogs();
}

/**
 * Export a Positionable item from panel.
 */
//class DragDecoratorLabel extends PositionableLabel implements DragGestureListener, DragSourceListener, Transferable {

//    DataFlavor dataFlavor;

    /*public*/DragDecoratorLabel::DragDecoratorLabel(QString s, Editor* editor, TextItemPanel* textItemPanel) : PositionableLabel(s, editor){
        //super(s, editor);
 this->textItemPanel = textItemPanel;
#if 0
        DragSource dragSource = DragSource.getDefaultDragSource();
        dragSource.createDefaultDragGestureRecognizer(this,
                DnDConstants.ACTION_COPY, this);
        try {
            dataFlavor = new DataFlavor(Editor.POSITIONABLE_FLAVOR);
        } catch (ClassNotFoundException cnfe) {
            log.error("Unable to find class supporting {}", Editor.POSITIONABLE_FLAVOR, cnfe);
        }
#endif
    }
#if 0
    /**
     * ************** DragGestureListener **************
     */
    //@Override
    public void dragGestureRecognized(DragGestureEvent e) {
        if (log.isDebugEnabled()) {
            log.debug("DragPositionable.dragGestureRecognized ");
        }
        //Transferable t = getTransferable(this);
        e.startDrag(DragSource.DefaultCopyDrop, this, this);
    }

    /**
     * ************** DragSourceListener ***********
     */
    //@Override
    /*public*/ void dragDropEnd(DragSourceDropEvent e) {
    }

    //@Override
    public void dragEnter(DragSourceDragEvent e) {
    }

    //@Override
    public void dragExit(DragSourceEvent e) {
    }

    //@Override
    public void dragOver(DragSourceDragEvent e) {
    }

    //@Override
    public void dropActionChanged(DragSourceDragEvent e) {
    }

    /**
     * ************* Transferable ********************
     */
    //@Override
    public DataFlavor[] getTransferDataFlavors() {
        //if (log.isDebugEnabled()) log.debug("DragPositionable.getTransferDataFlavors ");
        return new DataFlavor[]{dataFlavor};
    }

    //@Override
    public boolean isDataFlavorSupported(DataFlavor flavor) {
        //if (log.isDebugEnabled()) log.debug("DragPositionable.isDataFlavorSupported ");
        return dataFlavor.equals(flavor);
    }

    //@Override
    public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
        if (!isDataFlavorSupported(flavor)) {
            return null;
        }
        String link = _linkName.getText().trim();
        PositionableLabel l;
        if (link.length() == 0) {
            l = new PositionableLabel(getText(), _editor);
        } else {
            l = new LinkingLabel(getText(), _editor, link);
        }
        updateAttributes(l);
        l.setLevel(this.getDisplayLevel());
        return l;
    }
}
#endif
/*private*/ /*final*/ /*static*/ Logger* TextItemPanel::log = LoggerFactory::getLogger("TextItemPanel");
