/* This is a program which shows how Double Linked Lists work. By any means
it's supposed to be perfect, I mean, I did it, and I am not perfect. I did not
take a lot of time to do it, yet I did it with risponsibility even though I am
still learning the C programming language. Struct nodo contains some primitive
data types in order to show how to work with the most common ones. The program
main loop is in the main function, where the user is prompted to select a
choice from the menu in order to start to work with the Double Linked List.
Each function describes itself. I hope this program will be useful for you and
if you find a mistake (something that might happen) do not hestitate to contact
me, I will be willing to correct it, or else, why don't you correct it and send
the program back to me?
If you liked the program and believe it is clear please send me an email stating
it, I will feel happy!!
If you did not like the program I will be willing to know why and to improve it,
but please try not to be rude...
My name is Nicolas Raitman and I am from Argentina
E-Mail:	elrancha@hotmail.com
*/
#include <stdio.h>
#include <stdlib.h>
/* Constants */
#define EXIT_OK
/* Macros */
#define CHOICE(answer)\
printf("\nChoice: ");\
scanf("%i", &answer);
struct nodo
{
	int 	nclient; 	/* primary key of the "record" */
	char    name[40];       /* name */
	float	total;          /* how much this client owes us */
	struct	nodo * next;    /* pointer to the next struct */
	struct	nodo * prev;	/* pointer to the previous struct */
};
/* Functions */
void AddClient 		(struct nodo ** list);
void Exit       	(struct nodo ** list);
void SeeAll		(struct nodo ** list);
void OneByOne		(struct nodo ** list);
void Search		(struct nodo ** list);
void Delete		(struct nodo ** list);
void FreeAll		(struct nodo ** list);
void Flush2File		(struct nodo ** list);
void ReadFile		(struct nodo ** list);
void Money		(struct nodo ** list);
void CalcTotal		(struct nodo ** list);
void HighestTotal       (struct nodo ** list);
void LowestTotal	(struct nodo ** list);
void Average		(struct nodo ** list);
void AddBegin		(struct nodo ** list, struct nodo * add);
void AddEnd		(struct nodo ** list, struct nodo * add);
void AddBetween		(struct nodo ** list, struct nodo * add);
int NumberExists	(struct nodo ** list, int number);
void ShowData		(struct nodo * data);
int  StrCompare		(char * s1, char * s2);
void ErrorOpeningFile 	(void);
int main (void)
{
	struct nodo * list = NULL; 	/* list will be a pointer to the first
					node of the linked list */
	int	choice;
	do
	{
		clrscr();
		textcolor (4);
		cputs ("\nDouble Linked Lists - Nicolas Raitman");
		textcolor (7);
		puts("\n\n0 - Exit");
		puts("1 - New Item");
		puts("2 - See All Items in the Linked List");
		puts("3 - Show Items One by One");
		puts("4 - Search Item");
		puts("5 - Delete Item");
		puts("6 - Delete Entire List");
		puts("7 - Money");
		puts("8 - Flush Linked List to File");
		puts("9 - Read File and Create Linked List");
		CHOICE (choice);
		switch (choice)
		{
			case 0:	Exit(&list); break;
			case 1: AddClient(&list); break;
			case 2: SeeAll(&list); break;
			case 3: OneByOne(&list); break;
			case 4: Search(&list); break;
			case 5: Delete(&list); break;
			case 6: FreeAll(&list); break;
			case 7: Money (&list); break;
			case 8: Flush2File(&list); break;
			case 9: ReadFile(&list); break;
			default: break;
		}
	} while (choice != 0);
	return EXIT_OK;
}
void ReadFile (struct nodo ** list)
{
	/* creates a new linked list from data in 'dlist.bin'
	deleting all repeated entries, filtering by nodo->nclient */
	struct nodo * aux = NULL;
	FILE	* fp;
	int	sizenodo = sizeof(struct nodo);
	/* first we make sure to free all the memory used by the list
	since we are going to create a new one */
	FreeAll (list);
	*list = NULL;
	if ((fp = fopen("dlist.bin", "rb")) == NULL)
	{
		ErrorOpeningFile();
		return;
	}
	/* we read the first record on the file and we add it to the
	beginning of the list */
	aux = (struct nodo *) malloc (sizenodo);
	fread(aux, sizenodo, 1, fp);
	AddBegin (list, aux);
	/* we do the loop while we are not in the end of file */
	while (!feof(fp))
	{
		aux = (struct nodo *) malloc (sizeof(struct nodo));
		if(fread(aux, sizenodo, 1, fp))
		{
			/* if nclient does not exist in our list then
			we add the node to the list */
			if (!NumberExists(list, aux->nclient))
				AddBetween(list, aux);
			else
				/* since I did not add the item to the list
				I free the memory used by it */
				free (aux);
		}
	}
	free (aux);
	printf("Data was read from \'dlist.bin\' and Double Linked List was created.\nPress any key to continue...");
	getch();
}
void ErrorOpeningFile (void)
{
	/* it shows a message stating that the file could not be opened*/
	printf("\nError while opening file.");
	getch();
}
int NumberExists (struct nodo ** list, int number)
{
	/* searches for number in all act->nclient, and if it finds
	any match it return 1, else it returns 0 */
	struct nodo * act = NULL;
	act = *list;
	while (act)
	{
		if (act->nclient == number)
			return 1;
		act = act->next;
	}
	/* if we reach this point then no match was found */
	return 0;
}
void Flush2File (struct nodo ** list)
{
	/* flushes all the items in the linked list into a file */
	struct nodo * act = NULL;
	FILE	* fp;
	int	choice;
	if (! *list)
		return;
	act = *list;
	printf("\n\n1 - New File");
	printf("\n2 - Append Data");
	CHOICE (choice);
	if (choice == 1)
	{
		/* we delete all the contents of the file and open it to write */
		if ((fp = fopen("dlist.bin", "wb")) == NULL)
		{
			ErrorOpeningFile();
			return;
		}
	}
	else
	{
		/* we open the file to append data */
		if ((fp = fopen("dlist.bin", "ab")) == NULL)
		{
			ErrorOpeningFile();
			return;
		}
	}
	/* while we have a node pointing to a differnt address than NULL... */
	while (act)
	{
		/* now we write into the file each node of the linked list */
		fwrite (act, sizeof (struct nodo), 1, fp);
		act = act->next;
	}
	fclose(fp);
	printf("\n\nData was flushed into \'dlist.bin\'. Press any key to continue...");
	getch();
}
void Money (struct nodo ** list)
{
	/* this function shows a loop and it calls different functions to
	perform several calculation with the field "total" in the struct
	Not a big deal, just to show basic arithmetic calculations. Most
	of the functions that are called are described by its name */
	int choice;
	if (! *list)
	{
		printf("\nEmpty List. No calculations can be performed.");
		getch();
		return;
	}
	do
	{
		puts("\n0 - Exit");
		puts("1 - Calculate Total");
		puts("2 - Highest Total");
		puts("3 - Lowest Total");
		puts("4 - Average Total");
		CHOICE(choice);
		switch (choice)
		{
			case 0: break;
			case 1: CalcTotal(list); break;
			case 2: HighestTotal(list); break;
			case 3: LowestTotal(list); break;
			case 4: Average(list); break;
			default: break;
		}
	} while (choice != 0);
}
void Average (struct nodo ** list)
{
	/* calculates the average of all the act->total for each node in the
	linked list */
	struct nodo * act = NULL;
	int	count = 0;
	float	total = 0, average;
	act = *list;
	while (act)
	{
		total += act->total;
		count++;
		act = act->next;
	}
	average = total / count;
	printf ("\nAverage = %.2f\n", average);
}
void LowestTotal (struct nodo ** list)
{
	struct nodo * act = NULL, * lowest = NULL;
	act = *list;
	lowest = *list;
	while (act)
	{
		if (act->total < lowest->total)
			lowest = act;
		act = act->next;
	}
	ShowData(lowest);
}
void HighestTotal (struct nodo ** list)
{
	struct nodo * act = NULL, * highest = NULL;
	act = *list;
	highest = *list;
	while (act)
	{
		if (act->total > highest->total)
			highest = act;
		act = act->next;
	}
	ShowData(highest);
}
void CalcTotal (struct nodo ** list)
{
	struct nodo * act = NULL;
	float	total = 0;
	act = *list;
	while (act)
	{
		total += act->total;
		act = act->next;
	}
	printf("\nTotal = %.2f\n", total);
}
void Delete (struct nodo ** list)
{
	/* this functions deletes a specific node in the list */
	struct nodo * act = NULL, * prev = NULL;
	int number;
	if (! *list)
		return;
	act = *list;
	prev = *list;
	printf("\nNumber to Delete: "); scanf("%i", &number);
	while (act)
	{
		/* we search until we find a the same number */
		if (act->nclient == number)
		{
			if (prev == act)
			{
				/* if trying to delete the first node
				then the beginning of the list will be the
				address of the next struct... */
				*list = act->next;
				/* so we assign a NULL address to the prev
				field of the next struct */
				act->next->prev = NULL;
			}
			else
			{
				/* this is easy to understand... just
				reordering the pointers to the next and
				previous structures since we deleted one */
				prev->next = act->next;
				act->next->prev = prev;
			}
			free (act);
			printf("\nItem Deleted. Press Any Key.");
			getch();
		}
		prev = act;
		act = act->next;
	}
}
int StrCompare (char * s1, char * s2)
{
	/* if the string are equal return 1, otherwise return 0
	just trying to implement something similar to strcmp */
	int cont, lens1, lens2, different;
	lens1 = strlen(s1);
	lens2 = strlen(s2);
	for (cont = 0, different = 1; (cont < lens1) && (cont < lens2); cont++)
		if ( (*(s1 + cont)) != (*(s2 + cont)) )
			/* if I found one different character they are not equal */
			different = 0;
	return different;
}
void Search (struct nodo ** list)
{
	/* this function searches for either a number of a client or for
	its name. We present a menu until the user exits the loop */
	struct nodo * act = NULL;
	int	choice, number, foundit = 0;
	char	name[40];
	if (! *list)
		return;
	do
	{
		act = *list;
		puts("\n\n0 - Exit");
		puts("1 - Search By Name");
		puts("2 - Search By Number");
		CHOICE(choice);
		switch (choice)
		{
			case 1:
				printf("\Name: "); scanf("%s", name);
				while (act)
				{
					if (StrCompare(name, act->name))
					{
						foundit = 1;
						break;
					}
					act = act->next;
				}
				if (foundit)
				{
					printf("\n\tFound it!");
					ShowData(act);
				}
				break;
			case 2:
				printf("\nSearch Number: "); scanf("%i", &number);
				while (act)
				{
					if (act->nclient == number)
					{
						foundit = 1;
						break;
					}
					act = act->next;
				}
				if (foundit)
				{
					printf("\n\tFound it!");
					ShowData(act);
				}
				else
					printf("\n\n\tNo Data was found");
				break;
			default:
				break;
		}
	} while (choice != 0);
}
void OneByOne (struct nodo ** list)
{
	/* this is my favourite function! When this function is called for the
	first time, the first node of the list is shown. Then the user has the
	possibility to look at the next, the previous, the last and the first
	*/
	struct nodo * act = NULL;
	int choice;
	if (! *list)
	{
		printf("\nEmpty List.");
		return;
	}
	act = *list;
	ShowData(act);
	do
	{
		printf("\n\n0 - Exit");
		printf("\n1 - Next");
		printf("\n2 - Previous");
		printf("\n3 - First");
		printf("\n4 - Last");
		CHOICE(choice);
		switch (choice)
		{
			case 0: break;
			case 1:
				if (!act->next)
					/* if we have a NULL address in
					act->next then we are looking at the
					last one */
					printf ("\t\tNo more entries.");
				else
				{
					/* we point to the address of the next
					structure and show it */
					act = act->next;
					ShowData(act);
				}
				break;
			case 2:
				if (!act->prev)
					/* if act->prev == NULL then we are
					showing the first one */
					printf("\t\tNo previous entries.");
				else
				{
					/* we point to address of the previous
					structure */
					act = act->prev;
					ShowData(act);
				}
				break;
			case 3:
				/* to show the first item */
				while (act->prev)
					act = act->prev;
				ShowData(act);
				break;
			case 4:
				/* to show the last item */
				while (act->next)
					act = act->next;
				ShowData(act);
				break;
			default:
				printf("Invalid Choice");
				break;
		}
	} while (choice != 0);
}
void ShowData (struct nodo * data)
{
	printf("\n\n\tNumber:\t\t%i", data->nclient);
	printf("\n\tName:\t\t%s", data->name);
	printf("\n\tTotal:\t\t%.2f", data->total);
}
void SeeAll (struct nodo ** list)
{
	struct nodo * act = NULL;
	int	itemshown = 0;
	if (! *list)
	{
		printf("\nNo Data to Show. Empty List.");
		getch();
		return;
	}
	act = *list;
	while (act)
	{
		if (itemshown == 5)
		{
			/* since no more than 5 items can be shown on screen
			we hold until the user presses a key */
			itemshown = 0;
			printf("\nPress any key to continue...");
			getch();
		}
		itemshown++;
		ShowData(act);
		act = act->next;
	}
	printf("\n\nPress any key to continue..."); getch();
}
void AddClient (struct nodo ** list)
{
	/* this functions adds a new node to the linked list. The node can
	be added at the beginning, at the end or ordered by number */
	struct nodo * aux = NULL;
	char	temp[40];
	int	number, choice;
	aux = (struct nodo *) malloc (sizeof (struct nodo));
	if (aux)
	{
		/* we ask for the information about the new client */
		printf("\nNumber: "); scanf("%i", &(aux->nclient));
		printf("Name: "); scanf("%s", aux->name);
		printf("Total: "); scanf("%f", &(aux->total));
		if (! *list)
		{
			/* we are creating the list. There are neither previous
			nor nexts. So, we have to specify it by assigning NULL
			to those addresses */
			*list = aux;
			aux->next = NULL;
			aux->prev = NULL;
		}
		else
		{
			puts("\n0 - Cancel");
			puts("1 - Add at the beginning.");
			puts("2 - Add at the end.");
			puts("3 - Add ordered");
			CHOICE(choice);
			switch (choice)
			{
				case 0: free(aux); break;
				case 1: AddBegin(list, aux); break;
				case 2: AddEnd(list, aux); break;
				case 3: AddBetween(list, aux); break;
				default: break;
			}
		}
	}
	else
	{
		puts ("Memory unavailable.");
		getch();
	}
}
void AddEnd (struct nodo ** list, struct nodo * add)
{
	/* we will be adding "add" to the end of "list" */
	struct nodo * prev = NULL, * act = NULL;
	act = *list;
	/* we serch for the last node in the list */
	while (act)
	{
		prev = act;
		act = act->next;
	}
	/* easy to understand... */
	prev->next = add; /* the previous node addressing to the next will be addressing to add */
	add->next = NULL; /* the one we are adding addressing to next will be addressing NULL, since it's the last one */
	add->prev = prev; /* finally, the one we are adding addressing the previous one will address prev */
}
void AddBegin (struct nodo ** list, struct  nodo * add)
{
	/* Add a new node to the beginning of the list */
	struct nodo * act = NULL;
	act = *list;
	act->prev = add;
	add->prev = NULL; /* since it's the first one then there are not any previous one */
	add->next = act;
	*list = add;
}
void AddBetween (struct nodo ** list, struct nodo * add)
{
	struct nodo * act = NULL, * prev = NULL;
	/* this function will add the item in the linked list
	according to nodo->nclient. This function will never create the
	list, since all the functions that call this one, check if they
	have to create the list. The function can add items at the beginning,
	middle or end of the list. */
	act = *list;
	prev = *list;
	while (act && (act->nclient <= add->nclient))
	{
		prev = act;
		act = act->next;
	}
	if (! act)
		AddEnd (list, add);
	else if (prev == act)
		AddBegin (list, add);
	else
	{
		/* once again we rearrange pointers. Easy to get the idea
		if you look at the names */
		prev->next = add;
		add->next = act;
		add->prev = prev;
		act->prev = add;
	}
}
void Exit (struct nodo ** list)
{
	FreeAll (list);
}
void FreeAll (struct nodo ** list)
{
	/* we free the memory allocated for each struct */
	struct nodo * act = NULL, * next = NULL;
	if (! *list)
		return;
	act = *list;
	while (act)
	{
		next = act->next;
		free (act);
		act = next;
	}
	*list = NULL;
}