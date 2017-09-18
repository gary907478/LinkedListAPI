/*
 * CIS2750 F2017
 * Assignment 0
 * Jianning Zhang 0886809
 * This file contains the implementation of the linked List API
 * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, whcih I took
 * in the fall of 2016 with professor Fangju Wang.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by
 * my current CIS2750 professor, Denis Nikitenko.
 */
#include "LinkedListAPI.h"

/*
funciton to initialize the list metadata head with the appropriate function pointers.
 */
List initializeList(char *(*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first, const void *second))
{
   List list;
   list.head = NULL;
   list.tail = NULL;
   list.printData = printFunction;
   list.deleteData = deleteFunction;
   list.compare = compareFunction;
   return list;
}

/*
function for creating a node for the linked list.
 */
Node* initializeNode(void *data)
{
   Node* node = malloc(sizeof(Node));
   node->previous = NULL;
   node->next = NULL;
   node->data = data;
   return node;
}

/*
inserts a node at the front of a linked list
 */
void insertFront(List *list, void *toBeAdded)
{
    if (list == NULL) {
        return;
    }
    Node* node = initializeNode(toBeAdded);
    if(list->head == NULL||list->tail == NULL){
        list->head = node;
        list->tail = node;
    }
    else{
       list->head->previous = node;
       node->next = list->head;
       list->head = node;
    }
}

/*
inserts a node at the back of a linked list.
 */
void insertBack(List *list, void *toBeAdded)
{
    if (list == NULL) {
        return;
    }
    Node* tail = initializeNode(toBeAdded);
    if(list->head == NULL||list->tail == NULL){
        list->head = tail;
        list->tail = tail;
    }
    else{
        tail->previous = list->tail;
        list->tail->next = tail;
        list->tail = tail;
    }
}

/*
clear the contents linked list, freeing all memory asspociated with these contents.
 */
void clearList(List *list)
{
    if (list == NULL) {
        return;
    }
    if(list->head == NULL||list->tail == NULL)
       return;
    else if(list->head->next == NULL){
       list->deleteData(list->head->data);
       free(list->head);
    }
    else{
       while (list->tail->previous!=NULL){
           Node* node = list->tail;
           list->tail = node->previous;
           list->tail->next = NULL;
           list->deleteData(node->data) ;
           free(node);
       }
       list->deleteData(list->head->data);
       free(list->head);
    }
    list->head = NULL;
    list->tail = NULL;
}

/*
uses the comparison function pointer to place the element in the appropriate position in the list.
 */
void insertSorted(List *list, void *toBeAdded)
{
    if (list == NULL) {
        return;
    }
    Node* node = initializeNode(toBeAdded);
    if(list->head == NULL||list->tail == NULL){
        list->head = node;
        list->tail = node;
    }
    else if(list->head->next == NULL)
    {
        insertBack(list, node);
    }
    else{
        Node* listNode = list->head;
        int comper = list->compare(list->head,list->tail) ;
        while(node->next != NULL){
            if(comper == list->compare(listNode, node))
                listNode = listNode->next;
            else {
                node->next = listNode;
                node->previous = listNode->previous;
                listNode->previous->next = node;
                listNode->previous = node;
                break;
            }
        }
    }
}

/*
remove data from the list, deletes the node and frees the memory
 */
void* deleteDataFromList(List *list, void *toBeDeleted)
{
    if (list == NULL) {
        return NULL;
    }

    if(list->head == NULL||list->tail == NULL)
        return NULL;

    Node* listNode = list->head;
    while(listNode != NULL){
        if(listNode->data == toBeDeleted ){
            if( listNode->previous != NULL) {
                listNode->previous->next = listNode->next;
            }

            if( listNode->next != NULL ) {
                listNode->next->previous = listNode->previous;
            }
            void* data = listNode->data;
            free(listNode);
            return data;
        }
        listNode = listNode->next;
    }
    return NULL;
}

/*
return a pointer to the data at the front of the list.
 */
void* getFromFront(List list)
{
    if(list.head == NULL||list.tail == NULL)
        return NULL;
    return list.head->data;
}

/*
returns a pointer to the data at the back of the list.
 */
void* getFromBack(List list)
{
    if(list.head == NULL||list.tail == NULL)
        return NULL;
    return list.tail->data;
}

/*
returns a string that contains a string representation of
the list traversed from  head to tail.
 */
char* toString(List list)
{
    if(list.head == NULL||list.tail == NULL)
        return NULL;
    Node* listNode = list.head;
    int curSize = 256;
    char* str = malloc(sizeof(char) * 256);
    str[0]='\0';
    while(listNode != NULL) {
        if( strlen(str) > curSize ) {
            char* oldStr = str;
            str = malloc(sizeof(char) * curSize * 2);
            curSize = curSize * 2;
            strcpy(str, oldStr);
            free(oldStr);
        }
        strcat (str, list.printData(listNode->data));
        listNode = listNode->next;
    }
    return str;
}

/*
function for creating an iterator for the linked list.
 */
ListIterator createIterator(List list)
{
    ListIterator itr;
    itr.current = list.head;
    return itr;

}

/*
function that returns the next element of the list through the iterator.
 */
void* nextElement(ListIterator *iter)
{
    if( iter == NULL || iter->current == NULL ) {
        return NULL;
    }
    else {
       void* data = iter->current->data;
       iter->current = iter->current->next;
       return data;
    }
}
