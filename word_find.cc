/*###########################################################################################
#  wordfind.cc                                                                              #
#  Muhammad Najib                                                                           #
#  project2 Finding Words                                                                   #
#  30 January 2015                                                                          #
#  The program finds a given word in a grid of characters and prints the grid with the given# 
#  word in capitalized form                                                                 #
############################################################################################*/

#include <wordgrid.h>
#include <iostream>
#include <ctype.h>

using namespace std;

//-function: bool find(string word, wordgrid & grid)------------------------
// PRE: word consists of lowercase letters
// POST: If word is found in grid, starting anywhere 
//       and in any of the 8 directions, it is converted
//       to uppercase in the grid, and true is returned.
//       otherwise, grid is unchanged, and false is returned.

// check1 function to check if row or column in find func are in bounds
//extra brackets used to be safe
bool check1(int sr ,int sc, int dr, int dc, int dim)
{
  // checks for only negative directions
  // returns false if row or col zero
  if(dr == -1){
    if(sr == 0){
       return false;
   }
  }

  if(dc == -1)
  {
   if( sc == 0){
     return false;
   }
  }


  return true;

}

// same as check1 except it checks for positive directions
// returns false if row or col reaches max value
bool check2(int sr ,int sc, int dr, int dc, int dim)
{
  if(dr == 1){
    if(sr == dim){
       return false;
   }
  }

  if(dc == 1)
  {
   if( sc == dim){
     return false;
   }
  }


  return true;

} 




bool match(wordgrid & grid, string target, size_t  sr, size_t  sc, size_t dr, size_t dc, size_t D)
{
  //testword used for capitalizing the required word 
  char testword;

  //myrow stores original row value for capitalizing later
  size_t myrow = sr;

  //mycol stores original col value for capitalizing later
  size_t mycol = sc;

  //dim stores the length of one side of grid
  size_t dim = D;
  
  //for loop to go through target each letter and compare with grid char 
  for ( size_t i = 0; i < target.length(); i++)  
    {
      // condition to check if grid character at sr,sc matches target char at position i
      if(grid.get(sr,sc) == target[i])
        {

          //if the last char of target has matched program exits loop
	  if(i == target.length()-1)
	    {
              break;
            }

          // check for out of bound row or col if below zero         
          if(!( check1(sr, sc, dr, dc, dim))){
	       return false;   }

          //increment row and col in direction (dr, dc) 
          sr += dr;
          sc += dc;

	  // check for out of bound row or col if above dim
	  if(!(check2(sr, sc, dr, dc, dim))){
	    return false;   }        
	}
      else
	{
        //returns false if char at (sr,sc) not equal to target at i position
        return false;
	}
    }
  
  // Now that word has been found, since false was not returned, we capitalize the word
  // using original (sr,sc) values stored in myrow and mycol
  for ( size_t i = 0; i < target.length(); i++)
    {
      //testword  stores the char returned by get fucntion of wordgrid
      testword = grid.get(myrow, mycol);

      //toupper function used from ctype.h library
      testword =  toupper(testword);
   
      //set function of wordgrid to capitalize the given char   
      grid.set(myrow,mycol,testword);

      // move in direction (dr,dc) to capitalize next char
      myrow += dr;
      mycol += dc;
    }
  
  // return true if word has been found by match function
  return true;

}




bool find(string word, wordgrid & grid)
{
  // integer D stores the grid dimenstion as returned by size()
  size_t D = grid.size();
  size_t sr =0; // starting row
  size_t sc =0; // starting col
  size_t dr =0; // starting row direction
  size_t dc =0; // starting col direction
  size_t i = 0; // counter for loop

  //2-D array for all possible directions to pass to the function match 
  size_t directions [8][2] = {{1,1},{1,0},{1,-1},{-1,-1},{-1,0},{-1,1}};

  //for loop to loop through every char position in grid
  for( sr = 0; sr< D; sr++)
    {
      for( sc =0; sc< D; sc++)
	{
	  // for loop for 2-D array
	  for( i =0; i < 8 ; i++){
              {
                //dr takes the first value of ith row in directions array
		dr = directions[i][0];
                //dc takes the first value of ith row in directions array
                dc = directions[i][1];

                // match function to check if word matches string in given direction
                // at (sr,sc)
                if(match(grid, word , sr, sc, dr,dc,D))
		  { 
		    //return true if match is true
                    //Word FOUND
		    return true;
		  }
         
              }        
	  }

	}
    } 

  return false;
}

//------------------------------------------------------------------------
int main()
{
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  // SETUP
  cin >> dim;  // read the dimension 
  // read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    cin >> one_row;
    all_rows += one_row;
  }
  wordgrid grid(dim, all_rows);  // create the grid from that data
  cin >> word; // read the word

  // SEARCH  (you do)
  found = find(word, grid);
  
  // REPORT
  if (found) {
    cout << "FOUND!" << endl;
    cout << grid;
  }    
  else
    cout << "NOT FOUND!" << endl;
}
