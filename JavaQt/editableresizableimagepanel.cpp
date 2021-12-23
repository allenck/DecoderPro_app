#include "editableresizableimagepanel.h"
#include "logger.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>
#include <QAction>
#include "filedrop.h"
#include "file.h"
#include "fileutil.h"

EditableResizableImagePanel::EditableResizableImagePanel(QWidget* parent)
 : ResizableImagePanel(parent)
{
 setDnd(true);

}
///*public*/ class EditableResizableImagePanel extends ResizableImagePanel implements FileDrop.Listener {


/**
 * Default constructor.
 *
 */
///*public*/ EditableResizableImagePanel() {
//    super();
//    setDnd(true);
//}

/**
 * Constructor with initial image file path as parameter. Component will be
 * (preferred) sized to image sized
 *
 * @param imagePath Path to image to display
 */
/*public*/ EditableResizableImagePanel::EditableResizableImagePanel(QString imagePath, QWidget* parent)
 : ResizableImagePanel(imagePath, parent)
{
    //super(imagePath);
    setDnd(true);
}

/**
 * Constructor for DnDImagePanel with forced initial size
 *
 * @param imagePath Path to image to display
 * @param w         Panel width
 * @param h         Panel height
 */
/*public*/ EditableResizableImagePanel::EditableResizableImagePanel(QString imagePath, int w, int h, QWidget* parent)
 : ResizableImagePanel(imagePath, w, h,parent)
{
    //super(imagePath, w, h);
    setDnd(true);
}

/**
 * Enable or disable drag'n drop, dropped files will be copied in latest
 * used image path top folder when dnd enabled, also enable contextual menu
 * with remove entry
 *
 */
/*public*/ void EditableResizableImagePanel::setDnd(bool dnd)
{
    log = new Logger("EditableResizableImagePanel");

    if (dnd)
    {

     fileDrop = new FileDrop(this, (FileDrop::Listener*)this);
     connect(fileDrop, SIGNAL(dropFiles(QList<File*>)), this, SLOT(filesDropped(QList<File*>)));
#if 0
        if (myMouseAdapter == NULL) {
            myMouseAdapter = new MyMouseAdapter(this);
        }
        addMouseListener(myMouseAdapter);
#endif
        setAcceptDrops(true);
    }
    else
    {

        FileDrop::remove(this);
#if 0
        if (myMouseAdapter != NULL) {
            removeMouseListener(myMouseAdapter);
        }
#endif
    }
}
#if 0
//
// For contextual menu remove
class MyMouseAdapter implements MouseListener {

    /*private*/ final JPopupMenu popUpMenu;
    /*private*/ final JMenuItem removeMenuItem;
    /*private*/ ResizableImagePanel rip;

    /*public*/ MyMouseAdapter(ResizableImagePanel resizableImagePanel) {
        rip = resizableImagePanel;
        popUpMenu = new JPopupMenu();
        removeMenuItem = new JMenuItem("Remove");
        removeMenuItem.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                rip.setImagePath(null);
            }
        });
        popUpMenu.add(removeMenuItem);
    }

    void setRemoveMenuItemEnable(boolean b) {
        removeMenuItem.setEnabled(b);
    }

    @Override
    /*public*/ void mouseClicked(MouseEvent e) {
        maybeShowPopup(e);
    }

    @Override
    /*public*/ void mousePressed(MouseEvent e) {
        maybeShowPopup(e);
    }

    @Override
    /*public*/ void mouseReleased(MouseEvent e) {
        maybeShowPopup(e);
    }

    @Override
    /*public*/ void mouseEntered(MouseEvent e) {
    }

    @Override
    /*public*/ void mouseExited(MouseEvent e) {
    }

    /*private*/ void maybeShowPopup(MouseEvent e) {
        if (e.isPopupTrigger()) {
            popUpMenu.show(e.getComponent(), e.getX(), e.getY());
        }
    }
}
#endif
void EditableResizableImagePanel::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::RightButton  )
    {
       popup = new QMenu();
       QAction* act = new QAction(tr("Remove"), this);
       popup->addAction(act);
       connect(act, SIGNAL(triggered()), this, SLOT(on_removeAction()));
       popup->exec(QCursor::pos());
    }
}

void EditableResizableImagePanel::on_removeAction()
{
 setImagePath("");
}

/*public*/ void EditableResizableImagePanel::setDropFolder(QString s) {
    dropFolder = s;
}

/*public*/ QString EditableResizableImagePanel::getDropFolder() {
    return dropFolder;
}
#if 1
/**
 * Callback for the dnd listener
 */
//@Override
/*public*/ void EditableResizableImagePanel::filesDropped(QList<File*> files) {
    if (files.isEmpty()) {
        return;
    }
    if (files.length() == 0) {
        return;
    }
    File* dest = files[0];
    if (dropFolder != NULL) {
        dest = new File(dropFolder + File::separatorChar + files.at(0)->getName());
        if (files.at(0)->getParent().compare(dest->getParent()) != 0) {
            try {
                FileUtil::createDirectory(dest->getParentFile()->getPath());
                FileUtil::copy(files[0], dest);
            } catch (IOException* ex) {
                log->error("filesDropped: error while copying new file, using original file");
                dest = files.at(0);
            }
        }
    }
    setImagePath(dest->getPath());
}
#endif
#if 0
void EditableResizableImagePanel::dragEnterEvent(QDragEnterEvent * event)
{
 QStringList l = event->mimeData()->formats();
 log->debug(tr("drag enter %1 ").arg(l.at(0)));
  if (event->mimeData()->hasFormat("text/uri-list"))
          event->acceptProposedAction();
}

void EditableResizableImagePanel::dropEvent(QDropEvent *event)
{
// textBrowser->setPlainText(event->mimeData()->text());
//     mimeTypeCombo->clear();
//     mimeTypeCombo->addItems(event->mimeData()->formats());
 QString text = event->mimeData()->text();
 event->acceptProposedAction();
 QUrl url = QUrl(text);
 log->debug(tr("drag drop %1 ").arg(url.toLocalFile()));
 QString path = url.toLocalFile();
 path.replace("\r\n", "");
 if(url.isLocalFile())
 {
  QImage img = QImage(path);
  if(!img.isNull())
  {
    setImagePath(path);
  }
  else
   log->warn(tr("Dropped file %1 is not a valid Image").arg(url.toLocalFile()));
  event->acceptProposedAction();
 }
}
#endif
