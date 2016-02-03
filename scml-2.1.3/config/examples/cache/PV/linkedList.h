// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: Structure for storing cache line info viz. dirty bit, 
//          tag and cache index
//          And implementation of linked list used by cache controller

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
/* Structure for storing cache line info viz. dirty bit, tag and cache index */
typedef struct cacheLineInfo {
    bool dirtyBit;
    int cacheIndex;
    unsigned int tag;
    cacheLineInfo *next, *prev;
}* ptrCacheLineInfo;


/* implementation of linked list used by cache controller */
class linkedList {
public:
    ptrCacheLineInfo head, tail;
    unsigned int listSize, sizeOfset;
    ptrCacheLineInfo* cacheIndexOccupied;

public:
    linkedList() {
        head=NULL;
        tail=NULL;
        listSize = 0;
        sizeOfset = 0;
    }

    ~linkedList() {
        ptrCacheLineInfo tmpNode,currNode;
        tmpNode = head;
        currNode = head;
        while(tmpNode!=NULL) {
            currNode = tmpNode->next;
            delete tmpNode;
            tmpNode = currNode;
        }
        delete[] cacheIndexOccupied;
    }
/* function to initialize index array used to access each cacheLineInfo entry randomly
   called from constructor of cache*/
    void setSizeofSet(unsigned int _sizeOfSet) {
        sizeOfset = _sizeOfSet;
        cacheIndexOccupied = new ptrCacheLineInfo[sizeOfset];
        for(unsigned int loop = 0; loop < sizeOfset; loop++)
            cacheIndexOccupied[loop] = NULL;
    }

/* function to move specified cacheLineInfo entry at end 
   called when a node is accessed*/
    void moveNodeToTail(unsigned int cacheIndexVal) {
        assert(head!=NULL); 
        assert(cacheIndexOccupied[cacheIndexVal]!=NULL);
        ptrCacheLineInfo currNode;
        currNode = cacheIndexOccupied[cacheIndexVal];
        if(currNode->next==NULL) //already at tail
            return;
        else {//node not at tail, move it to tail
            (currNode->next)->prev = currNode->prev;
            if(currNode->prev!=NULL)
                (currNode->prev)->next = currNode->next;
            else head = head->next;
            tail->next = currNode;
            currNode->next = NULL;
            currNode->prev = tail;
            tail = currNode;
        }
    }

/* this function adds a new node at the tail 
 * called when a line is mapped to cache*/
    void addNodeAtTail(bool dirtyBitVal, int cacheIndexVal, unsigned int tagVal) {
        assert(cacheIndexOccupied[cacheIndexVal]==NULL);//cacheIndex not already occupied
        ptrCacheLineInfo newNode = new cacheLineInfo;
        newNode->next = NULL;
        newNode->prev = tail;
        newNode->dirtyBit = dirtyBitVal;
        newNode->cacheIndex = cacheIndexVal;
        newNode->tag = tagVal;
        if(listSize==0)
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
        listSize++;
        cacheIndexOccupied[newNode->cacheIndex] = newNode;
    }

/* this function removes node from the head of linked list 
   called when a line is replaced, head will have least recently used node */
    ptrCacheLineInfo removeNodeFromHead() {
        assert(head!=NULL); //linked list should not be empty, as node will be removed when line replaced
        ptrCacheLineInfo removedNode = head;
        if(head->next!=NULL) {
            (head->next)->prev = NULL;
            head = head->next;
        }
        else
            tail = head = NULL;
        listSize--;
        cacheIndexOccupied[removedNode->cacheIndex] = NULL;
        removedNode->next = NULL;
        return removedNode;
    }

/* returns index of free line in a set or -1 if set is full */
    int getFreeCacheIndex() {
        unsigned int loop;
        if(listSize==sizeOfset) return -1; //set is full
        for(loop = 0; loop < sizeOfset; loop++) 
            if(cacheIndexOccupied[loop]==NULL)
                break;
        return loop;
    }

/* set sepcified cacheIndex in set as dirty */
    void setDirty(unsigned int cacheIndexVal) {
        assert(cacheIndexOccupied[cacheIndexVal]!=NULL);
        cacheIndexOccupied[cacheIndexVal]->dirtyBit = true;
    }

/* returns tag of specified index */
    unsigned int getTag(unsigned int cacheIndexVal) {
        assert(cacheIndexOccupied[cacheIndexVal]!=NULL);
        return cacheIndexOccupied[cacheIndexVal]->tag;
    }
};
#endif /* LINKEDLIST_H */
