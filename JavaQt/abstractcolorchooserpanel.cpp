#include "abstractcolorchooserpanel.h"
#include <QIcon>
#include "exceptions.h"
#include "jcolorchooser.h"
#include "defaultcolorselectionmodel.h"

// /*public*/ /*abstract*/ class AbstractColorChooserPanel extends JPanel {


/*public*/ AbstractColorChooserPanel::AbstractColorChooserPanel(QWidget *parent)
 : JPanel(parent)
{
    // compiled code
}

/*public*/ /*abstract*/ void AbstractColorChooserPanel::updateChooser() {}

/*protected*/ /*abstract*/ void AbstractColorChooserPanel::buildChooser() {}

/*public*/ /*abstract*/ QString AbstractColorChooserPanel::getDisplayName() {return "";}

/**
 * Provides a hint to the look and feel as to the
 * <code>KeyEvent.VK</code> constant that can be used as a mnemonic to
 * access the panel. A return value &lt;= 0 indicates there is no mnemonic.
 * <p>
 * The return value here is a hint, it is ultimately up to the look
 * and feel to honor the return value in some meaningful way.
 * <p>
 * This implementation returns 0, indicating the
 * <code>AbstractColorChooserPanel</code> does not support a mnemonic,
 * subclasses wishing a mnemonic will need to override this.
 *
 * @return KeyEvent.VK constant identifying the mnemonic; &lt;= 0 for no
 *         mnemonic
 * @see #getDisplayedMnemonicIndex
 * @since 1.4
 */
/*public*/ int AbstractColorChooserPanel::getMnemonic() {
    // compiled code
}

/**
 * Provides a hint to the look and feel as to the index of the character in
 * <code>getDisplayName</code> that should be visually identified as the
 * mnemonic. The look and feel should only use this if
 * <code>getMnemonic</code> returns a value &gt; 0.
 * <p>
 * The return value here is a hint, it is ultimately up to the look
 * and feel to honor the return value in some meaningful way. For example,
 * a look and feel may wish to render each
 * <code>AbstractColorChooserPanel</code> in a <code>JTabbedPane</code>,
 * and further use this return value to underline a character in
 * the <code>getDisplayName</code>.
 * <p>
 * This implementation returns -1, indicating the
 * <code>AbstractColorChooserPanel</code> does not support a mnemonic,
 * subclasses wishing a mnemonic will need to override this.
 *
 * @return Character index to render mnemonic for; -1 to provide no
 *                   visual identifier for this panel.
 * @see #getMnemonic
 * @since 1.4
 */
/*public*/ int AbstractColorChooserPanel::getDisplayedMnemonicIndex() {
    return 0;
}

/**
 * Returns the small display icon for the panel.
 * @return the small display icon
 */
/*public*/ /*abstract*/ QIcon AbstractColorChooserPanel::getSmallDisplayIcon() {return QIcon();}

/**
 * Returns the large display icon for the panel.
 * @return the large display icon
 */
/*public*/ /*abstract*/ QIcon AbstractColorChooserPanel::getLargeDisplayIcon() {return QIcon();}

/**
 * Invoked when the panel is added to the chooser.
 * If you override this, be sure to call <code>super</code>.
 *
 * @param enclosingChooser the chooser to which the panel is to be added
 * @exception RuntimeException  if the chooser panel has already been
 *                          installed
 */
/*public*/ void AbstractColorChooserPanel::installChooserPanel(JColorChooser* enclosingChooser) {
 if (chooser != nullptr) {
     throw /*RuntimeException*/ Exception("This chooser panel is already installed");
 }
 chooser = enclosingChooser;
 chooser->addPropertyChangeListener("enabled", enabledListener);
 setEnabled(chooser->isEnabled());
 buildChooser();
 updateChooser();
}

/**
 * Invoked when the panel is removed from the chooser.
 * If override this, be sure to call <code>super</code>.
 *
 * @param enclosingChooser the chooser from which the panel is to be removed
 */
/*public*/ void AbstractColorChooserPanel::uninstallChooserPanel(JColorChooser* enclosingChooser) {
 chooser->removePropertyChangeListener("enabled", enabledListener);
         chooser = nullptr;
}

/**
 * Returns the model that the chooser panel is editing.
 * @return the <code>ColorSelectionModel</code> model this panel
 *         is editing
 */
/*public*/ ColorSelectionModel* AbstractColorChooserPanel::getColorSelectionModel() {
 return (this->chooser != nullptr)
                 ? this->chooser->getSelectionModel()
                 : nullptr;
}

/**
 * Returns the color that is currently selected.
 * @return the <code>Color</code> that is selected
 */
/*protected*/ QColor AbstractColorChooserPanel::getColorFromModel() {
 ColorSelectionModel* model = getColorSelectionModel();
 return (model != nullptr)
         ? model->getSelectedColor()
         : nullptr;
}

void AbstractColorChooserPanel::setSelectedColor(QColor color) {
 ColorSelectionModel* model = getColorSelectionModel();
 if (model != nullptr) {
     model->setSelectedColor(color);
 }
}
/**
 * Sets whether color chooser panel allows to select the transparency
 * (alpha value) of a color.
 * This method fires a property-changed event, using the string value of
 * {@code TRANSPARENCY_ENABLED_PROPERTY} as the name
 * of the property.
 *
 * <p>The value is a hint and may not be applicable to all types of chooser
 * panel.
 *
 * <p>The default value is {@code true}.
 *
 * @param b true if the transparency of a color can be selected
 * @see #isColorTransparencySelectionEnabled()
 */
//@BeanProperty(description
//        = "Sets the transparency of a color selection on or off.")
/*public*/ void AbstractColorChooserPanel::setColorTransparencySelectionEnabled(bool b){
}
/**
 * Gets whether color chooser panel allows to select the transparency
 * (alpha value) of a color.
 *
 * @return true if the transparency of a color can be selected
 * @see #setColorTransparencySelectionEnabled(boolean)
 */
/*public*/ bool AbstractColorChooserPanel::isColorTransparencySelectionEnabled(){
    return true;
}
///*public*/ void AbstractColorChooserPanel::paint(Graphics g) {
//    // compiled code
//}

/**
 * Returns an integer from the defaults table. If <code>key</code> does
 * not map to a valid <code>Integer</code>, <code>default</code> is
 * returned.
 *
 * @param key  an <code>Object</code> specifying the int
 * @param defaultValue Returned value if <code>key</code> is not available,
 *                     or is not an Integer
 * @return the int
 */
int AbstractColorChooserPanel::getInt(QVariant key, int defaultValue) {
#if 0
 Object value = UIManager.get(key, getLocale());

         if (value instanceof Integer) {
             return ((Integer)value).intValue();
         }
         if (value instanceof String) {
             try {
                 return Integer.parseInt((String)value);
             } catch (NumberFormatException nfe) {}
         }
         return defaultValue;
#endif
}

/*public*/ QString AbstractColorChooserPanel::toString()
{
 return QString(this->metaObject()->className());
}
