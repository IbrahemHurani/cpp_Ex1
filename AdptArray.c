#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    COPY_FUNC cFunc;
    DEL_FUNC dFunc;
    PRINT_FUNC pFunc;
    int sizeArray;
    PElement *plementArray;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cFunc2, DEL_FUNC dFunc2 ,PRINT_FUNC pFunc2){
    PAdptArray adptArr;
    adptArr=(PAdptArray)malloc(sizeof(AdptArray));
    if(adptArr==NULL){
        return NULL;
    }
    adptArr->sizeArray=0;
    adptArr->plementArray=NULL;
    adptArr->cFunc=cFunc2;
    adptArr->dFunc=dFunc2;
    adptArr->pFunc=pFunc2;
    return adptArr;

}
void DeleteAdptArray(PAdptArray adptArr){
    int i;
    if(adptArr->plementArray==NULL){
        return ;
    }
    for(i=0;i<adptArr->sizeArray;i++){
        if(adptArr->plementArray[i]!=NULL){
            adptArr->dFunc((adptArr->plementArray)[i]);
        }
    }
    free(adptArr->plementArray);
    free(adptArr);
        


}

Result SetAdptArrayAt(PAdptArray adptArr, int index, PElement pel)
{
    PElement *newPel;
    if(adptArr==NULL||index<0){
        return FAIL;
    }
    if(adptArr->plementArray[index]!=NULL&&index<adptArr->sizeArray){
        adptArr->dFunc((adptArr->plementArray)[index]);
        (adptArr->plementArray)[index]=adptArr->cFunc(pel);
        return SUCCESS;

    }
    if(index>=adptArr->sizeArray){
        newPel=(PElement*)calloc((index+1),sizeof(PElement));
        if(newPel==NULL){
            return FAIL;
        }
        memcpy(newPel,adptArr->plementArray,(adptArr->sizeArray)*sizeof(PElement));
        if(adptArr->plementArray!=NULL){
            free(adptArr->plementArray);
        }
        adptArr->plementArray=newPel;
        adptArr->sizeArray=index+1;
        return SUCCESS;

        }
    return FAIL;
       
}



PElement GetAdptArrayAt(PAdptArray adptArray, int index){
    if(adptArray==NULL||(adptArray->plementArray)[index]==NULL){
        return NULL;
    }
   return adptArray->cFunc((adptArray->plementArray)[index]);

}
int GetAdptArraySize(PAdptArray adptArray){
    if(adptArray==NULL||adptArray->plementArray==NULL){
        return -1;
    }
    return adptArray->sizeArray;


}
void PrintDB(PAdptArray adptArray){
    if(adptArray==NULL||adptArray->plementArray==NULL){
        return ;
    }
    int i;
    for(i=0;i<adptArray->sizeArray;i++){
        adptArray->pFunc((adptArray->plementArray)[i]);
    }


}