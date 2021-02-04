#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QObject>
#include <QVariant>
#include "javaqt_global.h"
#include "propertychangelistener.h"
#include "propertychangesupport.h"
#include "tabledelegates.h"

class PropertyChangeEvent;
class JAVAQTSHARED_EXPORT TableColumn : public QObject
{
 Q_OBJECT
public:
 explicit TableColumn(QObject *parent = 0);
 /*public*/ /*final*/ static QString COLUMN_WIDTH_PROPERTY;// = "columWidth";
 /*public*/ /*final*/ static QString HEADER_VALUE_PROPERTY;// = "headerValue";
 /*public*/ /*final*/ static QString HEADER_RENDERER_PROPERTY;// = "headerRenderer";
 /*public*/ /*final*/ static QString CELL_RENDERER_PROPERTY;// = "cellRenderer";
 /*public*/ TableColumn(int modelIndex, QObject *parent = 0);
 /*public*/ TableColumn(int modelIndex, int width, QObject *parent = 0);
 /*public*/ TableColumn(int modelIndex, int width,
                              TableCellRenderer* cellRenderer,
                              TableCellEditor* cellEditor, QObject *parent = 0);
 /*public*/ void setModelIndex(int modelIndex);
 /*public*/ int getModelIndex();
 /*public*/ void setIdentifier(QVariant identifier);
 /*public*/ QVariant getIdentifier();
 /*public*/ void setHeaderValue(QVariant headerValue) ;
 /*public*/ QVariant getHeaderValue();
 /*public*/ void setWidth(int width) ;
 /*public*/ int getWidth();
 /*public*/ void setPreferredWidth(int preferredWidth);
 /*public*/ int getPreferredWidth();
 /*public*/ void setMinWidth(int minWidth);
 /*public*/ int getMinWidth();
 /*public*/ void setMaxWidth(int maxWidth);
 /*public*/ int getMaxWidth();
 /*public*/ void setResizable(bool isResizable);
 /*public*/ bool getResizable();
 /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ void setCellRenderer(TableCellRenderer* cellRenderer);
 /*public*/ TableCellRenderer* getCellRenderer();
 /*public*/ void setCellEditor(TableCellEditor* cellEditor);
 /*public*/ TableCellEditor* getCellEditor();

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
private:
 /**
  * If any <code>PropertyChangeListeners</code> have been registered, the
  * <code>changeSupport</code> field describes them.
  */
// /*private*/ SwingPropertyChangeSupport changeSupport;
 PropertyChangeSupport* changeSupport;

 void common();
 /*private*/ void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);

protected:
 /**
   * The index of the column in the model which is to be displayed by
   * this <code>TableColumn</code>. As columns are moved around in the
   * view <code>modelIndex</code> remains constant.
   */
 /*protected*/ int       modelIndex =0;

 /**
  *  This object is not used internally by the drawing machinery of
  *  the <code>JTable</code>; identifiers may be set in the
  *  <code>TableColumn</code> as as an
  *  optional way to tag and locate table columns. The table package does
  *  not modify or invoke any methods in these identifier objects other
  *  than the <code>equals</code> method which is used in the
  *  <code>getColumnIndex()</code> method in the
  *  <code>DefaultTableColumnModel</code>.
  */
 /*protected*/ QVariant    identifier;

 /** The width of the column. */
 /*protected*/ int       width = 75;

 /** The minimum width of the column. */
 /*protected*/ int       minWidth =0;

 /** The preferred width of the column. */
 /*private*/ int         preferredWidth = 75;

 /** The maximum width of the column. */
 /*protected*/ int       maxWidth;

 /** The renderer used to draw the header of the column. */
 /*protected*/ TableCellRenderer* headerRenderer;

 /** The header value of the column. */
 /*protected*/ QVariant            headerValue;

 /** The renderer used to draw the data cells of the column. */
 /*protected*/ TableCellRenderer* cellRenderer;

 /** The editor used to edit the data cells of the column. */
 /*protected*/ TableCellEditor*   cellEditor;

 /** If true, the user is allowed to resize the column; the default is true. */
 /*protected*/ bool   isResizable = true;



 friend class JTable;
};

#endif // TABLECOLUMN_H
