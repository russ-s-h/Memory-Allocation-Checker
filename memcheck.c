#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
int memcheck_main();
void print_list();
char *strdup2();
void *memcheck_malloc();
/* linked list structure definition */
struct linked_list_struct {
   char *file;
   int line;
   char *ptr;
   struct linked_list_struct *next;
};

/* initialize the global head pointer */
struct linked_list_struct *list = NULL;

int main() {
   /* run the main function*/
   memcheck_main();
   /* print the remaining items that haven't been freed */
   print_list(list);
   free(list);
   return 0;
}

void *memcheck_calloc(size_t nmemb , size_t size , char *file, int line) {
  /* use a similar method for malloc this time using calloc */
  struct linked_list_struct *new_list_item;
  char *temp;
  /* add an item to the linked list */
  new_list_item = malloc(sizeof(struct linked_list_struct));
  new_list_item->file = strdup2(file);
  new_list_item->line = line;
  new_list_item->next = list;
  new_list_item->ptr = calloc(nmemb,size);
  list = new_list_item;
  temp = new_list_item->ptr;
  return temp;
}

void *memcheck_realloc(void *ptr, size_t size, char *file, int line) {
  struct linked_list_struct **listptr;
  char *temp;
  listptr = &list;
  /* loop through the linked list to see if the ptr matches */
  while (*listptr) {
     if((*listptr)->ptr == ptr) {
        /* update the linked list node with the new information */
        temp = realloc(ptr,size);
        (*listptr)->ptr = temp;
        (*listptr)->file = file;
        (*listptr)->line = line;
        /* return the new pointer */
        return temp;
    }
    else {
        listptr = &((*listptr)->next);
    }
  }
  /* if the pointer is not in the linked list return a new one */
  return memcheck_malloc(size,file,line);
}

void *memcheck_malloc(size_t size, char *file, int line) {
   struct linked_list_struct *new_list_item;
   char *temp;
   /* create a new linked list node with the passed information */
   new_list_item = malloc(sizeof(struct linked_list_struct));
   new_list_item->file = strdup2(file);
   new_list_item->line = line;
   new_list_item->next = list;
   new_list_item->ptr = malloc(size);
   list = new_list_item;
   temp = new_list_item->ptr;
   return temp;
}

void memcheck_free(void *ptr, char *file, int line) {
   /* initialize temp pointers */
   struct linked_list_struct *item;
   struct linked_list_struct **listptr;
   listptr = &list;
   /* loop through each linked list node */
   while (*listptr) {
      /* check if the passed pointer matches the one stored in the node */
      if((*listptr)->ptr == ptr) {
         /* pop that node in the linked list and free the value */
         item = *listptr;
         *listptr = item->next;
         item->next = NULL;
         free(ptr);
         free(item);
         return;
     }
     else {
         listptr = &((*listptr)->next);
     }
   }
   /* if the ptr passed in doesn't exist in the linked list print the error */
   printf("memcheck error:  attempting to free memory address %p in file \"%s\", line %d.\n",(void*)ptr,file,line);
   return;
}

char *strdup2(char *str) {
  /* this is the provided strdup2 function from the blog */
   char *new;
   new = malloc(strlen(str) + 1);
   if (new) {
      strcpy( new , str);
   }
   return new;
}

void print_list(struct linked_list_struct *list) {
   /* loop though the linked list and print the un-freed addresses */
   while (list) {
      printf("memcheck error:  memory address %p which was allocated in file \"%s\", line %d, was never freed\n",list->ptr,list->file,list->line);
      list = list->next;
   }
   return;
}
