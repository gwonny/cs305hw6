#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "graph.h"

void dijkstra(Graph * g, char * source)
{
	int nodeToUse = 0;
	
	for(int i = 0; i < g->V; i++)
	{
		if(strcmp(g->array[i].label, source) == 0)//finds index of array of source
		{
			nodeToUse = i;
		}
	}
	
	g->array[nodeToUse].dValue = 0;//source is a distance of 0 from itself
	
	while(!isEmpty(g))//while white nodes exist:
	{
		int U = getMin(g);//finds smallest white node
		
		while(g->array[U].head != NULL)//while adjacent list still has adjacent nodes
		{	
			int neighborindex;
			
			for(int i = 0; i < g->V; i++)//finds the particular neighbor's index
			{
				if(strcmp(g->array[i].label, g->jump[g->array[U].head->dest]) == 0)
				{
					neighborindex = i;
				}
			}
			
			if(g->array[neighborindex].dValue > g->array[U].dValue + g->array[U].head->cost)//if neighbor's dvalue is larger than focus-node's dvalue and the cost between them,
			{
				g->array[neighborindex].dValue = g->array[U].dValue + g->array[U].head->cost;//set its dvalue to the focus-node's dvalue + distance between them
				g->array[neighborindex].pred = U;//set neighbor as its predecessor
			}
			
			g->array[U].head = g->array[U].head->next;//goes to next adjacent node in list
			
		}
	g->array[U].color = BLACK;//sets the focus-node to black because all its adjacent nodes have been scanned and covered
	}
	return;
}

int isEmpty(Graph * g)//checks if white nodes are nonexistent, 1 for yes, 0 for no
{
	if(g == NULL)
	{
		return 1;
	}
	
	for(int i = 0; i < g->V; i++)
	{
		if(g->array[i].color == WHITE)
		{
			return 0;
		}
	}
	
	return 1;
}

int getMin(Graph * g)//indexes white node with smallest dvalue 
{
	if(g == NULL)
	{
		return -1;
	}
	
	int currentMin = INF;
	int currentMinNode = 0;
	
	for(int i = 0; i < g->V; i++)//for all vertices, compares dvalues
	{
		if(isEmpty(g))
		{
			return -1;
		}
		
		if(g->array[i].dValue < currentMin && g->array[i].color == WHITE)
		{
		currentMin = g->array[i].dValue;
		currentMinNode = i;
		}
	}//smallest white node will be resulted
	
	return currentMinNode;
}
