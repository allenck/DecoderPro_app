#include "imagedelegate.h"
#include "rostertablemodel.h"
#include "rosterentry.h"
#include "imageicon.h"
#include "roster.h"
#include <QSortFilterProxyModel>

ImageDelegate::ImageDelegate(QObject * parent)
  : QAbstractItemDelegate(parent)
{
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
 return QSize(32,32);
}

void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
 QSortFilterProxyModel* sorter = (QSortFilterProxyModel*)index.model();
 QModelIndex ix = sorter->mapToSource(index);
 RosterTableModel* model = (RosterTableModel*)ix.model();
 int row = index.data(Qt::DisplayRole).toInt();
 RosterEntry* re = Roster::instance()->getGroupEntry(model->getRosterGroup(), row);
 QString iconPath = re->getImagePath();
 if(!QFile(iconPath).exists()) return;
 QPixmap pm(iconPath);
 painter->drawPixmap(option.rect, pm.scaled(option.rect.width(), option.rect.height(),Qt::KeepAspectRatio));
 return;
}
