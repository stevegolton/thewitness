#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

// Describes the dimensions of the screen buffer character array
#define SBUF_WIDTH 50
#define SBUF_HEIGHT 16

// This struct defines a node in a grid. It has an array of pointers to other nodes which are the nodes it can route to.
// The route is a pointer to the currently routed node or NULL if the node has not been visited yet.
// The x and y values are the positions of the node in the grid, and are only used for printing the grid, not for solving.
struct node
{
	struct node* nodes[4];
	struct node* route;
	int x;
	int y;
};

// This struct defines an entire grid with one entry point and exit point.
// The start and end pointers point to the entry and exit nodes respectively.
// The pool pointer points to the start of the pool of nodes which must be allocated manually.
struct grid
{
	struct node* start;
	struct node* end;
	struct node* pool;
	struct node* required_nodes[100];
	int required_nodes_count;
	int node_count;
};

// Describes the screen buffer (only used for printing)
char sbuf[SBUF_HEIGHT][SBUF_WIDTH];

// Clears the screen buffer (fills with spaces)
void sbuf_clear()
{
	memset(sbuf, ' ', sizeof(sbuf));
}

// Prints the screen buffer to stdout
void sbuf_print()
{
	int x, y;
	for(y=0; y<SBUF_HEIGHT; y++)
	{
		for(x=0; x<SBUF_WIDTH; x++)
		{
			printf("%c", sbuf[x][y]);
		}
		printf("\n");
	}
}

// Creates a gird of dimensions width and height.
// The starting node is at (0, 0), and the exit node is at (width-1, height-1).
// TODO make it so that the entry and exit points can be changed!
void make_grid(struct grid* grid, int width, int height)
{
	// Set everything in the grid to 0/NULL
	memset(grid, 0, sizeof(struct grid));

	grid->node_count = width*height;

	// Allocate enough room to store all of the nodes which make up this grid and reset all values to 0
	grid->pool = malloc(sizeof(struct node) * width * height);
	memset(grid->pool, 0, sizeof(struct node) * width * height);	

	// Go through each node in the grid and assign its x & y positions as well as its neighbouring nodes as connections.
	int x, y, i;
	for(y=0; y<height; y++)
	{
		for(x=0; x<width; x++)
		{
			grid->pool[x + y*width].x = x*2;
			grid->pool[x + y*width].y = y*2;
			i = 0;
			if(x > 0)          grid->pool[x + y*width].nodes[i++] = &grid->pool[(x-1) + y*width];
			if(x < (width-1))  grid->pool[x + y*width].nodes[i++] = &grid->pool[(x+1) + y*width];
			if(y > 0)          grid->pool[x + y*width].nodes[i++] = &grid->pool[(x) + (y-1)*width];
			if(y < (height-1)) grid->pool[x + y*width].nodes[i++] = &grid->pool[(x) + (y+1)*width];
		}
	}
	
	// Set the start and end nodes
	grid->start = &grid->pool[0];
	grid->end = &grid->pool[(width*height) - 1];
}

// Frees the node pool in a grid
void delete_grid(struct grid* grid)
{
	free(grid->pool);
}

void add_required_node(struct grid *grid, struct node *node)
{
	grid->required_nodes[grid->required_nodes_count++] = node;
}

bool validate_grid(struct grid *grid)
{
	struct node **head = &grid->required_nodes[0];

	while(NULL != *head)
	{
		// Ensure the node is routed
		if(NULL == (*head)->route)
		{
			return false;
		}

		head++;
	}

	return true;
}

void grid_print(struct grid* grid)
{
	int i;

	//printf("%d nodes:\n", grid->node_count);


	for (i = 0; i < grid->node_count; i++)
	{
		sbuf[grid->pool[i].x][grid->pool[i].y] = '.';
	}

	struct node** head = &grid->required_nodes[0];
	while (NULL != *head) {
		sbuf[(*head)->x][(*head)->y] = 'x';
		head++;
	}
}

// Work through all the connecting nodes starting at a particular node
// Recursively calls do_node() on all connecting nodes which haven't been visited yet
int do_node(struct node* node, struct grid* grid, bool findone)
{
	int solution_count = 0;
	int nodeidx;
	struct node *printnode;
	
	if(node == grid->end)
	{
		// We have reached the end node, a solution has been found, validate the solution
		if(validate_grid(grid))
		{
			printf("Found a solution\n");

			solution_count++;

			// The node we are currently printing is the start node
			printnode = grid->start;
			
			// Clear the screen buffer
			sbuf_clear();

			grid_print(grid);

			// Run through all nodes and print them to the screen buffer
			while(NULL !=printnode)
			{
				// Switch on the type of node we are dealing with
				if(grid->start == printnode)
					sbuf[printnode->x][printnode->y] = 'S';
				else if(grid->end == printnode)
					sbuf[printnode->x][printnode->y] = 'E';
				else
					sbuf[printnode->x][printnode->y] = 'o';

				// Put a line between this and the next route node
				if(printnode->route != NULL)
				{
					char linechar = (printnode->x == printnode->route->x)? '|' : '-';
					sbuf[(printnode->x + printnode->route->x)/2][(printnode->y + printnode->route->y)/2] = linechar;
				}

				// Move the print node on to the next in the route
				printnode = printnode->route;
			}
			// Print the screen buffer to stdout
			sbuf_print();
		}
	}
	else
	{
		// Search for non NULL and non-visited connecting nodes
		for(nodeidx=0; nodeidx<4; nodeidx++)
		{
			if ((node->nodes[nodeidx] != NULL) && (node->nodes[nodeidx]->route == NULL))
			{
				// Temporarily set the route to be this node then call do_node on it
				node->route = node->nodes[nodeidx];
				solution_count += do_node(node->nodes[nodeidx], grid, findone);
				if (solution_count == 1 && findone) break;
				node->route = NULL;
			}
		}
	}

	return solution_count;
}

// Main entry point
int main(void)
{
	struct grid mygrid;
	
	// Let's make ourselves a grid
	make_grid(&mygrid, 8, 8);
	add_required_node(&mygrid, &mygrid.pool[1]);
	add_required_node(&mygrid, &mygrid.pool[4]);
	add_required_node(&mygrid, &mygrid.pool[5]);
	add_required_node(&mygrid, &mygrid.pool[6]);
	add_required_node(&mygrid, &mygrid.pool[12]);

	// Print the grid
	sbuf_clear();
	grid_print(&mygrid);
	sbuf_print();

	// Start by looking at the first node
	int solutions = do_node(mygrid.start, &mygrid, true);

	delete_grid(&mygrid);

	// Print the number of solutions found
	printf("solutions = %d\n", solutions);	

	return 0;
}
