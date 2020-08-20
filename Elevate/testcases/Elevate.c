#include "Elevate.h"
#include <stdlib.h>
#include <stdio.h>


//Sam McGinnis sa653767
//COP 3502C, Summer 2018


double difficultyRating(void);
double hoursSpent(void);
double averageWaitTime(int num_floors, int left, int right);
int delta(int pickup_floor, int elevator_floor);
int smallestDelta(int pickup_floor, int left, int right);


int main(int argc, char **argv)
{
    int i, leftElevator, rightElevator;
    int num_floors=9, left=1, right=1;
    double Dleft, Dright;
    
    printf("1  1\n");
   
  
    for(i=1; i<argc; i++)//read in argurmnts
    {
        leftElevator=delta(argv[i][0]-'0',left);//find distance betweens floors for left elevator
        rightElevator=delta(argv[i][0]-'0',right);//find distance betweens floors for right elevator

        if(leftElevator==rightElevator)//if distance between floors is eqaul, use rule two
            {
                
                Dleft= averageWaitTime(num_floors, argv[i][2]-'0', right);//finds average wait time for left elevator
                Dright= averageWaitTime(num_floors, left, argv[i][2]-'0');//finds average wait time for right elevator

                if(Dright==Dleft)//rule three
                    right=argv[i][2]-'0';
                
                if(Dright<Dleft)//sends right elevator
                    right=argv[i][2]-'0';
                
                if(Dleft<Dright)//sends left elevator
                   {
                    left=argv[i][2]-'0';
                   }
            }
        if(rightElevator<leftElevator)//rule one: sends right elevator
            right=argv[i][2]-'0';
            
        if(leftElevator<rightElevator)//rule one; sends left elevator
            left=argv[i][2]-'0';
            
        printf("%d  %d\n",left, right);
        
    }
    return 0;
}

double difficultyRating(void)//required
{

    return 3.0;
}

double hoursSpent(void)//required
{

    return 12.0;
}

double averageWaitTime(int num_floors, int left, int right)//rule two: find algorithm for shorstest average
{
    
    double avrg,avrg2=0, final;
    int i;
   
    for(i=1; i<=num_floors; i++)//runs small delta 9 times
    {
        avrg= smallestDelta( i, left, right);
        avrg2+=avrg;//adds all nine values to avrg2
       
    }
    
    final= avrg2/num_floors;//final is eqaul to avrg2 divided by 9
    

    return final;
}

int smallestDelta(int pickup_floor, int left, int right)
{
    
   int Left, Right;
   
   Left= pickup_floor- left;//finds smallest amount of levels for left elevator
   Right= pickup_floor- right;//finds smallest amount of levels for right elevator

    if(Left<0)//abs catch statement
       Left= Left * (-1);
   
    if(Right<0)//abs catch statement
     Right= Right * (-1);
  
    
    if(Left < Right)//add left value
        return Left;
    
    if(Right < Left)//add right value 
        return Right;    
    
    if(Right==Left)//add both values
        return Right+Left;
        
}

int delta(int pickup_floor, int elevator_floor)//call twice, each for left and right
{
    int num_floors;

    num_floors= (pickup_floor - elevator_floor);//finds distance between elevator and pickup floor

    if(num_floors < 0)//abs function
    {
        num_floors= num_floors * (-1);
    }

    
    return num_floors;
}