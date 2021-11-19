#include "previewdialog.h"
#include "actionlistener.h"
#include "jframe.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include "jtextfield.h"
#include <QPushButton>
#include "actionlistener.h"
#include <QMessageBox>
#include "catalogpanel.h"
#include <QScrollArea>
#include <QRadioButton>
#include <QButtonGroup>
#include <QByteArray>
#include <QList>
#include "gridbagconstraints.h"
#include "namedicon.h"
#include "dragjlabel.h"
#include "imageindexeditor.h"
#include "dataflavor.h"
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>

//PreviewDialog::PreviewDialog(QWidget *parent) :
//    QDialog(parent)
//{
//}
/**
 * Create a Dialog to display the images in a file system directory.
 * <P>
 *
 *
 * <hr>
 * This file is part of JMRI.  Displays filtered files from a file system
 * directory.  May be modal or modeless.  Modeless has dragging enabled.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
///*public*/ class PreviewDialog extends JDialog {

/*static*/ QColor    PreviewDialog::_grayColor =  QColor(235,235,235);

    //static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.catalog.CatalogBundle");

/*public*/ PreviewDialog::PreviewDialog(JFrame* frame, QString title, QDir* dir, QStringList filter) : JDialog(frame, title, false)
{
 //super(frame, tr(title), modality);
 _currentBackground = _grayColor;

 _previewLabel = new QLabel();
  _noMemory = false;
  log = new Logger("PreviewDialog");
  _cnt = 0;
  _startNum = 0;

 _currentDir = dir;
 _filter =  QStringList();
 for (int i=0; i<filter.length(); i++) {
     _filter.append( filter.at(i));
    }
}

/*public*/ void PreviewDialog::init(ActionListener* addAction, ActionListener* moreAction, ActionListener* lookAction, ActionListener* cancelAction, int startNum, JFrame* waitDialog)
{
 waitDialog->setVisible(true);
#if 1
//    waitDialog.invalidate();
//    waitDialog.repaint();
    if (log->isDebugEnabled()) log->debug("Enter _previewDialog.init dir= "+_currentDir->absolutePath());
//    addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                DirectorySearcher.instance().close();
//                dispose();
//            }
//        });
 QWidget* pTop = new QWidget();
 pTop->setLayout(new QVBoxLayout(pTop/*, BoxLayout.Y_AXIS*/));
 pTop->layout()->addWidget(new QLabel(_currentDir->absolutePath()));
 JTextField* msg = new JTextField();
 msg->setFont( QFont("Dialog", 12, QFont::Bold));
 msg->setReadOnly(true);
//    msg.setBackground(pTop.getBackground());
 if(layout() == NULL)
  setLayout(new QVBoxLayout);
 pTop->layout()->addWidget(msg);
 /* getContentPane()->*/layout()->addWidget(pTop/*, BorderLayout.NORTH*/);

 QWidget* p = new QWidget();
 p->setLayout(new QHBoxLayout(p/*, BoxLayout.X_AXIS*/));
 //p.add(Box.createHorizontalStrut(5));
 ((QBoxLayout*)p->layout())->addStrut(5);

 if (moreAction != NULL)
 {
  //p.add(Box.createHorizontalStrut(5));
  ((QBoxLayout*)p->layout())->addStrut(5);
  _moreButton = new QPushButton(tr("Show More"));
  //_moreButton.addActionListener(moreAction);
  connect(_moreButton, SIGNAL(clicked()), moreAction->self(), SLOT(actionPerformed()));
  p->layout()->addWidget(_moreButton);
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(_moreButton->sizePolicy().hasHeightForWidth());
  _moreButton->setSizePolicy(sizePolicy);
 }

 QWidget* previewPanel = setupPanel();     // provide panel for images, add to bottom of window
 _startNum = startNum;
//    try {
 _moreButton->setVisible(setIcons(startNum));
//    } catch (OutOfMemoryError oome) {
//        log->error("OutOfMemoryError AvailableMemory= "+QString::number(availableMemory())+", "+QString::number(_cnt)+" files read.");
//        resetPanel();
//    }

 if (addAction != NULL)
 {
  if (_moreButton->isVisible())
  {
//            JOptionPane.showMessageDialog(this,
//                                  java.text.MessageFormat.format(tr("tooManyIcons"),
//                                  new Object[] {_currentDir.getName()}),
//                                  tr("warn"), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("Warning"), tr("Directory \"%1\" has too many images to add to the Catalog.\nMove or copy those you want to use to another directory.").arg(_currentDir->dirName()));
   msg->setText(tr("Press \"Show More\" to see more images from this directory"));
  }
  else
  {
   //p.add(Box.createHorizontalStrut(5));
    ((QBoxLayout*)p->layout())->addStrut(5);
    _addButton = new QPushButton(tr("Add To Catalog"));
    //_addButton.addActionListener(addAction);
    connect(_addButton, SIGNAL(clicked()), addAction->self(), SLOT(actionPerformed()));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_addButton->sizePolicy().hasHeightForWidth());
    _addButton->setSizePolicy(sizePolicy);
    p->layout()->addWidget(_addButton);
   msg->setText(tr("Press \"Add\" to add this directory and its subdirectories to the Catalog"));
  }
 }
 else if (lookAction != NULL)
 {
  if (_moreButton->isVisible())
  {
   msg->setText(tr("Press \"Show More\" to see more images from this directory"));
  }
 }
 else
 {
  msg->setText(tr("Drag any image you may want to an Image Index node or icon editor "));
 }

 if (lookAction != NULL)
 {
  //p.add(Box.createHorizontalStrut(5));
  ((QBoxLayout*)p->layout())->addStrut(5);
  QPushButton* lookButton = new QPushButton(tr("Continue Searching"));
  //lookButton->layout()->addWidgetActionListener(lookAction);
  connect(lookButton, SIGNAL(clicked()), lookAction->self(), SLOT(actionPerformed()));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(lookButton->sizePolicy().hasHeightForWidth());
  lookButton->setSizePolicy(sizePolicy);
  p->layout()->addWidget(lookButton);
 }
 //p.add(Box.createHorizontalStrut(5));
 ((QBoxLayout*)p->layout())->addStrut(5);
 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
 //cancelButton.addActionListener(cancelAction);
 connect(cancelButton, SIGNAL(clicked()), cancelAction->self(), SLOT(actionPerformed()));
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
 cancelButton->setSizePolicy(sizePolicy);
 p->layout()->addWidget(cancelButton);
 //p.add(Box.createHorizontalStrut(5));
 ((QBoxLayout*)p->layout())->addStrut(5);
 p->resize( QSize(400, _moreButton->sizeHint().height()));

 QWidget* panel = new QWidget();
 panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
 panel->layout()->addWidget(p);
 //panel.add(new JSeparator());
 QFrame* line = new QFrame(/*centralwidget()*/this);
 line->setObjectName(QString::fromUtf8("line"));
 line->setFrameShape(QFrame::HLine);
 line->setFrameShadow(QFrame::Sunken);
 panel->layout()->addWidget(line);

 panel->layout()->addWidget(previewPanel);
 /*getContentPane()->*/layout()->addWidget(panel);
 resize( QSize(450, previewPanel->size().height() + 2*p->size().height()));
 //setMinimumSize(new Dimension(450,300));
 //setLocationRelativeTo(NULL);
 pack();
 waitDialog->setVisible(false);
 setVisible(true);
#endif
}

/**
* Setup a display panel to display icons
*/
/*private*/ QWidget* PreviewDialog::setupPanel() {
    QWidget* previewPanel = new QWidget();
    previewPanel->setLayout(new QVBoxLayout(previewPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* p = new QWidget();
    p->setLayout(new QHBoxLayout(p/*, BoxLayout.X_AXIS*/));
    p->layout()->addWidget(_previewLabel);
    previewPanel->layout()->addWidget(p);
//    _preview = new QWidget();
//    _preview->setGeometry( QRect(0,0,2*CatalogPanel::ICON_WIDTH, 2*CatalogPanel::ICON_HEIGHT));
//    gridbag = new QGridLayout();
//    _preview->setLayout(gridbag);
    _preview = new QTableWidget();
    _preview->setColumnCount(6);
    _preview->resizeRowsToContents();
    _preview->horizontalHeader()->hide();
    _preview->verticalHeader()->hide();
    previewPanel->layout()->addWidget(_preview);
//    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(_preview->sizePolicy().hasHeightForWidth());
//    _preview->setSizePolicy(sizePolicy);
//    js = new QScrollArea(previewPanel);
//    js->setWidgetResizable(true);
//    previewPanel->layout()->addWidget(js);
//    js->setWidget(_preview);
    //_preview->setMinimumSize( QSize(200, 150));
    QRadioButton* whiteButton = new QRadioButton(tr("White")/*,false*/);
    QRadioButton* grayButton = new QRadioButton(tr("Light Gray")/*,true*/);
    grayButton->setChecked(true);
    QRadioButton* darkButton = new QRadioButton(tr("Dark Gray")/*,false*/);
//    whiteButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setBackGround(Color.white);
//            }
//        });
    connect(whiteButton, SIGNAL(clicked()), this, SLOT(whiteButton_clicked()));
//    grayButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setBackGround(_grayColor);
//            }
//        });
    connect(grayButton, SIGNAL(clicked()), this, SLOT(grayButton_clicked()));
//    darkButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setBackGround(new Color(150,150,150));
//            }
//        });
    connect(darkButton, SIGNAL(clicked()), this, SLOT(darkButton_clicked()));
    QWidget* pp = new QWidget();
    pp->setLayout(new QHBoxLayout);
    pp->layout()->addWidget(new QLabel(tr("Set Background")));
    previewPanel->layout()->addWidget(pp);
    QWidget* panel = new QWidget();
    panel->setLayout(new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
    QButtonGroup* selGroup = new QButtonGroup();
    selGroup->addButton(whiteButton);
    selGroup->addButton(grayButton);
    selGroup->addButton(darkButton);
    panel->layout()->addWidget(whiteButton);
    panel->layout()->addWidget(grayButton);
    panel->layout()->addWidget(darkButton);
    previewPanel->layout()->addWidget(panel);
    return previewPanel;
}
void PreviewDialog::whiteButton_clicked()
{
    setBackground(QColor(Qt::white));
}
void PreviewDialog::darkButton_clicked()
{
    setBackground(QColor(Qt::darkGray));
}
void PreviewDialog::grayButton_clicked()
{
 setBackground(_grayColor);
}

/*private*/ void PreviewDialog::setBackground(QColor color) {
#if 0
    _preview.setBackground(color);
    _currentBackground = color;
    Component[] comp = _preview.getComponents();
    for (int i=0; i<comp.length; i++){
        QLabel l = NULL;
        if (comp[i].getClass().getName().equals("javax.swing.QWidget")) {
            QWidget* p = (QWidget)comp[i];
            p.setBackground(color);
            l = (QLabel)p.getComponent(0);
        } else if (comp[i].getClass().getName().equals("javax.swing.QLabel")) {
            l = (QLabel)comp[i];
        } else {
            if (log->isDebugEnabled()) log->debug("setBackGround label #"+i+
                                                ", class= "+comp[i].getClass().getName());
            return;
        }
        l.setBackground(color);
    }
    _preview.invalidate();

#endif

    _preview->setStyleSheet(QString("QWidget {background-color : rgb(%1,%2,%3); font-size : 7pt; }").arg(color.red()).arg(color.green()).arg(color.blue()));

}

void PreviewDialog::resetPanel() {
    _selectedImage = NULL;
    if (_preview == NULL) {
        return;
    }
    if (log->isDebugEnabled()) log->debug("resetPanel");
//    Component[] comp = _preview.getComponents();
//    for (int i=comp.length-1; i>=0; i--) {
//        _preview.remove(i);
//        comp[i] = NULL;
//    }
//    QObjectList l =_preview->layout()->children();
//    foreach(QObject* o, l)
//    {
//     _preview->layout()->removeWidget((QWidget*)o);
//     delete o;
//    }
    _preview->clear();
    //_preview->setBackground(_currentBackground);
    //_preview.invalidate();
    pack();
}

/*public*/ int PreviewDialog::getNumFilesShown() {
    return _startNum + _cnt;
}
#if 0
class MemoryExceptionHandler implements Thread.UncaughtExceptionHandler {
    /*public*/ void uncaughtException(Thread t, Throwable e) {
        _noMemory = true;
        log->error("Exception from setIcons: "+e, e);
        if (log->isDebugEnabled()) log->debug("memoryAvailable = "+availableMemory());
    }
}

#endif
/**
*  Displays (thumbnails if image is large) of the current directory.
*  Number of images displayed may be restricted due to memory constraints.
*  Returns true if memory limits displaying all the images
*/
/*private*/ bool PreviewDialog::setIcons(int startNum) /*throws OutOfMemoryError*/ {
    // VM launches another thread to run ImageFetcher.
    // This handler will catch memory exceptions from that thread
    _noMemory = false;
    //Thread.setDefaultUncaughtExceptionHandler(new MemoryExceptionHandler());
    int numCol = 6;
    int numRow = 5;
    long memoryNeeded = 0;
    // allow room for ImageFetcher threads
    long memoryAvailable = availableMemory() - 10000000;
    if (log->isDebugEnabled()) log->debug("setIcons: startNum= "+QString::number(startNum)+" memoryAvailable = "+QString::number(availableMemory()));
    bool newCol = false;
//    QGridLayout* gridbag = new QGridLayout();
//    _preview->setLayout(gridbag);
    GridBagConstraints c;// = GridBagConstraints();
    c.fill = GridBagConstraints::NONE;
    c.anchor = GridBagConstraints::CENTER;
    c.weightx = 1.0;
    c.weighty = 1.0;
    c.gridy = 0;
    c.gridx = -1;
    _cnt = 0;
    int cnt = 0;
    //File[] files = _currentDir.listFiles();
    QStringList filters;
    filters << "*.jpg" << "*.gif" << "*.png" << "*.bmp";
    QFileInfoList files = _currentDir->entryInfoList(filters,QDir::Files);
    for (int i=0; i<files.length(); i++)
    {
//        String ext = jmri.util.FileChooserFilter.getFileExtension(files[i]);
//        for (int k=0; k<_filter.length; k++) {
//            if (ext != NULL && ext.equalsIgnoreCase(_filter[k])) {
                if (cnt < startNum || _noMemory) {
                    cnt++;
                    //continue;
                }
                QString name = files.at(i).baseName();
//                int index = name.indexOf('.');
//                if (index > 0) {
//                    name = name.substring(0, index);
//                }
//                 try {
                    QString path = files.at(i).absoluteFilePath();
                    NamedIcon* icon = new NamedIcon(path, name);
//                    memoryNeeded += 3*icon->getIconWidth()*icon->getIconHeight();
//                    if (memoryAvailable < memoryNeeded) {
//                        _noMemory = true;
//                        continue;
//                    }
                    double scale = icon->reduceTo(CatalogPanel::ICON_WIDTH,
                                                 CatalogPanel::ICON_HEIGHT, CatalogPanel::ICON_SCALE);
                    if (_noMemory) {
                        continue;
                    }
                       if (c.gridx < numCol) {
                        c.gridx++;
                    } else if (c.gridy < numRow) { //start next row
                        c.gridy++;
                        if (!newCol) {
                            c.gridx=0;
                        }
                    } else if (!newCol) { // start new column
                        c.gridx++;
                        numCol++;
                        c.gridy = 0;
                        newCol = true;
                    } else {  // start new row
                        c.gridy++;
                        numRow++;
                        c.gridx = 0;
                        newCol = false;
                    }
                    c.insets = new Insets(5, 5, 0, 0);
                    DragJLabel* image;
                    //modeless is for ImageEditor dragging
                    try {
                        image = new DragJLabel(new DataFlavor(ImageIndexEditor::IconDataFlavorMime));
                    } catch (ClassNotFoundException cnfe) {
                        //cnfe.printStackTrace();
                        image = new DragJLabel(NULL);
                    }
//                    image->setOpaque(true);
                    image->setName(name);
//                    image->setBackground(_currentBackground);
                    image->setIcon(icon);
                    QGroupBox* p = new QGroupBox();
                    p->setLayout(new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
                    ((QBoxLayout*)p->layout())->addWidget(image,0,Qt::AlignHCenter);
                    if (name.length()>18) {
                        name = name.mid(0, 18);
                    }
                    QLabel* nameLabel = new QLabel(name);
                    QLabel* label = new QLabel(tr("scale %1:1").arg(CatalogPanel::printDbl(scale,2)));
                    p->layout()->addWidget(label);
                    p->layout()->addWidget(nameLabel);
                    p->setMinimumSize(CatalogPanel::ICON_WIDTH, CatalogPanel::ICON_HEIGHT+20);
//                    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
//                    sizePolicy.setHorizontalStretch(0);
//                    sizePolicy.setVerticalStretch(0);
//                    sizePolicy.setHeightForWidth(p->sizePolicy().hasHeightForWidth());
//                    p->setSizePolicy(sizePolicy);
//                    gridbag->addWidget(p, c.gridy, c. gridx, 2,1);
//                    gridbag->setRowMinimumHeight(c.gridy,CatalogPanel::ICON_HEIGHT+100);
                    _preview->setRowCount(c.gridy + 1);
                    _preview->setRowHeight(c.gridy,CatalogPanel::ICON_HEIGHT+20);
                    _preview->setCellWidget(c.gridy, c.gridx,p);
                    if (_noMemory) {
                        continue;
                    }
                    if (log->isDebugEnabled()) log->debug(name+" inserted at ("+QString::number(c.gridx)+", "+QString::number(c.gridy)+")");
                    //_preview->layout()->addWidget(p);
                    _cnt++;
                    cnt++;
                    if (_cnt > 300) { // somewhere above this number, VM can't build display of panel
                        _noMemory = true;
                    }
//                } catch (OutOfMemoryError oome) {
//                    JOptionPane.showMessageDialog(this,
//                            java.text.MessageFormat.format(tr("OutOfMemory"),
//                            new Object[] {Integer.valueOf(_cnt)}),
//                            tr("error"), JOptionPane.INFORMATION_MESSAGE);
//                    _noMemory = true;
//                }
//            }
//        }
    }
    c.gridy++;
    c.gridx++;
    QLabel* bottom = new QLabel();
    //gridbag.setConstraints(bottom, c);
    //_preview->layout()->addWidget(bottom);
    //gridbag->addWidget(bottom, c.gridy, c.gridx, 1,1);
    _preview->setRowCount(c.gridy + 1);
    _preview->setCellWidget(c.gridy, c.gridx,bottom);
    QString msg = tr("Directory \"%1\" has %2 image files.").arg(_currentDir->dirName()).arg(cnt);
    if (startNum>0) {
        msg = msg +" "+ tr("(%1 previously displayed)").arg( startNum);
    }
    _previewLabel->setText(msg);
    _preview->setMinimumSize( QSize(CatalogPanel::ICON_WIDTH, 2*CatalogPanel::ICON_HEIGHT));
    //js->setWidget(_preview);
//    CatalogPanel::packParentFrame(this);

    if (_noMemory) {
//        JOptionPane.showMessageDialog(this,
//                java.text.MessageFormat.format(tr("OutOfMemory"),
//                new Object[] {Integer.valueOf(_cnt)}),
//                tr("error"), JOptionPane.INFORMATION_MESSAGE);
        QMessageBox::critical(this, tr("Error"), tr("Not enough Memory!  Only %1 images can be displayed.").arg(cnt));
    }
//    Thread.setDefaultUncaughtExceptionHandler(new jmri.util.exceptionhandler.UncaughtExceptionHandler());
    return _noMemory;
}


/*private*/ long PreviewDialog::availableMemory() {
    long total = CHUNK;
//    //ArrayList <byte[]> memoryTest = new ArrayList <byte[]>();
//    QList<QByteArray*>* memoryTest = new QList<QByteArray*>();
////    try {
//        while (true) {
//            QByteArray* ba = new QByteArray(CHUNK,0);
//            if(ba == NULL)
//            {
//             for (int i=0; i<memoryTest->size(); i++)
//             {
//                memoryTest->removeAt(i);
//             }
//            memoryTest = NULL;
//            break;

//            }
//            memoryTest->append(new QByteArray(CHUNK,0));
//            total += CHUNK;
//        }
//    } catch (OutOfMemoryError me) {
//        for (int i=0; i<memoryTest.size(); i++){
//            memoryTest.remove(i);
//        }
//        memoryTest = NULL;
        //if (log.isDebugEnabled()) log.debug("Max Memory available= "+total+" bytes");
//    }
    return total;
}

/*public*/ void PreviewDialog::dispose() {
    if (_preview != NULL) resetPanel();
//    this.removeAll();
    _preview = NULL;
    //super.dispose();
    close();
    log->debug("PreviewDialog disposed.");
}

