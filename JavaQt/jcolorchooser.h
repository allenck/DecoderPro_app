#ifndef JCOLORCHOOSER_H
#define JCOLORCHOOSER_H
#include <QWidget>
#include "actionlistener.h"
#include <QVector>
#include "component.h"

class ColorChooserDialog;
class ColorChooserUI;
class ColorTracker;
class JDialog;
class AbstractColorChooserPanel;
class ColorSelectionModel;
class JColorChooser : public QWidget
{
 Q_OBJECT
public:
 /*public*/ static ColorChooserDialog *createDialog(Component *c, QString title, bool modal,
     JColorChooser* chooserPane, ActionListener* okListener,
     ActionListener* cancelListener);
 /*public*/ static /*final*/ QString      SELECTION_MODEL_PROPERTY;// = "selectionModel";
 /*public*/ static /*final*/ QString      PREVIEW_PANEL_PROPERTY;// = "previewPanel";
 /*public*/ static /*final*/ QString      CHOOSER_PANELS_PROPERTY;// = "chooserPanels";
 /*public*/ static QColor showDialog(Component *component,
     QString title, QColor initialColor);
 /*public*/ JColorChooser(QWidget* parent = nullptr);
 /*public*/ JColorChooser(QColor initialColor, QWidget* parent = nullptr);
 /*public*/ JColorChooser(ColorSelectionModel* model, QWidget* parent = nullptr);
// /*public*/ ColorChooserUI* getUI() ;
// /*public*/ void setUI(ColorChooserUI ui);
// /*public*/ void updateUI();
// /*public*/ QString getUIClassID();
 /*public*/ QColor getColor();
 /*public*/ void setColor(QColor color);
 /*public*/ void setColor(int r, int g, int b);
 /*public*/ void setColor(int c);
 /*public*/ void setDragEnabled(bool b);
 /*public*/ bool getDragEnabled();
 /*public*/ void setPreviewPanel(QWidget* preview);
 /*public*/ QWidget* getPreviewPanel();
 /*public*/ void addChooserPanel( AbstractColorChooserPanel* panel );
 /*public*/ AbstractColorChooserPanel* removeChooserPanel( AbstractColorChooserPanel* panel );
 /*public*/ void setChooserPanels( QVector<AbstractColorChooserPanel*> panels);
 /*public*/ QVector<AbstractColorChooserPanel*> getChooserPanels();
 /*public*/ ColorSelectionModel* getSelectionModel();
 /*public*/ void setSelectionModel(ColorSelectionModel* newModel );


signals:

public slots:

private:
    /*private*/ void common(ColorSelectionModel* model);
 /**
  * @see #getUIClassID
  * @see #readObject
  */
 /*private*/ static /*final*/ QString uiClassID;// = "ColorChooserUI";

 /*private*/ ColorSelectionModel* selectionModel;

 /*private*/ QWidget* previewPanel;// = ColorChooserComponentFactory.getPreviewPanel();

 /*private*/ QVector<AbstractColorChooserPanel*> chooserPanels;// = new AbstractColorChooserPanel[0];

 /*private*/ bool dragEnabled;

};



class ColorTracker : public ActionListener/*, Serializable*/
{
    JColorChooser* chooser;
    QColor color;
public:
    /*public*/ ColorTracker(JColorChooser* c) {
        chooser = c;
    }

    /*public*/ void actionPerformed(/*ActionEvent e*/) {
        color = chooser->getColor();
    }

    /*public*/ QColor getColor() {
        return color;
    }
};
#endif // JCOLORCHOOSER_H
