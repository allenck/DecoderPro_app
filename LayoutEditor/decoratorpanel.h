#ifndef DECORATORPANEL_H
#define DECORATORPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QRadioButton>
#include "positionablelabel.h"

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
class QColorDialog;
class QButtonGroup;
class PositionableLabel;
class PositionablePopupUtil;
class Editor;
class AJSpinner;
class AJComboBox;
class DecoratorPanel : public QWidget
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
    /*public*/ DecoratorPanel(Editor* editor, DisplayFrame* paletteFrame, QWidget *parent = 0);
    /*public*/ void initDecoratorPanel(Positionable* pos);
    /*public*/ void stateChanged(ChangeEvent* e);
    /*public*/ PositionablePopupUtil* getPositionablePopupUtil();
    /*public*/ void getText(Positionable* pos);
    /*public*/ bool isOpaque();
    /*public*/ void itemStateChanged(ItemEvent* e);
    /*public*/ void setSuppressRecentColor(bool b);
    /*public*/ void setAttributes(Positionable* pos);

signals:

public slots:
    void AJRadioButton_toggled(bool);
    void currentColorChanged(QColor);
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
     FOREGROUND_BUTTON = 1,
     BACKGROUND_BUTTON = 2,
     TRANSPARENT_BUTTON = 3,
     BORDERCOLOR_BUTTON = 4
    };

    /*private*/ AJRadioButton* _fontButton;
    /*private*/ AJRadioButton* _borderButton;
    /*private*/ AJRadioButton* _backgroundButton;


    QColorDialog* _chooser;
    /*private*/ QWidget* makeBgButtonPanel(/*@Nonnull*/ ImagePanel* preview1, ImagePanel* preview2, QVector<BufferedImage*>* imgArray);

    /*private*/ PositionablePopupUtil* _util;
    bool _isOpaque;			// transfer opaqueness from decorator label here to panel label being edited
    /*private*/ QButtonGroup* _buttonGroup;
    /*private*/ int _selectedButton;
    /*private*/ QString _selectedState;
    /*private*/ QMap<QString, PositionableLabel*>* _samples = nullptr;

    Editor* _editor;
    /*private*/ QWidget* makeBoxPanel(QString caption, AJComboBox* box);
    /*private*/ QWidget* makeSpinPanel(QString caption, AJSpinner* spin);
    /*private*/ QWidget* makeTextPanel(QString caption, PositionableLabel* sample, int state);
    /*private*/ AJRadioButton* makeButton(AJRadioButton* button);
    /*private*/ void updateSamples();
    QString text;
    QVector<BufferedImage*>* imgArray;
    static Logger* log;
    ImagePanel* preview1;
    ImagePanel* _previewPanel;
    /*private*/ /*final*/ QWidget* _samplePanel;
    /*private*/ bool _isPositionableLabel;
    /*protected*/ void fontChange();
    /*private*/ void finishInit(bool addBgCombo);
    /*private*/ void doPopupUtility(QString type, PositionableLabel* sample, bool editText);
    /*private*/ void makeFontPanels();

    private slots:
    void on_bgColorBox();

protected:
    /*protected*/ QVector<BufferedImage*>* _backgrounds; // array of Image backgrounds
    /*protected*/ QComboBox* _bgColorBox;

    friend class AJRBActionListener;
    friend class TextFieldListener;
    /*protected*/ DisplayFrame* _paletteFrame;
    /*protected*/ QVector<BufferedImage*>* getBackgrounds();
    /*protected*/ void setBackgrounds(QVector<BufferedImage*>*  imgArray);
friend class TextItemPanel;
};
/*static*/ class AJComboBox : public QComboBox
{
 Q_OBJECT
 int _which;
public:
 AJComboBox(QStringList items, int which);
 friend class DecoratorPanel;
};
/*static*/ class AJSpinner : public  QSpinBox
{
    Q_OBJECT
    int _which;
public:
    AJSpinner(SpinnerModel* model, int which);
    friend class DecoratorPanel;
};
/*static*/ class AJRadioButton : public QRadioButton {
    Q_OBJECT
int which;
public:
 AJRadioButton(QString text, int w);
 friend class DecoratorPanel;
 friend class AJRBActionListener;
};
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
class ChangeEvent : public QObject
{
 Q_OBJECT
 QObject* source;
public:
 ChangeEvent(QObject* source) {this->source = source;}
 QObject* getSource() { return source;}
};
class ItemEvent : public QObject
{
 Q_OBJECT
 QObject* source;
public:
 ItemEvent(QObject* source) {this->source = source;}
 QObject* getSource() { return source;}
};

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
#if 1
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
 void mousePressEvent(QMouseEvent *e);

}; // end DragDecoratorLabel
#endif
class TextFieldListener : public ActionListener
{
 Q_OBJECT
 DecoratorPanel* panel;
 JLabel* sample;
 JTextField* textField;
public:
 TextFieldListener* init(JTextField* textField, JLabel* sample, DecoratorPanel* panel);
public slots:
 void actionPerformed(ActionEvent *e = 0);

};

#endif // DECORATORPANEL_H
