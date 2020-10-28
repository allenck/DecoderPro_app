#ifndef JCOLORCHOOSER_H
#define JCOLORCHOOSER_H
#include <QWidget>
#include "actionlistener.h"
#include <QVector>
#include "component.h"
#include "propertychangesupport.h"
#include "jdialog.h"
#include "jcomponent.h"
#include "propertychangesupport.h"

class ChangeEvent;
class QTabWidget;
class ColorChooserDialog;
class ColorChooserUI;
class ColorTracker;
class JDialog;
class AbstractColorChooserPanel;
class ColorSelectionModel;
class JColorChooser : public QWidget, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 /*public*/ static JDialog* createDialog(Component* component, QString title,
                                    bool modal, JColorChooser* chooserPane,
                                    ActionListener* okListener,
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
 /*public*/ void setChooserPanels(QVector<AbstractColorChooserPanel *> *panels);
 /*public*/ QVector<AbstractColorChooserPanel*>* getChooserPanels();
 /*public*/ ColorSelectionModel* getSelectionModel();
 /*public*/ void setSelectionModel(ColorSelectionModel* newModel );

 void addPropertyChangeListener(QString s, PropertyChangeListener* l);
 void removePropertyChangeListener(QString s, PropertyChangeListener* l);
 PropertyChangeSupport* pcs;
 /*public*/ QObject* jself() {return (QObject*)this;}

 /*public*/ bool isOpaque() {return true;}
 QColor getForeground();
 /*public*/ QColor getBackground() {return QColor();}
 /*public*/ void setBackground(QColor) {}
 /*public*/ void setOpaque(bool) {}
 /*public*/ QFont getFont() {return QFont();}
 /*public*/ void setFont(QFont) {}
 /*public*/ void setBorder(Border* border) override {this->_border = border;}
 /*public*/ Border* getBorder() {return _border;}
 /*public*/ void setEnabled(bool b) override {QWidget::setEnabled(b);}
signals:

public slots:
 void stateChanged(ChangeEvent* evt);

private:
    /*private*/ void common(ColorSelectionModel* model);
 /**
  * @see #getUIClassID
  * @see #readObject
  */
 /*private*/ static /*final*/ QString uiClassID;// = "ColorChooserUI";

 /*private*/ ColorSelectionModel* selectionModel = nullptr;

 /*private*/ QWidget* previewPanel;// = ColorChooserComponentFactory.getPreviewPanel();

 /*private*/ QVector<AbstractColorChooserPanel*>* chooserPanels;// = new AbstractColorChooserPanel[0];

 /*private*/ bool dragEnabled;
 QTabWidget* tabWidget;
 void firePropertyChange(QString propertyName, QVariant old, QVariant newP );
 Border* _border = nullptr;


protected:
 /*protected*/ QString paramString();

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

/**
 * This method resets the JColorChooser color to the initial color when the
 * action is performed.
 */
 /*static*/ class DefaultResetListener : public ActionListener
 {
 Q_OBJECT
  /** The JColorChooser to reset. */
  /*private*/ JColorChooser* chooser;

  /** The initial color. */
  /*private*/ QColor init;
public:
  /**
   * Creates a new DefaultResetListener with the given JColorChooser.
   *
   * @param chooser The JColorChooser to reset.
   */
   /*public*/ DefaultResetListener(JColorChooser* chooser)
   {
    //super();
    this->chooser = chooser;
    init = chooser->getColor();
   }

   /**
    * This method resets the JColorChooser to its initial color.
    *
    * @param e The ActionEvent.
    */
    /*public*/ void actionPerformed(/*ActionEvent e*/)
    {
     chooser->setColor(init);
    }
   };

/**
 * A helper class that hides a JDialog when the action is performed.
 */
 /*static*/ class DefaultOKCancelListener : public ActionListener
 {
 Q_OBJECT
  /** The JDialog to hide. */
  /*private*/ JDialog* dialog;
  bool bAccept;
public:
  /**
   * Creates a new DefaultOKCancelListener with the given JDialog to hide.
   *
   * @param dialog The JDialog to hide.
   */
   /*public*/ DefaultOKCancelListener(JDialog* dialog, bool accept)
   {
     //super();
     this->dialog = dialog;
    bAccept = accept;
   }
  public slots:
   /**
    * This method hides the JDialog when called.
    *
    * @param e The ActionEvent.
    */
    /*public*/ void actionPerformed(/*ActionEvent e*/)
    {
     dialog->hide();
     if(bAccept)
      dialog->accept();
     else
      dialog->reject();
    }
   };
#endif // JCOLORCHOOSER_H
