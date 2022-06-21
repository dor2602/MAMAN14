#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include <ctype.h>
#define N 100 // N is the table range
#define h(x) (x % m) //h(x) = x mod m

/* List Struct */
typedef struct Node
{
	int val;
	struct Node* next;
}Node;

/* Tree Struct */
struct node//Tree Struct
{
	int key;
	struct node* left, * right;
};

//Announce all the functions we will use during the program
struct node* InsertWithoutDuplicates(struct node*, int, int*, int*, int*);
struct node* NewNode(int item);
Node* Insert(Node*, int, int);
Node* FillTable(Node*, int*, int, int);
void  PrintFunction(int, int, long int, long int);
void ContingSortArray(int*, int);
void InsertionSort(int*, int);
void Merge(int*, int, int, int, long int*, long int*);
void MergeSort(int*, int, int, long int*, long int*);
void FreeTable(Node**);
void ErrorFunction();
int CheckQentityOfDiffrentElemInList(Node*, int);

/*Main function*/
int main()
{
	int n, choose;
	int* count;
	long int *x, *y, *placements, *comparsions;
	int a = 0, b = 0, c = 0, d = 0, e = 0, placements_for_hash = 0, comparsions_for_hash = 0;
	count = &a;
	x = &b;
	y = &c;
	placements = &d;
	comparsions = &e;
	printf("Please enter the quentity of the elements that you want to insert to the array: ");
	scanf_s("%d", &n);
	printf("\n");
	int* array1 = (int*)malloc(n * sizeof(int));//memory allocation for the array
	if (array1 == NULL)
	{
		ErrorFunction();
		exit(1);
	}
	Node* table = (Node*)malloc(N * sizeof(Node));
	if (table == NULL)
	{
		ErrorFunction();
		free(array1);
		exit(1);
	}
	struct node* root = NULL;
	srand(time(NULL));
	for (int i = 0; i < n; i++)//random value to all a[i] ,the random is between 1 to 100
		array1[i] = rand() % 100 + 1;
	printf("Hello again user,now please choose an algorithm:\n\n");
	printf(" ***For Insertion Sort algorithm type '1'***\n ***For Merge Sort algorithm type '2'***\n");
	printf(" ***for C array of Counting Sort type '3'***\n ***For Hash Table type '4'***\n ***For BTS type '5'***\n ***For Exit type '6'***\n");
	scanf_s("%d", &choose);
	while (choose != 6)
	{
	    if(choose == 1)
			InsertionSort(array1, n);
		else if (choose == 2)
		{
			MergeSort(array1, 0, n, comparsions, placements);
			count = NumberOfDiffrentElements(array1, n);
			PrintFunction(n, count, *comparsions, *placements);
		}
		else if (choose == 3)
			ContingSortArray(array1, n);
		else if (choose == 4)
		{
			Node* table = (Node*)malloc(N * sizeof(Node));
			if (table == NULL)
			{
				ErrorFunction();
				free(array1);
				exit(1);
			}
			for (int i = 0; i < N; i++)//initallize all linked lists
			{
				table[i].next = NULL;
				placements_for_hash++;
			}
			placements_for_hash += n;
			comparsions_for_hash = n;
			table = FillTable(table, array1, N, n);
			count = CheckQentityOfDiffrentElemInList(table, N);
			PrintFunction(n, count, comparsions_for_hash, placements_for_hash);
			free(table);
		}
		else if (choose == 5)
		{
			struct node* root = NULL;
			for (int i = 0; i < n; i++)//insert all the values in the array to the binary tree
				root = InsertWithoutDuplicates(root, array1[i], count, x, y);
			PrintFunction(n, *count, *x, *y);
		}
		else if (choose == 6)
			break;
		printf("***Choose another algorithm if you want to continue, else for exit type 6***\n");
		scanf_s("%d", &choose);
	}
		return 0;
}

void InsertionSort(int arr[], int n)
{
	long int x = 0, y = 0;
	int i, key, j, count = 0;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
			x++;
			y++;
		}
		arr[j + 1] = key;
	}
	count = NumberOfDiffrentElements(arr, n);//call to number_of_diffrent_elements that return the number of the diffrent elements in the input array
	PrintFunction(n, count, x, y);
}
void ContingSortArray(int a[], int n)//y is counting the number of the placement and x the comparisons
{
	int c_array[100], i, x = 0, y = 0, count = 0;
	for (i = 0; i < 100; i++)//this loop initalize all the places in c_array to 0
		c_array[i] = 0;
	for (i = 0; i < n; i++)// in this loop we are transform the elements on the input array to the counting array c_array
	{
		c_array[a[i] - 1]++;
		y++;
	}
	for (i = 0; i < 100; i++)//in this loop we counting the number of the diffrent elements in the array
	{
		x++;
		if (c_array[i] != 0)
			count++;//increase the number of the difrrent elemnts in one
	}
	PrintFunction(n, count, x, y);//print to the user the results of this algorithm
}
int NumberOfDiffrentElements(int a[], int n)//this function get an sorted array and caulculate the number of the diffrent elements in the array, and return this number;
{
	int i, count = 0, j = 0;
	if (n == 0)//check if the given array is not empty
		return count;
	else count++;//increase the counting by one
	for (i = 1; i < n; i++)//lineary loop that check the number of the diffrent elements in the array
		if (a[i] != a[i - 1])
			count++;
	return count;
}

struct node* InsertWithoutDuplicates(struct node* node, int key, int* count, int* x, int* y)
{
	/* If the tree is empty, return a new node */
	if (node == NULL)
	{
		*count = *count + 1;
		return NewNode(key);
	}
	/* Otherwise, recur down the tree */
	*x = *x + 1;
	*y = *y + 1;
	if (key < node->key)
		node->left = InsertWithoutDuplicates(node->left, key, count, x, y);
	else if (key > node->key)
		node->right = InsertWithoutDuplicates(node->right, key, count, x, y);
	else return;
	/* return the (unchanged) node pointer */
	return node;
}
void Merge(int arr[], int l, int m, int r, long int* x, long int* y)
{

	int i, j, k, a = 0, b = 0;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int* L = (int*)malloc(n1 * sizeof(int));
	if (L == NULL)
	{
		ErrorFunction();
		exit(1);
	}
	int* R = (int*)malloc(n2 * sizeof(int));
	if (R == NULL)
	{
		ErrorFunction();
		exit(1);
	}

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
		*y = *y + 1;
	}

	for (j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
		*y = *y + 1;
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		*x = *x + 1;
		if (L[i] <= R[j])
		{
			*y = *y + 1;
			arr[k] = L[i];
			i++;
		}
		else
		{
			*y = *y + 1;
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		*y = *y + 1;
		arr[k] = L[i];
		i++;
		k++;
	}
	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		*y = *y + 1;
		arr[k] = R[j];
		j++;
		k++;
	}
}
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void MergeSort(int arr[], int l, int r, long int* x, long  int* y)
{
	if (l < r)
	{
		*x = *x + 1;
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		*y = *y + 1;
		int m = l + (r - l) / 2;
		// Sort first and second halves
		MergeSort(arr, l, m, x, y);
		MergeSort(arr, m + 1, r, x, y);
		Merge(arr, l, m, r, x, y);
	}
}
Node* FillTable(Node* table, int* array1, int table_range, int n)
{
	int i, y = 0;
	for (i = 0; i < n; i++)//loop that insert all the elememts in the array to the hash table 
	{
		table = Insert(table, array1[i] % table_range, array1[i]);
		y++;
	}
	return table;
}
Node* Insert(Node* table, int hash_index, int val)
{
	Node* NewestNode;
	int x = 0;
	NewestNode = (Node*)malloc(sizeof(Node));//create a new node for the key
	if (NewestNode == NULL)
	{
		ErrorFunction();
		exit(1);
	}
	NewestNode->val = val;
	NewestNode->next = NULL;
	x++;
	if (table[hash_index].next == NULL)//if the tash table[hash_index] is empty then put there nn node (new node)
		table[hash_index].next = NewestNode;
	else free(NewestNode);
	return table;
}
int CheckQentityOfDiffrentElemInList(Node* table, int size)//this function check how meny diffrent elements we have in the hash table
{
	int i, count = 0;
	for (i = 0; i < size; i++)
	{
		if (table[i].next != NULL)
			count++;
	}
	return count;
}
void FreeTable(Node** table) //this function is free all the memory that allocated for the hash table
{
	int i;
	Node* nodeToFree;
	for (i = 0; i < N; i++) { // for each list
		if (table[i] == NULL) { // if empty
			continue;
		}
		nodeToFree = table[i];
		while (table[i] != NULL) { // else print all the values
			table[i] = table[i]->next; //cur=cur+1;
			free(nodeToFree);
			nodeToFree = table[i];
		}
	}
}
struct node* NewNode(int item)//create a new node
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));//memory allocate for new node for the tree
	if (temp == NULL)//check if the allocation was sucsses
	{
		ErrorFunction();
		exit(1);
	}
	temp->key = item;//initiallizue the key
	temp->left = temp->right = NULL;
	return temp;//return the new node
}
void PrintFunction(int n, int count, long int x, long  int y)//print all the measures for utility and the result of each algorithm
{
	printf("There is %d diffrent elements in the array\n", count);
	printf("For n=%d the algorithm made x=%ld comparisons and y=%ld placements\n", n, x, y);
}
void ErrorFunction()//this function is called when we cannot allocate memory for the array(with the given n that the user is put in) 
{
	printf("error,cannot allocated memory!");
}