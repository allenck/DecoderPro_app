#include "splitbuttoncolorchooserpanel.h"
#include "bufferedimage.h"
#include <QPainter>
#include "imageicon.h"
#include <QBoxLayout>
#include "jsplitbutton.h"
#include "colorlistpopupmenu.h"
#include <QPixmap>
#include "jcolorchooser.h"
#include "colorselectionmodel.h"
#include "defaultcolorselectionmodel.h"

SplitButtonColorChooserPanel::SplitButtonColorChooserPanel(QWidget *parent)
 : AbstractColorChooserPanel(parent)
{
 setLayout(new QVBoxLayout());
}
/**
 * Abstract Color Chooser extension that presents a split button
 * to set the color. Clicking the button results in a
 * JColorChooser launching.
 *
 * @author Paul Bender Copyright (C) 2018
 * @since 4.1.1
 */
// /*public*/ class SplitButtonColorChooserPanel extends AbstractColorChooserPanel {

/*private*/ /*static*/ /*final*/ int SplitButtonColorChooserPanel::ICON_DIMENSION = 20;

//@Override
/*public*/ void SplitButtonColorChooserPanel::updateChooser(){
    QColor color = getColorFromModel();
    // update the Swatch to have the right color showing.
    BufferedImage image = BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
            /*BufferedImage::TYPE_INT_RGB*/QImage::Format_ARGB32_Premultiplied);

    //Graphics g = image.getGraphics();
    QPainter g(&image);
    // fill it with its representative color
    //g.setColor(color);
    g.fillRect(0, 0, ICON_DIMENSION, ICON_DIMENSION, color);
    // draw a black border around it
    //g.setColor(Color.black);
    g.setPen(QColor(Qt::black));
    g.drawRect(0, 0, ICON_DIMENSION - 1, ICON_DIMENSION - 1);
    g.end();
    //setButton.setImage(image);
    //ImageIcon* icon = new ImageIcon(image);
    setButton->setIcon(QIcon(QPixmap::fromImage(image)));
    setButton->setPopupMenu(new ColorListPopupMenu(getColorSelectionModel()));
    connect((DefaultColorSelectionModel*)getColorSelectionModel(), SIGNAL(stateChanged(ChangeEvent*)), this, SLOT(stateChanged(ChangeEvent*)));
    //g.dispose();
}

void SplitButtonColorChooserPanel::stateChanged(ChangeEvent *)
{
 updateChooser();
}

//@Override
/*protected*/ void SplitButtonColorChooserPanel::buildChooser(){
    BufferedImage image =  BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
            /*BufferedImage::TYPE_INT_RGB*/QImage::Format_ARGB32_Premultiplied);

    //Graphics g = image.getGraphics();
    QPainter g(&image);
    // set completely transparent
    //g.setColor(getColorFromModel());
    g.fillRect(0, 0, ICON_DIMENSION, ICON_DIMENSION, getColorFromModel());

    //ImageIcon* icon = new ImageIcon(image);
    //g.dispose();
    g.end();

    setButton = new JSplitButton(tr("SetColor") + "      ",QIcon(QPixmap::fromImage(image)));  // NOI18N
//    setButton.addButtonClickedActionListener((ActionEvent e) -> {
//        Color desiredColor = JColorChooser.showDialog(setButton.getParent(),
//                Bundle.getMessage("SetColor"), // NOI18N
//                getColorFromModel());
//        if (desiredColor != null) {
//            getColorSelectionModel().setSelectedColor(desiredColor);
//        }
//    });
    setButton->addButtonActionListener((ActionListener*)this);

//    setButton->addSplitButtonClickedActionListener((ActionEvent e) -> {
        //Color desiredColor = JColorChooser.showDialog(this,
        //                     Bundle.getMessage("SetColor"),
        //                     getColorFromModel());
        //if (desiredColor!=null) {
        //    getColorSelectionModel().setSelectedColor(desiredColor);
//    });

    //setButton.setImage(image);
    setButton->setPopupMenu(new ColorListPopupMenu(getColorSelectionModel()));
    this->layout()->addWidget(setButton);
}

void SplitButtonColorChooserPanel::buttonClicked(JActionEvent*)
{
// QColor desiredColor = JColorChooser::showDialog((Component*)setButton->parent(),
//        tr("SetColor"), // NOI18N
//        getColorFromModel());
// if (!desiredColor.isValid())
// {
//     getColorSelectionModel()->setSelectedColor(desiredColor);
// }
}

void SplitButtonColorChooserPanel::splitButtonClicked(JActionEvent* e)
{
 buttonClicked(e);
}


//@Override
/*public*/ QString SplitButtonColorChooserPanel::getDisplayName() {
     return tr("SplitButtonColorChooserName");  // NOI18N
}

//@Override
/*public*/ QIcon getSmallDisplayIcon(){
   return QIcon();
}

//@Override
/*public*/ QIcon getLargeDisplayIcon(){
   return QIcon();
}
