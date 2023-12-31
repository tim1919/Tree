template <typename myType>
bool List<myType>::initList_SQ(void)
{
    list = (myType *)malloc(sizeof(myType));
    if (list == 0)
        return 0;

    Status = SQ;
    LENGTH = 0;
    SIZE = 1;
    return 1;
}

template <typename myType>
bool List<myType>::initList_link(void)
{
    Header = (listNode*)malloc(sizeof(listNode));//创建一个表头
    
    if (Header == 0)
        return 0;
    Header->next = 0;//初始化表头
    Status = link;
    LENGTH = 0;
    SIZE = 0;
    return 1;
}

template <typename myType>
bool List<myType>::destroyList(void)
{
    if (Status == SQ)
    {
        free(list);
        list = 0;
        SIZE = 0;
        LENGTH = 0;
        return 1;
    }
    else if (Status == link)
    {
        for (int i = 0; i < LENGTH; ++i)
        {
            deleteElem(0);
        }
        free(Header);
        Header = 0;
        SIZE = 0;
        LENGTH = 0;
        return 1;
    }
}


template <typename myType>
bool List<myType>::clearList(void)
{
    if (Status == SQ)
    {}
    else if (Status == link)
    {
        if (LENGTH == 0)
        {
            return 1;
        }
        else
        {
            listNode* p = Header;
            for (int i = 0; i < LENGTH; ++i)
            {
                p = p->next;
                p->data = 0;
            }
        }
        
    }
}


template <typename myType>
bool List<myType>::isEmpty(void)
{
    if (LENGTH == 0)
        return 1;
    else
        return 0;
}

template <typename myType>
int List<myType>::length(void)
{
    return LENGTH;
}

template <typename myType>
myType List<myType>::getElem(int i)
{
    if (i < 0 || i >= LENGTH)
    {
        return 0;
    }
    else
    {
        if (Status == SQ)
        {
            return list[i];
        }
        else
        {
            listNode* p = Header->next;
            for (int j = 0; j < i; ++j)
            {
                p = p->next;
            }
            return p->data;
        }
    }
}

template <typename myType>
myType List<myType>::priorElem(int i)
{
    if (i <= 0 || i >= LENGTH)
    {
        return 0;
    }
    else
    {
        return getElem(i - 1);
    }
}


template <typename myType>
bool List<myType>::insertElem(int i, myType elem)
{
    if (i < 0 || i > LENGTH)
    {
        std::cout << "Out of scope!" << std::endl;
        return 0;
    }

    if (Status == SQ)
    {
        if (SIZE == LENGTH)
        {
            list = (myType*)realloc(list, 2 * SIZE * sizeof(myType));
            SIZE *= 2;
        }

        for (int j = LENGTH - 1; j >= i; --j)
        {
            list[j + 1] = list[j];
        }

        list[i] = elem;

    }
    else if (Status == link)
    {
        listNode* p = Header;
        for (int j = 0; j < i; ++j)
        {
            p = p->next;
        }
        listNode* tmp = (listNode*)malloc(sizeof(listNode));
        tmp->data = elem;
        if (i == LENGTH - 1)
        {
            tmp->next = 0;
        }
        else
        {
            tmp->next = p->next;//有问题
        }
        p->next = tmp;
        ++SIZE;
        ++LENGTH;
        return 1;
    }


    LENGTH++;
    return 1;
}

template <typename myType>
bool List<myType>::deleteElem(int i)
{
    if (i < 0 || i >= LENGTH)
    {
        std::cout << "Out of scope!" << std::endl;
        return 0;
    }

    if (Status == SQ)
    {
        for (int j = i; j < LENGTH - 1; ++j)
        {
            list[j] = list[j + 1];
        }
        --LENGTH;
        return 1;
    }
    else if (Status == link)
    {
        listNode* p = Header;
        for (int k = 0; k < i; ++k)
        {
            p = p->next;
        }
        listNode* tmp = p->next;
        p->next = p->next->next;
        free(tmp);
        tmp = 0;
        --SIZE;
        --LENGTH;
        return 1;
    }
}

