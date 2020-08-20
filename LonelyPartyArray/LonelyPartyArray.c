// Sam McGinnis
// COP 3502, Summer 2018


#include "LonelyPartyArray.h"
#include <stdlib.h>
#include <stdio.h>

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
   int i;

   //first catch statment for funcntion 
   if(num_fragments<=0 || fragment_length <= 0)
        return NULL;
    
    //mallocs room for LPA
    LonelyPartyArray *party;
    party= malloc(sizeof (LonelyPartyArray));
    
    //initialized paramaters
    party->num_fragments= num_fragments;
    party->fragment_length= fragment_length;

    //Set elements of LPA to 0;
    party->num_active_fragments=0;
    party->size=0;

    //malloc array of pointers to hold adresses of integers
    party->fragments= malloc(sizeof(int*) * party->num_fragments);
    
    for(i=0; i < party->num_fragments; i++)
        party->fragments[i]=NULL;
    
    //mallocs n amounts of boxes for int array
    party->fragment_sizes= malloc(sizeof(int) * party->num_fragments);
    
    //                ^     
    //sets n elements | to 0
    for(i=0; i < party->num_fragments; i++)
        party->fragment_sizes[i] = 0;

    printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", (party->num_fragments * party->fragment_length), party->num_fragments);

    return party;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
    int i;

    //catch statement for a null party param
    if(party != NULL)
    {    
        //if party->fragments isnt equal to null, loop through party->fragemnt
        //sub i and free all NON-NULL sub i frags
        if(party->fragments != NULL)
        {
            for(i=0; i< party->num_fragments; i++)
            {
                if(party->fragments[i] != NULL)
                {    
                    free(party->fragments[i]);
                    party->fragments[i]= NULL;
                }

                else
                    continue;      
            }
        }
        
        //free remaning malloc is reverse order.
        free(party->fragments);
        free(party->fragment_sizes);
        free(party);

        printf("-> The LonelyPartyArray has returned to the void.\n");
    }

        return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
   int fragLoop, j, s, i= 0;
   
   //catch statement for NULL party param
   if (party == NULL )
    {    
        printf("-> Bloop! NULL pointer detected in set().\n");
        return LPA_FAILURE;
    }
    
    fragLoop = party->fragment_length - 1;

    //catch statment for invalid index
    if(index<0 || index> (party->fragment_length * party->num_fragments - 1))
    { 
        //algorithim for finding index placement
        while(fragLoop < abs(index))
        {
            fragLoop+= party->fragment_length;  
            i++;        
        }
    
        j= abs(index) % party->fragment_length;
      
        //catch for neg integer
        if(index< 0)
            printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, -abs(i), -abs(j) );

        else
            printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, abs(i), abs(j) );

        return LPA_FAILURE;
    }
    

    while(fragLoop < index)
    {
        fragLoop+= party->fragment_length;  
        i++;
    }
    
    j= index % party->fragment_length;
    
    //if index is empty ,malloc space for it and update thr pgrogram counter sizes.
    if(party->fragments[i]== NULL)
    {   
        party->fragments[i]= malloc(sizeof(int) * (party->fragment_length));

        for(s=0; s < party->fragment_length; s++)
            party->fragments[i][s]= INT_MIN;

        party->num_active_fragments++;
        party->fragments[i][j]= key;
        party->size++;
        party->fragment_sizes[i]++;

        printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",  i, party->fragment_length, ( i * party->fragment_length), i * party->fragment_length + (party->fragment_length - 1));
        return LPA_SUCCESS;
    }
    
    //if its fragment sub i, isnt empty
    if(party->fragments[i]!=NULL)
    {    
        if(party->fragments[i][j]== UNUSED)
        {   
            party->fragment_sizes[i]++;
            party->size++;
        }
        party->fragments[i][j]= key;
        
        return LPA_SUCCESS;
        
    }
}

int get(LonelyPartyArray *party, int index)
{
   int fragLoop, j, s, key, i= 0;
   
   //catch statement for NULL party param
    if(party == NULL)
    {   printf("-> Bloop! NULL pointer detected in get().\n");
        return LPA_FAILURE;
    }
   
    fragLoop = party->fragment_length - 1;     
    
    //see set(); function
    if(index<0 || index> (party->fragment_length * party->num_fragments - 1))
    { 
        while(fragLoop < abs(index))
        {
            fragLoop+= party->fragment_length;  
            i++;
        }
    
        j= abs(index) % party->fragment_length;

        //see set(); function
        if(index< 0)
            printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, -abs(i), -abs(j) );

        else
            printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, abs(i), abs(j) );
        
       return LPA_FAILURE;
    }

    //see set(); function
    while(fragLoop < index)
    {
        fragLoop+= party->fragment_length;  
        i++;
    }
    
    j= abs(index) % party->fragment_length;
    
    if(party->fragments[i]== NULL)
        return UNUSED;
    
    key= party->fragments[i][j];

    //returns key value calculated by algorithm 
    return key;
}

int delete(LonelyPartyArray *party, int index)
{
    int fragLoop, j, i=0;

    if(party == NULL)
    {   printf("-> Bloop! NULL pointer detected in delete().\n");
        return LPA_FAILURE;
    }
   
    fragLoop = party->fragment_length - 1;     

    //see set(); function
    if(index<0 || index> (party->fragment_length * party->num_fragments - 1))
    { 
        while(fragLoop < abs(index))
        {
            fragLoop+= party->fragment_length;  
            i++;    
        }
    //finds what cell needed
    j= abs(index) % party->fragment_length;
      
        //catch for neg integeres
        if(index< 0)
            printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, -abs(i), -abs(j) );

        else
            printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, abs(i), abs(j) );
        
       return LPA_FAILURE;
    }
    
    while(fragLoop < index)
    
    {
        fragLoop+= party->fragment_length;  
        i++;
        
    }
    
    j= abs(index) % party->fragment_length;
    
    //seg fault catch
    if(party->fragments[i]== NULL || party->fragments[i][j]== UNUSED)
        return LPA_FAILURE;

    //update program counters & cell
    party->fragments[i][j]= UNUSED;
    party->size--;
    party->fragment_sizes[i]--;

    //when fragments becomes empty we free the memory to avoide memory leaks
    if(party->fragment_sizes[i]<=0)
    { 
        printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", i, party->fragment_length, ( i * party->fragment_length), i * party->fragment_length + (party->fragment_length - 1));
        free(party->fragments[i]);
        party->fragments[i]= NULL;
        party->num_active_fragments--;    
    }
    
    return LPA_SUCCESS;
}

int containsKey(LonelyPartyArray *party, int key)
{
   int i=0, j;
    
    
    if(party == NULL)
        return 0;

    for(i=0; i< party->num_fragments; i++)
    {
        //loops while fragments sub i is empty
        //gets to an adress and compares each cell to key
        while(party->fragments[i]== NULL)
            i++;

        for(j=0; j<party->fragment_length; j++)
        {
            if(party->fragments[i][j]== key)
                return 1;
            else
                continue;
        }

        return 0;
    }
}

int isSet(LonelyPartyArray *party, int index)
{     
    int fragLoop, j, i=0;

    if(party == NULL)
        return 0;
    // invalid index
    if(index<0 || index> (party->fragment_length * party->num_fragments - 1))
        return 0;
    
    fragLoop = party->fragment_length - 1;     

    //see set(); Function
    while(fragLoop < index)
    {
        fragLoop+= party->fragment_length;  
        i++;
        
    }
    
    j= abs(index) % party->fragment_length;
    
    if(party->fragments[i]== NULL || party->fragments[i][j]== UNUSED)
        return 0;

    if(party->fragments[i][j]!= UNUSED)
        return 1;

}

int printIfValid(LonelyPartyArray *party, int index)
{
    int fragLoop, j, i=0;

    //catch for NULL party param
    if(party == NULL)
        return LPA_FAILURE;
    
    //invalid index
    if(index<0 || index> (party->fragment_length * party->num_fragments - 1))
        return LPA_FAILURE;
    
    fragLoop = party->fragment_length - 1;     

    //see set();
    while(fragLoop < index)
    {
        fragLoop+= party->fragment_length;  
        i++;
        
    }
    
    j= abs(index) % party->fragment_length;
    
    if(party->fragments[i]== NULL || party->fragments[i][j]== UNUSED)
        return LPA_FAILURE;

    //prints value at index
    printf("%d\n", party->fragments[i][j]);
    
    return LPA_SUCCESS;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
    int i;

    if(party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
        return party;
    }
    
    for(i=0; i< party->num_fragments; i++)
    {
        //jumps through fragments and free mem leak from any NON-NUll pointer
        //then sets that pointer index to NULL
        while(party->fragments[i]== NULL)
            i++;
            
        free(party->fragments[i]);
        party->fragments[i]= NULL;
    }

    //loops through frag_size array and eqaul sub i to 0
    for(i=0; i< party->num_fragments; i++)
    {
        party->fragment_sizes[i]= 0;
    }
    
    //updates program counter
    party->num_active_fragments=0;
    party->size=0;

    printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->fragment_length * party->num_fragments, party->num_fragments);

    return party;
}

int getSize(LonelyPartyArray *party)
{

    if(party== NULL)
        return -1;

    //acces LPA size member
    else
        return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
    if(party== NULL)
        return -1;

    //get max amount of elements LPA can store
    else
        return party->fragment_length * party->num_fragments;

}

int getAllocatedCellCount(LonelyPartyArray *party)
{
    if(party== NULL)
        return -1;

    //retruns the amount of (max amount) that was actaully malloced
    else    
        return party->num_active_fragments * party->fragment_length;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
   long long unsigned int bytes_used;

    if(party== NULL)
        return 0;

    //retruns number of bytes getCapacity(); would use
    bytes_used= (long long unsigned)(party->fragment_length * party->num_fragments) * sizeof(int);

    return bytes_used;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
    long long unsigned int LPAptr_bytes, LPA_bytes, FRAGptr_bytes;
    long long unsigned int frag_bytes, FRAGptr_cell, array1, array2;

    
    if(party== NULL)
        return 0;

    //gets the value of bytes GetAllocatedCellCount(); would use
    LPAptr_bytes= (long long unsigned int) sizeof(LPA*);
    LPA_bytes= (long long unsigned int) sizeof(LPA);
    
    FRAGptr_bytes = (long long unsigned int) sizeof(int*) * party->num_fragments;
    frag_bytes= (long long unsigned int) sizeof(int) * party->num_fragments;
    FRAGptr_cell= (long long unsigned int)  sizeof(int) * (party->num_active_fragments * party->fragment_length);

    return LPAptr_bytes + LPA_bytes + FRAGptr_bytes + FRAGptr_cell + frag_bytes;

}

double difficultyRating(void)
{
    return 3.0;

}
double hoursSpent(void)
{
    return 15.0;
}