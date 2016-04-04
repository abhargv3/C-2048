#include "game.h"
/*INTRO PARAGRAPH
For this mp, we implemented the game 2048. To do this, we used dynamically allocated arrays to store the game data. The current game is a structure of rows and columns and a pointer  to cells. We had to implement making the game and remaking the game which clears the board and sets all the cells to -1 which represents nothing. Then we made a pointer to cells so that we can access them. Then we made move functions which shift the whole board in different directions depending on what the user inputted. Then we made sure that the game ended by checking if all the cells are filled and there are no 2 cells of equal value  next to each other.
*/

// minor changes to each move function to account for differences in each one.



game* make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //Initialize all other variables in game struct
    int i;
	// sets all cells to -1 for clean board.
    
    (*mygame).rows=rows;
    (*mygame).cols=cols;
    (*mygame).score=0;
    for(i=0; i<(rows*cols); i++)
    {
        mygame->cells[i]=-1;
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
    game structure to have the given number of rows and columns. Initialize
    the score and all elements in the cells to -1. Make sure that any 
    memory previously allocated is not lost in this function.   
*/
{
    /*Frees dynamically allocated memory used by cells in previous game,
     then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
    free((*_cur_game_ptr)->cells);
    (*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	// sets all cells to -1 for the new game
     
    int i;
    (**_cur_game_ptr).rows=new_rows;
    (**_cur_game_ptr).cols=new_cols;
    (**_cur_game_ptr).score=0;
    
    for(i=0; i<(new_rows*new_cols); i++)
    {
        (*_cur_game_ptr)->cells[i]=-1;
    }

    return; 
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
	// uses free to desotry the game

    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
    if the row and col coordinates do not exist.
*/
{
 	// return pointer to te cell that we awant. useing structures.
    int total_cols=(*cur_game).cols;
    int total_rows=(*cur_game).rows;

    if(row>=0 && row<total_rows && col>=0 && col<total_cols)
    {
        return &(cur_game->cells[row*total_cols+col]);
    }
        
    else{return NULL;}
}
int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
   	// follows algotirm to shift stuff up.	
    int target=-1;  //Initializing target
    int columns = (cur_game)->cols;
    int rows = (cur_game)->rows;
    int ccol, crow, last_combined_row;
    int flag=0;	
    for(ccol=0; ccol<columns; ccol++) //Starting from top
    {
        last_combined_row=-1;
        for(crow=0; crow<rows;crow++)
        {
        
            if((*get_cell(cur_game, crow, ccol)!=-1)) //if its full cell
            {
                target = crow-1;
		while(target>=0)
		{ 
		 if(*get_cell(cur_game,target,ccol)==-1)
                  {  *get_cell(cur_game, target, ccol)=*get_cell(cur_game, crow, ccol);
                    *get_cell(cur_game, crow, ccol)=-1;
		    flag=1;
		    crow = target;
		    
		  }
		   target --;
		}
		target = crow-1;  //want our target to be before current row 
	    }    
        } 
     }

    for(ccol=0; ccol<columns; ccol++) //loop to combine
    {
        last_combined_row=-1;
	target =-1;
        for(crow=0; crow<rows;crow++)
        {	
    		target = crow-1;
                 if((target)!=last_combined_row && target !=-1)
                {
                    if(*get_cell(cur_game, target, ccol)==*get_cell(cur_game, crow, ccol)&& *get_cell(cur_game, target, ccol)!=-1)
                    {
                        *get_cell(cur_game, target, ccol)=2*(*get_cell(cur_game, target, ccol));		// increases the value
                        *get_cell(cur_game, crow, ccol)=-1;
                     	cur_game->score += (*get_cell(cur_game, target, ccol)); 
			flag=1;

			last_combined_row= target-1;
		    }
                }
        }		 
    
    }

    for(ccol=0; ccol<columns; ccol++) //loop to shift up the combined cells
	{
		for(crow=0; crow<rows;crow++)
		{
			if(*get_cell(cur_game, crow, ccol)!=-1)
			{ 
				target=crow-1;
				while(target>=0)
				{
					if(*get_cell(cur_game, target, ccol) ==-1)
					{
					
						*get_cell(cur_game, target, ccol)=*get_cell(cur_game, crow, ccol);
						*get_cell(cur_game, crow, ccol)=-1;
						crow=target;
					}
					target--;
				}
				target = crow-1;
			}
		}
	
		
	}
	

	return flag;
};

int move_s(game * cur_game) //slide down
{
          // implemented the same way as the other but down.

int columns = (cur_game)->cols;
    int rows = (cur_game)->rows;
    int target=rows;
    int ccol, crow, last_combined_row;
    int flag=0;	
    for(ccol=0; ccol<columns; ccol++)
    {
        last_combined_row=rows;
        for(crow=rows-1; crow>=0;crow--)
        {
            if((*get_cell(cur_game, crow, ccol)!=-1))
            {
                target = crow+1;
		while(target<rows)
		{ 
		 if(*get_cell(cur_game,target,ccol)==-1)
                  {  *get_cell(cur_game, target, ccol)=*get_cell(cur_game, crow, ccol); //// changes the value to the target row.
                    *get_cell(cur_game, crow, ccol)=-1;
		    flag=1;						// flag for 1 so that we know it is succeded, change occured.
		    crow = target;
		    
		  }
		   target ++;
		}
		target = crow+1;     
            } 
                 if((target)!=last_combined_row && target !=rows)
                {
                    if(*get_cell(cur_game, target, ccol)==*get_cell(cur_game, crow, ccol) && *get_cell(cur_game, crow, ccol) != -1 )
                    {
                        *get_cell(cur_game, target, ccol)=2*(*get_cell(cur_game, target, ccol));	// combine cells
			
			(cur_game)->score += (*get_cell(cur_game, target, ccol));
                        *get_cell(cur_game, crow, ccol)=-1;
                     
			flag=1;
			last_combined_row= target+1;
		    }
                }
        }		 
        
    }
    for(ccol=0; ccol<columns; ccol++)
	{
		for(crow=0; crow<rows;crow++)
		{
			if(*get_cell(cur_game, crow, ccol)!=-1)
		{
			target=crow+1;
			while(target<rows)
			{
			if(*get_cell(cur_game, target, ccol) ==-1)
			{
				
				*get_cell(cur_game, target, ccol)=*get_cell(cur_game, crow, ccol);
				*get_cell(cur_game, crow, ccol)=-1;
				crow=target;
			}
				target++;
			}
			target = crow+1;
			}
		}
	}
	return flag;   
};


int move_a(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{	

	////        DOES move left, same way as the others, minor changes
    int target=-1;
    int columns = (cur_game)->cols;
    int rows = (cur_game)->rows;
    int ccol, crow, last_combined_row;
    int flag=0;	
    for(crow=0; crow<rows; crow++)
    {
        last_combined_row=-1;
        for(ccol=0; ccol<columns;ccol++)
        {
        
            if((*get_cell(cur_game, crow, ccol)!=-1))
            {
                target = ccol-1;
		while(target>=0)
		{ 
		 if(*get_cell(cur_game,crow,target)==-1)
                  {  *get_cell(cur_game, crow, target)=*get_cell(cur_game, crow, ccol);		// redo cell
                    *get_cell(cur_game, crow, ccol)=-1;
		    flag=1;
		    ccol = target;
		    
		  }
		   target --;
		}
		target = ccol-1;     
            } 
                 if((target)!=last_combined_row && target !=-1)
                {
                    if(*get_cell(cur_game, crow, target)==*get_cell(cur_game, crow, ccol)&& *get_cell(cur_game, crow, target)!=-1)
                    {
                        *get_cell(cur_game, crow, target)=2*(*get_cell(cur_game, crow, target)); 		// combine cells
			(cur_game)->score +=(*get_cell(cur_game,crow,target)); //update code
                        *get_cell(cur_game, crow, ccol)=-1;
                     
			flag=1;

			last_combined_row= target-1;
		    }
                }
        }		 
        
    }
    for(crow=0; crow<rows; crow++)
    {
		for(ccol=columns-1; ccol>=0;ccol--)
		{
			if(*get_cell(cur_game, crow, ccol)!=-1)
		{ 
			target=ccol-1;
			while(target>=0)
			{
			if(*get_cell(cur_game, crow, target) ==-1)
			{
				
				*get_cell(cur_game, crow, target)=*get_cell(cur_game, crow, ccol);
				*get_cell(cur_game, crow, ccol)=-1;
				ccol=target;
			}
				target--;
			}
			target = ccol-1;
			}
		}
	
		
	}
	

	return flag;
};

int move_d(game * cur_game){ //slide to the right
    
// same way as slide left but start from other side
	
    
    int columns = (cur_game)->cols;
int target=columns;
    int rows = (cur_game)->rows;
    int ccol, crow, last_combined_column;
    int flag=0;	
    for(crow=0; crow<rows; crow++)
    {
        last_combined_column=columns;
        for(ccol=columns-1; ccol>=0; ccol--)
        {
        
            if((*get_cell(cur_game, crow, ccol)!=-1))
            {
                target = ccol+1;
		while(target<columns)
		{ 
		 if(*get_cell(cur_game, crow, target)==-1)
                  {  *get_cell(cur_game, crow, target)=*get_cell(cur_game, crow, ccol);		// changes target cell
                    *get_cell(cur_game, crow, ccol)=-1;
		    flag=1;
		    ccol = target;
		    
		  }
		   target ++;
		}
		target = ccol+1;     
            } 
                 if((target)!=last_combined_column && target !=columns)
                {
                    if(*get_cell(cur_game, crow, target)==*get_cell(cur_game, crow, ccol) && *get_cell(cur_game, crow, ccol) !=-1 )
                    {
                        *get_cell(cur_game, crow, target)=(*get_cell(cur_game, crow, target));			
			(cur_game)->score +=(*get_cell(cur_game,crow,target));
                        *get_cell(cur_game, crow, ccol)=-1;
                     
			flag=1;
			last_combined_column= target+1;
		    }
                }
        }		 
        
    }
	
for(crow=0; crow<rows;crow++)
	{
		for(ccol=0; ccol<columns; ccol++)
		{
			if(*get_cell(cur_game, crow, ccol)!=-1)
		{//once we find a 
			target=ccol+1;
			while(target<columns)
			{
			if(*get_cell(cur_game, crow, target) ==-1)
			{
				
				*get_cell(cur_game, crow, target)=*get_cell(cur_game, crow, ccol);
				*get_cell(cur_game, crow, ccol)=-1;
				ccol=target;
			}
				target++;
			}
			target = ccol+1;
			}
		}
	
		
	}
	
    return flag;
};


int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
    Return 1 if there are possible legal moves, 0 if there are none.
 */
{
	
	int i, j;
	int rows, cols;
	// Declare variables for use later on
	rows = cur_game->rows;
	cols = cur_game->cols;
	int *cells = cur_game->cells;

	// Go through each element in the matrix
	for(i = 0; i<rows; i++ ) {
		for(j = 0; j<cols; j++) {

			// If a cell is empty, there are still legal moves
			if(cells[i *cols + j] == -1)
				return 1;

			// If two cells in the column are equal, there are still legal moves
			if(i+1 < rows ){
				if( cells[i * cols + j] == cells[(i+1)*cols + j])
					return 1;
			}
	
			// If two cells in the row are equal, there are still legal moves
			if(j+1 < cols){
                                if( cells[i * cols + j]	== cells[(i)*cols + (j + 1)])
                                        return 1;
                        }

		}
	}

    return 0;
	
}

/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
    
    cell * cell_ptr;
    cell_ptr =  cur_game->cells;
    
    if (cell_ptr == NULL){  
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
    
    
    //check for an empty cell
    int emptycheck = 0;
    int i;
    
    for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
        if ((*cell_ptr) == -1){
                emptycheck = 1;
                break;
        }       
        cell_ptr += 1;
    }
    if (emptycheck == 0){
        printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
        exit(0);
    }
    
    int ind,row,col;
    int num;
    do{
        ind = rand()%((cur_game->rows)*(cur_game->cols));
        col = ind%(cur_game->cols);
        row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
    num = rand()%20;
    if(num <= 1){
        *get_cell(cur_game, row, col) = 4; // 1/10th chance
    }
    else{
        *get_cell(cur_game, row, col) = 2;// 9/10th chance
    }
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr =  cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
    
    printf("\n\n\nscore:%d\n",cur_game->score); 
    
    
    printf("\u2554"); // topleft box char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // top box char
    printf("\u2557\n"); //top right char 
    
    
    for(i = 0; i < rows; i++){
        printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    default:
                        printf("  X  ");

                }

            }
            cell_ptr++;
        }
    printf("\u2551\n"); //print right wall and newline
    }
    
    printf("\u255A"); // print bottom left char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // bottom char
    printf("\u255D\n"); //bottom right char
    
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
    int rows,cols;
    char buf[200];
    char garbage[2];
    int move_success = 0;
    
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
    case 'n':
        //get row and col input for new game
        dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
        while (NULL == fgets(buf,200,stdin)) {
            printf("\nProgram Terminated.\n");
            return 0;
        }
        
        if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
        rows < 0 || cols < 0){
            printf("Invalid dimensions.\n");
            goto dim_prompt;
        } 
        
        remake_game(&cur_game,rows,cols);
        
        move_success = 1;
        
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

    
    
    
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
         print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}