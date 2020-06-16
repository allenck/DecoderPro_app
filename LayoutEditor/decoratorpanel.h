#ifndef DECORATORPANEL_H
#define DECORATORPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QRadioButton>
#include "positionablelabel.h"
#include "changeevent.h"
#include "changelistener.h"
#include "jpanel.h"
#include "jspinner.h"
#include <QGraphicsView>
#include "editscene.h"
#include "jtextfield.h"
#include <QDrag>
#include <QMimeData>
#include "positionablelabelxml.h"
#include "editor.h"
#include "jcombobox.h"
#include "positionablepopuputil.h"

class AJComboBox;
class DragJTextField;
class JComboBox;
class PreviewPanel;
class PreviewScene;
class DPChangeListener;
class QGroupBox;
class QSignalMapper;
class DragDecoratorLabel;
class ChangeListener;
class FontPanel;
class ImagePanel;
class BufferedImage;
class JTextField;
class DataFlavor;
class QLabel;
class SpinnerModel;
class AJRadioButton;
class ChangeEvent;
class ItemEvent;
class Positionable;
class JColorChooser;
class QButtonGroup;
class PositionableLabel;
class PositionablePopupUtil;
class Editor;
class AJSpinner;
class AJSpinner;
class DecoratorPanel : public JPanel
{
    Q_OBJECT
public:
    enum WHICH
    {
     SIZE = 1,
     STYLE = 2,
     JUST = 3
    };
    //explicit DecoratorPanel(QWidget *parent = 0);
    static /*final*/ QStringList JUSTIFICATION;// = {ItemPalette.rbp.getString("left"),
//                                            ItemPalette.rbp.getString("center"),
//                                            ItemPalette.rbp.getString("right")};

    static /*final*/ QStringList STYLES;// = {ItemPalette.rbp.getString("plain"),
//                                    ItemPalette.rbp.getString("bold"),
//                                    ItemPalette.rbp.getString("italic"),
//                                    ItemPalette.rbp.getString("bold/italic")};

    static /*final*/ QStringList FONTSIZE;// = {"6", "8", "10", "11", "12", "14", "16",
//                                        "20", "24", "28", "32", "36"};
    /*public*/ static /*final*/ const int STRUT = 10;
enum VALUES
{
 BORDER = 1,
 MARGIN = 2,
 FWIDTH = 3,
 FHEIGHT = 4,

 TEXT_FONT = 10,
 ACTIVE_FONT = 11,
 INACTIVE_FONT = 12,
 UNKOWN_FONT = 13,
 INCONSISTENT_FONT = 14,
 TEXT_BACKGROUND = 20,
 ACTIVE_BACKGROUND = 21,
 INACTIVE_BACKGROUND = 22,
 UNKOWN_BACKGROUND = 23,
 INCONSISTENT_BACKGROUND = 24,
 TRANSPARENT_COLOR =31,
 BORDER_COLOR =32
};
    /*public*/ DecoratorPanel(Editor *editor, QWidget *parent = 0);
    /*public*/ void initDecoratorPanel(Positionable* pos);
    /*public*/ PositionablePopupUtil* getPositionablePopupUtil();
    /*public*/ void getText(Positionable* pos);
    /*public*/ bool isOpaque();
//    /*public*/ void itemStateChanged(ItemEvent* e);
//    /*public*/ void setSuppressRecentColor(bool b);
    /*public*/ void setAttributes(Positionable* pos);
//    /*public*/ void mousePressEvent(QMouseEvent *event);
//    /*public*/ QByteArray mimeData();
    /*public*/ DragJTextField* getDragJTextField();
    enum Font
    {
     PLAIN = 0,
     BOLD = 1,
     ITALIC = 2
    };
signals:

public slots:
    void AJRadioButton_toggled(bool);
    void currentColorChanged(QColor);
    ///*public*/ void AJRBListener();
//    void mappedButton(QWidget*);
    /*public*/ void stateChanged(ChangeEvent* e);
    /*public*/ void itemStateChanged(ItemEvent* e);

private:
    /*private*/ FontPanel* _fontPanel;
    AJComboBox* _fontSizeBox;
    AJComboBox* _fontStyleBox;
    AJComboBox* _fontJustBox;

    AJSpinner* _borderSpin;
    AJSpinner* _marginSpin;
    AJSpinner* _widthSpin;
    AJSpinner* _heightSpin;
    enum BUTTONS
    {
     FOREGROUND_BUTTON = 10,
     BACKGROUND_BUTTON = 20,
     TRANSPARENT_BUTTON = 31,
     BORDERCOLOR_BUTTON = 32
    };

    /*private*/ AJRadioButton* _fontButton;
    /*private*/ AJRadioButton* _borderButton;
    /*private*/ AJRadioButton* _backgroundButton;
    AJRadioButton* button;
    QString bundleCaption;
    QSignalMapper* _mapper;

    JColorChooser* _chooser;
    /*private*/ QWidget* makeBgButtonPanel(/*@Nonnull*/ ImagePanel* preview1, ImagePanel* preview2, QVector<BufferedImage*>* imgArray);
//    /*private*/ JPanel* makeColorPanel(bool addCaption);
    /*private*/ JPanel* makeBoxPanel(QString caption, JComboBox* box);

    /*private*/ PositionablePopupUtil* _util;
    bool _isOpaque;			// transfer opaqueness from decorator label here to panel label being edited
    /*private*/ QHash<QString, PositionableLabel*>* _sample = nullptr;
    /*private*/ QButtonGroup* _buttonGroup;
    /*private*/ int _selectedButton = -1;
    /*private*/ QString _selectedState;

    Editor* _editor;
//    /*private*/ QWidget* makeBoxPanel(QString caption, AJSpinner* box);
    /*private*/ JPanel* makeSpinPanel(QString caption, JSpinner* spin);
    /*private*/ JPanel* makeTextPanel(QString caption, JLabel* sample, int state);
    /*private*/ AJRadioButton* makeButton(AJRadioButton* button);
    /*private*/ void updateSamples();
    QString text;
    QVector<BufferedImage*>* imgArray;
    static Logger* log;
    ImagePanel* preview1;
    JPanel* _previewPanel;
    /*private*/ /*final*/ ImagePanel* _samplePanel;
    /*private*/ QGraphicsView* _sampleView;
    /*private*/ PreviewScene* _scene;
    /*private*/ bool _isPositionableLabel;
    /*protected*/ void fontChange();
//    /*private*/ void finishInit(bool addBgCombo);
//    /*private*/ void doPopupUtility(QString type, PositionableLabel* sample, bool editText);
    /*private*/ void makeFontPanels();
//    /*private*/ AJRadioButton* makeColorRadioButton(QString caption, int which);
    DragDecoratorLabel* sample = nullptr;
    DPChangeListener* listener = nullptr;
    /*private*/ void colorChange();
    /*private*/ QWidget* _textEditComponent;
    PositionableLabel* _label = nullptr;
    QDrag* dr;
    DragJTextField* _dragJTextField = nullptr;
    QString fontStyle(QFont f);
    void updateDragJText();

private slots:
    void on_bgColorBox();
    void propertyChange(PropertyChangeEvent* evt);

protected:
    /*protected*/ QVector<BufferedImage*>* _backgrounds; // array of Image backgrounds
    /*protected*/ QComboBox* _bgColorBox;
    /*protected*/ DisplayFrame* _frame;
    /*protected*/ QVector<BufferedImage*>* getBackgrounds();
//    /*protected*/ void setBackgrounds(QVector<BufferedImage*>*  imgArray);
    /*protected*/ void initDecoratorPanel(DragDecoratorLabel* sample);
    /*protected*/ JPanel* getPreviewPanel();

    friend class TextFieldListener;
    friend class TextItemPanel;
    friend class ColorDialog;
    friend class FontActionListener;
    friend class DPChangeListener;
    friend class PreviewScene;
    friend class TextAttrDialog;
};

/*static*/ class AJSpinner : public  JSpinner
{
    Q_OBJECT
    int _which;
public:
    AJSpinner(SpinnerModel* model, int which, QWidget *parent = nullptr);
    friend class DecoratorPanel;
    friend class ColorDialog;
};

/*static*/ class AJRadioButton : public QRadioButton {
    Q_OBJECT
    int _which;
    //QString _state;

public:
    AJRadioButton(QString text, int w) : QRadioButton(text)
    {
     //super(text);
     _which = w;
     //_state = state;

    }
    //QString getState();
    friend class DecoratorPanel;
    friend class AJRBActionListener;
signals:
    void stateChanged(ChangeEvent*);
public slots:
};

#if 0
class AJRBActionListener : public QObject
{
 Q_OBJECT
 AJRadioButton* button ;
 DecoratorPanel* self;
public:
 AJRBActionListener* init(AJRadioButton* b, DecoratorPanel* self) ;
public slots:
 /*public*/ void actionPerformed();

};
#endif
//class ChangeEvent : public QObject
//{
// Q_OBJECT
// QObject* source;
//public:
// ChangeEvent(QObject* source) {this->source = source;}
// QObject* getSource() { return source;}
//};
class ItemEvent : public QObject
{
 Q_OBJECT
 QObject* source;
public:
 ItemEvent(QObject *source, QObject* parent = nullptr) :  QObject(parent) {this->source = source; }
 QObject* getSource() { return source;}
};
#if 0
class AJListener : public QObject
{
 Q_OBJECT
 QObject* obj;
 DecoratorPanel* self;
public:
 AJListener* init(QObject* obj, DecoratorPanel* self) { this->obj = obj; this->self = self; return this;}
public slots:
 void actionPerformed()
 {
  self->itemStateChanged(new ItemEvent((QObject*)obj));
 }
};
#endif

class DPDragDecoratorLabel : public PositionableLabel //implements DragGestureListener, DragSourceListener, Transferable
{
    Q_OBJECT

 DataFlavor* dataFlavor;
public:
/*public*/ DPDragDecoratorLabel(QString s, Editor* editor, QObject* parent);
    /**************** DragGestureListener ***************/
//    /*public*/ void dragGestureRecognized(DragGestureEvent e);
    /**************** DragSourceListener ************/
///*public*/ void dragDropEnd(DragSourceDropEvent());
//    /*public*/ void dragExit(DragSourceEvent e);
//    /*public*/ void dragOver(DragSourceDragEvent e);
//    /*public*/ void dropActionChanged(DragSourceDragEvent e);
//    /*************** Transferable *********************/
    /*public*/ QList<DataFlavor*> getTransferDataFlavors();
    /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
//    /*public*/ QObject* getTransferData(DataFlavor flavor) throw (UnsupportedFlavorException,IOException) ;
 QString mimeData();
 void mousePressEvent(QGraphicsSceneMouseEvent *e);

}; // end DragDecoratorLabel

class TextFieldListener : public ActionListener
{
 Q_OBJECT
 DecoratorPanel* panel;
 JLabel* sample;
 JTextField* textField;
public:
 TextFieldListener(JTextField* textField, JLabel* sample, DecoratorPanel* panel);
public slots:
 void textFieldChanged(QString txt);

};

class FontActionListener : public ActionListener
{
 DecoratorPanel* dc;
 Q_OBJECT
public:
 FontActionListener(DecoratorPanel* dc) {this->dc = dc;}
public slots:
 void actionPerformed()
 {
  dc->fontChange();
 }
};

class DPChangeListener :public ChangeListener
{
 Q_OBJECT
 DecoratorPanel* panel;
public:
 DPChangeListener(DecoratorPanel* panel) {this->panel = panel;}
public slots:
 void stateChanged(ChangeEvent* evt)
 {
  panel->stateChanged(evt);
 }
};

#if 0
class PreviewScene : public QGraphicsScene
{
 Q_OBJECT
 DecoratorPanel* panel;
 QGraphicsItem* item;

public:
 PreviewScene(DecoratorPanel* panel) : QGraphicsScene() {this->panel = panel;}
 void mousePressEvent(QGraphicsSceneMouseEvent* evt);
 void mouseMoveEvent(QGraphicsSceneMouseEvent*event);
 /*public*/ void setImage(QImage* img);

private:
 QMouseEvent* convertMouseEvent(QGraphicsSceneMouseEvent* evt);
 /*private*/ BufferedImage* back;// = null;
 /*private*/  QPixmap bkgnd;
};
#endif
/*
 * Draggable text field that can maintain properties for a PositionableLabel
 *
 */
class DragJTextField : public JTextField
{
 Q_OBJECT
 QDrag* dr;
 Logger* log;
 Editor* editor = nullptr;
 PositionablePopupUtil* util;
public:
 DragJTextField(QString text, int cols, Editor* editor, PositionablePopupUtil* util, QWidget* parent = 0) : JTextField(text, cols, parent)
 {
  log = new Logger("DragJTextField");
  this->editor = editor;
  this->util = util;
  setFrame(false);
 }

 void mousePressEvent(QMouseEvent * event)
 {
  if(event->button()&Qt::LeftButton)
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
 }
 /*public*/ QByteArray mimeData()
 {
  QByteArray xmldata;
  PositionableLabelXml* xml = new PositionableLabelXml();
  PositionableLabel* label = new PositionableLabel(text(), editor);
  label->setPopupUtility(util);        // no text
  label->setLevel(Editor::LABELS);
  QDomElement e = xml->store((QObject*)label);
  xml->doc.appendChild(e);
  xmldata.append(xml->doc.toString());
  log->info(tr("xml data: %1").arg(xml->doc.toString()));
  return xmldata;
 }
 void setUtil(PositionablePopupUtil* util) {this->util = util;}
};

class AJComboBox : public JComboBox
{
 Q_OBJECT
public:
 int _which;
 AJComboBox(QStringList items, int which, QWidget* parent = nullptr) : JComboBox(items, parent)
 {
  _which = which;
  connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
 }
signals:
 void itemStateChanged(ItemEvent *e);
public slots:
 void currentIndexChanged(int)
 {
  emit itemStateChanged(new ItemEvent(this));
 }
};
#endif // DECORATORPANEL_H
