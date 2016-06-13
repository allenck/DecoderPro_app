#ifndef EDITOR_H
#define EDITOR_H
#include "jmrijframe.h"
#include <QLineEdit>

class UrlErrorDialog : QDialog {
    QLineEdit* _urlField;
    CatalogPanel  _catalog;
    QString _badUrl;
    UrlErrorDialog(QString msg, QString url)
    {
        super(_targetFrame, Bundle.getMessage("BadIcon"), true);
        _badUrl = url;
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(new JLabel(java.text.MessageFormat.format(Bundle.getMessage("IconUrlError"), msg)));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt1")));
        panel.add(javax.swing.Box.createVerticalStrut(10));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt2")));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt3")));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt4")));
        _urlField = new JTextField(url);
        _urlField.setDragEnabled(true);
        _urlField.setTransferHandler(new jmri.util.DnDQStringImportHandler());
        panel.add(_urlField);
        panel.add(makeDoneButtonPanel());
        _urlField.setToolTipText(Bundle.getMessage("TooltipFixUrl"));
        panel.setToolTipText(Bundle.getMessage("TooltipFixUrl"));
        _catalog = CatalogPanel.makeDefaultCatalog();
        _catalog.setToolTipText(Bundle.getMessage("ToolTipDragIconToText"));
        panel.add(_catalog);
        setContentPane(panel);
        setLocation(200, 100);
        pack();
        setVisible(true);
    }
    /*protected*/ JPanel makeDoneButtonPanel() {
        JPanel panel0 = new JPanel();
        panel0.setLayout(new FlowLayout());
        JButton doneButton = new JButton(Bundle.getMessage("ButtonContinue"));
        doneButton.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    _newIcon = NamedIcon.getIconByName(_urlField.getText());
                    if (_newIcon!=null) {
                        _urlMap.put(_badUrl, _urlField.getText());
                    }
                    dispose();
                }
        });
        doneButton.setToolTipText(Bundle.getMessage("TooltipContinue"));
        panel0.add(doneButton);

        JButton deleteButton = new JButton(Bundle.getMessage("ButtonDeleteIcon"));
        deleteButton.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    _delete = true;
                    dispose();
                }
        });
        panel0.add(deleteButton);
        deleteButton.setToolTipText(Bundle.getMessage("TooltipDelete"));

        JButton cancelButton = new JButton(Bundle.getMessage("ButtonIgnore"));
        cancelButton.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    _ignore = true;
                    dispose();
                }
        });
        panel0.add(cancelButton);
        cancelButton.setToolTipText(Bundle.getMessage("TooltipIgnore"));
        return panel0;
    }
};
static class ToolTipTimer : QTimer {
    ToolTip* tooltip;
    ToolTipTimer(int delay, ActionListener listener, ToolTip tip) {
        super(delay, listener);
        tooltip = tip;
    }
    ToolTip getTooltip() {
        return tooltip;
    }
};
/**
 *  Special internal class to allow drawing of layout to a JLayeredPane
 *  This is the 'target' pane where the layout is displayed
 */
/*public*/ class TargetPane : JLayeredPane
{
    int h = 100;
    int w = 150;
    /*public*/ TargetPane() {
        setLayout(null);
    }

    /*public*/ void setSize(int width, int height) {
//            if (_debug) log.debug("size now w="+width+", h="+height);
        this.h = height;
        this.w = width;
        super.setSize(width, height);
    }
    /*public*/ Dimension getSize() {
        return new Dimension(w,h);
    }
    /*public*/ Dimension getPreferredSize() {
        return new Dimension(w,h);
    }
    /*public*/ Dimension getMinimumSize() {
        return getPreferredSize();
    }
    /*public*/ Dimension getMaximumSize() {
        return getPreferredSize();
    }
    /*public*/ Component add(Component c, int i) {
        int hnew = Math.max(this.h, c.getLocation().y+c.getSize().height);
        int wnew = Math.max(this.w, c.getLocation().x+c.getSize().width);
        if (hnew>h || wnew>w) {
//                if (_debug) log.debug("size was "+w+","+h+" - i="+i);
            setSize(wnew,hnew);
        }
        return super.add(c, i);
    }
    /*public*/ void add(Component c, Object o) {
        super.add(c, o);
        int hnew = Math.max(h, c.getLocation().y+c.getSize().height);
        int wnew = Math.max(w, c.getLocation().x+c.getSize().width);
        if (hnew>h || wnew>w) {
//                if (_debug) log.debug("adding of "+c.getSize()+" with Object - i="+o);
            setSize(wnew,hnew);
        }
    }

    /*private*/ Color _highlightColor = new Color(204, 207, 88);
    /*private*/ Color _selectGroupColor = new Color(204, 207, 88);
    /*private*/ Color _selectRectColor = Color.red;
    /*private*/ transient Stroke _selectRectStroke = DASHED_LINE;
    /*public*/ void setHighlightColor(Color color) {
         _highlightColor = color;
    }
    /*public*/ void setSelectGroupColor(Color color) {
        _selectGroupColor = color;
    }
    /*public*/ void setSelectRectColor(Color color) {
        _selectRectColor = color;
   }
    /*public*/ void setSelectRectStroke(Stroke stroke) {
        _selectRectStroke = stroke;
   }
    /*public*/ void setDefaultColors() {
        _highlightColor = new Color(204, 207, 88);
        _selectGroupColor = new Color(204, 207, 88);
        _selectRectColor = Color.red;
        _selectRectStroke = DASHED_LINE;
    }

    /*public*/ void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D)g;
        g2d.scale(_paintScale, _paintScale);
        super.paint(g);
        paintTargetPanel(g);
        java.awt.Stroke stroke = g2d.getStroke();
        Color color = g2d.getColor();
        if (_selectRect != null) {
            //Draw a rectangle on top of the image.
            g2d.setStroke(_selectRectStroke);
            g2d.setColor(_selectRectColor);
            g.drawRect(_selectRect.x, _selectRect.y, _selectRect.width, _selectRect.height);
        }
        if (_selectionGroup!=null){
            g2d.setColor(_selectGroupColor);
            g2d.setStroke(new java.awt.BasicStroke(2.0f));
            if (_selectionGroup!=null){
                for(int i=0; i<_selectionGroup.size();i++){
                    g.drawRect(_selectionGroup.get(i).getX(), _selectionGroup.get(i).getY(),
                               _selectionGroup.get(i).maxWidth(), _selectionGroup.get(i).maxHeight());
                }
            }
        }
        //Draws a border around the highlighted component
        if (_highlightcomponent!=null) {
            g2d.setColor(_highlightColor);
            g2d.setStroke(new java.awt.BasicStroke(2.0f));
            g.drawRect(_highlightcomponent.x, _highlightcomponent.y,
                       _highlightcomponent.width, _highlightcomponent.height);
        }
        g2d.setColor(color);
        g2d.setStroke(stroke);
        if (_tooltip != null) {
            _tooltip.paint(g2d, _paintScale);
        }
    }

    /*public*/ void setBackgroundColor(Color col){
        setBackground(col);
        setOpaque(true);
    }

    /*public*/ void clearBackgroundColor(){
        setOpaque(false);
    }

    /*public*/ Color getBackgroundColor(){
        if (isOpaque())
            return getBackground();
        return null;
    }
};

class Editor : public JmriJFrame
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    /*public*/ Editor(QString name, bool saveSize, bool savePosition, QObject* parent=0);
    /*public*/ Editor(QString name, QObject* parent=0);

    const /*public*/ static int BKG       = 1;
    const /*public*/ static int TEMP      = 2;
    const /*public*/ static int ICONS     = 3;
    const /*public*/ static int LABELS    = 4;
    const /*public*/ static int MEMORIES  = 5;
    const /*public*/ static int REPORTERS = 5;
    const /*public*/ static int SECURITY  = 6;
    const /*public*/ static int TURNOUTS  = 7;
    const /*public*/ static int LIGHTS    = 8;
    const /*public*/ static int SIGNALS   = 9;
    const /*public*/ static int SENSORS   = 10;
    const /*public*/ static int CLOCK     = 10;
    const /*public*/ static int MARKERS   = 10;
    const /*public*/ static int NUM_LEVELS= 10;

    const /*public*/ static int SCROLL_NONE       = 0;
    const /*public*/ static int SCROLL_BOTH       = 1;
    const /*public*/ static int SCROLL_HORIZONTAL = 2;
    const /*public*/ static int SCROLL_VERTICAL   = 3;
    const /*public*/ static int OPTION_POSITION = 1;
    const /*public*/ static int OPTION_CONTROLS = 2;
    const /*public*/ static int OPTION_HIDDEN = 3;
    const /*public*/ static int OPTION_TOOLTIP= 4;
    //    const /*public*/ static int OPTION_COORDS = 5;
    /*public*/ void loadFailed();
    /*public*/ NamedIcon* loadFailed(QString msg, QString url);
    /*public*/ void disposeLoadData();
    /*public*/ bool loadOK();
    /*public*/ QList <Positionable*> getContents();
    /*public*/ void setDefaultToolTip(ToolTip* dtt);
    /*public*/ const JComponent* getTargetPanel();
    /*public*/ const JFrame getTargetFrame();
    /*public*/ QColor getBackgroundColor();
    /*public*/ void setBackgroundColor(Color col);
    /*public*/ void clearBackgroundColor();
    /**
     * Get/Set scale for TargetPane drawing
     */
    /*public*/ const double getPaintScale();
    static const int TOOLTIPSHOWDELAY = 1000; // msec
    static const int TOOLTIPDISMISSDELAY = 4000;  // msec
    /**
    * Wait TOOLTIPSHOWDELAY then show tooltip.  Wait TOOLTIPDISMISSDELAY and disaappear
    */
    /*public*/ void actionPerformed(ActionEvent event);


signals:
    
public slots:
private:
    /*private*/ bool _debug = false;
    /*private*/ bool _loadFailed = false;

    bool showCloseInfoMessage = true;	//display info message when closing panel
    void commonInit();
    /*private*/ JFrame      _targetFrame;
    /*private*/ JScrollPane _panelScrollPane;
    // Option menu items
    /*private*/ bool _positionable = true;
    /*private*/ bool _controlLayout = true;
    /*private*/ bool _showHidden = true;
    /*private*/ bool _showTooltip = true;
    /*private*/ bool _globalSetsLocal = true;    // pre 2.9.6 behavior
    /*private*/ bool _useGlobalFlag = false;     // pre 2.9.6 behavior

    /*private*/ ToolTip* _defaultToolTip;
    /*private*/ ToolTip* _tooltip = null;

    NamedIcon* _newIcon;
    bool _ignore = false;
    bool _delete;
    QMap<QString, QString>* _urlMap = new QMap<QString, QString>();
    ToolTipTimer* _tooltipTimer;

 protected:
    /*protected*/ QVector <Positionable*>* _contents = new QVector<Positionable*>();
    /*protected*/ JLayeredPane _targetPanel;
    /*protected*/ int _scrollState = SCROLL_NONE;
    /*protected*/ bool _editable = true;
    // mouse methods variables
    /*protected*/ int _lastX;
    /*protected*/ int _lastY;
    BasicStroke DASHED_LINE = new BasicStroke(1f, BasicStroke.CAP_BUTT,
                                    BasicStroke.JOIN_BEVEL,
                                    10f, new float[] {10f, 10f}, 0f);

    /*protected*/ Rectangle _selectRect = null;
    /*protected*/ Rectangle _highlightcomponent = null;
    /*protected*/ bool _dragging = false;
    /*protected*/ QVector <Positionable> _selectionGroup = null;  // items gathered inside fence

    /*protected*/ Positionable _currentSelection;
    // Accessible to editor views
    /*protected*/ int xLoc = 0;     // x coord of selected Positionable
    /*protected*/ int yLoc = 0;     // y coord of selected Positionable
    /*protected*/ int _anchorX;     // x coord when mousePressed
    /*protected*/ int _anchorY;     // y coord when mousePressed

    //    /*private*/ bool delayedPopupTrigger = false; // Used to delay the request of a popup, on a mouse press as this may conflict with a drag event

    /*protected*/ double _paintScale = 1.0;   // scale for _targetPanel drawing

    /*protected*/ QColor defaultBackgroundColor = QColor.lightGray;
    /*protected*/ bool _pastePending = false;

    // map of icon editor frames (incl, icon editor) keyed by name
    /*protected*/ QHash <QString, JFrameItem*> _iconEditorFrame = new QHash <QString, JFrameItem*>();
    /**
    * An Editor may or may not choose to use 'this' as its frame or
    * the interior class 'TargetPane' for its targetPanel
    */
    /*protected*/ void setTargetPanel(JLayeredPane* targetPanel, JmriJFrame* frame);
    /*protected*/ void setTargetPanelSize(int w, int h);
    /*protected*/ Dimension* getTargetPanelSize();
    /*protected*/ const JScrollPane* getPanelScrollPane();

    ToolTipTimer* _tooltipTimer;

    
};

#endif // EDITOR_H
