#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NODES 20
#define TOTAL_RECO 100

struct People
{
	int id;
	int no_of_neighbours;
	struct People *next[TOTAL_NODES];
};

 struct People *nodes[TOTAL_NODES];

 int visited[TOTAL_NODES][TOTAL_NODES];

 void vertex(int id)
{
	struct People *temp = (struct People*)malloc(sizeof(People));
	temp->id = id;
	temp->no_of_neighbours =0;
	for(int i=0;i<TOTAL_NODES;i++)
	{
		temp->next[i]=NULL;
	}
	nodes[id] = temp;
}

bool isNeighbour(int source, int destination)
{
	int count = nodes[source]->no_of_neighbours;

	for(int i=0; i< count; i++)
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

void removeLink(int source, int destination)
{
	int count = nodes[source]->no_of_neighbours;

	for(int i=0; i< count; i++)
	{
		if(nodes[source]->next[i] == nodes[destination])
		{
			nodes[source]->next[i] = NULL;
			return;
		}
	}
	printf(" |-|---------------  Neighbour doesn't exist  ---------------|-| \n");
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

char* recommendations(int source, int destination)
{

	int cnt_src = nodes[source]->no_of_neighbours;
	int cnt_dest = nodes[destination]->no_of_neighbours;

	char *return_value = (char*)malloc(TOTAL_RECO);

	strcpy(return_value,"\0");

	if(cnt_dest==0)
	{
		strcpy(return_value,"");
		return return_value;
	}

	int n_src[cnt_src];
	int n_dest[cnt_dest];


	for(int i=0; i< cnt_src; i++)
	{
		n_src[i] = nodes[source]->next[i]->id;
	}

	for(int i=0; i< cnt_dest; i++)
	{
		n_dest[i] = nodes[destination]->next[i]->id;

		if(isNeighbour(source, n_dest[i]) == false && source!= n_dest[i] && !isAlreadyInReco(source,n_dest[i]))
		{
			char temp_buffer[10];
			sprintf(temp_buffer,"%d ",n_dest[i]);
			strcat(return_value, temp_buffer);
			addToReco(source,n_dest[i]);
		}
	}

	return return_value;
}

void recommendations(int source)
{

	int cnt_src = nodes[source]->no_of_neighbours;

	if(cnt_src == 0)
	{
		printf("\nRecommendations for %d are\n", source );
		printf("|-|---------------  %d You have no Friends , Get a few friends for recommendations  ---------------|-| \n",source);
		return;
	}

	char* result = (char*)malloc(TOTAL_RECO*TOTAL_NODES);

	strcpy(result,"\0");

	for(int i=0; i< cnt_src; i++)
	{
		strcat(result,recommendations(source,nodes[source]->next[i]->id));
	}

        printf("Recommendations for %d are\n", source );

    if( strcmp(result,"") == 0 )
        printf("|-|---------------  Sorry No Recommendations for you  ---------------|-| \n");
    else
	    printf("%s \n",result );

	free(result);

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
		printf(" %d ", nodes[id]->next[count-1]->id);
		count--;
	}
	printf("\n");
}

int main()
{
	printf(" |-|---------------  GRAPH BASED RECOMMENDATION SYSYTEM  ---------------|-| \n\n");

	int n;
	printf(" Enter the number of people in Society \n");
	scanf("%d",&n);
    printf("\n Neighbours of people in Society are \n\n");

    for(int i = 1 ; i <= n ; i++)
    {
        vertex(i);                  // 13 by default
    }

	edge(1,4);
	edge(1,2);
	edge(2,1);
	edge(2,2);
	edge(2,3);
	edge(2,4);
	edge(2,5);
	edge(2,6);
	edge(3,5);
	edge(3,6);
	edge(3,11);
	edge(3,12);

	//edge(4,5);

        printNeighbours(1);
	printNeighbours(2);
	printNeighbours(3);
	printNeighbours(4);

	int k;
	printf("\n Enter the number of people whose recommendation you want to know in Society \n");
	scanf("%d",&k);
    printf("\n");

    for(int i = 1 ; i <= k ; i++)
    {
        recommendations(i);
    }
	return 0;
}