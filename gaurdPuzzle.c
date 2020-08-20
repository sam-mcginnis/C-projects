/* COP 3502C Midterm Assignment Two
This program is written by: Samuel McGinnis */
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    struct node *next;
    struct node *prev;
}Prisoner;

int lastman(Prisoner **head, int k)
{
    int i;
    Prisoner *delete;
    Prisoner *copy;
    
    copy = *head;
    delete = *head;
    while (delete->next != delete)
    {
        for (i = 0; i < k - 1; i++) 
        {
            copy = delete;
            delete = delete->next;
        }
        
        copy->next = delete->next;   
        free(delete); 
        delete = copy->next;
    }
    
    *head = delete;

    return (delete->num);
}

void initialize (Prisoner **head)
{
    Prisoner *temp;
    Prisoner *rear;
    int k, n, i;
    
    printf("Enter n number of prisoners: ");
    scanf("%d", &n);
    
    for(i=1;i<=n;i++)
    { 
        temp = (Prisoner*)malloc(sizeof(Prisoner));
        temp->num = i;
        temp->next = NULL;
        
        if(*head == NULL)
            *head = temp;
        
        else
            rear->next = temp;
        
        rear = temp;
    }
    
    rear->next = *head;
}

int main()
{
    int survive, skip;
    
    Prisoner *head; 
    head= NULL;

    initialize(&head); 
    
    printf("Enter k number of prisoners to be skipped: "); 
    scanf("%d", &skip);
    
    printf("The position number who will survive: %d\n", lastman(&head, skip));
    free(head); 

return 0;
}
