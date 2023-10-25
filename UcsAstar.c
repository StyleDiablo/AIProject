#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNODES 30000
#define GOALS 30000

typedef struct node{
	char ar[30];
	int cost;
	struct node* next;
	struct node* parent;
	
}Node;
//FUNCTION DECLARATION
int check(char str[],int N);
void swap (char *x, char *y);
void allchildren(char str[],int N,Node **children);
void print(Node *goals,int N);
int isEmpty(Node** head);
void push(Node** head, char str[], int p);
char* peeks(Node **head);
void pop(Node** head);
Node* newNode(char str[], int p);
void ucs(Node **states,char str[],int N);
int heuristicCost(char str[],int N);
int input();
void A_star(Node **states,char str[],int N);
//MAIN FUNCTION
int main(){
	char *str;
	char str1[30];
	int choice,heu;
	printf("Press 1 to use Uniform Cost Search Algorithm.\n"); 
    printf("Press 2 to use A* Search Algorithm.\n"); 
    printf("Press 3 to exit.\n"); 
	printf("Enter your choice: \n");
	choice = input();
	switch(choice){
		case 1: {
			printf("Enter initial state:\n");
			scanf("%s",str1);
			int L = strlen(str1);
			str = (char*)malloc(L*sizeof(char));
			str = str1;
			int N = strlen(str) * 0.5 ;
			int size = (2*N)+1;
			Node* states= newNode(str,0);
			ucs(&states,str,N);
		}
		case 2:{
			printf("Enter initial state:\n");
			scanf("%s",str1);
			int L = strlen(str1);
			str = (char*)malloc(L*sizeof(char));
			str = str1;
			int N = strlen(str) * 0.5 ;
			int size = (2*N)+1;
			Node* states= newNode(str,0);
			A_star(&states,str,N);
		}
		case 3:{
			printf("Terminated \n");
			return 0;
		}
		default:
			printf("Wrong Input \n");
	}
	return 0;
	
}
int heuristicCost(char str[],int N){
	int cost= 0;
	int first = 0;
	int last = 2*N;
	if(check(str,N)){
			return cost;
		}
	else if(str[2*N] == '-'){
		swap(&str[(2*N)-1],&str[2*N]);
		cost++;
		if(check(str,N)){
			return cost;
		}
	}
	while(!check(str,N)){
		//printf("str is now :%s\n",str);
		while(str[first] != 'A'){
			first++;
			//printf("first is %d\n",first);
		}	
		while(str[last] != 'M'){
			last--;
			//printf("last is %d\n",last);
		}
		//printf("SHOULD BE A-M %c-%c\n",str[first],str[last]);
		swap(&str[first],&str[last]);
		//printf("after swap %s \n",str);
		cost += last-first;
		continue;
	}
	//printf("str is now :%s\n",str);
	return cost;
		

}

//USC CODE
void ucs (Node **states,char str[],int N){
	//INITIALIZE
	Node visited[GOALS] ;
	int adder = 0;
	int j = 0;
	int buffer= 0;
	int nl = 0;
	int terminator = 0;
	Node *goals = newNode("end",30000);
	Node *init = newNode("end",30000);
	Node *temp;
	temp = init;
	int i, checkGoal;
	Node *children;
	Node *buff = newNode("end",30000);
	children = buff;
	push(states,"end",30000);
	int ref= 29999;
	Node *path = newNode(str,ref);
	path->parent = newNode("NULL",ref);
	
	while(1){ 
		//PUT FIRST ITEM OF STATES TO TEMP
		S1:if((*states)->cost == 30000){
			printf("States is empty\n\n");
			break;
		}
		strcpy(temp->ar,(*states)->ar);
		temp->cost = (*states)->cost ;
		pop(states);
		for(i = 0; i <= GOALS; i++){
			if(strcmp(temp->ar,visited[i].ar) == 0){
				goto S1;
			}
			else{
			}
		}
		//CHECK IF TEMP IS GOAL
		checkGoal = check(temp->ar,N);
		if (checkGoal == 1){
			push(&goals,temp->ar,temp->cost); 
			strcpy(visited[adder].ar,temp->ar);
			adder++;
			terminator++;
			if(terminator == (2*N)-2){
				break;
			}
			goto S1;
		}
		//TEMP IS NOT GOAL SO FIND CHILDREN
		else{
			allchildren(temp->ar,N,&children);
			adder++;
			strcpy(visited[adder].ar,temp->ar);
			while(children->cost != 30000){
				if(strlen(children->ar) != (2*N)+1){
					pop(&children);
				}
				for(i = 0; i <= GOALS; i++){
					if(strcmp(children->ar,visited[i].ar) != 0){
						buffer++;
						if(buffer == GOALS){
							push(&path,children->ar,ref);
							path->parent = newNode(temp->ar,ref);
							ref--;
						}
					}
					else {
						break;
					}
				}
				buffer = 0;
				i = 0;
				push(states,children->ar,children->cost + temp->cost);
				pop(&children); 
			}
		}
		goto S1;
		
	}
	
	for(i=0; i<GOALS;i++){
		if(visited[i].cost){
			nl++;
		}
		continue;
	}
	printf("This is the best goal  %s with cost: %d \n",goals->ar,goals->cost);
	/*while(strcmp(path->ar,goals->ar) != 0){
		pop(&path);
	}
	*/
	printf("%d visited\n",nl);
	//printf("%s ~~~>.........~~~>",str);
	//printf("%s ~~~>",path->parent->ar);
	//printf("%s ",goals->ar);
	//printf("Found %d nodes \n",strlen(visited));
	
}




//FIND ALL CHILDREN FROM GIVEN NODE
void allchildren(char str[],int N,Node **children){
	int i,j,z,k,g;
	int error;
	int tester1,tester2;
	int adder=0;
	for (i=0; i <= 2*N; i++){
		if (str[i] == '-'){
			error = str[i-N]; // return >0 only if it actually exits in they array
			if(error <= 0){
				for(j= 0 ; j<=(N+i); j++){
					if(j==i){
						continue;
					}
					swap(&str[i],&str[j]);
					push(children,str,abs(j-i));
					swap(&str[j],&str[i]);
					adder += 1;
					//printf("%dnd time passed 1st case :%s\n",j,(*children)->ar);
				}
			}
			else{
				for(k= (i-N); k <= 2*N; k++){
					if(i==k){
						continue;
					}
					swap(&str[i],&str[k]);
					push(children,str,abs(k-i));
					swap(&str[k],&str[i]);
					adder += 1;
					//printf("%dnd time passed 1st case :%s\n",k,(*children)->ar);
				}
			}
		}
		else{
		}
	}
}

void A_star(Node **states,char str[],int N){
	//INITIALIZE
	Node visited[GOALS] ;
	int adder = 0;
	int j = 0;
	int buffer= 0;
	int heur= 0;
	int nl = 0;
	int terminator= 0;
	Node *goals = newNode("end",30000);
	Node *init = newNode("end",30000);
	Node *temp;
	temp = init;
	int i, checkGoal;
	Node *children;
	Node *buff = newNode("end",30000);
	children = buff;
	push(states,"end",30000);
	int ref= 29999;
	Node *path = newNode(str,ref);
	path->parent = newNode("NULL",ref);
	
	while(1){ 
		//PUT FIRST ITEM OF STATES TO TEMP
		S1:if((*states)->cost == 30000){
			printf("States is empty\n\n");
			break;
		}
		strcpy(temp->ar,(*states)->ar);
		temp->cost = (*states)->cost ;
		pop(states);
		for(i = 0; i <= GOALS; i++){
			if(strcmp(temp->ar,visited[i].ar) == 0){
				goto S1;
			}
		}
		//CHECK IF TEMP IS GOAL
		checkGoal = check(temp->ar,N);
		if (checkGoal == 1){
			push(&goals,temp->ar,temp->cost); 
			strcpy(visited[adder].ar,temp->ar);
			adder++;
			terminator++;
			if(terminator == ((2*N)-2)){
				break;
			}
			goto S1;
		}
		//TEMP IS NOT GOAL SO FIND CHILDREN
		else{
			allchildren(temp->ar,N,&children);
			adder++;
			strcpy(visited[adder].ar,temp->ar);
			while(children->cost != 30000){
				if(strlen(children->ar) != (2*N)+1){
					pop(&children);
					continue;
				}
				for(i = 0; i <= GOALS; i++){
					if(strcmp(children->ar,visited[i].ar) != 0){
						buffer++;
						if(buffer == GOALS){
							push(&path,children->ar,ref);
							path->parent = newNode(temp->ar,ref);
							ref--;
						}
					}
					else {
						break;
					}
				}
				buffer = 0;
				i = 0;
				heur = heuristicCost(children->ar,N);
				push(states,children->ar,heur + children->cost +temp->cost );
				pop(&children); 
			}
		}
		goto S1;
		
	}
	
	for(i=0; i<GOALS;i++){
		if(visited[i].cost ){
			nl++;
		}
		continue;
	}
	printf("%d visited\n",nl);
	//while(strcmp(path->ar,goals->ar) != 0){
	//	pop(&path);
	//}
//	printf("%s ~~~>.........~~~>",str);
	//printf("%s ~~~>",path->parent->ar);
	//printf("%s ",goals->ar);
	//printf("Found %d nodes \n",strlen(visited));
	
}


//swap 2 chars 
void swap(char *x, char *y){
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
	
	return;
}
//Check if given array fulfills our goal requirments and returns 1 if so

int check(char str[],int N){
	int i,j,buf,flag;
	buf = 0;
	flag = 0;
	//printf("%s\n",str);
	if (str[2*N] != 'A'){
		return 0;
	}
	for (i=0; i<2*N; i++){
		if(str[i] == 'M' || str[i] == '-'){
			buf += 1;
			if (str[i] == '-'){
				flag = 1;
			}
			if(buf == (N) && flag == 1){
				if(str[N] ==  'M'){
					return 1;
				}
				else{
					return 0;
				}
			}
			if(buf == N && flag == 0){
				return 1;
			}
		}
		else{
			return 0;
		}					
	} 
}

/*
int check(char str[],int N){
int buf,buf2,i,j;
printf("%s\n",str);
buf = 0;
buf2 = 0;
for (i =0; i<N; i++){
	if (str[i] != 'A' && str[2*N] == 'A'){
		buf += 1;
		if(buf <= N){
			if(str[N]== '-' || str[N]=='M'){
				return 1;
			}
			else if(str[N] == 'A'){
				for(j = N; j< 2*N; j++){
					buf2++;
					if (buf2 > N){
						if(str[j]== 'M'){
							return 0;
						}
						else if(str[j] == '-'){
							return 1;
						}
					}
					else{
						return 0;
					}
				}
			}
			else{
				return 0;
			}
		}
		else{
			//printf("hi\n");
			continue;
		}
	}
	else{
		return 0;
	}
}
}
*/
// Function to Create A New Node 
Node* newNode(char str[], int p) 
{ 
    Node *temp= (Node*)malloc(sizeof(Node));
    strcpy(temp->ar,str);
    temp->cost = p; 		
    temp->next = NULL; 
  
    return temp; 
} 
 // return char of head node
 char* peeks(Node **head){
 	return 	(*head)->ar;
 }
 //remove head 
 void pop(Node** head) 
{ 
	
    Node *temp = *head; 
    (*head) = (*head)->next;
	free(temp); 
} 

//add node to list
void push(Node** head, char str[], int p) 
{ 
	Node *start = *head; 

	Node *temp = newNode(str, p); 

    
    if((*head)->cost > p){
    	temp->next = *head;
		(*head) = temp; 
	}
	else{
		while(start->next !=NULL && start->next->cost <p){
			start = start->next;
		}
		temp->next = start->next;
		start->next = temp;
	}
	
}
//check if empty 
int isEmpty(Node** head) 
{ 
    return (*head) == NULL; 
} 

int input() 
{ 
    int number; 
    scanf("%d", &number); 
    return (number); 
} 
  

