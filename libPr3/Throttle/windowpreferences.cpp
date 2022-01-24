#include "windowpreferences.h"
#include "exceptions.h"
#include "system.h"
#include "logger.h"

WindowPreferences::WindowPreferences()
{

}

/**
 * A helper class for getting and setting XML attributes of a JInternalFrame.
 */
// /*public*/ class WindowPreferences {

/**
 * Collect JInternalFrame preferences.
 *
 * @param c The JInternalFrame being XMLed.
 * @return An Element containing the following prefs:
 * <ul>
 * <li> x location
 * <li> y location
 * <li> width
 * <li> height
 * <li> isIcon
 * </ul>
 */
/*public*/ /*static*/ QDomElement WindowPreferences::getPreferences(JmriJFrame* c) {
    QDomElement window = getPreferences((QWidget*) c);
    window.setAttribute("isIconified", /*String.valueOf(c.isIcon()*/ c->isMinimized()?"true":"false");
    return window;
}

/**
 * Set JInternalFrame preferences from an XML Element.
 *
 * @param c The JInternalFrame being set.
 * @param e An Element containing the following prefs:
 * <ul>
 * <li> x location
 * <li> y location
 * <li> width
 * <li> height
 * <li> isIcon
 * </ul>
 */
/*public*/ /*static*/ void WindowPreferences::setPreferences(JmriJFrame* c, QDomElement e)
{
 setPreferences((QWidget*) c, e);
 try
 {
  if (e.attribute("isIconified") != "")
  {
      //c.setIcon(e.attribute("isIconified").getBooleanValue());
   if(e.attribute("isIconified") == "true")
    c->showMinimized();
   else
    c->showNormal();
  }
 }
 catch (DataConversionException* ex) {
     //System::out.println(ex);
  Logger::error(ex->getMessage());
 }
// catch (PropertyVetoException ex) {
//     System::out.println(ex);
// }
}

/**
 * Collect container preferences.
 *
 * @param c The container being XMLed.
 * @return An Element containing the following prefs:
 * <ul>
 * <li> x location
 * <li> y location
 * <li> width
 * <li> height
 * </ul>
 */
/*public*/ /*static*/ QDomElement WindowPreferences::getPreferences(QWidget* c) {
 QDomDocument doc = QDomDocument();
    QDomElement window = doc.createElement("window");
    window.setAttribute("x", (c->pos().x()));
    window.setAttribute("y", (c->pos().y()));
    QSize size = c->size();
    window.setAttribute("width",(size.width()));
    window.setAttribute("height", (size.height()));
    window.setAttribute("isVisible", (c->isVisible()?"true":"false"));
    return window;
}

/**
 * Set Container preferences from an XML Element.
 *
 * @param c The Container being set.
 * @param e An Element containing the following prefs:
 * <ul>
 * <li> x location
 * <li> y location
 * <li> width
 * <li> height
 * </ul>
 */
/*public*/ /*static*/ void WindowPreferences::setPreferences(QWidget* c, QDomElement e, bool ignorePosition) {
    try {
  bool bok;
        int x = e.attribute("x").toInt(&bok); if(!bok) throw new DataConversionException();
        int y = e.attribute("y").toInt(&bok); if(!bok) throw new DataConversionException();
        int width = e.attribute("width").toInt(&bok); if(!bok) throw new DataConversionException();
        int height = e.attribute("height").toInt(&bok); if(!bok) throw new DataConversionException();
        if (!ignorePosition) {
            c->move(x, y);
        }
        c->resize(width, height);
        if (e.attribute("isVisible") != "") {
            c->setVisible(e.attribute("isVisible")== "true");
        }
    } catch (DataConversionException* ex) {
        //System.out.println(ex);
  Logger::error(ex->getMessage());
    }
}

/*public*/ /*static*/ void WindowPreferences::setPreferences(QWidget* c, QDomElement e) {
    setPreferences(c, e, false);
}

