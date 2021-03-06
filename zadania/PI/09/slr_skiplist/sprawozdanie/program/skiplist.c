#include "skiplist.h"
#include "uti.h"

/////////////////////////////////////////////////////////////////////////////
////* SKIPLISTA */
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
sl_node * sl_node_getnew(const int value, const int level)
{
    sl_node * new_node = (sl_node *)(malloc(sizeof(sl_node)));
    new_node->value = value;
    new_node->level = level;

    // tworzenie listy forward
    // utworzenie tablicy wskaźników
    new_node->forward = (sl_node **)(malloc(sizeof(sl_node *) * level));

    return new_node;
}
/////////////////////////////////////////////////////////////////////////////
void sl_node_delete(sl_node * node)
{
    free(node->forward);
    free(node);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void sl_init(sl * slist, const int max_level)
{
    slist->max_level = max_level;
    slist->curr_level = 1;
    slist->head = sl_node_getnew(MINF, max_level);
    slist->tail = sl_node_getnew(INF, max_level);

    // ustawiamy wszystkie wskaźniki wartownika listy na element końca listy
    for (sl_node ** i = slist->head->forward; i < slist->head->forward + max_level; ++i)
        *i = slist->tail;
}
/////////////////////////////////////////////////////////////////////////////
void sl_delete(sl * slist)
{
    // przechodzimy po najniższym poziomie listy
    sl_node * tmp = (*(slist->head->forward)), * tmp2; 

    while (tmp != slist->tail)
    {
        tmp2 = tmp;
        tmp = *(tmp->forward);
        sl_node_delete(tmp2);
    }    
    sl_node_delete(slist->tail);
    sl_node_delete(slist->head);
}
/////////////////////////////////////////////////////////////////////////////
int sl_find(sl * slist, const int value)
{
    sl_node * x = slist->head;

    for (int i = slist->curr_level - 1; i >= 0; --i)
    {
        // jeżeli 'nie patrzymy za daleko'
        while ( (*(x->forward + i))->value < value )
            x = *(x->forward + i);
    }
    
    x = *(x->forward);
    
    if (x->value == value)  return 1;   // sukces
    else                    return 0;  
}  
/////////////////////////////////////////////////////////////////////////////
void sl_insert(sl * slist, const int value)
{
    sl_node * x = slist->head;

    sl_node * update[slist->max_level];

    for (sl_node ** i = update; i < update + slist->max_level; ++i)
        *i = NULL;
    
    for (int i = slist->curr_level - 1; i >= 0; --i)
    {
        // jeżeli 'nie patrzymy za daleko'
        while ( (*(x->forward + i))->value < value )
            x = *(x->forward + i);

        *(update + i) = x;
    }
    
    x = *(x->forward);
    
    // if (x->value == value)  return;

    // losujemy poziom nowego węzła
    int level = getlevel(slist->max_level);

    // printf("WYLOSOWANO LVL: %d\n", level); 
    if (level > slist->curr_level)
    {
        for (int i = slist->curr_level; i < level; ++i)
            (*(update + i)) = slist->head;

        slist->curr_level = level;
    }

    x = sl_node_getnew(value, level);

    for (int i = 0; i < level; ++i)
    {
        // x->forward[i] = update[i]->forward[i];
        // update[i]->forward[i] = x;
        *(x->forward + i) = *((*(update + i))->forward + i);
        *((*(update + i))->forward + i) = x;
    }        
    
}
/////////////////////////////////////////////////////////////////////////////
void sl_remove(sl * slist, const int value)
{
    sl_node * x = slist->head;
    // printf("sl_remove: %d\n", 1);
    sl_node * update[slist->max_level];

    for (sl_node ** i = update; i < update + slist->max_level; ++i)
        *i = NULL;
    
    for (int i = slist->curr_level - 1; i >= 0; --i)
    {
        // jeżeli 'nie patrzymy za daleko'
        while ( (*(x->forward + i))->value < value )
            x = *(x->forward + i);

        *(update + i) = x;
    }
    // printf("sl_remove: %d\n", 2);
    x = *(x->forward);

    if (x->value == value)
    {
        for (int i = 0; i < slist->curr_level; ++i)
        {
            if (*((*(update + i))->forward + i) != x) break;

            *((*(update + i))->forward + i) = *(x->forward + i);
        }
        // printf("sl_remove: %d\n", 3);
        free(x->forward);
        free(x);
        // printf("sl_remove: %d\n", 4);
        // jeżeli usunęliśmy element o najwięskszym poziomie, to odpowiednio obniżamy poziom listy
        while ((slist->curr_level > 1) && ((*(slist->head->forward + slist->curr_level - 1)) == slist->tail))
        {
            --(slist->curr_level);
        }
        // printf("sl_remove: %d\n", 5);
        
    }
}
/////////////////////////////////////////////////////////////////////////////
void sl_print(sl * slist)
{
    sl_node * iter = slist->head;
    while (iter != slist->tail)
    {
        printf("(val=%d, lvl=%d)  ", iter->value, iter->level);
        iter = *(iter->forward);
    }
    printf("\n");
}    
/////////////////////////////////////////////////////////////////////////////
////* END */
/////////////////////////////////////////////////////////////////////////////