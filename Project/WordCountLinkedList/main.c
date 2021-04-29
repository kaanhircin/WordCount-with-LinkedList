#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct node{
    char kelime[20];
    int adet;
    struct node* next;

}node;
const char* to_convert;

struct node * elemanEkle(struct node *r, char * c[20], int x){

    if(r->adet <x){
        struct node*temp = (struct node*)malloc(sizeof(struct node));
        temp->adet =x;
        strcpy(temp->kelime,c);
        temp->next = r;
        return temp;
    }
    struct node * iter=r;
    while(iter->next!=NULL &&iter->next->adet >x){
        iter=iter->next;
    }
    struct node * temp = (struct node*)malloc(sizeof(struct node));
    temp->next = iter->next;
    iter->next = temp;
    temp->adet = x;
    strcpy(temp->kelime,c);
    return r;
}

struct node * elemanSil(struct node *r, char * c[20]){
    struct node *temp;
    struct node *iter =r;

    if(!strcmp(r->kelime,c)){
        temp = r;
        r = r->next;
        free(temp);

        return r;
    }
    while(iter->next !=NULL && strcmp(iter->next->kelime,c)){
        iter = iter->next;

    }
    if(iter->next ==NULL){

        return r;
    }
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    return r;

}

     struct node * readChar( struct node * r, char * c[20]){
    if(r==NULL){

        r=( struct node* )malloc(sizeof(struct node));
        r->next =NULL;
        r->adet =1;
        strcpy(r->kelime,c);

        return r;
    }
    int flag = 0;
    node * iter = ( struct node *) malloc(sizeof( struct node));
    iter = r;
    while(iter->next != NULL){
        if(!strcmp(iter->kelime,c)){

            flag = 1;
            break;
        }
        iter = iter->next;
    }

    if(!strcmp(iter->kelime,c)){ //Son elemanin kontrolu.

            flag = 1;
        }
    if(flag == 0){//kelime bagli listede yoksa

        iter->next = ( struct node *) malloc(sizeof( struct node));
        iter->next->next =NULL;
        strcpy(iter->next->kelime,c);
        iter->next->adet = 1;
        return r;
    }
    if(flag == 1){// kelime bagli listede varsa

        int kelimeAdeti = iter->adet;
        kelimeAdeti++;

        r = elemanSil(r,c); // kelimeyi bagli listeden siler.
        r = elemanEkle(r,c,kelimeAdeti);
        return r;
    }

}

void bastir(struct node * r){
    while(r!= NULL){
        printf("kelime:%s -> Adeti:%d \n",r->kelime,r->adet);
        r = r->next;
    }
}


int main()
{
    setlocale(LC_ALL,"Turkish");

    struct node * root;
    root = NULL;
    struct FILE *file = fopen("file.txt","r");
    char x[20];

    while (fscanf(file, " %19s", x) == 1) {
        root = readChar(root,x);
    }


    bastir(root);
    fclose(file);




    return 0;
}
