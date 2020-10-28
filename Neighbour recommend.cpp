#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NODES 20
#define TOTAL_RECO 100

struct People
{
	int id;
	int rating;
	int no_of_neighbours;
	struct People *next[TOTAL_NODES];
};

struct People *nodes[TOTAL_NODES];
int visited[TOTAL_NODES][TOTAL_NODES];

void vertex(int id,int Rating)
{
	struct People *temp = (struct People*)malloc(sizeof(People));
	temp->id = id;
	temp->no_of_neighbours = 0;
	temp->rating=Rating;

	for(int i=0;i<TOTAL_NODES;i++)
	{
		temp->next[i]=NULL;
	}
	nodes[id] = temp;
}

bool isNeighbour(int source, int destination)
{
	int count_ = nodes[source]->no_of_neighbours;

	for(int i=0; i< count_; i++)
	{
		if(nodes[source]->next[i] == nodes[destination])
		{
			return true;
		}
	}
	return false;
}

void edge(int source, int destination)
{

	if(isNeighbour(source,destination))
	{
		printf(" |-|---------------  Already a link. Can't add duplicates  ---------------|-| \n");
		return;
	}

	nodes[source]->next[nodes[source]->no_of_neighbours] = nodes[destination];
	nodes[source]->no_of_neighbours++;
}

void addToReco(int source,int val)
{
    visited[source][val] = 1;
}

bool isAlreadyInReco(int source, int val)
{
	if(visited[source][val]==1)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void printNeighbours(int id)
{
	int count = nodes[id]->no_of_neighbours;
	printf("Neighbours of %d are\n", id);

	if(count==0)
	{
		printf(" |-|---------------  You Have no neighbours  ---------------|-| ");
		printf("\n");
		return;
	}


	while(count!=0)
	{
        printf(" \n %d with rating = %d \n" ,nodes[id]->next[count-1]->id,nodes[id]->next[count-1]->rating);
		count--;
	}
	printf("\n");
}

int main()
{
	printf(" |-|---------------  GRAPH BASED RECOMMENDATION SYSYTEM  ---------------|-| \n\n");

	int n;
	printf(" \nEnter the number of people in Society \n");
	scanf("%d",&n);
	printf(" \nNow Enter rating of each people in Society \n");

    for(int i = 1 ; i <= n ; i++)
    {
        int rating;
        scanf("%d",&rating);
        vertex(i,rating);                  // 13 by default
    }

	edge(1,4);
	edge(1,2);
	edge(2,1);
	edge(2,2);
	edge(2,3);
	edge(2,4);
	edge(2,5)
	edge(2,6);
	edge(3,5);
	edge(3,6);
	edge(3,11);
	edge(3,12);

    printf("\n|-|---------------  NEIGHBOUR OF PEOPLE IN SOCIETY ARE  ---------------|-| \n\n");
    printNeighbours(1);
    printNeighbours(2);
    printNeighbours(3);
    printNeighbours(4);

	return 0;
}

