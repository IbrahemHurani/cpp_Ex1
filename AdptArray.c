#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
   int sizeArray;
   COPY_FUNC copy;
   DEL_FUNC delete;
   PRINT_FUNC print;
   PElement* pelement;
} AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cFunc, DEL_FUNC dFunc,PRINT_FUNC pFunc)
{
    PAdptArray NewAdpt=(PAdptArray)malloc(sizeof(AdptArray));
    if(NewAdpt==NULL){
        return FAIL;
    }
    NewAdpt->sizeArray=0;
    NewAdpt->copy=cFunc;
    NewAdpt->delete=dFunc;
    NewAdpt->pelement=NULL;
    NewAdpt->print=pFunc;
    return NewAdpt;
}

void DeleteAdptArray(PAdptArray adpt)
{
    if(adpt==NULL){
        return;
    }
    int i;
    for(i=0;i<adpt->sizeArray;i++){
        if((adpt->pelement)[i]!=NULL){
            adpt->delete((adpt->pelement)[i]);
        }
    }
    free(adpt->pelement);
    free(adpt);
    
}

Result SetAdptArrayAt(PAdptArray adpt, int index, PElement newPElement)
{
    if(adpt==NULL||index<0){
        return FAIL;
    }
    if(index>adpt->sizeArray){
        PElement* newPArray=(PElement*)calloc((index+1),sizeof(PElement));
        if(newPArray==NULL){
            return FAIL;
        }
        memcpy(newPArray,adpt->pelement,GetAdptArraySize(adpt)*sizeof(PElement));
        free(adpt->pelement);
        adpt->pelement=newPArray;
        adpt->sizeArray=index+1;
    }
    if((adpt->pelement)[index]!=NULL&&index<adpt->sizeArray){
        adpt->delete((adpt->pelement)[index]);
    }
    (adpt->pelement)[index]=adpt->copy(newPElement);
    return SUCCESS;
    
}

PElement GetAdptArrayAt(PAdptArray adpt, int index)
{
    if(adpt==NULL||(adpt->pelement)[index]==NULL||index<0){
        return NULL;
    }
    PElement temp;
    temp=adpt->copy((adpt->pelement)[index]);
    return temp;
}

int GetAdptArraySize(PAdptArray adpt)
{
    if(adpt==NULL){
        return -1;
    }
    return adpt->sizeArray;
    
}

void PrintDB(PAdptArray adpt)
{
   if(adpt==NULL){
    return;
   }
   int i;
   for(i=0;i<adpt->sizeArray;i++){
    if((adpt->pelement)[i]!=NULL){
        adpt->print((adpt->pelement)[i]);
    }
   }
}