#include "m_balanced_binary_tree.h"

m_balanced_binary_tree::m_balanced_binary_tree()
{
    root = new tree_root;
    for (int i = 0; i<= WORD_MAX_SIZE; i++)
            root->ptr[i] = NULL;
}

void m_balanced_binary_tree::deletenode(node *p)
{
    if (!p) return;
    node * lc = p->LChild , *rc = p->RChild;
    delete(p);
    if (lc)
        deletenode(lc);
    if (rc)
        deletenode(rc);
}

m_balanced_binary_tree::~m_balanced_binary_tree()
{
    //清空树
    node *tmp;
    for (int i = 0; i<= WORD_MAX_SIZE; i++)
    {
        tmp = root->ptr[i];
        deletenode(tmp);
    }
    delete []root;
}

bool m_balanced_binary_tree::insert (wchar_t * v,int wordID)
{
    bool taller = false;
    m_charstring<wchar_t> str(v);
    if (str.getSavednum() <= WORD_MAX_SIZE)
        return insert_into_tree(root->ptr[str.getSavednum()],v,taller,wordID);
    else
        return false;
}

int m_balanced_binary_tree::insert_into_tree(node* &tmp, wchar_t *v,bool &taller,int wordID)
{
    m_charstring<wchar_t> str(v);
    if (!tmp)
    {
        tmp = new node;
        tmp->LChild = NULL;
        tmp->RChild = NULL;
        tmp->index = EH;
        tmp->value  = str;
        tmp->wordID = wordID;
        tmp->Occur = 0;
        taller = true;
    }
    else
    {
        if (tmp->value == str)
        {
            taller = false;
            return 0;
        }
        if (str < tmp->value)
        {
            if(!insert_into_tree(tmp->LChild,v,taller,wordID))	return 0;
            if (taller)
                switch(tmp->index)
                {
                    case EH:
                        tmp->index = LH;
                        taller = true;
                        break;
                    case RH:
                        tmp->index = EH;
                        taller = false;
                        break;
                    case LH:
                        adjust(tmp,0);
                        taller = false;
                        break;
                }
        }
        else
        {
            if (!insert_into_tree(tmp->RChild,v,taller,wordID)) return 0;
            if (taller)
                switch(tmp->index)
            {
                case EH:
                    tmp->index = RH;
                    taller = true;
                    break;
                case LH:
                    tmp->index = EH;
                    taller = false;
                    break;
                case RH:
                    adjust(tmp,1);
                    taller = false;
                    break;
            }
        }
    }
    return 1;
}

void m_balanced_binary_tree::r_rotate (node *&p)
{
    node *lc = p ->LChild;
    p->LChild = lc->RChild;
    lc->RChild = p;
    p = lc;
}

void m_balanced_binary_tree::l_rotate (node *&p)
{
    node *rc = p->RChild;
    p->RChild = rc->LChild;
    rc->LChild = p;
    p = rc;
}


void m_balanced_binary_tree::adjust (node *&p, int type)
{
    if (type == 0)
    {
        node * lc = p->LChild;
        switch(lc->index)
        {
            case LH:
                p->index = EH;
                lc->index = EH;
                //右旋处理
                r_rotate(p);
                break;
            case RH:
                node *rd = lc->RChild;
                switch (rd->index)
                {
                case EH:
                    p->index = EH;
                    lc->index = EH;
                    break;
                case LH:
                    p->index = RH;
                    lc->index = EH;
                    break;
                case RH:
                    p->index = EH;
                    lc->index = LH;
                    break;
                }
                rd->index = EH;
                l_rotate (p->LChild);
                r_rotate (p);
                break;
        }
    }
    else if (type == 1)
    {
        node *rc = p ->RChild;
        switch (rc->index)
        {
            case RH:
                p->index = EH;
                rc->index = EH;
                l_rotate(p);
                break;
            case EH:
                node * ld = rc->LChild;
                switch (ld->index)
                {
                case EH:
                    p->index = EH;
                    rc->index = EH;
                    break;
                case RH:
                    p->index = LH;
                    rc->index = EH;
                    break;
                case LH:
                    p->index = EH;
                    rc->index = RH;
                    break;
                }
                ld->index = EH;
                r_rotate(p->RChild);
                l_rotate(p);
                break;
        }
    }
}

node* m_balanced_binary_tree::search(m_charstring<wchar_t> str)
{
    node * tmp = root->ptr[str.getSavednum()];
    return search_subtree(str,tmp);
}

node* m_balanced_binary_tree::search_subtree (m_charstring<wchar_t> str, node*tmp)
{
    if (!tmp) return NULL;
    if (tmp->value == str) return tmp;
    else if (tmp->value > str) return search_subtree (str,tmp->LChild);
    else if (tmp->value < str) return search_subtree(str,tmp->RChild);
}
