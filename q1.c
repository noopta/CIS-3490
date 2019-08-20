#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

typedef struct binary{
  struct wordStruct *key;
  struct binary *left;
  struct binary *right;
}binarySearch;

typedef struct wordStruct{
  char *stringKey;
  float frequency;
}word;

int sum(struct binary *root, int i, int j);

// A recursive function to calculate cost of optimal
// binary search tree

void searchNode(char *stringWord, struct binary *n) {
    if (n == NULL)
        printf("\nValue does not exist in tree!");
    //else if((*n)->data == i)
    else if(strcmp(n->key->stringKey, stringWord) == 0)
        printf("string %s found\n ", stringWord);

    //else if(i > (*n)->data)
      else if(strcmp(stringWord, n->key->stringKey) > 0){
        printf("Compared with %s (%f), go right subtree\n", n->key->stringKey, n->key->frequency/600 );
        //searchNode(i, &((*n)->rightChildNode));
        searchNode(stringWord, n->right);

      }
    else{
          printf("Compared with %s (%f), go left subtree\n", n->key->stringKey, n->key->frequency/600 );
        searchNode(stringWord, n->left);
      }
}

int optCost(struct binary *root, int i, int j)
{
   // Base cases
   if (j < i)  {    // no elements in this subarray
     return 0;
   }
   if (j == i){     // one element in this subarray
     return  root->key->frequency;
   }
   // Get sum of freq[i], freq[i+1], ... freq[j
   int fsum = sum(root, i, j);

   // Initialize minimum value
   int min = INT_MAX;

   // One by one consider all elements as root and
   // recursively find cost of the BST, compare the
   // cost with min and update min if needed
   for (int r = i; r <= j; ++r)
   {
       int cost = optCost(root, i, r-1) +
                  optCost(root, r+1, j);
       if (cost < min)
          min = cost;
   }

   // Return minimum value

   return min + fsum;
 }

// The main function that calculates minimum cost of
// a Binary Search Tree. It mainly uses optCost() to
// find the optimal cost.
int optimalSearchTree(struct binary *root, int n)
{
     // Here array keys[] is assumed to be sorted in
     // increasing order. If keys[] is not sorted, then
     // add code to sort keys, and rearrange freq[]
     // accordingly.
     return optCost(root, 0, n-1);

}

// A utility function to get sum of array elements
// freq[i] to freq[j]
int sum(struct binary *root, int i, int j)
{
    int s = 0;
    for (int k = i; k <=j; k++){
       //s += freq[k];
       s += root->key->frequency;
     }

    return s;
}


void printPostorder(struct binary* node)
{
     if (node == NULL)
        return;

     // first recur on left subtree
     printPostorder(node->left);

     // then recur on right subtree
     printPostorder(node->right);

     // now deal with the node
     printf("string : %s frequency : %f \n", node->key->stringKey , node->key->frequency );
}

struct binary *newNode(char *key)
{

    struct binary *temp =  (struct binary *)malloc(sizeof(struct binary));
    //temp->key = item;
    temp->key = malloc(sizeof(word));
    temp->key->stringKey = calloc(999, sizeof(char));
    temp->key->frequency = 1;
    strcpy(temp->key->stringKey,key);    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct binary *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s \n", root->key->stringKey);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
struct binary* insert(struct binary* node, char *key)
{
    /* If the tree is empty, return a new node
*/
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
  // if (key < node->key)
  if(strcmp(key, node->key->stringKey) < 0){

        node->left  = insert(node->left, key);
      //  printf("Compared with %d, go left subtree\n", node->key->frequency);

  //  else if (key > node->key)
}else if(strcmp(key, node->key->stringKey) > 0){
    //printf("Compared with %d, go right subtree\n", node->key->frequency);
        node->right = insert(node->right, key);

}
  else if(strcmp(key, node->key->stringKey) == 0){
    node->key->frequency++;
  }
    /* return the (unchanged) node pointer */
    return node;
}

size_t string_parser( const char *input, char ***word_array)
{
    size_t n = 0;
    const char *p = input;

    while ( *p )
    {
        while ( isspace( ( unsigned char )*p ) ) ++p;
        n += *p != '\0';
        while ( *p && !isspace( ( unsigned char )*p ) ) ++p;
    }

    if ( n )
    {
        size_t i = 0;

        *word_array = calloc(1, n * sizeof( char * ) );

        p = input;

        while ( *p )
        {
            while ( isspace( ( unsigned char )*p ) ) ++p;
            if ( *p )
            {
                const char *q = p;
                while ( *p && !isspace( ( unsigned char )*p ) ) ++p;

                size_t length = p - q;

                ( *word_array )[i] = ( char * )calloc(1, length + 1 );

                strncpy( ( *word_array )[i], q, length );
                ( *word_array )[i][length] = '\0';

                ++i;
            }
        }
    }

    return n;
}


#define Debug printf("********************************Debug**********\n");

int main(int argc, char* argv[]){

  //FILE *fp;
  char **word_array;
  struct binary *root;
  char *s;
  int i;
  char keyEntered[100];
  long length;
  FILE *fp;
  //int nVal = 2045;

  //int count = 1;
    //  char c;



  fp = fopen(argv[1], "r");

  if(fp == NULL)
       printf("file not found\n");




/*
  while((c = fgetc(fp)) != EOF) {
        if(c == ' ')
            count++;
    }
    printf("words = %d\n", count);
*/




  fseek (fp, 0, SEEK_END);
  length = ftell (fp);
   s = calloc(1,(length));
  fseek (fp, 0, SEEK_SET);

  if (s)
  {
    fread (s, 1, length, fp);
  }
  size_t n = string_parser( s, &word_array );



  //printf("word_array[0] = %s\n", word_array[0]);

  root = newNode(word_array[0]);
  for(i=1; i< 2045; i++){

    //printf(" test: %s \n", word_array[i]);
    insert(root, word_array[i]);

  }


          //optimalSearchTree(root, nVal));
  //printPostorder(root);

  printf("Enter a string to search: ");
  scanf("%s", keyEntered );
  searchNode(keyEntered, root);


  fclose(fp);



  return 0;
}
