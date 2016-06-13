#include "jtitledseparator.h"
#include <QBoxLayout>
#include "jseparator.h"
#include <QLabel>

//JTitledSeparator::JTitledSeparator(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * A separator with a title.
 *
 * @author Randall Wood
 */
///*public*/ class JTitledSeparator extends JPanel {

/**
 *
 */
//private static final long serialVersionUID = 4197641321226803099L;

#if 0
private final static class SeparatorPane extends JPanel {

    /**
     *
     */
    private static final long serialVersionUID = 17667095414633319L;

    private SeparatorPane() {
        super(new GridBagLayout());
        setOpaque(false);
        setDoubleBuffered(false);
        add(new JSeparator(), new GridBagConstraints(0, 0, 1, 1, 1, 0, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
    }

    @Override
    /*public*/ void setBounds(int x, int y, int w, int h) {
        super.setBounds(x, y, w, h);
        doLayout();
    }
};
#endif

/**
 * Construct a separator with a title.
 *
 * @param title the title to set.
 */
/*public*/ JTitledSeparator::JTitledSeparator(QString title, QWidget* parent)
{
 //super(new BorderLayout());
 layout = new QHBoxLayout;
 setLayout(layout);
 label = new QLabel();
// JPanel westPanel = new JPanel(new BorderLayout())
// {

//    /**
//     *
//     */
//    private static final long serialVersionUID = 2501748738360927763L;

//    @Override
//    /*public*/ void setBounds(int x, int y, int w, int h) {
//        super.setBounds(x, y, w, h);
//        doLayout();
//  }
// };
 WestPanel* westPanel = new WestPanel(this);
 //westPanel.setOpaque(false);
 //westPanel.setDoubleBuffered(false);
 bool isLeftToRight =  true; //getComponentOrientation().isLeftToRight();
 //setOpaque(false);
 westPanel->layout->addWidget(label, 0, Qt::AlignHCenter);
 if (isLeftToRight)
 {
  layout->addWidget(westPanel, 0, Qt::AlignLeft);
 }
 else
 {
  layout->addWidget(westPanel, 0,Qt::AlignRight);
 }
 SeparatorPane* separatorPane = new SeparatorPane(this);
 if (isLeftToRight)
 {
//  separatorPane.setBorder(BorderFactory.createEmptyBorder(0, 2, 0, 0));
 }
 else
 {
//  separatorPane.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 2));
 }
 layout->addWidget(separatorPane, 0, Qt::AlignHCenter);
 setTitle(title);
 this->setMaximumSize(QSize(/*Integer.MAX_VALUE*/4096, this->sizeHint().height()));
 adjustLook();
}
JTitledSeparator::WestPanel::WestPanel(JTitledSeparator* parent)
    : QWidget(parent)
{
 layout = new QHBoxLayout;
 this->setLayout(layout);
}
void JTitledSeparator::WestPanel::setBounds(int x, int y, int w, int h)
{
 parent->setGeometry(x, y, w, h);
// parent->doLayout();
}
JTitledSeparator::SeparatorPane::SeparatorPane(JTitledSeparator* parent) : QWidget(parent)
{
 layout = new QHBoxLayout;
 this->setLayout(layout);

 //add(new JSeparator(), new GridBagConstraints(0, 0, 1, 1, 1, 0, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
 layout->addWidget(new JSeparator());
}
void JTitledSeparator::SeparatorPane::setBounds(int x, int y, int w, int h)
{
 parent->setGeometry(x, y, w, h);
}

/**
 * Get the title of this separator.
 *
 * @return the title.
 */
/*public*/ QString JTitledSeparator::getTitle() {
    return label->text();
}

/**
 * Set the title of the separator.
 *
 * @param title the new title.
 */
/*public*/ void JTitledSeparator::setTitle(QString title)
{
 if (title == NULL)
 {
  title = "";
 }
 bool isVisible = title.length() != 0;
 label->setVisible(isVisible);
 label->setText(title);
}

//@Override
/*public*/ void JTitledSeparator::updateUI() {
    //super.updateUI();
    adjustLook();
}

/*private*/ void JTitledSeparator::adjustLook()
{
 if (label != NULL)
 {
#if 0
  QColor titleColor = UIManager.getColor("TitledBorder.titleColor");
  QFont font = UIManager.getFont("TitledBorder.font");
        if (titleColor == QColor() || font == null)
  {
            TitledBorder titledBorder = new TitledBorder("");
            titleColor = titledBorder.getTitleColor();
            font = titledBorder.getTitleFont();
  }
  label.setForeground(titleColor);
  label.setFont(font);
#endif
 }
}
