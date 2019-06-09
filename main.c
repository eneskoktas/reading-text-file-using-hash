#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#pragma warning(disable : 4996)
#define _GNU_SOURCE

struct Node {
	float latitude;
	float longitude;
	float temperature;
	int hash_value;
	struct node* next;
	
};

int write_hash(float latitude, float longitude) {    //hash degeri olustur
	float temp;
	temp = latitude * 1e6 + longitude * 1e6;
	int hash;
	hash = ((int)abs(temp)) % 1052;
	return hash;      //hash degerini dondur
}

struct Node* insert(struct Node* root, float latitude, float longitude, float temperature){   //Bagli Listeye eleman ekleme
	if(root == NULL){
	root = (struct Node*) malloc(sizeof(struct Node*));
	root->next = NULL;
	root->latitude=  latitude;
	root->longitude=  longitude;
	root->temperature=  temperature;
	root->hash_value = write_hash(latitude, longitude);
	return root;
}

	struct Node* iter;
	iter = root;
	
	while (iter->next != NULL){
		iter = iter->next;		
	}
	struct Node *temp=(struct Node *) malloc(sizeof(struct Node));
    iter->next=temp;
    temp->longitude=longitude;
    temp->latitude=latitude;
    temp->temperature=temperature;
    temp->hash_value=write_hash(latitude,longitude);
    temp->next = NULL;
    return root;
}

void print_Linked_List(struct Node* root){  //bagli listeyi yazdir
	struct Node* iter;
	iter = root;

	
	while (iter != NULL){
		printf("%d\t%d\t%d\t%d\n", iter->hash_value,iter->latitude,iter->longitude,iter->temperature);
		iter = iter->next;
			
	}	
}

void selection_sort(struct Node*temp){    //bagli listeyi sirala
  
  struct Node*sort_node=NULL,*help=NULL;
  int sort_value;
  while(temp){
    sort_node=temp;
    help=temp->next;
    
    /*Find smallest element*/
    while(help){
        /*compare data*/  
      if(help->hash_value<sort_node->hash_value){
        sort_node=help;
      }
      /*Move next node*/
      help=help->next;
    }
    if(sort_node!=temp){
      /*interchange node data*/
      sort_value=sort_node->hash_value;
      sort_node->hash_value=temp->hash_value;
      temp->hash_value=sort_value;
    }
    /*Move next node*/
    temp=temp->next;
  }
}


struct Node* read_and_write_text() {
	
	char const* const veri = "data.txt"; 
	FILE* file = fopen(veri, "r");    //dosyay ac ve oku
	char line[256];             

	float latitude;
	float longitude;
	float temperature;
	struct Node* root = NULL;

	while (fgets(line, sizeof(line), file)) {

		sscanf_s(line, "%f %f %f", &latitude, &longitude, &temperature);  //satirlari 3 e bolerek oku
		root = insert(root, latitude, longitude, temperature);    //okunan degerleri bagli listeye ekle
	}
	
	fclose(file);     //dosyayý kapat
	return root;
}

int main()
{
	struct Node* root = read_and_write_text();
	print_Linked_List(root);
	printf("--------------------------------------\n---------------------------------------\n");
	selection_sort(root);
	print_Linked_List(root);

	getchar();
	getchar();

	return 0;
}






