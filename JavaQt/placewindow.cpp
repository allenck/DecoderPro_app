#include "placewindow.h"
#include "loggerfactory.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include "jcomponent.h"

/**
 * Position a Window relative to a component in another window so as
 * to not obscure a component in that window. Typically, the Component
 * is being edited by actions done in the target Window.
 * <p>
 * @author Pete Cressman Copyright (C) 2018
 * @since 4.13.1
 */
// /*public*/ class PlaceWindow {
//    static GraphicsEnvironment _environ = GraphicsEnvironment.getLocalGraphicsEnvironment();
/*static*/ QList<QSize> PlaceWindow::_screenSize = QList<QSize>();
#if 0
/**
 * In a possibly multi-monitor environment, find which screens are
 * displaying the windows. This is debug code to experiment to find a
 * way to get both windows on the same device (monitor screen)
 * \p
 * getLocation() and getLocationOnScreen() return the same Point which
 * has coordinates in the total display area, i.e. all screens combined.
 * Note DefaultScreen is NOT this total combined display area.
 *
 * We assume monitors are aligned horizontally - at least this is the only
 * configuration possible from Windows settings.
 *
 * @param parent parent window
 * @param target target window
 * @return Screen number of parent window location
 */
/*public*/ static int PlaceWindow::getScreen(QWidget* parent, QWidget* target) {
    DisplayMode dm;
    QString parentDeviceID = "?";
    int parentScreenNum = -1;
    QString targetDeviceID = "?";
    int targetScreenNum = -1;
    GraphicsDevice parentDevice = parent.getGraphicsConfiguration().getDevice();
    DisplayMode parentDisplay = parentDevice.getDisplayMode();
    GraphicsDevice targetDevice = target.getGraphicsConfiguration().getDevice();
    DisplayMode targetDisplay = targetDevice.getDisplayMode();
    GraphicsDevice[] gd = _environ.getScreenDevices();
    _screenSize = new QSize[gd.length];
    for (int i = 0; i < gd.length; i++) {
        String deviceID = gd[i].getIDstring();
        if (gd[i].equals(parentDevice)) {
            parentDeviceID = deviceID;
        }
        if (gd[i].equals(targetDevice)) {
            targetDeviceID = deviceID;
        }
        dm = gd[i].getDisplayMode();
        if (dm.equals(parentDisplay)) {
            parentScreenNum = i;
        }
        if (dm.equals(targetDisplay)) {
            targetScreenNum = i;
        }
        _screenSize[i] = new QSize(dm.getWidth(), dm.getHeight());
        if (log->isDebugEnabled()) {
            log->debug("\"Screen # {} deviceID= {}: width= {}, height= {}",
                    i, deviceID, dm.getWidth(), dm.getHeight());
        }
    }
    if (log->isDebugEnabled()) {
        Point pt1 = parent.getLocation();
        Point pt2 = parent.getLocationOnScreen();
        log->debug("parentDevice= {}, parentScreenNum #{}: getLocation()= [{}, {}] getLocationOnScreen()= [{}, {}]",
                parentDeviceID, parentScreenNum, pt1.x, pt1.y, pt2.x, pt2.y);
        pt1 = target.getLocation();
        log->debug("targetDevice= {}, targetScreenNum # {}: getLocation()= [{}, {}]",
                targetDeviceID, targetScreenNum, pt1.x, pt1.y);
        GraphicsDevice dgd = _environ.getDefaultScreenDevice();
        dm = dgd.getDisplayMode();
        log->debug("\"DefaultScreen= {}: width= {}, height= {}", dgd.getIDstring(), dm.getWidth(), dm.getHeight());
        QSize totalScreen = getScreenSizeOf(gd.length - 1);
        log->debug("\"Total Screen size: width= {}, height= {}", totalScreen.width, totalScreen.height);
    }
    return parentScreenNum;
}

/**
 *
 * @param screenNum screen number
 * @return nominal QSize of screen for object on screenNum
 */
static /*private*/ QSize getScreenSizeOf(int screenNum) {
    QSize dim = new QSize(0, 0);
    int i = 0;
    while (i <= screenNum) {
        dim.width += _screenSize[i].width;
        dim.height = _screenSize[i].height;
        i++;
    }
    return dim;
}
#endif
/**
 * Find the best place to position the target window next to the parent window.
 * Choose the first position (Left, Right, Below, Above) where there is no overlap.
 * If all overlap, choose first position (Left, Right, Below, Above) where there
 * is no overlap of the component of the parent. finally bail out using the lower
 * right corner.
 * @param parent Window containing the Component
 * @param comp Component contained in the parent Window
 * @param target a popup or some kind of window with tools to
 *  edit the component
 * @return the location Point to open the target window.
 */
/*public*/ /*static*/ QPoint PlaceWindow::nextTo(QWidget* parent, JComponent* comp, QWidget* target) {
    if (target == nullptr || parent == nullptr) {
        return QPoint(0, 0);
    }
    QPoint loc;
//        Point parentLoc = parent.getLocationOnScreen();
    QPoint parentLoc = parent->pos();
    QSize parentDim = parent->size();
//    int screenNum = getScreen(parent, target);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QList<QScreen*> screens = QGuiApplication::screens();
    int screenNum = desktopWidget->screenNumber(target);
//    QSize screen = getScreenSizeOf(screenNum);
    QSize screen = screens.at(screenNum)->availableSize();
    QSize targetDim = target->sizeHint();
    QPoint compLoc;
    QSize compDim;
    if (comp != nullptr) {
        compLoc = QPoint(((QWidget*)comp->jself())->pos().x() + parentLoc.x(), ((QWidget*)comp->jself())->pos().y() + parentLoc.y());
        compDim = ((QWidget*)comp->jself())->size();
    } else {
        compLoc = QPoint(parentLoc.x() + parentDim.width()/2, parentLoc.y() + parentDim.height()/2);
        compDim = QSize(0, 0);
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("\"parentLoc: X= %1, Y= %2 is on Screen= #%3").arg(parentLoc.x()).arg(parentLoc.y()).arg(screenNum));
        log->debug(tr("\"parentDim: width= %1, height= %2").arg(parentDim.width()).arg(parentDim.height()));
        log->debug(tr("\"targetDim: width= %1, height= %2").arg(targetDim.width()).arg(targetDim.height()));
        log->debug(tr("\"screen: width= %1, height= %2").arg(screen.width()).arg( screen.height()));
    }
    // try alongside entire parent window
    int xr = parentLoc.x() + parentDim.width();
    int xl = parentLoc.x() - targetDim.width();
    int off = compLoc.y() + (compDim.height() -  targetDim.height())/2;
    if (off < 0) {
        off = 0;
    }
    QSize prevScreen = desktopWidget->screen(screenNum-1)->size();
    if (xl >= prevScreen.width()){
        loc = QPoint(xl, off);
    } else if ((xr + targetDim.width() > prevScreen.width()) && (xr + targetDim.width() <= screen.width())) {
        loc = QPoint(xr, off);
    } else {
         // try below or above parent window
        int yb = parentLoc.y() + parentDim.height();
        int ya = parentLoc.y() - targetDim.height();
        off = compLoc.x() + (compDim.width() -  targetDim.width())/2;
        if (off < 0) {
            off = 0;
        }
        if (yb + targetDim.height() < screen.height()) {
            loc = QPoint(off, yb);
        } else if (ya >= 0) {
                loc = QPoint(off, ya);
        } else {
            // try along side of component
            int space = 20;
            xr = compLoc.x() + compDim.width() + space;
            xl = compLoc.x() - targetDim.width() - space;
            if (xl >= prevScreen.width()) {
                loc = QPoint(xl, parentLoc.y());
            } else if ((xr + targetDim.width() > prevScreen.width()) && (xr + targetDim.width() <= screen.width())) {
                loc = QPoint(xr, parentLoc.y());
            } else {
                yb = compLoc.y() + compDim.height() + space;
                ya = compLoc.y() - targetDim.height();
                if (yb + targetDim.height() <= screen.height()) {
                    loc = QPoint(compLoc.x(), yb);
                } else if (ya >= 0) {
                    loc = QPoint(compLoc.x(), ya);
                } else {
                    loc = QPoint(screen.width() - targetDim.width(), screen.height() - targetDim.height());
                }
            }
        }
    }
/*
    if ((xl >= 0 && onDefaultScreen) || (xl >= dm.getWidth())) {
        loc = new Point(xl, off);
    } else if ((xr + targetDim.width < dm.getWidth() && onDefaultScreen) || (xr + targetDim.width <= screen.width && !onDefaultScreen)) {
        loc = new Point(xr, off);
    } else {
         // try below or above parent window
        int yb = parentLoc.y + parentDim.height;
        int ya = parentLoc.y - targetDim.height;
        off = compLoc.x + (compDim.width -  targetDim.width)/2;
        if (off < 0) {
            off = 0;
        }
        if (yb + targetDim.height < screen.height) {
            loc = new Point(off, yb);
        } else if (ya >= 0) {
                loc = new Point(off, ya);
        } else {
            // try along side of component
            int space = 20;
            xr = compLoc.x + compDim.width + space;
            xl = compLoc.x - targetDim.width - space;
            if ((xl >= 0 && onDefaultScreen) || (xl >= dm.getWidth())) {
                loc = new Point(xl, parentLoc.y);
            } else if ((xr + targetDim.width < dm.getWidth() && onDefaultScreen) || (xr + targetDim.width <= screen.width && !onDefaultScreen)) {
                loc = new Point(xr, parentLoc.y);
            } else {
                yb = compLoc.y + compDim.height + space;
                ya = compLoc.y - targetDim.height;
                if (yb + targetDim.height <= screen.height) {
                    loc = new Point(compLoc.x, yb);
                } else if (ya >= 0) {
                    loc = new Point(compLoc.x, ya);
                } else if (onDefaultScreen) {
                    loc = new Point(dm.getWidth() - targetDim.width, dm.getHeight() - targetDim.height);
                } else {
                    loc = new Point(screen.width - targetDim.width, screen.height - targetDim.height);
                }
            }
        }
    }
*/
    if (log->isDebugEnabled()) {
        log->debug(tr("return target location: X= %1, Y= %2").arg(loc.x()).arg(loc.y()));
    }
    return loc;
}
/*private*/ /*final*/ /*static*/ Logger* PlaceWindow::log = LoggerFactory::getLogger("PlaceWindow");
