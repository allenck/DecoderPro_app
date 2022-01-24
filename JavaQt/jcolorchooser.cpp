#include "jcolorchooser.h"
#include "jdialog.h"
#include "joptionpane.h"
#include "colorchooserdialog.h"
#include "colorselectionmodel.h"
#include "jcomponent.h"
#include "abstractcolorchooserpanel.h"
#include "defaultcolorselectionmodel.h"
#include <QBoxLayout>
#include <QTabWidget>
#include "vptr.h"
#include "jmricolorchooserpanel.h"
#include "defaultswatchchooserpanel.h"
#include "colorchoosercomponentfactory.h"
#include "exceptions.h"
#include <QMainWindow>
#include "flowlayout.h"
#include <QPushButton>
#include <QTabBar>

/**
 * <code>JColorChooser</code> provides a pane of controls designed to allow
 * a user to manipulate and select a color.
 * For information about using color choosers, see
 * <a
 href="https://docs.oracle.com/javase/tutorial/uiswing/components/colorchooser.html">How to Use Color Choosers</a>,
 * a section in <em>The Java Tutorial</em>.
 *
 * <p>
 *
 * This class provides three levels of API:
 * <ol>
 * <li>A static convenience method which shows a modal color-chooser
 * dialog and returns the color selected by the user.
 * <li>A static convenience method for creating a color-chooser dialog
 * where <code>ActionListeners</code> can be specified to be invoked when
 * the user presses one of the dialog buttons.
 * <li>The ability to create instances of <code>JColorChooser</code> panes
 * directly (within any container). <code>PropertyChange</code> listeners
 * can be added to detect when the current "color" property changes.
 * </ol>
 * <p>
 * <strong>Warning:</strong> Swing is not thread safe. For more
 * information see <a
 * href="package-summary.html#threading">Swing's Threading
 * Policy</a>.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 *
 * @beaninfo
 *      attribute: isContainer false
 *    description: A component that supports selecting a Color.
 *
 *
 * @author James Gosling
 * @author Amy Fowler
 * @author Steve Wilson
 */
///*public*/ class JColorChooser extends JComponent implements Accessible {



/**
 * The selection model property name.
 */
/*public*/ /*static*/ /*final*/ QString      JColorChooser::SELECTION_MODEL_PROPERTY = "selectionModel";

/**
 * The preview panel property name.
 */
/*public*/ /*static*/ /*final*/ QString      JColorChooser::PREVIEW_PANEL_PROPERTY = "previewPanel";

/**
 * The chooserPanel array property name.
 */
/*public*/ /*static*/ /*final*/ QString      JColorChooser::CHOOSER_PANELS_PROPERTY = "chooserPanels";

/*private*/ /*static*/ /*final*/ QString JColorChooser::uiClassID = "ColorChooserUI";

/**
 * This method shows a JColorChooser inside a JDialog. The JDialog will
 * block until it is hidden. The JDialog comes with three buttons: OK,
 * Cancel, and Reset. Pressing OK or Cancel hide the JDialog. Pressing
 * Reset will reset the JColorChooser to its initial value.
 *
 * @param component The Component that parents the JDialog.
 * @param title The title displayed in the JDialog.
 * @param initial The initial color.
 *
 * @return The selected color.
 */
/*public*/ /*static*/ QColor JColorChooser::showDialog(Component* component, QString title,
                               QColor initial)
{
  JColorChooser* choose = new JColorChooser(initial);

  JDialog* dialog = createDialog(component, title, true, choose, nullptr, nullptr);

  dialog->layout()->addWidget(choose);
  dialog->adjustSize();
  dialog->show();

  return choose->getColor();
} // showDialog()

/**
 * This method will take the given JColorChooser and place it in a JDialog
 * with the given modal property. Three buttons are displayed in the
 * JDialog: OK, Cancel and Reset. If OK or Cancel are pressed, the JDialog
 * is hidden. If Reset is pressed, then the JColorChooser will take on its
 * default color value. The given okListener will be registered to the OK
 * button and the cancelListener will be registered to the Cancel button.
 * If the modal property is set, then the JDialog will block until it is
 * hidden.
 *
 * @param component The Component that will parent the JDialog.
 * @param title The title displayed in the JDialog.
 * @param modal The modal property.
 * @param chooserPane The JColorChooser to place in the JDialog.
 * @param okListener The ActionListener to register to the OK button.
 * @param cancelListener The ActionListener to register to the Cancel
 *        button.
 *
 * @return A JDialog with the JColorChooser inside of it.
 *
 * @throws AWTError If the component is not a suitable parent.
 */
/*public*/ /*static*/ JDialog* JColorChooser::createDialog(Component* component, QString title,
                                   bool modal, JColorChooser* chooserPane,
                                   ActionListener* okListener,
                                   ActionListener* cancelListener)
{
  QObject* parent = component;// /*findParent*/component->parent();
//  if (parent == nullptr)
//    throw /*AWTError*/Exception("No suitable parent found for Component.");

  JDialog* dialog;
  //if (parent instanceof Frame)
  if(qobject_cast<QMainWindow*>(parent))
    dialog = new JDialog((QMainWindow*) parent, title, modal);
  else
    dialog = new JDialog((QDialog*) parent, title, modal);

  QVBoxLayout* thisLayout;
  dialog->setLayout(thisLayout = new QVBoxLayout());

  JPanel* panel = new JPanel();
  FlowLayout* panelLayout;
  panel->setLayout(panelLayout = new FlowLayout());

  ActionListener* al = new DefaultOKCancelListener(dialog, true);

  QPushButton* ok = new QPushButton("OK");
//  ok.addActionListener(okListener);
  if(okListener)
   connect(ok, SIGNAL(clicked(bool)), okListener->self(), SLOT(actionPerformed()));
//  ok.addActionListener(al);
  connect(ok, SIGNAL(clicked(bool)), al->self(), SLOT(actionPerformed()));

  al = new DefaultOKCancelListener(dialog, false);
  QPushButton* cancel = new QPushButton("Cancel");
//  cancel.addActionListener(cancelListener);
  if(cancelListener)
   connect(cancel, SIGNAL(clicked(bool)), cancelListener->self(), SLOT(actionPerformed()));
//  cancel.addActionListener(al);
  connect(cancel, SIGNAL(clicked(bool)), al->self(), SLOT(actionPerformed()));

  QPushButton* reset = new QPushButton("Reset");
//  reset.addActionListener(new DefaultResetListener(chooserPane));
  DefaultResetListener* resetListener = new DefaultResetListener(chooserPane);
  connect(reset, SIGNAL(clicked(bool)), resetListener/*->self()*/, SLOT(actionPerformed()));

  thisLayout->addWidget(chooserPane, 1, Qt::AlignTop);//BorderLayout.NORTH);

  panelLayout->addWidget(ok);
  panelLayout->addWidget(cancel);
  panelLayout->addWidget(reset);

  thisLayout->addWidget(panel, 0, Qt::AlignBottom);//BorderLayout.SOUTH);

  return dialog;
} // createDialog()


/**
 * Creates a color chooser pane with an initial color of white.
 */
/*public*/ JColorChooser::JColorChooser(QWidget* parent) : QWidget(parent) {
    //this(Color.white);
 common(new DefaultColorSelectionModel());
}

/**
 * Creates a color chooser pane with the specified initial color.
 *
 * @param initialColor the initial color set in the chooser
 */
/*public*/ JColorChooser::JColorChooser(QColor initialColor, QWidget* parent) : QWidget(parent){
    //this( new DefaultColorSelectionModel(initialColor) );
 common(new DefaultColorSelectionModel(initialColor));
}

/**
 * Creates a color chooser pane with the specified
 * <code>ColorSelectionModel</code>.
 *
 * @param model the <code>ColorSelectionModel</code> to be used
 */
/*public*/ JColorChooser::JColorChooser(ColorSelectionModel* model, QWidget* parent) : QWidget(parent)  {
 common(model);
}

void JColorChooser::common(ColorSelectionModel* model)
{
 previewPanel = ColorChooserComponentFactory::getPreviewPanel();

 chooserPanels = new QVector<AbstractColorChooserPanel*>();
 selectionModel = model;
// updateUI();
 dragEnabled = false;
 pcs = new SwingPropertyChangeSupport(this, nullptr);

 setLayout(new QVBoxLayout());

// QColorDialog* dlg;
// layout()->addWidget(dlg = new QColorDialog());
// dlg->setOption(QColorDialog::NoButtons);
 tabWidget = new QTabWidget();
 ((QVBoxLayout*)layout())->addWidget(tabWidget, 1);
 if(getPreviewPanel())
   ((QVBoxLayout*)layout())->addWidget(getPreviewPanel(),0);
}

/**
 * Returns the L&amp;F object that renders this component.
 *
 * @return the <code>ColorChooserUI</code> object that renders
 *          this component
 */
///*public*/ ColorChooserUI* JColorChooser::getUI() {
//    return (ColorChooserUI)ui;
//}

/**
 * Sets the L&amp;F object that renders this component.
 *
 * @param ui  the <code>ColorChooserUI</code> L&amp;F object
 * @see UIDefaults#getUI
 *
 * @beaninfo
 *       bound: true
 *      hidden: true
 * description: The UI object that implements the color chooser's LookAndFeel.
 */
///*public*/ void JColorChooser::setUI(ColorChooserUI* ui) {
////    super.setUI(ui);
//}

/**
 * Notification from the <code>UIManager</code> that the L&amp;F has changed.
 * Replaces the current UI object with the latest version from the
 * <code>UIManager</code>.
 *
 * @see JComponent#updateUI
 */
///*public*/ void JColorChooser::updateUI() {
//// ??   setUI((ColorChooserUI*)UIManager.getUI(this));
//}

/**
 * Returns the name of the L&amp;F class that renders this component.
 *
 * @return the string "ColorChooserUI"
 * @see JComponent#getUIClassID
 * @see UIDefaults#getUI
 */
///*public*/ QString JColorChooser::getUIClassID() {
//    return uiClassID;
//}

/**
 * Gets the current color value from the color chooser.
 * By default, this delegates to the model.
 *
 * @return the current color value of the color chooser
 */
/*public*/ QColor JColorChooser::getColor() {
    return selectionModel->getSelectedColor();
}

/**
 * Sets the current color of the color chooser to the specified color.
 * The <code>ColorSelectionModel</code> will fire a <code>ChangeEvent</code>
 * @param color the color to be set in the color chooser
 * @see JComponent#addPropertyChangeListener
 *
 * @beaninfo
 *       bound: false
 *      hidden: false
 * description: The current color the chooser is to display.
 */
/*public*/ void JColorChooser::setColor(QColor color) {
 QColor oldC = selectionModel->getSelectedColor();
    selectionModel->setSelectedColor(color);
    firePropertyChange("colorChange", qvariant_cast<QColor>(oldC), qvariant_cast<QColor>(color));
}

/**
 * Sets the current color of the color chooser to the
 * specified RGB color.  Note that the values of red, green,
 * and blue should be between the numbers 0 and 255, inclusive.
 *
 * @param r   an int specifying the amount of Red
 * @param g   an int specifying the amount of Green
 * @param b   an int specifying the amount of Blue
 * @exception IllegalArgumentException if r,g,b values are out of range
 * @see java.awt.Color
 */
/*public*/ void JColorChooser::setColor(int r, int g, int b) {
    setColor(QColor(r,g,b));
}

/**
 * Sets the current color of the color chooser to the
 * specified color.
 *
 * @param c an integer value that sets the current color in the chooser
 *          where the low-order 8 bits specify the Blue value,
 *          the next 8 bits specify the Green value, and the 8 bits
 *          above that specify the Red value.
 */
/*public*/ void JColorChooser::setColor(int c) {
    setColor((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
}

/**
 * Sets the <code>dragEnabled</code> property,
 * which must be <code>true</code> to enable
 * automatic drag handling (the first part of drag and drop)
 * on this component.
 * The <code>transferHandler</code> property needs to be set
 * to a non-<code>null</code> value for the drag to do
 * anything.  The default value of the <code>dragEnabled</code>
 * property
 * is <code>false</code>.
 *
 * <p>
 *
 * When automatic drag handling is enabled,
 * most look and feels begin a drag-and-drop operation
 * when the user presses the mouse button over the preview panel.
 * Some look and feels might not support automatic drag and drop;
 * they will ignore this property.  You can work around such
 * look and feels by modifying the component
 * to directly call the <code>exportAsDrag</code> method of a
 * <code>TransferHandler</code>.
 *
 * @param b the value to set the <code>dragEnabled</code> property to
 * @exception HeadlessException if
 *            <code>b</code> is <code>true</code> and
 *            <code>GraphicsEnvironment.isHeadless()</code>
 *            returns <code>true</code>
 *
 * @since 1.4
 *
 * @see java.awt.GraphicsEnvironment#isHeadless
 * @see #getDragEnabled
 * @see #setTransferHandler
 * @see TransferHandler
 *
 * @beaninfo
 *  description: Determines whether automatic drag handling is enabled.
 *        bound: false
 */
/*public*/ void JColorChooser::setDragEnabled(bool b) {
//    if (b && GraphicsEnvironment.isHeadless()) {
//        throw new HeadlessException();
//    }
    dragEnabled = b;
}

/**
 * Gets the value of the <code>dragEnabled</code> property.
 *
 * @return  the value of the <code>dragEnabled</code> property
 * @see #setDragEnabled
 * @since 1.4
 */
/*public*/ bool JColorChooser::getDragEnabled() {
    return dragEnabled;
}

/**
 * Sets the current preview panel.
 * This will fire a <code>PropertyChangeEvent</code> for the property
 * named "previewPanel".
 *
 * @param preview the <code>JComponent</code> which displays the current color
 * @see JComponent#addPropertyChangeListener
 *
 * @beaninfo
 *       bound: true
 *      hidden: true
 * description: The UI component which displays the current color.
 */
/*public*/ void JColorChooser::setPreviewPanel(QWidget* preview) {

    if (previewPanel != preview) {
        QWidget* oldPreview = previewPanel;
        previewPanel = preview;
     firePropertyChange(JColorChooser::PREVIEW_PANEL_PROPERTY, VPtr<QWidget>::asQVariant(oldPreview), VPtr<QWidget>::asQVariant(preview));
    }
}

/**
 * Returns the preview panel that shows a chosen color.
 *
 * @return a <code>JComponent</code> object -- the preview panel
 */
/*public*/ QWidget* JColorChooser::getPreviewPanel() {
    return previewPanel;
}

/**
 * Adds a color chooser panel to the color chooser.
 *
 * @param panel the <code>AbstractColorChooserPanel</code> to be added
 */
/*public*/ void JColorChooser::addChooserPanel( AbstractColorChooserPanel* panel )
{
  if(panel == nullptr)
   return;

  QVector<AbstractColorChooserPanel*>* old = chooserPanels;
  QVector<AbstractColorChooserPanel*>* newPanels = new QVector<AbstractColorChooserPanel*>(old->length()+1);
    //System.arraycopy(oldPanels, 0, newPanels, 0, oldPanels.length);
  if(old)
    qCopy(old->begin(), old->end(),newPanels->begin());
  newPanels->replace(newPanels->length()-1, panel);
  chooserPanels = newPanels;
  panel->installChooserPanel(this);
//  firePropertyChange(CHOOSER_PANELS_PROPERTY, old, newPanels);
}

void JColorChooser::stateChanged(ChangeEvent* evt)
{
 JmriColorChooserPanel* o = (JmriColorChooserPanel*)evt->getSource();
 firePropertyChange("colorChange", QVariant(), qvariant_cast<QColor>(o->getColorSelectionModel()->getSelectedColor()));
}

/**
 * Removes the Color Panel specified.
 *
 * @param panel   a string that specifies the panel to be removed
 * @return the color panel
 * @exception IllegalArgumentException if panel is not in list of
 *                  known chooser panels
 */
/*public*/ AbstractColorChooserPanel* JColorChooser::removeChooserPanel( AbstractColorChooserPanel* panel ) {


    int containedAt = -1;

    for (int i = 0; i < chooserPanels->length(); i++) {
        if (chooserPanels->at(i) == panel) {
            containedAt = i;
            break;
        }
    }
    if (containedAt == -1) {
        throw new IllegalArgumentException("chooser panel not in this chooser");
    }

    QVector<AbstractColorChooserPanel*>* newArray = new QVector<AbstractColorChooserPanel*>(chooserPanels->length()-1);

    if (containedAt == chooserPanels->length()-1) {  // at end
        //System.arraycopy(chooserPanels, 0, newArray, 0, newArray.length);
     qCopy(newArray->begin(), newArray->end(), chooserPanels->begin());
    }
    else if (containedAt == 0) {  // at start
//        System.arraycopy(chooserPanels, 1, newArray, 0, newArray.length);
     qCopy(newArray->begin()+1, newArray->end(), chooserPanels->begin());
    }
    else {  // in middle
        //System.arraycopy(chooserPanels, 0, newArray, 0, containedAt);
     qCopy(newArray->begin(), newArray->end(), chooserPanels->begin());
//        System.arraycopy(chooserPanels, containedAt+1,
//                         newArray, containedAt, (chooserPanels.length - containedAt - 1));
     qCopy(newArray->begin()+containedAt, newArray->end(), chooserPanels->begin()+(chooserPanels->length() - containedAt - 1));
    }


    setChooserPanels(newArray);

    return panel;
}


/**
 * Specifies the Color Panels used to choose a color value.
 *
 * @param panels  an array of <code>AbstractColorChooserPanel</code>
 *          objects
 *
 * @beaninfo
 *       bound: true
 *      hidden: true
 * description: An array of different chooser types.
 */
/*public*/ void JColorChooser::setChooserPanels( QVector<AbstractColorChooserPanel*>* panels) {
    QVector<AbstractColorChooserPanel*>* oldValue = chooserPanels;
    chooserPanels = panels;
    firePropertyChange(CHOOSER_PANELS_PROPERTY, VPtr<QVector<AbstractColorChooserPanel*> >::asQVariant(oldValue),
                       VPtr<QVector<AbstractColorChooserPanel*> >::asQVariant(panels));
    tabWidget->clear();
//    if(chooserPanels->size() > 1)
    {
     foreach(AbstractColorChooserPanel* panel, *chooserPanels)
     {
      if(panel == nullptr)
       continue;
      panel->installChooserPanel(this);
      QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
      sizePolicy.setHorizontalStretch(1);
      sizePolicy.setVerticalStretch(1);
      sizePolicy.setHeightForWidth(panel->sizePolicy().hasHeightForWidth());
      panel->setSizePolicy(sizePolicy);

      tabWidget->addTab(panel, panel->getTitle());

     }
    }
    if(chooserPanels->size() == 1)
     tabWidget->tabBar()->hide();
//    else
//    {
//     layout()->removeWidget(tabWidget);
//     layout()->addWidget(chooserPanels->at(0));
//     chooserPanels->at(0)->adjustSize();
//    }

}

/**
 * Returns the specified color panels.
 *
 * @return an array of <code>AbstractColorChooserPanel</code> objects
 */
/*public*/ QVector<AbstractColorChooserPanel*>* JColorChooser::getChooserPanels() {
    return chooserPanels;
}

/**
 * Returns the data model that handles color selections.
 *
 * @return a <code>ColorSelectionModel</code> object
 */
/*public*/ ColorSelectionModel* JColorChooser::getSelectionModel() {
    return selectionModel;
}


/**
 * Sets the model containing the selected color.
 *
 * @param newModel   the new <code>ColorSelectionModel</code> object
 *
 * @beaninfo
 *       bound: true
 *      hidden: true
 * description: The model which contains the currently selected color.
 */
/*public*/ void JColorChooser::setSelectionModel(ColorSelectionModel* newModel ) {
    ColorSelectionModel* oldModel = selectionModel;
    selectionModel = newModel;
    firePropertyChange(JColorChooser::SELECTION_MODEL_PROPERTY, VPtr<ColorSelectionModel>::asQVariant(oldModel), VPtr<ColorSelectionModel>::asQVariant(newModel));
}

#if 0
/**
 * See <code>readObject</code> and <code>writeObject</code> in
 * <code>JComponent</code> for more
 * information about serialization in Swing.
 */
private void writeObject(ObjectOutputStream s) throws IOException {
    s.defaultWriteObject();
    if (getUIClassID().equals(uiClassID)) {
        byte count = JComponent.getWriteObjCounter(this);
        JComponent.setWriteObjCounter(this, --count);
        if (count == 0 && ui != null) {
            ui.installUI(this);
        }
    }
}
#endif

/**
 * Returns a string representation of this <code>JColorChooser</code>.
 * This method
 * is intended to be used only for debugging purposes, and the
 * content and format of the returned string may vary between
 * implementations. The returned string may be empty but may not
 * be <code>null</code>.
 *
 * @return  a string representation of this <code>JColorChooser</code>
 */
/*protected*/ QString JColorChooser::paramString() {
    QString chooserPanelsString;// = new StringBuffer("");
    for (int i=0; i<chooserPanels->length(); i++) {
        chooserPanelsString.append("[" + chooserPanels->at(i)->toString()
                                   + "]");
    }
    QString previewPanelString = (previewPanel != nullptr ?
                                 previewPanel->objectName() : "");

    return /*super.paramString() +*/
    ",chooserPanels=" + chooserPanelsString/*.toString()*/ +
    ",previewPanel=" + previewPanelString;
}
#if 0
/////////////////
// Accessibility support
////////////////

protected AccessibleContext accessibleContext = null;

/**
 * Gets the AccessibleContext associated with this JColorChooser.
 * For color choosers, the AccessibleContext takes the form of an
 * AccessibleJColorChooser.
 * A new AccessibleJColorChooser instance is created if necessary.
 *
 * @return an AccessibleJColorChooser that serves as the
 *         AccessibleContext of this JColorChooser
 */
/*public*/ AccessibleContext getAccessibleContext() {
    if (accessibleContext == null) {
        accessibleContext = new AccessibleJColorChooser();
    }
    return accessibleContext;
}

/**
 * This class implements accessibility support for the
 * <code>JColorChooser</code> class.  It provides an implementation of the
 * Java Accessibility API appropriate to color chooser user-interface
 * elements.
 */
protected class AccessibleJColorChooser extends AccessibleJComponent {

    /**
     * Get the role of this object.
     *
     * @return an instance of AccessibleRole describing the role of the
     * object
     * @see AccessibleRole
     */
    /*public*/ AccessibleRole getAccessibleRole() {
        return AccessibleRole.COLOR_CHOOSER;
    }

} // inner class AccessibleJColorChooser
}


/*
* Class which builds a color chooser dialog consisting of
* a JColorChooser with "Ok", "Cancel", and "Reset" buttons.
*
* Note: This needs to be fixed to deal with localization!
*/
class ColorChooserDialog extends JDialog {
private Color initialColor;
private JColorChooser chooserPane;
private JButton cancelButton;

/*public*/ ColorChooserDialog(Dialog owner, String title, boolean modal,
    Component c, JColorChooser chooserPane,
    ActionListener okListener, ActionListener cancelListener)
    throws HeadlessException {
    super(owner, title, modal);
    initColorChooserDialog(c, chooserPane, okListener, cancelListener);
}

/*public*/ ColorChooserDialog(Frame owner, String title, boolean modal,
    Component c, JColorChooser chooserPane,
    ActionListener okListener, ActionListener cancelListener)
    throws HeadlessException {
    super(owner, title, modal);
    initColorChooserDialog(c, chooserPane, okListener, cancelListener);
}

protected void initColorChooserDialog(Component c, JColorChooser chooserPane,
    ActionListener okListener, ActionListener cancelListener) {
    //setResizable(false);

    this.chooserPane = chooserPane;

    Locale locale = getLocale();
    String okString = UIManager.getString("ColorChooser.okText", locale);
    String cancelString = UIManager.getString("ColorChooser.cancelText", locale);
    String resetString = UIManager.getString("ColorChooser.resetText", locale);

    Container contentPane = getContentPane();
    contentPane.setLayout(new BorderLayout());
    contentPane.add(chooserPane, BorderLayout.CENTER);

    /*
     * Create Lower button panel
     */
    JPanel buttonPane = new JPanel();
    buttonPane.setLayout(new FlowLayout(FlowLayout.CENTER));
    JButton okButton = new JButton(okString);
    getRootPane().setDefaultButton(okButton);
    okButton.getAccessibleContext().setAccessibleDescription(okString);
    okButton.setActionCommand("OK");
    okButton.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            hide();
        }
    });
    if (okListener != null) {
        okButton.addActionListener(okListener);
    }
    buttonPane.add(okButton);

    cancelButton = new JButton(cancelString);
    cancelButton.getAccessibleContext().setAccessibleDescription(cancelString);

    // The following few lines are used to register esc to close the dialog
    Action cancelKeyAction = new AbstractAction() {
        /*public*/ void actionPerformed(ActionEvent e) {
            ((AbstractButton)e.getSource()).fireActionPerformed(e);
        }
    };
    KeyStroke cancelKeyStroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
    InputMap inputMap = cancelButton.getInputMap(JComponent.
                                                 WHEN_IN_FOCUSED_WINDOW);
    ActionMap actionMap = cancelButton.getActionMap();
    if (inputMap != null && actionMap != null) {
        inputMap.put(cancelKeyStroke, "cancel");
        actionMap.put("cancel", cancelKeyAction);
    }
    // end esc handling

    cancelButton.setActionCommand("cancel");
    cancelButton.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            hide();
        }
    });
    if (cancelListener != null) {
        cancelButton.addActionListener(cancelListener);
    }
    buttonPane.add(cancelButton);

    JButton resetButton = new JButton(resetString);
    resetButton.getAccessibleContext().setAccessibleDescription(resetString);
    resetButton.addActionListener(new ActionListener() {
       /*public*/ void actionPerformed(ActionEvent e) {
           reset();
       }
    });
    int mnemonic = SwingUtilities2.getUIDefaultsInt("ColorChooser.resetMnemonic", locale, -1);
    if (mnemonic != -1) {
        resetButton.setMnemonic(mnemonic);
    }
    buttonPane.add(resetButton);
    contentPane.add(buttonPane, BorderLayout.SOUTH);

    if (JDialog.isDefaultLookAndFeelDecorated()) {
        boolean supportsWindowDecorations =
        UIManager.getLookAndFeel().getSupportsWindowDecorations();
        if (supportsWindowDecorations) {
            getRootPane().setWindowDecorationStyle(JRootPane.COLOR_CHOOSER_DIALOG);
        }
    }
    applyComponentOrientation(((c == null) ? getRootPane() : c).getComponentOrientation());

    pack();
    setLocationRelativeTo(c);

    this.addWindowListener(new Closer());
}

/*public*/ void show() {
    initialColor = chooserPane.getColor();
    super.show();
}

/*public*/ void reset() {
    chooserPane.setColor(initialColor);
}

class Closer extends WindowAdapter implements Serializable{
    /*public*/ void windowClosing(WindowEvent e) {
        cancelButton.doClick(0);
        Window w = e.getWindow();
        w.hide();
    }
}

static class DisposeOnClose extends ComponentAdapter implements Serializable{
    /*public*/ void componentHidden(ComponentEvent e) {
        Window w = (Window)e.getComponent();
        w.dispose();
    }
}

}
#endif
//class ColorTracker implements ActionListener, Serializable {
//    JColorChooser chooser;
//    Color color;

//    /*public*/ ColorTracker(JColorChooser c) {
//        chooser = c;
//    }

//    /*public*/ void actionPerformed(ActionEvent e) {
//        color = chooser.getColor();
//    }

//    /*public*/ Color getColor() {
//        return color;
//    }
//}

void JColorChooser::addPropertyChangeListener(QString propertyName, PropertyChangeListener *listener)
{
 pcs->SwingPropertyChangeSupport::addPropertyChangeListener(propertyName, listener);
}

void JColorChooser::removePropertyChangeListener(QString propertyName, PropertyChangeListener *listener)
{
 pcs->removePropertyChangeListener(propertyName, listener);
}

void JColorChooser::firePropertyChange(QString propertyName, QVariant oldVal, QVariant newVal )
{
 pcs->firePropertyChange(propertyName, oldVal, newVal);
}

QColor JColorChooser::getForeground()
{
 QColor c;
 QPalette p = palette();
 QString ss = styleSheet();
 c = p.color(QPalette::Foreground);
 if(ss == "")
   return c;
}
