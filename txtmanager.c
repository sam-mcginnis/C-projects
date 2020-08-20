/* COP 3502C Final term Assignment 2
This program is written by: Samuel McGinnis */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define limit 50

typedef struct tree
{
   char word[limit];
   struct tree *left;  
   struct tree *right;
}TreeNode;

TreeNode *node;
void BinarySearch(char *word, TreeNode **parent, TreeNode **location);
void insert(char *word);
void twochildEmpty(TreeNode *parent, TreeNode *location);
void oneChildEmpty(TreeNode *parent, TreeNode *location);
void zerochildEmpty(TreeNode *parent, TreeNode *location);
int delete(char *word, FILE *out);
int preOrder(TreeNode *ptr, FILE *out);
void inOrder(TreeNode *ptr, FILE *out);
void postOrder(TreeNode *ptr, FILE *out);
void alphabetic(TreeNode *ptr);
int CountBefore(char searchKey[], TreeNode *root);

int main()
{
   char word[limit];
   int N, S, D, i, holder;
   TreeNode *location, *plc_hldr;
   FILE *in;
   FILE *out;
   node = NULL;
   in = fopen("in.txt", "r");
   
   if (in == NULL)
   {
       fprintf(out, "File not found");
       return 0;
   }
   
   fscanf(in, "%d %d %d", &N, &S, &D);
   for (i = 1; i <= N; i++)
   {
       fscanf(in, "%s", word);
       insert(word);
   }
   
  out = fopen("out.txt", "w");

   fprintf(out, "Pre Order: ");
   preOrder(node, out);
   
   fprintf(out, "\nIn Order: ");
   inOrder(node, out);
   
   fprintf(out, "\nPost Order: ");
   postOrder(node, out);
   
   fprintf(out,"\n\nSearch Phase:");
   for (i = 1; i <= S; i++)
   {
        plc_hldr = node;
        fscanf(in, "%s", word);
        holder = CountBefore(word, plc_hldr);
        if (holder == N)
        {    
            fprintf(out,"\n%s: Not found, Items before: 0", word);
        }
        else    
        {    
            fprintf(out,"\n%s: Found, Items before: %d", word, holder);
        }
   }
   fprintf(out, "\n\nDelete Phase:");
   for (i = 1; i <= D; i++)
   {

       fscanf(in, "%s", word);
       delete(word, out);
   }
  fprintf(out, "\n\nPre Order: ");
   preOrder(node, out);
  fprintf(out, "\nIn Order: ");
   inOrder(node, out);
  fprintf(out, "\nPost Order: ");
   postOrder(node, out);
   fprintf(out, "\n");
   fclose(out);

   return 0;
}
void BinarySearch(char *word, TreeNode **parent, TreeNode **location)
{
   TreeNode *ptr;
   TreeNode *temp;
   
   if (node == NULL)
   {
       *location = NULL;
       *parent = NULL;
       return;
   }
   
   if (strcmp(word, node->word) == 0)
   {
       *location = node;
       *parent = NULL;
       return;
   }
   if (strcmp(word, node->word) < 0)
       ptr = node->left;
   
   else
       ptr = node->right;

   temp = node;
   
   while (ptr != NULL)
   {
       if (strcmp(word, ptr->word) == 0)
       {
           *location = ptr;
           *parent = temp;
           return;
       }
       temp = ptr;
       if (strcmp(word, ptr->word) <= 0)
           ptr = ptr->left;
       else
           ptr = ptr->right;
   }
   *location = NULL;
   *parent = temp;
}
void insert(char *word)
{
   TreeNode *parent;
   TreeNode *location;
   TreeNode *temp;

   BinarySearch(word, &parent, &location);
   if (location != NULL)
       return;

   temp = (TreeNode*) malloc(sizeof(TreeNode));
   strcpy(temp->word, word);
   temp->left = NULL;
   temp->right = NULL;
   if (parent == NULL)
       node = temp;
   else
       if (strcmp(word, parent->word) <= 0)
           parent->left = temp;
       else
           parent->right = temp;
}
void twochildEmpty(TreeNode *parent, TreeNode *location)
{
   if (parent == NULL)
       node = NULL;
   else
       if (location == parent->left)
           parent->left = NULL;
       else
           parent->right = NULL;
}
void oneChildEmpty(TreeNode *parent, TreeNode *location)
{
   TreeNode *child;
   if (location->left != NULL)
       child = location->left;
   else
       child = location->right;
   if (parent == NULL)
       node = child;
   else
       if (location == parent->left)
           parent->left = child;
       else
           parent->right = child;
}
void zerochildEmpty(TreeNode *parent, TreeNode *location)
{
   TreeNode *ptr; 
   TreeNode*temp;
   TreeNode *next;
   TreeNode *prev;
   temp = location;
   ptr = location->right;
   while (ptr->left != NULL)
   {
       temp = ptr;
       ptr = ptr->left;
   }
   next = ptr;
   prev = temp;
   if (next->left == NULL && next->right == NULL)
       twochildEmpty(prev, next);
   else
       oneChildEmpty(prev, next);
   if (parent == NULL)
       node = next;
   else
       if (location == parent->left)
           parent->left = next;
       else
           parent->right = next;
   next->left = location->left;
   next->right = location->right;
}

int delete(char *word, FILE *out)
{
   TreeNode *parent;
   TreeNode *location;
  

   if (node == NULL)
       return 0;

   BinarySearch(word, &parent, &location);
   if (location == NULL)
   {
       fprintf(out, "\n%s could not be located", word);
       return 0;
   }
   
   if (location->left == NULL && location->right == NULL)
       twochildEmpty(parent, location);
   if (location->left != NULL && location->right == NULL)
       oneChildEmpty(parent, location);
   if (location->left == NULL && location->right != NULL)
       oneChildEmpty(parent, location);
   if (location->left != NULL && location->right != NULL)
       zerochildEmpty(parent, location);
   fprintf(out, "\n%s: deleted", location->word);  
   free(location);

}

int preOrder(TreeNode *ptr, FILE *out)
{
   if (node == NULL)
       return 0;

   if (ptr != NULL)
   {
       fprintf(out, "%s ", ptr->word);
       preOrder(ptr->left,out);
       preOrder(ptr->right, out);
   }
}
void inOrder(TreeNode *ptr, FILE *out)
{
   if (node == NULL)
       return;
   
   if (ptr != NULL)
   {
       inOrder(ptr->left, out);
       fprintf(out,"%s ", ptr->word);
       inOrder(ptr->right, out);
   }
}
void postOrder(TreeNode *ptr, FILE *out)
{
   if (node == NULL)
       return;
   
   if (ptr != NULL)
   {
       postOrder(ptr->left, out);
       postOrder(ptr->right, out);
       fprintf(out, "%s ", ptr->word);
   }
}
void alphabetic(TreeNode *ptr)
{
   if (ptr != NULL)
   {
       alphabetic(ptr->left);
       alphabetic(ptr->right);
   }
}
int CountBefore(char searchKey[],TreeNode *root)
{
  int count = 0;
    if(root == NULL)
        return 0;
  if(root != NULL) {
    if(strcmp(root->word, searchKey) < 0) {
      count++;
    }
    count += CountBefore( searchKey, root->left);
    count += CountBefore(searchKey, root->right);
  }
  return count;
}

