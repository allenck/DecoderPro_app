#include "lighttabledatamodel.h"
#include "loggerfactory.h"
#include "guilafpreferencesmanager.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "variablelight.h"
#include "lighttableaction.h"
#include "joptionpane.h"
#include "lighteditaction.h"
#include "imageio.h"
#include "file.h"
#include "fileutil.h"
#include "proxylightmanager.h"

/**
 * Data model for a Light Table.
 * Code originally within LightTableAction.
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class LightTableDataModel extends BeanTableDataModel<Light> {



    /*public*/ LightTableDataModel::LightTableDataModel() : BeanTableDataModel(){
        //super();
        initTable();
    }

    /*public*/ LightTableDataModel::LightTableDataModel(Manager/*<Light>*/* mgr) : BeanTableDataModel(){
        //super();
        setManager((AbstractManager*)mgr->self());
        initTable();
    }

    /*private*/ void LightTableDataModel::initTable() {
    setObjectName("LightTableDataModel");
     _graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();
     rootPath = FileUtil::getProgramPath() + "resources/icons/misc/switchboard/";
     onIconPath = rootPath + beanTypeChar + "-on-s.png";
     offIconPath = rootPath + beanTypeChar + "-off-s.png";
     loadIcons();
    }


    /**
     * {@inheritDoc}
     */
    //@Nonnull
    //@Override
    /*public*/ Manager *LightTableDataModel::getManager(){
        if (lightManager == nullptr) {
            lightManager = (LightManager*)InstanceManager::getDefault("LightManager");
        }
        return lightManager;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ /*final*/ void LightTableDataModel::setManager(/*@Nonnull*/ Manager *manager) {
        if (!(qobject_cast<LightManager*>(manager->self()))) {
            return;
        }
        getManager()->removePropertyChangeListener(this);
        if (!sysNameList.isEmpty()) {
            for (int i = 0; i < sysNameList.size(); i++) {
                // if object has been deleted, it's not here; ignore it
                NamedBean* b = getBySystemName(sysNameList.at(i));
                if (b != nullptr) {
                    b->removePropertyChangeListener(this);
                }
            }
        }
        lightManager = manager;
        getManager()->addPropertyChangeListener(this);
        updateNameList();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    ///*public*/ int LightTableDataModel::getColumnCount()
    /*public*/ int LightTableDataModel::columnCount(const QModelIndex& parent) const
    {
        return CONTROLCOL + 1 + getPropertyColumnCount();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    ///*public*/ QString getColumnName(int col)
    /*public*/ QVariant LightTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
        switch (section) {
            case EDITCOL:
                return ""; // no heading on "Edit"
            case INTENSITYCOL:
                return tr("Intensity");
            case ENABLECOL:
                return tr("Enabled");
            case CONTROLCOL:
                return tr("Light Controllers");
            default:
         break;
        }
     }
     return BeanTableDataModel::headerData(section, orientation, role);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString LightTableDataModel::getColumnClass(int col) const {
        switch (col) {
            case EDITCOL:
                return "JButton";
            case INTENSITYCOL:
                return "Double";
            case ENABLECOL:
                return "Boolean";
            case CONTROLCOL:
                return "String";
            case VALUECOL:  // may use an image to show light state
                return ( _graphicState ? "JLabel" : "JButton" );
            default:
                return BeanTableDataModel::getColumnClass(col);
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ int LightTableDataModel::getPreferredWidth(int col) {
        switch (col) {
            case USERNAMECOL: // override default value for UserName column
            case CONTROLCOL:
                return JTextField(16).sizeHint().width();
            case EDITCOL:
                return  JButton(tr("Edit")).sizeHint().width()+4;
            case INTENSITYCOL:
            case ENABLECOL:
                return  JTextField(6).getPreferredSize().width();
            default:
                return BeanTableDataModel::getPreferredWidth(col);
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    // /*public*/ bool isCellEditable(int row, int col)
    /*public*/ Qt::ItemFlags LightTableDataModel::flags(const QModelIndex &mindex) const
    {
     Light* l = ((Light*) getBySystemName(data(index(mindex.row(), SYSNAMECOL),Qt::DisplayRole).toString()));
     if (l == nullptr){
         return Qt::NoItemFlags;
     }
        switch (mindex.column()) {
            case INTENSITYCOL:
                //return getValueAt(row, SYSNAMECOL) instanceof VariableLight;
             if(static_cast<VariableLight*>(l))
              return Qt::ItemIsEnabled | Qt::ItemIsEditable;
             else {
              return Qt::ItemIsEnabled;
             }
            case EDITCOL:
            case ENABLECOL:
                return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
            case CONTROLCOL:
                return Qt::ItemIsEnabled;
            default:
                return BeanTableDataModel::flags(mindex);
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString LightTableDataModel::getValue(QString name)
    {
        NamedBean* l = lightManager->getBySystemName(name);
        return (l==nullptr ? ("Failed to find " + name) : l->describeState(l->getState()));
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    // /*public*/ Object getValueAt(int row, int col)
    /*public*/ QVariant LightTableDataModel::data(const QModelIndex &mindex, int role) const
    {
     int col = mindex.column();
     Light* l = (Light*)getBySystemName(sysNameList.at(mindex.row()));
     if(role == Qt::DisplayRole)
     {
      switch(col)
      {
        case EDITCOL:
            return tr("Edit");
        case INTENSITYCOL:
         if (qobject_cast<VariableLight*>(l)) {
             return ((VariableLight*)l)->getTargetIntensity();
         } else {
             return 0.0;
         }
       case CONTROLCOL:
        {
         QString sb;// = new StringBuilder();
         for (LightControl* lc : l->getLightControlList())
         {
             sb.append(LightTableAction::getDescriptionText(lc, lc->getControlType()));
             sb.append(" ");
         }
         return sb/*.toString()*/;
        }
       default:
        break;
      }
     }
     if(role == Qt::CheckStateRole)
     {
      if (col == ENABLECOL) {
            //return Boolean.valueOf(((Light) getBySystemName((String) getValueAt(row, SYSNAMECOL))).getEnabled());
          return l->getEnabled()? Qt::Checked : Qt::Unchecked;
      }
      if(col == VALUECOL)
       return l->getState()==Light::ON? Qt::Checked : Qt::Unchecked;
     }
     if(_graphicState && role == Qt::DecorationRole )
     {
      if(mindex.column() == ENABLECOL)
      {
       return l->getEnabled()? onIcon : offIcon;

      }
      if(mindex.column() == VALUECOL)
      {
       //return l->getState()==Light::ON? onIcon : offIcon;
       switch(l->getState())
       {
        case Light::ON:
         return onIcon;
        case Light::OFF:
         return offIcon;
//        case Light::INCONSISTENT:
//         return QColor(Qt::red);
//       case Light::INTERMEDIATE:
//        return "...";
       default:
        break;
       }
      }
     }
     return BeanTableDataModel::data(mindex, role);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    ///*public*/ void setValueAt(Object value, int row, int col)
    /*public*/ bool LightTableDataModel::setData(const QModelIndex &mindex, const QVariant &value, int role)
    {
        //Light* l = (Light*) getValueAt(row, SYSNAMECOL);
        Light* l = ((Light*) getBySystemName(data(index(mindex.row(), SYSNAMECOL),Qt::DisplayRole).toString()));
        if (l == nullptr){
            return false;
        }
        switch (mindex.column()) {
         case EDITCOL:
             // Use separate Runnable so window is created on top
//                javax.swing.SwingUtilities.invokeLater(() -> {
                 editButton(l);
//                });
             return true;
         case INTENSITYCOL:
             // alternate
             try {
                 if (static_cast<VariableLight*>(l)) {
                     double intensity = qMax(0., qMin(1.0,  value.toDouble()));
                     ((VariableLight*)l)->setTargetIntensity(intensity);
                 } else {
                     double intensity = ( value.toDouble());
                     l->setCommandedState( intensity > 0.5 ? Light::ON : Light::OFF);
                 }
             } catch (IllegalArgumentException* e1) {
                 JOptionPane::showMessageDialog(nullptr,  e1->getMessage());
             }
             fireTableRowsUpdated(mindex.row(), mindex.row());
             return true;
         case ENABLECOL:
             l->setEnabled(!l->getEnabled());
             fireTableRowsUpdated(mindex.row(), mindex.row());
             return true;
         case VALUECOL:
             clickOn((NamedBean*)l);
             fireTableRowsUpdated(mindex.row(), mindex.row());
             return true;
         default:
             //super.setValueAt(value, row, col);
             break;
        }
        return BeanTableDataModel::setData(mindex, value, role);
    }

    /*private*/ void LightTableDataModel::editButton(Light* bean){
        LightEditAction* beanEdit = new LightEditAction();
        beanEdit->setBean((NamedBean*)bean);
        beanEdit->actionPerformed(/*null*/);
    }

    /**
     * Delete the bean after all the checking has been done.
     * <p>
     * Deactivate the light, then use the superclass to delete it.
     */
    //@Override
    /*protected*/ void LightTableDataModel::doDelete(NamedBean* bean) {
        ((Light*)bean)->deactivateLight();
        BeanTableDataModel::doDelete(bean);
    }

    // all properties update for now
    //@Override
    /*protected*/ bool LightTableDataModel::matchPropertyName(PropertyChangeEvent* /*e*/) {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ NamedBean* LightTableDataModel::getBySystemName(/*@Nonnull*/ QString name) const{
        return lightManager->getBySystemName(name);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ NamedBean* LightTableDataModel::getByUserName(/*@Nonnull*/ QString name)  {
        return ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getByUserName(name);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ QString LightTableDataModel::getMasterClassName() {
        return "jmri.jmrit.beantable.LightTableAction";
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LightTableDataModel::clickOn(NamedBean* t) {
        t->setState( t->getState()==Light::OFF ? Light::ON : Light::OFF );
    }

    /*public*/ void LightTableDataModel::configureTable(JTable *table)
    {
     setColumnToHoldButton(table, EDITCOL);
     BeanTableDataModel::configureTable(table);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ JButton* LightTableDataModel::configureButton() {
        return new JButton(" " + tr("Off") + " ");
    }

    /**
     * Customize the light table Value (State) column to show an
     * appropriate graphic for the light state if _graphicState = true,
     * or (default) just show the localized state text when the
     * TableDataModel is being called from ListedTableAction.
     *
     * @param table a JTable of Lights
     */
    //@Override
    /*protected*/ void LightTableDataModel::configValueColumn(JTable* table) {
        // have the value column hold a JPanel (icon)
        //setColumnToHoldButton(table, VALUECOL, new JLabel("123456")); // for small round icon, but cannot be converted to JButton
        // add extras, override BeanTableDataModel
        log->debug(tr("Light configValueColumn (I am %1)").arg(this->toString()));
        if (_graphicState) { // load icons, only once
//            table->setDefaultEditor("JLabel", new ImageIconRenderer()); // editor
//            table.setDefaultRenderer(JLabel.class, new ImageIconRenderer()); // item class copied from SwitchboardEditor panel
        } else {
            BeanTableDataModel::configValueColumn(table); // classic text style state indication
        }
    }
   /**
    * Read and buffer graphics. Only called once for this table.
    *
    * @see #getTableCellEditorComponent(JTable, Object, boolean,
    * int, int)
    */
    /*protected*/ void LightTableDataModel::loadIcons() {
     try
     {
      onImage = ImageIO::read(new File(onIconPath));
      offImage = ImageIO::read(new File(offIconPath));
     } catch (IOException* ex) {
         log->error(tr("error reading image from %1 or %2").arg(onIconPath).arg(offIconPath), ex);
     }
     log->debug("Success reading images");
     int imageWidth = onImage->width();
     int imageHeight = onImage->height();
     // scale icons 50% to fit in table rows
     QImage smallOnImage = onImage->getScaledInstance(imageWidth / 2, imageHeight / 2, 0); //, Image.SCALE_DEFAULT);
     QImage smallOffImage = offImage->getScaledInstance(imageWidth / 2, imageHeight / 2, 0); //, Image.SCALE_DEFAULT);
     onIcon = QPixmap::fromImage(smallOnImage);
     offIcon =  QPixmap::fromImage(smallOffImage);
     iconHeight = onIcon.height();
    }

    /*static*/ Logger* LightTableDataModel::log = LoggerFactory::getLogger("LightTableDataModel");

