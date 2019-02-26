#include "mergeprompt.h"
#include "loggerfactory.h"
#include "warrantmanager.h"
#include "instancemanager.h"
#include "rosterspeedprofile.h"
#include <QBoxLayout>
#include "box.h"
#include <QLabel>
#include "rosterentry.h"
#include "roster.h"
#include "speedprofilepanel.h"
#include "jtextfield.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "pushbuttondelegate.h"

/**
 * Prompts user to select SpeedProfile to write to Roster
 *
 * @author Pete Cressman Copyright (C) 2017
 */
///*public*/ class MergePrompt extends JDialog {

/*static*/ int MergePrompt::STRUT = 20;


MergePrompt::MergePrompt(QString name, QMap<QString, bool>* cand, QMap<QString, QMap<int, bool>*>* anomalies, QWidget* parent)
 : JDialog(parent){
    //super();
    _candidates = cand;
    _anomalyMap = anomalies;
    WarrantManager* manager = static_cast<WarrantManager*>(InstanceManager::getDefault("WarrantManager"));
    _mergeProfiles = manager->getMergeProfiles();
    _sessionProfiles = manager->getSessionProfiles();
    setTitle(name);
    //setModalityType(java.awt.Dialog.ModalityType.APPLICATION_MODAL);
#if 0
    addWindowListener(new java.awt.event.WindowAdapter() {
        @Override
        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
            noMerge();
            dispose();
        }
    });
#endif
    addWindowListener(new MPWindowAdapter(this));
    MergeTableModel* model = new MergeTableModel(cand, this);
    JTable* table = new JTable(model);

    //table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
//    table->getColumnModel()->getColumn(MergeTableModel::VIEW_COL).setCellEditor(new ButtonEditor(new JButton()));

//        table.getColumnModel().getColumn(MergeTableModel.VIEW_COL).setCellRenderer(new ButtonRenderer());
    //table.getColumnModel().getColumn(MergeTableModel.VIEW_COL).setCellRenderer(new ButtonCellRenderer());
    table->setItemDelegateForColumn(MergeTableModel::VIEW_COL,new PushButtonDelegate());

    int tablewidth = 0;
    for (int i = 0; i < model->getColumnCount(); i++) {
        int width = model->getPreferredWidth(i);
        table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
        tablewidth += width;
    }
    //int rowHeight = new JButton("VIEW").getPreferredSize().height;
    //table.setRowHeight(rowHeight);
//        java.awt.Font font = table.getFont();
    QWidget* description = new QWidget();
    QHBoxLayout* descriptionLayout = new QHBoxLayout(description);
    QLabel* label = new QLabel(tr("Select the Speed Profiles to merge into the Roster. Then press a Merge button to exit."));
//        description.setFont(font);
    //label.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
    descriptionLayout->addWidget(label, 0, Qt::AlignCenter);

    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    QPushButton* button = new QPushButton(tr("Merge None"));
//    button.addActionListener((ActionEvent evt) -> {
//        noMerge();
//        dispose();
//    });
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onNoMergeButton()));
    panelLayout->addWidget(button);
    panelLayout->addWidget(Box::createHorizontalStrut(STRUT));
    button = new QPushButton(tr("Merge"));
//    button.addActionListener((ActionEvent evt) -> {
//        dispose();
//    });
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onMergeButton()));

    panelLayout->addWidget(button);
    panelLayout->addWidget(Box::createHorizontalStrut(STRUT));
    button = new QPushButton(tr("Close View"));
//    button.addActionListener((ActionEvent evt) -> {
//        if (_viewFrame != null) {
//            getContentPane().remove(_viewFrame);
//        }
//        pack();
//    });
    connect(button, SIGNAL(clicked(bool)), SLOT(onCloseView()));
    panelLayout->addWidget(button);

//        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    //JScrollPane pane = new JScrollPane(table);
    table->resize(QSize(tablewidth, tablewidth));

    QWidget* mainPanel = new QWidget();
    //mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* mainPanelLayout = new QVBoxLayout(mainPanel);
    mainPanelLayout->addWidget(description);
    mainPanelLayout->addWidget(table);
    if (_anomalyMap != nullptr && _anomalyMap->size() > 0) {
        QWidget* p = new QWidget();
        //p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
        QVBoxLayout* pLayout = new QVBoxLayout(p);
        QLabel* l = new QLabel(tr("View the red speed profiles to correct speed anomalies"));
        l->setStyleSheet("QLabel: color:red;}");
        //l.setAlignmentX(JComponent.CENTER_ALIGNMENT);
        pLayout->addWidget(l,0, Qt::AlignCenter);
        mainPanelLayout->addWidget(p);
    }
    mainPanelLayout->addWidget(panel);

    QWidget* p = new JPanel();
    //p.setLayout(new BoxLayout(p, BoxLayout.LINE_AXIS));
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    pLayout->addWidget(Box::createHorizontalStrut(STRUT));
    p->layout()->addWidget(Box::createHorizontalGlue());
    pLayout->addWidget(mainPanel);
    pLayout->addWidget(Box::createHorizontalGlue());
    pLayout->addWidget(Box::createHorizontalStrut(STRUT));

    QWidget* contentPane = getContentPane();
    //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));
    QHBoxLayout* contentPaneLayout = (QHBoxLayout*)contentPane->layout();
    contentPaneLayout->addWidget(p);
    //setContentPane(contentPane);
    pack();
//    QSize screen = getToolkit().getScreenSize();
//    setLocation(screen.width / 3, screen.height / 4);
//    setAlwaysOnTop(true);
    setVisible(true);
}

void MergePrompt::onNoMergeButton()
{
 noMerge();
 dispose();
}

void MergePrompt::onMergeButton()
{
 dispose();
}

void MergePrompt::onCloseView()
{
 if (_viewFrame != nullptr) {
     getContentPane()->layout()->removeWidget(_viewFrame);
 }
 pack();

}
/*private*/ void MergePrompt::noMerge() {
    //for (Map.Entry<String, Boolean> ent : _candidates.entrySet())
 QMapIterator<QString, bool> iter(*_candidates);
 while(iter.hasNext())
 {
     _candidates->insert(iter.key(), (false));
 }
}

void MergePrompt::showProfiles(QString id) {
    if (_viewFrame != nullptr) {
        getContentPane()->layout()->removeWidget(_viewFrame);
    }
    _viewFrame = new QWidget();
    //_viewFrame.setLayout(new BoxLayout(_viewFrame, BoxLayout.PAGE_AXIS));
    QVBoxLayout* _viewFrameLayout = new QVBoxLayout(_viewFrame);
    _viewFrameLayout->addWidget(Box::createGlue());
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("SpeedProfiles for %1").arg(id)));
    _viewFrameLayout->addWidget(panel);

    QMap<int, bool>* anomalies = _anomalyMap->value(id);
    if (anomalies != nullptr && anomalies->size() > 0) {
        panel = new QWidget();
        //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
        QVBoxLayout* panelLayout = new QVBoxLayout(panel);

        QLabel* label = new QLabel(tr("Edit cells so that non-zero speeds are monotonically increasing for the Merge SpeedProfile"));
        label->setStyleSheet("QLabel{color:red};");
//        label.setAlignmentX(JComponent.CENTER_ALIGNMENT);
        panelLayout->addWidget(label,0,Qt::AlignCenter);
        label = new QLabel(tr("Enter 0 and the value for throttle setting direction will be interpolated from adjacent values"));
        //label.setAlignmentX(JComponent.CENTER_ALIGNMENT);
        panelLayout->addWidget(label,0,Qt::AlignCenter);
        label = new QLabel(tr("Delete Key will delete a selected speed step from the Merge SpeedProfile"));
//        label.setAlignmentX(JComponent.CENTER_ALIGNMENT);
        panelLayout->addWidget(label,0,Qt::AlignCenter);
        _viewFrameLayout->addWidget(panel);

    }
    QWidget* spPanel = new QWidget();
    //spPanel.setLayout(new BoxLayout(spPanel, BoxLayout.LINE_AXIS));
    QHBoxLayout* spPanelLayout = new QHBoxLayout(spPanel);
    spPanelLayout->addWidget(Box::createGlue());

    panel = new QWidget();
    {
    //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("Roster SpeedProfile")));
    RosterEntry* re = Roster::getDefault()->entryFromTitle(id);
    RosterSpeedProfile* speedProfile = nullptr;
    if (re != nullptr) {
        speedProfile = re->getSpeedProfile();
    }
    if (speedProfile == nullptr) {
        speedProfile = new RosterSpeedProfile(nullptr);
    }
    SpeedProfilePanel* speedPanel = new SpeedProfilePanel(speedProfile, nullptr);
    panelLayout->addWidget(speedPanel);
    spPanelLayout->addWidget(panel);
    spPanelLayout->addWidget(Box::createGlue());
    }

    SpeedProfilePanel* speedPanel;
    panel = new JPanel();
    {
    //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("Merged SpeedProfile")));
    speedPanel = new SpeedProfilePanel(_mergeProfiles->value(id), anomalies);
//    speedPanel->setEditable(true);
    panelLayout->addWidget(speedPanel);
    spPanelLayout->addWidget(panel);
    spPanelLayout->addWidget(Box::createGlue());
    }

    panel = new JPanel();
    {
    //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("Session SpeedProfile")));
    speedPanel = new SpeedProfilePanel(_sessionProfiles->value(id), nullptr);
    panelLayout->addWidget(speedPanel);
    spPanelLayout->addWidget(panel);
    spPanelLayout->addWidget(Box::createGlue());
    }
    _viewFrameLayout->addWidget(spPanel);
    getContentPane()->layout()->addWidget(_viewFrame);
    pack();
}

/**
 * Check that non zero value are ascending for both forward and reverse
 * speeds. Omit anomalies.
 *
 * @param speedProfile speedProfile
 * @param id           roster id
 * @return HashMap of Key and direction of possible errors
 */
/*static*/ /*public*/ QMap<int, bool>* MergePrompt::validateSpeedProfile(RosterSpeedProfile* speedProfile, QString id) {
    // do forward speeds, then reverse
    QMap<int, bool>* anomalies = new QMap<int, bool>();
    QMap<int, SpeedStep*> rosterTree = speedProfile->getProfileSpeeds();
    float lastForward = 0;
    int lastKey = (0);
    //Iterator<Map.Entry<Integer, SpeedStep>> iter = rosterTree.entrySet().iterator();
#if 1
    QMapIterator<int, SpeedStep*> iter(rosterTree);
    while (iter.hasNext()) {
        /*Map.Entry<Integer, SpeedStep> entry =*/ iter.next();
        float forward = iter.value()->getForwardSpeed();
        int key = iter.key();
        if (forward > 0.0f) {
            if (forward < lastForward) {  // anomaly - remove bad entry
                while (iter.hasNext()) {
                    /*Map.Entry<Integer, SpeedStep> nextEntry =*/ iter.next();
                    float nextForward = iter.value()->getForwardSpeed();
                    if (nextForward > 0.0f) {
                        if (nextForward > lastForward) {    // remove forward
                            log->warn(tr("SpeedProfile anomaly at key=%1, forward=%2 for %3").arg(key).arg(forward).arg(id));
                            anomalies->insert(key, true);
                            //speedProfile.setForwardSpeed(key, 0.0f);
                            forward = nextForward;
                            key = iter.key();
                        } else {    // remove lastForward
                            log->warn(tr("SpeedProfile anomaly at key=%1, forward=%2 for %3").arg(lastKey).arg(lastForward).arg(id));
                            anomalies->insert(lastKey, true);
                            //speedProfile.setForwardSpeed(lastKey, 0.0f);
                        }
                        break;
                    }
                }
            }
            lastForward = forward;
            lastKey = key;
        }
    }

    rosterTree = speedProfile->getProfileSpeeds();
    float lastReverse = 0;
    lastKey = (0);
    //iter = rosterTree.entrySet().iterator();
    QMapIterator<int, SpeedStep*> iter1(rosterTree);
    while (iter1.hasNext()) {
        /*Map.Entry<Integer, SpeedStep> entry = */iter.next();
        float reverse = iter1.value()->getReverseSpeed();
        int key = iter1.key();
        if (reverse > 0.0f) {
            if (reverse < lastReverse) {  // anomaly - remove bad entry
                while (iter1.hasNext()) {
                    /*Map.Entry<Integer, SpeedStep> nextEntry =*/ iter1.next();
                    float nextreverse = iter1.value()->getReverseSpeed();
                    if (nextreverse > 0.0f) {
                        if (nextreverse > lastReverse) {    // remove reverse
                            log->warn(tr("SpeedProfile anomaly at key=%1, reverse=%2 for %3").arg(key).arg(reverse).arg(id));
                            anomalies->insert(key, false);
                            //speedProfile.setReverseSpeed(key, 0.0f);
                            reverse = nextreverse;
                            key = iter1.key();
                        } else {    // remove lastReverse
                            log->warn(tr("SpeedProfile anomaly at key=%1, reverse=%2 for %3").arg(lastKey).arg(lastReverse).arg(id));
                            anomalies->insert(lastKey, false);
                            //speedProfile.setReverseSpeed(lastKey, 0.0f);
                        }
                        break;
                    }
                }
            }
            lastReverse = reverse;
            lastKey = key;
        }
    }
#endif
    return anomalies;
}

//class MergeTableModel extends javax.swing.table.AbstractTableModel {

//    static final int MERGE_COL = 0;
//    static final int ID_COL = 1;
//    static final int VIEW_COL = 2;
//    static final int NUMCOLS = 3;

//    ArrayList<Map.Entry<String, Boolean>> candidateArray = new ArrayList<>();

    MergeTableModel::MergeTableModel(QMap<QString, bool>* map, MergePrompt* mp)
    {
     this->mp = mp;
     candidateArray = QList<QMapIterator<QString, bool> >();
        QMapIterator<QString, bool> iter(*map);
        while (iter.hasNext()) {
         iter.next();
            candidateArray.append(iter);
        }
    }

    bool MergeTableModel::hasAnomaly(int row) {
        QMapIterator<QString, bool> entry = candidateArray.at(row);
        QMap<int, bool>* anomaly = mp->_anomalyMap->value(entry.key());
        if (anomaly != nullptr && anomaly->size() > 0) {
            return true;
        }
        return false;
    }

    //@Override
    /*public*/ int MergeTableModel::columnCount(const QModelIndex &parent) const
    {
        return NUMCOLS;
    }

    //@Override
    /*public*/ int MergeTableModel::rowCount(const QModelIndex &parent) const
    {
        return candidateArray.size();
    }

    //@Override
    /*public*/ QVariant MergeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
        switch (section) {
            case MERGE_COL:
                return tr("Merge");
            case ID_COL:
                return tr("Train Id");
            case VIEW_COL:
                return tr("Speed Profiles");
            default:
                // fall out
                break;
        }
     }
        return QVariant();
    }

    //@Override
//    /*public*/ Class<?> getColumnClass(int col) {
//        switch (col) {
//            case MERGE_COL:
//                return Boolean.class;
//            case ID_COL:
//                return String.class;
//            case VIEW_COL:
//                return JButton.class;
//            default:
//                // fall out
//                break;
//        }
//        return String.class;
//    }

    /*public*/ int MergeTableModel::getPreferredWidth(int col) {
        switch (col) {
            case MERGE_COL:
                return JTextField(3).getPreferredSize().width();
            case ID_COL:
                return  JTextField(16).getPreferredSize().width();
            case VIEW_COL:
                return  JTextField(7).getPreferredSize().width();
            default:
                break;
        }
        return  JTextField(12).getPreferredSize().width();
    }

    //@Override
    /*public*/ Qt::ItemFlags MergeTableModel::flags(const QModelIndex &index) const
    {
        if (index.column() == ID_COL) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }

    //@Override
    /*public*/ QVariant MergeTableModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
     {
        QMapIterator<QString, bool> entry = candidateArray.at(index.row());
        switch (index.column()) {
            case MERGE_COL:
                return entry.value();
            case ID_COL:
                return entry.key();
            case VIEW_COL:
                return tr("View");
            default:
                // fall out
                break;
        }
     }
        return QVariant();
    }

    //@Override
    /*public*/ bool MergeTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     if(role == Qt::EditRole)
     {
        QMapIterator<QString, bool> entry = candidateArray.at(index.row());
        switch (index.column()) {
            case MERGE_COL:
                mp->_candidates->insert(entry.key(),  value.toBool());
                break;
            case ID_COL:
                break;
            case VIEW_COL:
                mp->showProfiles(entry.key());
                break;
            default:
                // fall out
                break;
        }
        return true;
      }
      return false;
    }
//};
#if 0
/*public*/ static class ButtonCellRenderer extends ButtonRenderer {

    @Override
    /*public*/ Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int col) {
        Component b = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, col);

        MergeTableModel tableModel = (MergeTableModel) table.getModel();
        if (tableModel.hasAnomaly(row)) {
            b.setBackground(java.awt.Color.RED);
        } else {
            b.setBackground(table.getBackground());
        }
        return b;
    }
}
#endif
/*private*/ /*final*/ /*static*/ Logger* MergePrompt::log = LoggerFactory::getLogger("MergePrompt");
