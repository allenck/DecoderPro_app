#include "whereusedframe.h"
#include "borderlayout.h"
#include <QScrollArea>
#include "jlabel.h"
#include <QPushButton>
#include "turnoutwhereused.h"
#include "sensorwhereused.h"
#include "jtextarea.h"
#include "namedbeancombobox.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "lightwhereused.h"
#include "signalheadwhereused.h"
#include "signalmastwhereused.h"
#include "reporterwhereused.h"
#include "blockwhereused.h"
#include "memorywhereused.h"
#include "entryexitwhereused.h"
#include "oblockwhereused.h"
#include "memorywhereused.h"
#include "routewhereused.h"
#include "warrantwhereused.h"
#include "sectionwhereused.h"
#include <QTextBrowser>
#include "vptr.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include "entryexitpairs.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"

/**
 * Create a where used report based on the selected bean.  The selection combo box is
 * based on the selected type.

 * @author Dave Sand Copyright (C) 2020
 */
///*public*/ class WhereUsedFrame extends jmri.util.JmriJFrame {


    /*public*/ WhereUsedFrame::WhereUsedFrame(QWidget* parent) : JmriJFrame(true, true, parent){
        //super(true, true);
        setTitle(tr("Where Used"));  // NOI18N
        createFrame();
        addHelpMenu("package.jmri.jmrit.whereused.WhereUsed", true);  // NOI18N
    }

    /**
     * Create the window frame.  The top part contains the item type, the item name
     * combo box, and a Create button.  The middle contains the scrollable "where used" text area and the
     * bottom part has a button for saving the content to a file.
     */
    void WhereUsedFrame::createFrame()
    {
//     QTextBrowser *centralWidget = new QTextBrowser;
//     centralWidget->setPlainText(tr("Central widget"));
//     setCentralWidget(centralWidget);

     BorderLayout *layout = new BorderLayout;

        // Build the top panel
        buildTopPanel();
        layout->addWidget(_topPanel, BorderLayout::North);

        // Build an empty where used listing
        buildWhereUsedListing(ItemType::ITEMTYPE::NONE, nullptr);
        layout->addWidget(_scrolltext, BorderLayout::Center);

        // Build the bottom panel
        buildBottomPanel();
        layout->addWidget(_bottomPanel, BorderLayout::South);
        QWidget* borderWidget = new QWidget();
        borderWidget->setLayout(layout);
        setCentralWidget(borderWidget);
        pack();
    }

    void WhereUsedFrame::buildTopPanel() {
        _topPanel = new JPanel(new FlowLayout());
        _topPanel->layout()->addWidget(new JLabel(tr("Select Item Type")));  // NOI18N
        _itemTypeBox = new JComboBox();
//        for (ItemType itemType : ItemType.values()) {
//            _itemTypeBox->addItem(itemType);
//        }
        for(int i=0; i < ItemType::numValues; i++)
         _itemTypeBox->addItem(values.at(i), i);
//        JComboBoxUtil.setupComboBoxMaxRows(_itemTypeBox);
        _topPanel->layout()->addWidget(_itemTypeBox);

        _topPanel->layout()->addWidget(new JLabel(tr("Item Name")));  // NOI18N
        _topPanel->layout()->addWidget(_itemNameBox);
        //_itemTypeBox.addActionListener((e) -> {
#if 1
        connect(_itemTypeBox, &QComboBox::currentTextChanged, [=]{
            _itemType = (ItemType::ITEMTYPE)_itemTypeBox->itemData(_itemTypeBox->currentIndex()).toInt();
            setItemNameBox(_itemType);
        });
#endif
        _createButton = new QPushButton(tr("Create"));  // NOI18N
        //_createButton.addActionListener((e) -> buildWhereUsedListing(_itemType, _itemBean));
        connect(_createButton, &QPushButton::clicked, [=]{
         buildWhereUsedListing(_itemType, _itemBean);
        });

        _topPanel->layout()->addWidget(_createButton);
        _itemNameBox->setEnabled(false);
        _createButton->setEnabled(false);
        return;
    }

    void WhereUsedFrame::buildBottomPanel() {
        _bottomPanel = new JPanel();
        _bottomPanel->setLayout(new BorderLayout());

        QPushButton* saveButton = new QPushButton(tr("Save"));   // NOI18N
        saveButton->setToolTip(tr("Save the where used content to a text file"));      // NOI18N
        ((BorderLayout*)_bottomPanel->layout())->addWidget(saveButton, BorderLayout::East);
        //saveButton.addActionListener((ActionEvent e) -> saveWhereUsedPressed());
        connect(saveButton, &QPushButton::clicked, [=]{
         saveWhereUsedPressed();
        });
    }

    /**
     * Create a new NamedBeanComboBox based on the item type and refresh the panel.
     * A selection listener saves the selection and enables the Create button.
     * @param itemType The enum for the selected item type.
     */
    void WhereUsedFrame::setItemNameBox(ItemType::ITEMTYPE itemType) {
        _createButton->setEnabled(false);
        buildWhereUsedListing(ItemType::NONE, nullptr);
        NamedBeanComboBox* newNameBox = createNameBox(itemType);
        if (newNameBox == nullptr) {
            _itemNameBox->setCurrentIndex(-1);
            _itemNameBox->setEnabled(false);
            return;
        }
        _topPanel->layout()->removeWidget(_itemNameBox);
        delete _itemNameBox;
        _topPanel->layout()->removeWidget(_createButton);

        _itemNameBox = newNameBox;
        _itemNameBox->setCurrentIndex(-1);
        ((FlowLayout*)_topPanel->layout())->addWidget(_itemNameBox);//, 3);
        _topPanel->layout()->addWidget(_createButton);

        _itemNameBox->setEnabled(true);
#if 1
        //_itemNameBox->addItemListener((e) -> {
        connect(_itemNameBox, &NamedBeanComboBox::currentTextChanged, [=]{
//            if (e.getStateChange() == ItemEvent.SELECTED) {
                _itemBean = VPtr<NamedBean>::asPtr( _itemNameBox->currentData());
                _createButton->setEnabled(true);
//            });
        });
#endif

        //pack();
        repaint();
    }

    /**
     * Build the where used content and update the JScrollPane.
     * <p>
     * The selected object is passed to the appropriate detail class which returns a populated textarea.
     * The textarea is formatted and inserted into a scrollable panel.
     */
    void WhereUsedFrame::buildWhereUsedListing(ItemType::ITEMTYPE type, NamedBean* bean) {
        switch (type) {
            case ItemType::TURNOUT:
                _textArea = TurnoutWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::SENSOR:
                _textArea = SensorWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::LIGHT:
                _textArea = LightWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::SIGNALHEAD:
                _textArea = SignalHeadWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::SIGNALMAST:
                _textArea = SignalMastWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::REPORTER:
                _textArea = ReporterWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::MEMORY:
                _textArea = MemoryWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::ROUTE:
                _textArea = RouteWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::OBLOCK:
                _textArea = OBlockWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::BLOCK:
                _textArea = BlockWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::SECTION:
                _textArea = SectionWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::WARRANT:
                _textArea = WarrantWhereUsed::getWhereUsed(bean);
                break;
            case ItemType::ENTRYEXIT:
                _textArea = EntryExitWhereUsed::getWhereUsed(bean);
                break;
            default:
                _textArea = new JTextArea(tr("	Select an item type, then select an item name and then press Create.	"));
                break;
        }

        _textArea->setFont(QFont("Monospaced", 12)); //new Font(Font.MONOSPACED, Font.PLAIN, 12));
        _textArea->setTabSize(4);
        _textArea->setEditable(false);
        _textArea->setEnabled(true);
#if 0
        _textArea->setCaretPosition(0);
        if (_scrolltext.getComponentCount() > 0) {
            _scrolltext.remove(0);
        }
#endif
        QTextCursor textCursor = _textArea->textCursor();
        textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
        _textArea->setTextCursor(textCursor); // The line to add

        QList<JTextArea*> wl = _scrolltext->findChildren<JTextArea*>();
        log->debug(tr("_scrolltext has %1 components").arg(wl.size()));
        foreach (QWidget* w , wl) {
          _scrolltext->layout()->removeWidget(w);
          delete w;
        }
        _scrolltext->layout()->addWidget(_textArea);
        //pack();
        repaint();
        return;
    }


    /**
     * Save the where used textarea content to a text file.
     */
    void WhereUsedFrame::saveWhereUsedPressed() {
        userFileChooser->setApproveButtonText(tr("Save Content"));  // NOI18N
        userFileChooser->setDialogTitle(tr("Save Where Used Content"));  // NOI18N
#if 0
        userFileChooser->rescanCurrentDirectory();
#endif

        QString itemName = _itemNameBox->getSelectedItemDisplayName();
        QString fileName = tr("%1 Where Used.txt").arg(((itemName.isNull()) ? "Unknown" : itemName));  // NOI18N
        userFileChooser->setSelectedFile(new File(fileName));
        int retVal = userFileChooser->showSaveDialog(nullptr);
        if (retVal != JFileChooser::APPROVE_OPTION) {
            log->debug("Save where used content stopped, no file selected");  // NOI18N
            return;  // give up if no file selected or cancel pressed
        }
        File* file = userFileChooser->getSelectedFile();
        log->debug(tr("Save where used content to '%1'").arg(file->getPath()));  // NOI18N

        if (file->exists()) {
            QVariantList options = QVariantList() << tr("Replace")  // NOI18N
                    << tr("Append")  // NOI18N
                    << tr("Cancel");               // NOI18N
            int selectedOption = JOptionPane::showOptionDialog(nullptr,
                    tr("File \"%1\" already exists, select Append or Replace").arg(file->getName()), // NOI18N
                    tr("Duplicate File"),   // NOI18N
                    JOptionPane::DEFAULT_OPTION,
                    JOptionPane::WARNING_MESSAGE,
                    QIcon(), options, options[0]);
            if (selectedOption == 2 || selectedOption == -1) {
                log->debug("Save where used content stopped, file replace/append cancelled");  // NOI18N
                return;  // Cancel selected or dialog box closed
            }
            if (selectedOption == 0) {
                FileUtil::_delete(file);  // Replace selected
            }
        }

        // Create the file content
        try {
            FileUtil::appendTextToFile(file, _textArea->toHtml());
        } catch (IOException e) {
            log->error(tr("Unable to write where used content to '%1', exception: '%2'").arg(file->getName()).arg( e.getMessage()));  // NOI18N
        }
    }

    /**
     * Create a combo name box for name selection.
     *
     * @param itemType The selected bean type
     * @return a combo box based on the item type or null if no match
     */
    NamedBeanComboBox* WhereUsedFrame::createNameBox(ItemType::ITEMTYPE itemType) {
        NamedBeanComboBox* nameBox;
        switch (itemType) {
            case ItemType::TURNOUT:
                nameBox = new NamedBeanComboBox/*<Turnout>*/((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"));
                break;
            case ItemType::SENSOR:
                nameBox = new NamedBeanComboBox/*<Sensor>*/((SensorManager*)InstanceManager::getDefault("SensorManager"));
                break;
            case ItemType::LIGHT:
                nameBox = new NamedBeanComboBox/*<Light>*/((LightManager*)InstanceManager::getDefault("LightManager"));
                break;
            case ItemType::SIGNALHEAD:
                nameBox = new NamedBeanComboBox/*<SignalHead>*/((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"));
                break;
            case ItemType::SIGNALMAST:
                nameBox = new NamedBeanComboBox/*<SignalMast>*/((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
                break;
            case ItemType::REPORTER:
                nameBox = new NamedBeanComboBox/*<Reporter>*/((ReporterManager*)InstanceManager::getDefault("ReporterManager"));
                break;
            case ItemType::MEMORY:
                nameBox = new NamedBeanComboBox/*<Memory>*/((MemoryManager*)InstanceManager::getDefault("MemoryManager"));
                break;
            case ItemType::ROUTE:
                nameBox = new NamedBeanComboBox/*<Route>*/((RouteManager*)InstanceManager::getDefault("RouteManager"));
                break;
            case ItemType::OBLOCK:
                nameBox = new NamedBeanComboBox/*<OBlock>*/((OBlockManager*)InstanceManager::getDefault("OBlockManager"));
                break;
            case ItemType::BLOCK:
                nameBox = new NamedBeanComboBox/*<Block>*/((BlockManager*)InstanceManager::getDefault("BlockManager"));
                break;
            case ItemType::SECTION:
                nameBox = new NamedBeanComboBox/*<Section>*/((SectionManager*)InstanceManager::getDefault("SectionManager"));
                break;
            case ItemType::WARRANT:
                nameBox = new NamedBeanComboBox/*<Warrant>*/((WarrantManager*)InstanceManager::getDefault("WarrantManager"));
                break;
            case ItemType::ENTRYEXIT:
                nameBox = new NamedBeanComboBox/*<DestinationPoints*>*/((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"));
                break;
            default:
                return nullptr;             // Skip any other items.
        }
        nameBox->setEditable(false);
        nameBox->setValidatingInput(false);
//        JComboBoxUtil.setupComboBoxMaxRows(nameBox);
        return nameBox;
    }
#if 0
    /**
     * The item types.  A bundle key for each type is stored with the type to
     * create a language dependent toString result.
     */
    enum ItemType {
        NONE("ItemTypeNone"),
        TURNOUT("BeanNameTurnout"),
        SENSOR("BeanNameSensor"),
        LIGHT("BeanNameLight"),
        SIGNALHEAD("BeanNameSignalHead"),
        SIGNALMAST("BeanNameSignalMast"),
        REPORTER("BeanNameReporter"),
        MEMORY("BeanNameMemory"),
        ROUTE("BeanNameRoute"),
        OBLOCK("BeanNameOBlock"),
        BLOCK("BeanNameBlock"),
        SECTION("BeanNameSection"),
        WARRANT("BeanNameWarrant"),
        ENTRYEXIT("BeanNameEntryExit");

        /*private*/ /*final*/ QString _bundleKey;

        /*private*/ ItemType(String bundleKey) {
            _bundleKey = bundleKey;
        }

        //@Override
        /*public*/ QString toString() {
            return Bundle.getMessage(_bundleKey);
        }
    }
#endif
    /*private*/ /*static*/ /*final*/ Logger* WhereUsedFrame::log = LoggerFactory::getLogger("WhereUsedFrame");
