<h1> SORRY STUDY.COM DOESN'T ALLOW .C FILES. I HAD TO SUBMIT IT AS .TXT. PLEASE DON'T TAKE POINTS OFF.<h1>
<h2>Also I would've submitted the program split into multiple files under normal circumstances<h2>


/******************************************************************************

                           Intro to C project final project 

*******************************************************************************/

/*
PURPOSE: demonstrate mastery over linked lists
    Add or delete items at the beginning of the list (push and pop)
    Remove items from the end of the list
    Remove a specific item by index or by value
    Print and load linked list from file
*/

/*=============================================================================
INSTRUCTIONS

compile
    gcc -wall -werror -wextra project.c
run
    ./a.out

menu
    a [data]                |     append data to front of list
    a_file [file_name]      |     append data from file, deliminated by return
    d                       |     delete first node
    d_end                   |     delete last node
    d_index [index]         |     delete node at [index]
    d_value [data]          |     search and delete [data] if exists in list
    search [data]           |     search for [datat] and return index
    print                   |     print the list from begining
    print_file [file_name]  |     outputs file to [file_name] seperated by return
    exit                    |     terminates the program

NOTE:
    * to run enter one of the menu commands
    * replace [] with user input data, bracket inclusive
    * ex. a_file testfile 
        * adds hello to the front of the list 

==============================================================================*/


/******************************************************************************
Test cases
----------------
a world
a hello
a abc 123
a 333
a adafd
print
print_file test
exit

(restart)

a_file test
d
print
d_end
print
d_index 0
print
search 333
exit
*******************************************************************************/


/*
IMPROVEMENTS
    1. increase the buffer size to INT_MAX, but it keeps crashing my vm so I limited it to 10k works compeletly find on macos though
    2. make the UI better
    3. if I was allowed globals. I would've made a jump table with addresses to functions to make the jumptable function more concise
*/
