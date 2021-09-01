#include <stdio.h>
#include <stdlib.h>
#include "strbuf.h"
#include <string.h>

#ifndef DEBUG
#define DEBUG 0
#endif

int sb_init(strbuf *L, size_t length)
{
    L->data = malloc(sizeof(char) * length);
    if (!L->data) return 1;

    L->length = length;
    L->used = 0;
    L->data[0] = '\0';

    return 0;
}

void sb_destroy(strbuf *L)
{
    free(L->data);
}


int sb_append(strbuf *L, char item)
{
    if (L->used == L->length) {
	size_t size = L->length * 2;
	char *p = realloc(L->data, sizeof(char) * size);
	if (!p) return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) printf("Increased size to %lu\n", size);
    }



    L->data[L->used] = item;
    L->data[L->used+1] = '\0';
    ++L->used;

    return 0;
}




int sb_remove(strbuf *L, char *item)
{
    if (L->used == 1) return 1;

    --L->used;

    if (item) *item = L->data[L->used]; //check this later

    L->data[L->used+1] = '\0';

    return 1;
}


int sb_insert(strbuf *list, int index, char item)
{

    if(list->used >= list->length || index >= list->length){

	if(index >= list->length*2){
		size_t bound = index+1;
		char* p = realloc(list->data, sizeof(char)*bound);
		if (!p){ 
			return 1;
		}

		list->data = p;
		list->length = bound;
        }else{
		size_t bound = list->length * 2;
		char* p = realloc(list->data, sizeof(char) * bound);

		if (!p){ 
			return 1;
		}

		list->data = p;
		list->length = bound;
        }
    }
	if(index >= list->used){
		list->data[list->used+1] = '\0';
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

int sb_concat(strbuf *sb, char *str){

	size_t fIndex = sb->used + strlen(str)-1;
	 if(fIndex >= sb->length){

		if(fIndex >= sb->length*2){
			size_t bound = fIndex+1;
			char* p = realloc(sb->data, sizeof(char)*bound);
			if (!p){ 
				return 1;
			}

			sb->data = p;
			sb->length = bound;
		}else{
			size_t bound = sb->length * 2;
			char* p = realloc(sb->data, sizeof(char) * bound);

			if (!p){ 
				return 1;
			}

			sb->data = p;
			sb->length = bound;
        }
    }

	

	int mark = sb->used;
	if(sb->data[mark-1] == '\0'){
		mark--;
	}
	
	for(int i = 0; i < strlen(str); i++){
		
		sb->data[mark] = str[i];
		mark++;
	}
	sb->data[mark] = '\0';
	sb->used = mark;

	return 0;
}

/*int main(){


	strbuf L; 
	sb_init(&L, 12);
sb_insert(&L, 0, 'H');
sb_append(&L, 'e');
sb_append(&L, 'l');
sb_append(&L, 'l');
sb_append(&L, 'o');
sb_concat(&L, "abcdefghijklmn");


	




	for ( int i = 0; i < L.length; i++){
		if(L.data[i] == '\0'){
			printf("/0 ");
		}else{
			printf("%c ", L.data[i]);
		}
	}
			printf("\n");

printf("%ld\n", L.length);
printf("%ld\n", L.used);

	
	return EXIT_SUCCESS;
}*/

