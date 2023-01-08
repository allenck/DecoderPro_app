#include "jtitledseparator.h"
#include "borderlayout.h"
#include "borderfactory.h"
#include "limits.h"
#include <QBoxLayout>

/**
 * A separator with a title.
 *
 * JTitledSeparator based on
 * https://github.com/rhwood/DJ-Swing-Suite/blob/master/DJSwingSuite/src/chrriis/dj/swingsuite/JTitledSeparator.java
 * by
 * Christopher Deckers (chrriis@nextencia.net)
 * http://www.nextencia.net
 *
 * @author Randall Wood
 */
///*public*/  class JTitledSeparator extends JPanel {


    /**
     * Construct a separator with a title.
     *
     * @param title the title to set.
     */
#if 0
    /*public*/  JTitledSeparator::JTitledSeparator(QString title, QWidget* parent)
    : JPanel(new BorderLayout(), nullptr) {
        //super(new BorderLayout());
        JPanel* westPanel = new JPanel(new BorderLayout(), nullptr);
//        {

//            //@Override
//            /*public*/  void setBounds(int x, int y, int w, int h) {
//                super.setBounds(x, y, w, h);
//                doLayout();
//            }
//        };
        westPanel->setOpaque(false);
//        westPanel->setDoubleBuffered(false);
//        bool isLeftToRight = getComponentOrientation().isLeftToRight();
        setOpaque(false);
        ((BorderLayout*)westPanel->layout())->addWidget(label, BorderLayout::Center);
//        if (isLeftToRight) {
            ((BorderLayout*)layout())->addWidget(westPanel, BorderLayout::West);
//        } else {
//            ((BorderLayout*)layout())->addWidget(westPanel, BorderLayout::East);
//        }
        SeparatorPane* separatorPane = new SeparatorPane();
//        if (isLeftToRight) {
            separatorPane->setBorder(BorderFactory::createEmptyBorder(0, 2, 0, 0));
//        } else {
//            separatorPane.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 2));
//        }
        ((BorderLayout*)layout())->addWidget(separatorPane, BorderLayout::Center);
        setTitle(title);
        this->setMaximumSize(QSize(INT_MAX, this->sizeHint().height()));
        adjustLook();
    }
#else
/*public*/  JTitledSeparator::JTitledSeparator::JTitledSeparator(QString title, QWidget* parent)
 :JPanel(new QHBoxLayout)
{
 QHBoxLayout* thisLayout = (QHBoxLayout*)layout();
 thisLayout->addWidget(new QLabel("<B>"+title+"</B>"),0, Qt::AlignLeft);
 thisLayout->addWidget(label, 1, Qt::AlignCenter);
}

#endif
    /**
     * Get the title of this separator.
     *
     * @return the title.
     */
    /*public*/  QString JTitledSeparator::getTitle() {
        return label->text();
    }

    /**
     * Set the title of the separator.
     *
     * @param title the new title.
     */
    /*public*/  void JTitledSeparator::setTitle(QString title) {
        if (title == "") {
            title = "";
        }
        bool isVisible = title.length() != 0;
        label->setVisible(isVisible);
        label->setText(title);
    }

    //@Override
//    /*public*/  void updateUI() {
//        super.updateUI();
//        adjustLook();
//    }

    /*private*/ void JTitledSeparator::adjustLook() {
        if (label != nullptr) {
#if 0
            QColor titleColor = UIManager.getColor("TitledBorder.titleColor");
            Font font = UIManager.getFont("TitledBorder.font");
            if (titleColor == null || font == null) {
                TitledBorder titledBorder = new TitledBorder("");
                titleColor = titledBorder.getTitleColor();
                font = titledBorder.getTitleFont();
            }
            label.setForeground(titleColor);
            label.setFont(font);
#endif
        }
    }
