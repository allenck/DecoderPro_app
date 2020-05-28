#ifndef TIMETABLEFRAME_H
#define TIMETABLEFRAME_H

#include <QObject>
#include "jmrijframe.h"
#include <QPushButton>
#include "timetabledatamanager.h"
#include "jtree.h"
#include "defaulttreemodel.h"
#include "defaultmutabletreenode.h"
#include <jtextfield.h>
#include <QComboBox>
#include "jlabel.h"
#include <QCheckBox>
#include "jcolorchooser.h"
#include "jspinner.h"
#include "jtextarea.h"
#include "gridbagconstraints.h"
#include "jcombobox.h"
#include "focuslistener.h"
#include "itemlistener.h"
#include "itemevent.h"
#include "jcheckbox.h"
#include "spinnernumbermodel.h"
#include "vptr.h"

class File;
class JFileChooser;
namespace TimeTable
{
class TimeTableTreeNode;
class TTTrain;
class TTSchedule;
class TimeTableFrame : public JmriJFrame
{
public:
 TimeTableFrame(QWidget* parent = nullptr);
 /*public*/ TimeTableFrame(QString tt, QWidget *parent = nullptr);
 /*public*/ static /*final*/ QString EMPTY_GRID;// = "EmptyGrid";
 /*public*/ void setShowReminder(bool dirty);

private:
 static Logger* log;
 TimeTableDataManager* _dataMgr;
 bool _isDirty = false;
 bool _showTrainTimes = false;
 bool _twoPage = false;

 // ------------ Tree variables ------------
 JTree* _timetableTree;
 DefaultTreeModel* _timetableModel;
 DefaultMutableTreeNode* _timetableRoot;
 TreeSelectionListener* _timetableListener;
 TreePath* _curTreePath = nullptr;

 // ------------ Tree components ------------
 TimeTableTreeNode* _layoutNode = nullptr;
 TimeTableTreeNode* _typeHead = nullptr;
 TimeTableTreeNode* _typeNode = nullptr;
 TimeTableTreeNode* _segmentHead = nullptr;
 TimeTableTreeNode* _segmentNode = nullptr;
 TimeTableTreeNode* _stationNode = nullptr;
 TimeTableTreeNode* _scheduleHead = nullptr;
 TimeTableTreeNode* _scheduleNode = nullptr;
 TimeTableTreeNode* _trainNode = nullptr;
 TimeTableTreeNode* _stopNode = nullptr;
 TimeTableTreeNode* _leafNode = nullptr;

 // ------------ Current tree node variables ------------
 TimeTableTreeNode* _curNode = nullptr;
 int _curNodeId = 0;
 QString _curNodeType = "";
 QString _curNodeText = "";
 int _curNodeRow = -1;

 // ------------ Edit detail components ------------
 JPanel* _detailGrid = new JPanel(new QVBoxLayout());
 JPanel* _detailFooter = new JPanel(new FlowLayout());
 JPanel* _gridPanel;  // Child of _detailGrid, contains the current grid labels and fields
 bool _editActive = false;
 QPushButton* _cancelAction;
 QPushButton* _updateAction;

 // Layout
 JTextField* _editLayoutName;
 JComboBox* _editScale;
 JTextField* _editFastClock;
 JTextField* _editThrottles;
 JCheckBox* _editMetric;
 JLabel* _showScaleMK;

 // TrainType
 JTextField* _editTrainTypeName;
 JColorChooser* _editTrainTypeColor;

 // Segment
 JTextField* _editSegmentName;

 // Station
 JTextField* _editStationName;
 JTextField* _editDistance;
 JCheckBox* _editDoubleTrack;
 JSpinner* _editSidings;
 JSpinner* _editStaging;

 // Schedule
 JTextField* _editScheduleName;
 JTextField* _editEffDate;
 JSpinner* _editStartHour;
 JSpinner* _editDuration;

 // Train
 JTextField *_editTrainName;
 JTextField* _editTrainDesc;
 JComboBox/*<TrainType>*/* _editTrainType;
 JTextField* _editDefaultSpeed;
 JTextField* _editTrainStartTime;
 JSpinner* _editThrottle;
 JTextArea* _editTrainNotes;
 JLabel* _showRouteDuration;

 // Stop
 JLabel* _showStopSeq;
 JComboBox/*<TimeTableDataManager::SegmentStation>*/* _editStopStation;
 JTextField* _editStopDuration;
 JTextField* _editNextSpeed;
 JSpinner* _editStagingTrack;
 JTextArea* _editStopNotes;
 JLabel* _showArriveTime;
 JLabel* _showDepartTime;

 // ------------ Button bar components ------------
 JPanel* _leftButtonBar;
 JPanel* _addButtonPanel;
 JPanel* _deleteButtonPanel;
 JPanel* _moveButtonPanel;
 JPanel* _graphButtonPanel;
 QPushButton* _addButton = new QPushButton();
 QPushButton* _deleteButton = new QPushButton();
 QPushButton* _displayButton = new QPushButton();
 QPushButton* _printButton = new QPushButton();
 QPushButton* _saveButton = new QPushButton();

 /*private*/ void createFrame();
 void createMenu();
 void buildComponents();
 void makeDetailGrid(QString gridType);
 void makeEmptyGrid(GridBagConstraints *c);
 void makeLayoutGrid(GridBagConstraints* c);
 void makeTrainTypeGrid(GridBagConstraints* c);
 void makeSegmentGrid(GridBagConstraints* c);
 void makeStationGrid(GridBagConstraints* c);
 void makeScheduleGrid(GridBagConstraints* c);
 void makeTrainGrid(GridBagConstraints* c);
 void makeStopGrid(GridBagConstraints* c);
 void makeGridLabel(int row, QString label, QString hint, GridBagConstraints *c);
 void addPressed();
 void addLayout();
 void addTrainType();
 void addSegment();
 void addStation();
 void addSchedule();
 void addTrain();
 void addStop();
 void editPressed();
 void editLayout();
 void editTrainType();
 void editSegment();
 void editStation();
 void editSchedule();
 void editTrain();
 void editStop();
 void updatePressed();
 void updateLayout();
 void updateTrainType();
 void updateSegment();
 void updateStation();
 void updateSchedule();
 void updateTrain();
 void updateStop();
 int parseNumber(JTextField* textField, QString fieldName);
 void deletePressed();
 void deleteLayout();
 void deleteTrainType();
 void deleteSegment();
 void deleteStation();
 void deleteSchedule();
 void deleteTrain();
 void deleteStop();
 void cancelPressed();
 void upPressed();
 void downPressed();
 void moveTreeNode(QString direction);
 void setMoveButtons();
 void graphPressed(QString graphType);
 void importPressed();
 void importCsvPressed();
 void completeImport(File* file);
 void importFromOperationsPressed();
 void exportCsvPressed();
 void savePressed();
 void donePressed();
 JTree* buildTree();
 void createTimeTableContent();
 QString buildNodeText(QString nodeType, QObject* component, int idx);
 void treeRowSelected(TimeTableTreeNode* selectedNode);
 void showNodeEditMessage();
 void setEditMode(bool active);
 JFileChooser* fileChooser;
 QList<QString> feedbackList;
 ChangeListener* detailChangeEvent = nullptr;
 FocusListener* detailFocusEvent = nullptr;
 ItemListener* stopStationItemEvent = nullptr;
 ItemListener* layoutScaleItemEvent = nullptr;
protected:
 QString getClassName() override;

 friend class TTFWindowListener;
 friend class TTFTreeSelectionListener;
 friend class TTFFocusListener;
 friend class TTFChangeListener;
 friend class StopStationItemEventListener;
};

class TTFWindowListener : public WindowListener
{
 Q_OBJECT
 TimeTableFrame* frame;
public:
 TTFWindowListener(TimeTableFrame* frame) {this->frame = frame;}
 void windowClosing(QCloseEvent *)
 {
  frame->donePressed();
 }
};

/**
 * Timetable Tree Node Definition.
 */
/*static*/ class TimeTableTreeNode : public DefaultMutableTreeNode {
Q_OBJECT
    /*private*/ QString ttText;
    /*private*/ QString ttType;
    /*private*/ int ttId;
    /*private*/ int ttRow;
public:
    /*public*/ TimeTableTreeNode(QString nameText, QString type, int sysId, int row) {
        this->ttText = nameText;
        this->ttType = type;
        this->ttId = sysId;
        this->ttRow = row;
    }

    /*public*/ QString getType() {
        return ttType;
    }

    /*public*/ int getId() {
        return ttId;
    }

    /*public*/ void setId(int newId) {
        ttId = newId;
    }

    /*public*/ int getRow() {
        return ttRow;
    }

    /*public*/ void setRow(int newRow) {
        ttRow = newRow;
    }

    /*public*/ QString getText() {
        return ttText;
    }

    /*public*/ void setText(QString newText) {
        ttText = newText;
    }

    //@Override
    /*public*/ QString toString() override{
        return ttText;
    }
};

 class TTFTreeSelectionListener : public TreeSelectionListener
 {
  Q_OBJECT
  TimeTableFrame* frame;
 public:
  TTFTreeSelectionListener(TimeTableFrame* frame) {this->frame = frame;}
 public slots:
  /*public*/ void valueChanged(TreeSelectionEvent* e) {
      if (frame->_editActive) {
          if (e->getNewLeadSelectionPath() != frame->_curTreePath) {
              frame->_timetableTree->setSelectionPath(e->getOldLeadSelectionPath());
              frame->showNodeEditMessage();
          }
          return;
      }

      frame->_curTreePath = frame->_timetableTree->getSelectionPath();
      if (frame->_curTreePath != nullptr) {
          QObject* chkLast = frame->_curTreePath->getLastPathComponent();
          if (qobject_cast<TimeTableTreeNode*>(chkLast)) {
              frame->treeRowSelected((TimeTableTreeNode*) chkLast);
          }
      }
  }

 };

 class TTFFocusListener : public FocusListener
 {
  Q_OBJECT
  TimeTableFrame* frame;
 public:
  TTFFocusListener(TimeTableFrame* frame) {this->frame = frame;}
 public slots:
  /*public*/ void focusGained(FocusEvent* e) {
      if (!frame->_editActive) {
          frame->setEditMode(true);
      }
  }

//  //@Override
//  /*public*/ void focusLost(FocusEvent* e) {
//  }

 };

 class TTFChangeListener : public ChangeListener
 {
  Q_OBJECT
  TimeTableFrame* frame;
 public:
  TTFChangeListener(TimeTableFrame* frame) {this->frame = frame;}
 public slots:
  //@Override
  /*public*/ void stateChanged(ChangeEvent* e) {
      if (!frame->_editActive) {
          frame->setEditMode(true);
      }
  }

 };

 class StopStationItemEventListener : public ItemListener
 {
  Q_OBJECT
  TimeTableFrame* frame;
 public:
  StopStationItemEventListener(TimeTableFrame* frame) {this->frame = frame;}
 public slots:
  //@Override
  /*public*/ void itemStateChanged(ItemEvent* e) {
#if 1
      if (e->getStateChange() == ItemEvent::SELECTED) {
          SegmentStation* segmentStation = VPtr<SegmentStation>::asPtr(e->getItem());
          int stagingTracks = frame->_dataMgr->getStation(segmentStation->getStationId())->getStaging();
          Stop* stop = frame->_dataMgr->getStop(frame->_curNodeId);
          if (stop->getStagingTrack() <= stagingTracks) {
              frame->_editStagingTrack->setModel(new SpinnerNumberModel(stop->getStagingTrack(), 0, stagingTracks, 1));
          }
      }
#endif
  }

 };

 class LayoutScaleItemEventListener : public ItemListener
 {
  Q_OBJECT
  TimeTableFrame* frame;
 public:
  LayoutScaleItemEventListener(TimeTableFrame* frame) {this->frame = frame;}
 public slots:
  //@Override
  /*public*/ void itemStateChanged(ItemEvent* e) {
#if 0
      if (e.getStateChange() == ItemEvent.SELECTED) {
          if (_editScale.hasFocus()) {
              Scale scale = (Scale) _editScale.getSelectedItem();
              if (scale.getScaleName() == ("CUSTOM")) {  // NOI18N
                  String ans = JOptionPane::showInputDialog(
                          tr("ScaleRatioChange"),  // NOI18N
                          scale.getScaleRatio()
                          );
                  if (ans != null) {
                      try {
                          double newRatio = Double.parseDouble(ans);
                          scale.setScaleRatio(newRatio);
                      } catch (java.lang.IllegalArgumentException
                              | java.beans.PropertyVetoException ex) {
                          log->warn("Unable to change custom ratio: {}", ex.getMessage());  // NOI18N
                          JOptionPane::showMessageDialog(null,
                                  tr("NumberFormatError", ans, "Custom ratio"),  // NOI18N
                                  tr("Warning"),  // NOI18N
                                  JOptionPane::WARNING_MESSAGE);
                          Layout layout = _dataMgr->getLayout(_curNodeId);
                          _editScale->setCheckedItem(layout->getScale());
                      }
                  }
              }
          }
      }
#endif
  }

 };

}
#endif // TIMETABLEFRAME_H
