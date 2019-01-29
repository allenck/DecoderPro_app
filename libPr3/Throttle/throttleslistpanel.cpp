#include "throttleslistpanel.h"
#include "throttlestablemodel.h"
#include "jtable.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QToolBar>
#include "largepowermanagerbutton.h"
#include "throttlespreferencesaction.h"
#include "throttleframemanager.h"
#include "throttlewindow.h"
#include <QHeaderView>
#include "listselectionmodel.h"
#include "windowpreferences.h"

//ThrottlesListPanel::ThrottlesListPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
// /*public*/ class ThrottlesListPanel extends JPanel {


/*public*/ ThrottlesListPanel::ThrottlesListPanel(QWidget *parent)
 : QWidget(parent)
{
 //super();

 throttleFramesLM = new ThrottlesTableModel();
 initGUI();
}

/*public*/ ThrottlesTableModel* ThrottlesListPanel::getTableModel() {
    return throttleFramesLM;
}

/*private*/ void ThrottlesListPanel::initGUI()
{
 throttleFrames = new JTable(throttleFramesLM);
 //throttleFrames->setSelectionMode(ListSelectionModel::SINGLE_SELECTION );
 throttleFrames->setSelectionMode(QAbstractItemView::SingleSelection);
//        throttleFrames.setRowHeight(ThrottlesTableCellRenderer.height);
//        throttleFrames.setTableHeader(null);
 throttleFrames->horizontalHeader()->setVisible(false);
 throttleFrames->horizontalHeader()->stretchLastSection();
//        throttleFrames.setDefaultRenderer(Object.class, new ThrottlesTableCellRenderer());
//        throttleFrames.addMouseListener( new MouseListener() {
//        /*public*/ void mouseClicked(MouseEvent e) {
//                    int row=throttleFrames.rowAtPoint(e.getPoint());
//                    throttleFrames.getSelectionModel().setSelectionInterval(row, row);
//            ((ThrottleFrame)throttleFramesLM.getValueAt(row, 0)).toFront();
//        }
 connect(throttleFrames, SIGNAL(clicked(QModelIndex)), this, SLOT(On_throttleFramesClicked(QModelIndex)));
//        /*public*/ void mouseEntered(MouseEvent arg0) {}
//        /*public*/ void mouseExited(MouseEvent arg0) {}
//        /*public*/ void mousePressed(MouseEvent arg0) {}
//        /*public*/ void mouseReleased(MouseEvent arg0) {}
//    });

 //JScrollPane scrollPane1 = new JScrollPane(throttleFrames);
 //setLayout(new BorderLayout());
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
 //setLayout(thisLayout);

 resize(QSize(320,200));

 QToolBar* throttleToolBar = new QToolBar("Throttles list toolbar");
 QPushButton* jbNew = new QPushButton();
 jbNew->setIcon(QIcon(":/resources/icons/throttles/new.png"));
 jbNew->setToolTip(tr("New throttles window"));
//    jbNew.setVerticalTextPosition(JButton.BOTTOM);
//    jbNew.setHorizontalTextPosition(JButton.CENTER);
//    jbNew.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            ThrottleFrame tf = ThrottleFrameManager.instance().createThrottleFrame();
//            tf.toFront();
//        }
//    });
 connect(jbNew, SIGNAL(clicked(bool)), this, SLOT(On_jbNewClicked()));
 throttleToolBar->addWidget(jbNew);

 throttleToolBar->addSeparator();
//    throttleToolBar.add(new StopAllButton());
 LargePowerManagerButton* pwr;
 throttleToolBar->addWidget(pwr =new LargePowerManagerButton());
 pwr->init();

 thisLayout->addWidget( throttleToolBar/*, BorderLayout.PAGE_START*/);
 //add( scrollPane1, BorderLayout.CENTER);
 thisLayout->addWidget(throttleFrames);

 throttleToolBar->addSeparator();
 QPushButton* jbPreferences = new QPushButton();
 jbPreferences->setIcon(QIcon(":/resources/icons/throttles/preferences.png"));
 jbPreferences->setToolTip(tr("Throttles preferences"));
//    jbPreferences.setVerticalTextPosition(JButton.BOTTOM);
//    jbPreferences.setHorizontalTextPosition(JButton.CENTER);
//    jbPreferences.addActionListener( new ThrottlesPreferencesAction() );
 connect(jbPreferences, SIGNAL(clicked(bool)), this, SLOT(On_preferencesClicked()));
 throttleToolBar->addWidget(jbPreferences);
}

/*public*/ QDomElement ThrottlesListPanel::getXml() {
        QDomElement me  = doc.createElement("ThrottlesListPanel");
        QList<QDomElement> children = QList<QDomElement>();
//        children.append(WindowPreferences.getPreferences(this.getTopLevelAncestor()));
        me.appendChild(WindowPreferences::getPreferences(this->window()));
//        me.setContent(children);
        return me;
}

/*public*/ void ThrottlesListPanel::setXml(QDomElement tlp) {
        QDomElement window = tlp.firstChildElement("window");
        if (!window.isNull())
                WindowPreferences::setPreferences(this->window(), window);
}

void ThrottlesListPanel::On_jbNewClicked()
{
 ThrottleWindow* tf = ThrottleFrameManager::instance()->createThrottleFrame();
 tf->toFront();

}

void ThrottlesListPanel::On_preferencesClicked()
{
 ThrottlesPreferencesAction * action = new ThrottlesPreferencesAction();
 action->actionPerformed(0);
}

void ThrottlesListPanel::On_throttleFramesClicked(QModelIndex index)
{
 int row = index.row();
 //throttleFrames->getSelectionModel()->setSelectionInterval(row, row);
 QVariant data =  index.model()->data(index,  Qt::DisplayRole);
 ThrottleWindow* window = VPtr<ThrottleWindow>::asPtr(data);
 window->toFront();
}


