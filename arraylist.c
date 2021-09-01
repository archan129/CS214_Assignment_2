#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int al_init(arraylist_t *L, size_t length)
{
    L->data = malloc(sizeof(int) * length);
    if (!L->data) return 1;

    L->length = length;
    L->used   = 0;

    return 0;
}

void al_destroy(arraylist_t *L)
{
    free(L->data);
}


int al_append(arraylist_t *L, int item)
{
    if (L->used == L->length) {
	size_t size = L->length * 2;
	int *p = realloc(L->data, sizeof(int) * size);
	if (!p) return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) printf("Increased size to %lu\n", size);
    }

    L->data[L->used] = item;
    ++L->used;

    return 0;
}




int al_remove(arraylist_t *L, int *item)
{
    if (L->used == 0) return 1;

    --L->used;

    if (item) *item = L->data[L->used];

    return 1;
}


int al_insert(arraylist_t *list, int index, int item)
{

    //int bound = list->length; //reallocating space if necessary 
    if(list->used >= list->length || index >= list->length){
       


	if(index >= list->length*2){
		size_t bound = index+1;
		int* p = realloc(list->data, sizeof(int)*bound);
		if (!p){ 
			return 1;
		}

		list->data = p;
		list->length = bound;
        }else{
		size_t bound = list->length * 2;
		int* p = realloc(list->data, sizeof(int) * bound);

		if (!p){ 
			return 1;
		}

		list->data = p;
		list->length = bound;
		

        }
    }

    if(index <= list->used){ //update used
        list->used++;
    }else if(index > list->used){
        list->used = index+1; 
    }

    int i; //add item at index and shift values
    for(i = list->length-1; i > index; i--){
        list->data[i] = list->data[i-1]; 
    }
    list->data[index] = item;
	return 0;



    
    




}

/*int main(int argc, char* argv[argc + 1]){


	arraylist_t L; 
	al_init(&L, 2);
	al_insert(&L, 0, 1);

	al_insert(&L, 1, 2);

	al_insert(&L, 3, 3);

	al_insert(&L, 10, 4);

	




	for ( int i = 0; i < L.length; i++){
		printf("%d\n", L.data[i]);
	}

	
	return EXIT_SUCCESS;
}*/
