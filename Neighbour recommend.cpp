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
        n_src[i]=0;
    }

    for(int i=0; i< cnt_dest; i++)
    {
        n_dest[i]=0;
    }

	for(int i=0; i< cnt_src; i++)
	{
		n_src[i] = nodes[source]->next[i]->id;
	}

	for(int i=0; i< cnt_dest; i++)
	{
		n_dest[i] = nodes[destination]->next[i]->id;

		if(isNeighbour(source, n_dest[i]) == false && source != n_dest[i] &&
           isAlreadyInReco(source,n_dest[i]) == false && nodes[source]->rating <= nodes[n_dest[i]]->rating )
		{
			char temp_buffer[10];

			sprintf(temp_buffer,"%d ",n_dest[i]);

			strcat(return_value, temp_buffer);

			addToReco(source,n_dest[i]);
		}

	}

	return return_value;

}

void get_recommendations(int source)
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
		char *ans = recommendations(source,nodes[source]->next[i]->id);
		strcat(result,ans);
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
        printf(" \n %d with rating = %d \n" ,nodes[id]->next[count-1]->id,nodes[id]->next[count-1]->rating);
		count--;
	}

	printf("\n");

}

int main()
{
    printf(" \n Date :%s\n \n ", __DATE__ );

    printf(" \n Time :%s\n \n ", __TIME__ );

    printf(" \n Line :%d\n \n \n \n ", __LINE__ );

	printf(" |-|---------------  GRAPH BASED RECOMMENDATION SYSYTEM  ---------------|-| \n\n");

	int n;
	printf(" \nEnter the number of people in Society \n");
	scanf("%d",&n);
	printf(" \nNow Enter rating of each people in Society \n");

	/*

	21 11 7 84 26 99 45 15 99 2 33 45

	*/

    for(int i = 1 ; i <= n ; i++)
    {
        int rating;
        scanf("%d",&rating);
        vertex(i,rating);                  // 12 by default
    }

    int edges;
	printf(" \nEnter the number of relations(edges) in Society \n");
	scanf("%d",&edges);

	printf(" \nNow Enter the 2 person id such that there is directed edge between them \n");
	
    // 12 by default
    
    for(int i = 1 ; i <= edges ; i++)
    {
        int from, to;
        scanf("%d %d",&from,&to);
        edge(from,to);
    }

    /*

	1 4
	1 2
	2 1
	2 2
	2 3
	2 4
	2 5
	2 6
	3 5
	3 6
	3 11
	3 12

   */

    printf("\n|-|---------------  NEIGHBOUR OF PEOPLE IN SOCIETY ARE  ---------------|-| \n\n");

    printNeighbours(1);

    printNeighbours(2);

    printNeighbours(3);

    printNeighbours(4);

    int k;
	printf("\n Enter the first n number of people whose recommendation you want to know in Society \n");
	scanf("%d",&k);

    printf("\n");
    for(int i = 1 ; i <= k ; i++)
    {
        get_recommendations(i);
    }

	return 0;

}
