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
#include "positionablelabelxml.h"
#include <QDrag>
#include "box.h"

//TextItemPanel::TextItemPanel(QWidget *parent) :
//    ItemPanel(parent)
//{
//}
/**
*  ItemPanel for text labels
*/
///*public*/ class TextItemPanel extends ItemPanel /*implements ActionListener */{

//    JTextField _text;

/*public*/ TextItemPanel::TextItemPanel(ItemPalette* parentFrame, QString  type, Editor* editor, QWidget *parent)
 : ItemPanel(parentFrame, type, editor, parent) {
        //super(parentFrame,  type, family, editor);
        setToolTip(tr("Drag the label from the Preview panel to add it to the control panel"));
        setObjectName("TextItemPanel");
    }

/*public*/ void TextItemPanel::init() {
 if (!_initialized) {
//             Thread.yield();
     JPanel* blurb = new JPanel();
     blurb->setLayout(new QVBoxLayout());//blurb, BoxLayout.Y_AXIS));
     blurb->layout()->addWidget(new JLabel(tr("Enter text and choose attributes for the label in the Preview panel.  Then")));
     blurb->layout()->addWidget(new JLabel(tr("Drag the label from the Preview panel to add it to the control panel")));
     blurb->layout()->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
     blurb->layout()->addWidget(new JLabel(tr("To make clicking on this %1 link to another JMRI panel or URL, ").arg("Text")));
     blurb->layout()->addWidget(new JLabel(tr("-- for a JMRI panel, type \"frame:<panel name>\" into the field at bottom.")));
     blurb->layout()->addWidget(new JLabel(tr("-- for an URL, type the link (i.e. \"http://etc\") into the field at bottom.")));
     JPanel* p = new JPanel(new FlowLayout());
     p->layout()->addWidget(blurb);
     layout()->addWidget(p);
     DragDecoratorLabel* sample = new DragDecoratorLabel(("sample"), _editor);
     _decorator = new DecoratorPanel(_editor);
     _decorator->initDecoratorPanel(sample);
     layout()->addWidget(_decorator);
     initLinkPanel();
     _paletteFrame->pack();
     ItemPanel::init();
 }
}

/*public*/ void TextItemPanel::updateAttributes(PositionableLabel* l)
{
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

/*public*/DragDecoratorLabel::DragDecoratorLabel(QString s, Editor* editor)
 : PositionableLabel(s, editor){
    //super(s, editor);
 QLabel::setVisible(false);
 QLabel::setAutoFillBackground(true);
 setLevel(Editor::LABELS);
 _foreground = QColor(Qt::black);
 QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(1);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(QLabel::hasHeightForWidth());
 setSizePolicy(sizePolicy);
 fg = getForeground();
 bg = getBackground();
 f = getFont();
 this->pointsize = f.pointSize();


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
void DragDecoratorLabel::setBackground(QColor bg)
{
 JLabel::setBackground(bg);
 PositionablePopupUtil* util = getPopupUtility();
 //util->_textComponent = nullptr;
 util->setBackgroundColor(bg);

 this->bg = bg;
 setAttributes();
 updateScene();

}
#endif
void DragDecoratorLabel::setForeground(QColor fg)
{
 PositionableLabel::setForeground(fg);
 this->fg = fg;
 setAttributes();
}

void DragDecoratorLabel::setBorderColor(QColor borderColor)
{
 this->borderColor = borderColor;
 PositionablePopupUtil* util = getPopupUtility();
 util->setBorderColor(borderColor);
 setAttributes();
}

void  DragDecoratorLabel::setBorderSize(int w)
{
 this->borderSize = w;
 PositionablePopupUtil* util = getPopupUtility();
 util->setBorderSize(w);
 setAttributes();
}

void  DragDecoratorLabel::setMargin(int w)
{
 this->margin = w;
 PositionablePopupUtil* util = getPopupUtility();
 util->setMargin(w);
 setAttributes();
}

void  DragDecoratorLabel::setFixedWidth(int w)
{
 if(w > 0)
  QLabel::setStyleSheet(tr("QLabel {width: %1px;}").arg(w));
}
void  DragDecoratorLabel::setFixedHeight(int h)
{
 if(h > 0)
  QLabel::setStyleSheet(tr("QLabel {height: %1px;}").arg(h));
}

void DragDecoratorLabel::setFontSize(int s)
{
 this->pointsize = s;
 f.setPointSize(s);
 JLabel::setFont(f);
 setAttributes();
}

void DragDecoratorLabel::setFontFamily(QString family)
{
 f.setFamily(family);
 setAttributes();
}

void DragDecoratorLabel::setFontStyle(int style)
{
 // plain. bold, italic, bold/italic
 //QFont f = QLabel::font();
 this->style = style;
 switch (style)
 {
  case 0: // plain
   f.setWeight(QFont::Weight::Normal);
   f.setStyle(QFont::Style::StyleNormal);
   break;
  case 1: // Bold
   f.setWeight(QFont::Weight::Bold);
   f.setStyle(QFont::Style::StyleNormal);
   break;
  case 2: // Italic
   f.setWeight(QFont::Weight::Normal);
   f.setStyle(QFont::Style::StyleItalic);
   break;
  case 3: // bold/italic
   f.setWeight(QFont::Weight::Bold);
   f.setStyle(QFont::Style::StyleItalic);
   break;
 }
 setAttributes();
}
/*public*/ void DragDecoratorLabel::setAttributes()
{
#if 1
 QString styleSheet = "QLabel {";
 styleSheet.append(QString("background-color: rgb(%1,%2,%3); color: rgb(%4,%5,%6);").arg(bg.red()).arg(bg.green()).arg(bg.blue()).arg(fg.red()).arg(fg.green()).arg(fg.blue()));
 if(borderSize)
 {
  styleSheet.append(QString("border-style: outset; border-width: %1px;").arg(borderSize));
  styleSheet.append(QString("border-color: rgb(%1,%2,%3);").arg(borderColor.red()).arg(borderColor.green()).arg(borderColor.blue()));
 }
 else
  styleSheet.append("border: none;");
 QStringList styles = QStringList() << "plain" << "bold" <<  "Italic" << "Bold/Italic";
 styleSheet.append(QString("font-size: %1pt;").arg(pointsize));

 styleSheet.append(QString("margin: %1px;").arg(margin));

 styleSheet.append("}");
// f.setPointSize(f.pointSize()+1);
// JLabel:: setFont(f);
// f.setPointSize(f.pointSize()-1);
 JLabel::setFont(f);
 JLabel::setStyleSheet(styleSheet);
#else
 QPalette pal = QLabel::palette();
 pal.setColor(QPalette::WindowText, fg);
 pal.setColor(QPalette::Window, bg);
 QLabel::setPalette(pal);
 QLabel::setStyleSheet(QString("border-style: outset; border-width: %1px;").arg(borderSize) + QString("border-color: rgb(%1,%2,%3);").arg(borderColor.red()).arg(borderColor.green()).arg(borderColor.blue()));
#endif
 QLabel::repaint();
 QLabel::update();
 updateScene();
}

void DragDecoratorLabel::mousePressEvent(QMouseEvent *e)
{
 if(e->button()&Qt::LeftButton)
 {
  dr = new QDrag(this);
  QMimeData *data = new QMimeData;
  QByteArray s_mimeData = mimeData();
  log->debug(tr("xmldata: %1").arg(s_mimeData.data()));
  data->setData("object/x-myApplication-object", s_mimeData);
  // Assign ownership of the QMimeData object to the QDrag object.
  dr->setMimeData(data);
  dr->exec();
 }
 if(e->button() & Qt::RightButton)
 {
//  emit showPopUp(getIcon());
 }
}
/*public*/ QByteArray DragDecoratorLabel::mimeData()
{
 QByteArray xmldata;
 PositionableLabelXml* xml = new PositionableLabelXml();
 QDomElement e = xml->store((QObject*)this);
 xml->doc.appendChild(e);
 xmldata.append(xml->doc.toString());
 log->info(tr("xml data: %1").arg(xml->doc.toString()));
 return xmldata;
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
/*private*/ /*final*/ /*static*/ Logger* DragDecoratorLabel::log = LoggerFactory::getLogger("DragDecoratorLabel");
