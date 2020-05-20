#ifndef WHEREUSEDFRAME_H
#define WHEREUSEDFRAME_H
#include "jmrijframe.h"
#include "namedbeancombobox.h"
#include "instancemanager.h"
#include "jfilechooser.h"
#include "fileutil.h"

class JTextArea;
class QPushButton;
class WhereUsedFrame : public JmriJFrame
{
 Q_OBJECT
public:
 /**
  * The item types.  A bundle key for each type is stored with the type to
  * create a language dependent toString result.
  */
 WhereUsedFrame(QWidget* parent = nullptr);
 QString getClassName() {return "WhereUsedFrame";}

private:
 static Logger* log;
 class ItemType
 {
 public:
  enum ITEMTYPE {
      NONE,
      TURNOUT,
      SENSOR,
      LIGHT,
      SIGNALHEAD,
      SIGNALMAST,
      REPORTER,
      MEMORY,
      ROUTE,
      OBLOCK,
      BLOCK,
      SECTION,
      WARRANT,
      ENTRYEXIT,
   numValues = ENTRYEXIT +1
  };
 };
   QStringList values = QStringList()
   << "None"
   << "Turnout"
   << "Sensor"
   << "Light"
   << "SignalHead"
   << "SignalMast"
   << "Reporter"
   << "Memory"
   << "Route"
   << "OBlock"
   << "Block"
   << "Section"
   << "Warrant"
   << "EntryExit";
   QString toString(ItemType::ITEMTYPE t)
   {
    return values.at((int)t);
   }

 ItemType::ITEMTYPE _itemType = ItemType::ITEMTYPE::NONE;
 QComboBox* _itemTypeBox;

 NamedBean* _itemBean;
 NamedBeanComboBox* _itemNameBox = new NamedBeanComboBox(
                     (SensorManager*)InstanceManager::getDefault("SensorManager"));

 JPanel* _topPanel;
 JPanel* _bottomPanel;
 JPanel* _scrolltext = new JPanel(new QVBoxLayout());

 JTextArea* _textArea;
 QPushButton* _createButton;
 void createFrame();
 void buildTopPanel();
 void buildBottomPanel();
 void setItemNameBox(ItemType::ITEMTYPE itemType);
 void buildWhereUsedListing(ItemType::ITEMTYPE type, NamedBean* bean);
 void saveWhereUsedPressed();
 JFileChooser* userFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
 NamedBeanComboBox* createNameBox(ItemType::ITEMTYPE itemType);

 friend class WhereUsedAction;
};

#endif // WHEREUSEDFRAME_H
