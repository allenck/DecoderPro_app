#include "treeselectionmodel.h"

/** Selection can only contain one path at a time. */
/*public*/ /*static*/ /*final*/ int               TreeSelectionModel::SINGLE_TREE_SELECTION = 1;

/** Selection can only be contiguous. This will only be enforced if
 * a RowMapper instance is provided. That is, if no RowMapper is set
 * this behaves the same as DISCONTIGUOUS_TREE_SELECTION. */
/*public*/ /*static*/ /*final*/ int               TreeSelectionModel::CONTIGUOUS_TREE_SELECTION = 2;

/** Selection can contain any number of items that are not necessarily
 * contiguous. */
/*public*/ /*static*/ /*final*/ int               TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION = 4;
