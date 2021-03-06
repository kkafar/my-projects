#ifndef __SL_H__
#define __SL_H__
#include  <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
////* SKIPLISTA */
/////////////////////////////////////////////////////////////////////////////
typedef struct SkipListNode
{
    int value, level;
    struct SkipListNode ** forward;
} sl_node;
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
typedef struct SkipList
{
    int max_level, curr_level;
    sl_node * head, * tail;
} sl;
/////////////////////////////////////////////////////////////////////////////
sl_node * sl_node_getnew(const int value, const int level);
/////////////////////////////////////////////////////////////////////////////
void sl_node_delete(sl_node * node);
/////////////////////////////////////////////////////////////////////////////
void sl_init(sl * slist, const int max_level);
/////////////////////////////////////////////////////////////////////////////
void sl_delete(sl * slist);
/////////////////////////////////////////////////////////////////////////////
int sl_find(sl * slist, const int value); 
/////////////////////////////////////////////////////////////////////////////
void sl_insert(sl * slist, const int value);
/////////////////////////////////////////////////////////////////////////////
void sl_remove(sl * slist, const int value);
/////////////////////////////////////////////////////////////////////////////
void sl_print(sl * slist); 
/////////////////////////////////////////////////////////////////////////////


#endif