#ifndef FONTPANEL_H
#define FONTPANEL_H
#include "jpanel.h"
#include "actionlistener.h"
#include "jcombobox.h"
#include "jspinner.h"

class PositionablePopupUtil;
class Logger;
class AJComboBox1;
class FontPanel : public JPanel
{
 Q_OBJECT
public:
 enum STYLES
 {
  PLAIN,
  BOLD,
  ITALIC
 };
 /*public*/ FontPanel(PositionablePopupUtil* util, ActionListener* ca);
 /*public*/ void setFontSelections();

public slots:
 /*public*/ void itemStateChanged(EventObject* e);

signals:
 void fontSizeChanged(int);
 void fontStyleChanged(int);
 void fontFaceChanged(QString);

private:
 static Logger* log;
 static /*final*/ QStringList JUSTIFICATION;
 static /*final*/ QStringList STYLES;
 static /*final*/ QStringList FONTSIZE;
 enum FATTR
 {
  SIZE = 1,
  STYLE = 2,
  JUST = 3,
  FACE = 4
 };
 /*private*/ AJComboBox1* _fontFaceBox;
 /*private*/ AJComboBox1* _fontSizeBox;
 /*private*/ AJComboBox1* _fontStyleBox;
 /*private*/ AJComboBox1* _fontJustBox;

 PositionablePopupUtil* _util;
 ActionListener* _callBack;
 /*private*/ JPanel* makeBoxPanel(QString caption, JComboBox* box);
 /*private*/ void makeFontPanels();


};
//@SuppressWarnings("unchecked")
/*static*/ class AJComboBox1 : public JComboBox /*<T> - can't get this to work*/ {
 Q_OBJECT
public:
    int _which;
    AJComboBox1(QVector<QFont> items, int which) : JComboBox(){
        //super(items);
        _which = which;
        foreach (QFont f, items) {
         addItem(f.family(), qvariant_cast<QFont>(f));
        }
    }
    AJComboBox1(QStringList items, int which) : JComboBox(items){
        //super(items);
        _which = which;
    }
};

/*static*/ class AJSpinner1 :public JSpinner {
 Q_OBJECT

    int _which;
public:

    AJSpinner1(SpinnerModel* model, int which) : JSpinner(model) {
        //super(model);
     _which = which;
 }
};

#endif // FONTPANEL_H
