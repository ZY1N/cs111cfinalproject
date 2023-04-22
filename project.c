/******************************************************************************

                           Intro to C project final project 

*******************************************************************************/

// NOTE IMPORTANT PLEASE READ
/*
    Study.com doesn't allow .c files. So I had to turn it in as a .txt.
    PLEASE CHANGE IT TO .C BEFORE COMPILING.
*/

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

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

//linkedlist structure aliased as ll
typedef struct linked_list{
    char *data;
    struct linked_list * next;
} ll;


/*============================================================================================
REPEAT GENERAL FUNCTIONS
    1. REMOVE_SPACE() - removes spaces infront and new lines from end
    2. IS_NUM() - checks to see if all characters in string are numbers, for atoi to work
    3. CREATE_NODE() - takes a ll poninter and a piece of data, makes new node and returns it
    4. PRINT_SUCCESS() - visual prompt to show user that command worked
    5. PRINT_MENU() - prints the menu of commands available to user
    6. GRAB_DATA() - grabs the data as arguments for processing, deletes ws
============================================================================================*/

//trims the beginning spaces and ending new line chars
char *remove_space(char *data)
{
    char *rtn = NULL;
    int start = 0;
    int end = 0;
    int counter = 0;
    int size = 0;

    //find indexes of the begining and end
    while (data[start] && data[start] == ' ')
    {
        start++;
    }
    end = strlen(data);

    // 8 is ascii backspace 32 is ascii space
    while (end != 0 && !(data[end] >= 8 && data[end] <= 32))
    {
        end --;
    }
    
    //if the string is empty afterwards
    if (start == end)
    {
        return (rtn);
    }

    //malloc memory and copy over the data
    size = end - start;
    rtn = (char *) malloc(sizeof(char) * size);
    
    //edge case of data1
    do{
        rtn[counter] = data[start];
        start++;
        counter++;
    } while (start < end);

    rtn[counter] = '\0';

    return (rtn);
}

int is_num(char *str)
{
    int i = 0;

    //loop through str and check to see if within character range
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            return (0);
        }
        i++;
    }

    return (1);
}

//create node
ll * create_node(char *data)
{
    ll *new;

    //allocate and init the node data
    new = (ll *)malloc(sizeof(ll));
    new->data = strdup(data);
    new->next = NULL;
    return (new);
}

//trimmer for spaces new lines
void print_success()
{
    printf("----------------------------------\n");
    printf("COMPLETE\n");
    printf("----------------------------------\n");
}

//prints the menu for the user
void print_menu()
{
    printf("MENU\n");
    printf("=====================================================================\n");
    printf("\t a [data]                |     append data to front of list\n");
    printf("\t a_file [file_name]      |     append data from file, deliminated by return\n");
    printf("\t d                       |     delete first node\n");
    printf("\t d_end                   |     delete last node\n");
    printf("\t d_index [index]         |     delete node at [index]\n");
    printf("\t d_value [data]          |     search and delete [data] if exists in list \n");
    printf("\t search [data]           |     search for [datat] and return index\n");
    printf("\t print                   |     print the list from begining \n");
    printf("\t print_file [file_name]  |     outputs file to [file_name] seperated by return\n");
    printf("\t exit                    |     terminates the program \n");
    printf("\n NOTE:  \n");
    printf("\t * to run enter one of the menu commands \n");
    printf("\t * replace [] with user input data, bracket inclusive \n");
    printf("\t\t * ex. \"a hello world\"\n");
    printf("\t PRINTS NOTHING ON SUCCESS, ONLY ON ERROR\"\n");
    printf("=====================================================================\n");
}

//read data from stand in and removes spaces
char *grab_data()
{
    char new_data[10000];
    char *temp = NULL;

    //grab the rest of standard input
    fgets(new_data, 10000, stdin);
    //remove the prepending/postpending spaces 
    temp = remove_space(new_data);

    return (temp);
}

/*============================================================================================
REPEAT GENERAL FUNCTIONS
    1. D_VALUE() - takes a value, seaches list and deletes it
    2. D_INDEX() - takes index, searches list and delets it if in range
    3. D_END() - traverses list and deletes the last element
    4. SEARCH() - takes string, traverses list and returns the index if found
    5. A_FILE() - takes a filename, tries to open it, and build a linkedlist out of it
    6. PRINT_FILE - prints the entire list to a file
    7. PRINT_LIST() - prints list onto screen
============================================================================================*/

//delete node by matching value
ll *d_value(ll *head, char *new_data)
{
    ll *current = NULL;
    ll *placeholder = NULL;

    if (head != NULL)
    {
        //traverse to end of linkedlist and then delete it, check to see if there is 
        current = head;
        placeholder = current;
        while (current->next)
        {
            if (strcmp(current->data, new_data) == 0)
            {
                break;
            }
            placeholder = current;
            current = current->next;
        }

        //check to see if index is within range
        if (strcmp(current->data, new_data) == 0)
        {
            //if the current is equal to head then that means there is only 1 node
            if (current == head)
            {
                //then we set head to head next, which is NULL
                head = head->next;
            }
            else
            {
                //relink n-1 to n+1
                placeholder->next = current->next;
                if (placeholder == head)
                {
                    head = NULL;
                }
                //free data and the node
                free(current->data);
                free(current); 
            }
            print_success();
        }
        else
        {
            printf("----------------------------------\n");
            //otherwise print not in range and exit
            printf("value not found in list\n");
            printf("----------------------------------\n");
        }
    }
    return (head);
}

//delete node by index
ll *d_index(ll *head, int index)
{
    ll *current = NULL;
    ll *placeholder = NULL;
    int counter = 0;

    if (head != NULL)
    {
        //traverse to end of linkedlist and then delete it, check to see if there is 
        current = head;
        placeholder = current;
        //printf("\ncurrent: %s\n", current->next);
        while (current->next && counter < index)
        {
            placeholder = current;
            current = current->next;
            counter++;
        }
        //check to see if index is within range
        if (counter == index)
        { 
            //if the current is equal to head then that means there is only 1 node
            if (current == head && counter == 0)
            {
                //then we set head to head next
                head = head->next;
            }
            else
            {
                //relink n-1 to n+1
                placeholder->next = current->next;
                //free data and the node
                free(current->data);
                free(current); 
            }
            print_success();
        }
        else
        {
            //otherwise print not in range and exit
            printf("----------------------------------\n");
            printf("index not in range\n");
            printf("----------------------------------\n");
        }
    }
    return (head);
}

//delete the last node
ll *d_end(ll *head)
{
    ll *current = NULL;
    ll *placeholder = NULL;
        
    if (head != NULL)
    {
        //traverse to end of linkedlist and then delete it, check to see if there is 
        current = head;
        placeholder = current;
        //printf("\ncurrent: %s\n", current->next);
        while (current->next)
        {
            placeholder = current;
            current = current->next;
        }
        //set placeholder next to NULL 
        placeholder->next = NULL;
        
        //once we reach the NULL delete it
        free(current->data);
        free(current);
        //set head to NULL for return if there is only 1 node
        if (placeholder == current)
        {
            head = NULL;
        }
        print_success();
    }
    else{
        printf("----------------------------------\n");
        printf("can't list empty\n");
        printf("----------------------------------\n");
    }
    return (head);
}

//search and return index
void search(ll *head, char *temp)
{
    int counter = 0;
    ll *current = NULL;
    int flag = 0;
    
    //go through linkedlist and print all of them with index
    if (head != NULL)
    {
        //traverse to end of linkedlist and then delete it, check to see if there is 
        current = head;

        while (current)
        {
            //printf("%s\n", temp);
            if (strcmp(current->data, temp) == 0)
            {
                printf("----------------------------------\n");
                printf("index:%d\t | \t%s\n",counter, temp);
                printf("----------------------------------\n");
                flag = 1;
                break;
            }
            counter++;
            current = current->next;
        }

        //if flag triggers nothing is found tell the user
        if (flag == 0)
        {
            printf("----------------------------------\n");
            printf("not found\n");
            printf("----------------------------------\n");
        }
    }
    else
    {
        //otherwise print not in range and exit
        printf("----------------------------------\n");
        printf("list is empty\n");
        printf("----------------------------------\n");
    }
}



//load 
ll * a_file(ll *head, char *file_name)
{
    FILE *handle = NULL;
    char tmp[10000];
    ll *current = NULL;
    
    //printf("|%s|\n", file_name);

    //open and check to see if file exists
    //handle = fopen(file_name, "r");
    handle = fopen(file_name, "r");
    if (handle == NULL)
    {
        printf("----------------------------------\n");
        printf("file doesn't exist\n");
        printf("----------------------------------\n");
        return (head);
    }
    
    //loop through the file 
    while (fgets(tmp, 10000, handle) != NULL)
    {
        // push each tmp to the front of the linkedlist
        current = create_node(remove_space(tmp));
        
        //swap head and new
        current->next = head;

        head = current;
        //printf("prepended succesffuly%d", head->next);z
    }
    //close filehandler
    print_success();
    fclose(handle);
    return (head); 
}



//print list
void print_file(ll *head, char *file_name)
{
    ll *tmp = head;
    int counter = 0;
    FILE *handle = NULL;


    //open up file in write mode
    handle = fopen(file_name,"w");


    if (handle == NULL)
    {
        printf("----------------------------------\n");
        printf("failed to open file\n");
        printf("----------------------------------\n");
    }
    //loop through the list till next is NULL
    while (tmp != NULL)
    {
        fprintf(handle, "%s\n", tmp->data);
        tmp = tmp->next;
        counter++;
    }
    print_success();
    fclose(handle);
}

//print list
void print_list(ll *head)
{
    ll *tmp = head;
    int counter = 0;

    //if its empty don't do anything
    if (head == NULL)
    {
        printf("----------------------------------\n");
        printf("List is empty\n");
        printf("----------------------------------\n");
    }
    else
    {
        //loop through the list till next is NULL
        while (tmp != NULL)
        {
            printf("index:%d\t | \t%s\n",counter, tmp->data);
            tmp = tmp->next;
            counter++;
        }
    }
}

//add to the beginning of list
ll * append(ll * head, char * temp)
{
    ll * current = NULL;

     //malloc a new node and add in data
    current = create_node(temp);
        
    //swap head and new
    current->next = head;
    head = current;

    return (head);
}

//delete from the beginning of list
ll * delete(ll * head)
{
    ll *current = NULL;
    // delete the first node
    //check to see if it is the last node
    if (head)
    {
        current = head->next;
        free(head->data);
        free(head);
        head = current;
        print_success();
    }
    return (head);
}


/*============================================================================================
JUMP TABLE - this checks stdin and tries to match it to a KEYWORD found in menu
    a
    a_file
    d
    d_end
    d_index
    d_value
    search
    print
    print_file
    exit
============================================================================================*/

//broke jump table in half for readibility
ll * jump_table_two(char * buffer, ll *head)
{
    char *temp = NULL;
    char new_data[10000];

    if (strcmp(buffer, "search") == 0)
    {
        //grab data remove spaces
        temp = grab_data();

        //if it doesn't have any characters besides ws
        if (temp == NULL){   
            return (head);
        }

        search(head, temp);
        free(temp);
    }
    else if (strcmp(buffer, "print") == 0)
    {
        //go through linkedlist and print all of them with index
        print_list(head);
    }
    else if (strcmp(buffer, "print_file") == 0)
    {
        //temp to get file name/location
        temp = grab_data();

        //don't bother if temp is empty
        if (temp == NULL){   
            return (head);
        }

        //abort if temp is empty
        if (strlen (temp) == 0)
        {
            printf("invalid filename\n");
        }
        else
        {
            print_file(head, temp);
            free(temp);
        }
    }
    else if (strcmp(buffer, "exit") == 0)
    {
        //exit the program
        exit(0);
    }
    else
    {
        //base case if something invalid was entered
        printf("invalid entry, try again\n");
        //clear the standardin
        fgets(new_data, 10000, stdin);
    }
    return (head);
}

//table that grabs initial argument, compare it to usable commands and feed the function in
ll * jump_table(char *buffer, ll *head)
{
    char *temp = NULL;
    int index = 0;
    
    //check to see if buffer is one of our valid options
    if (strcmp(buffer, "a") == 0)
    {
        //get the data to put into a
        temp = grab_data();

        if (temp == NULL){   
            return(head);
        }

        //create, insert and swap nodes
        head = append(head, temp);

        //free temp and print sucess
        print_success();
        free(temp);
    }
    else if (strcmp(buffer, "a_file") == 0)
    {
        //grab the argument and trim it
        temp = grab_data();

        //remove space fails that means it is empty string
        if (temp == NULL){
            printf("invalid file\n");   
            return (head);
        }
        
        //processing function, returns new head pointer
        head = a_file(head, temp);
        free(temp);
    }
    else if (strcmp(buffer, "d") == 0)
    {
        //jump to function and receive the new pointer to start
        head = delete(head);
    }
    else if (strcmp(buffer, "d_end") == 0)
    {
        head = d_end(head);
    }
    else if (strcmp(buffer, "d_index") == 0)
    {
        //prompt the user for the index and then go delete it
        temp = grab_data();

        //check for non valid temp
        if (temp == NULL){   
            return (head);
        }

        //check to see if temp is actuallhy a number
        if (is_num(temp) == 0)
        {

            printf("invalid index\n");
        }
        else
        {
            //jump to worker function
            index = atoi(temp);
            head = d_index(head, index);
        }

       free(temp);
    }
    else if (strcmp(buffer, "d_value") == 0)
    {
        //function ask for value and then go delete it
        temp = grab_data();
    
        if (temp == NULL){   
            return (head);
        }
        head = d_value(head, temp);
        free(temp);
    }
    else
    {
        head = jump_table_two(buffer, head);
    }

    return (head);
}

/*============================================================================================
MAIN - holds the loop till "exit" is entered
============================================================================================*/
int main()
{
    //init variables
    char input_buffer[10000];
    ll * head = NULL;
    
    //print instructions for users 
    print_menu();

    //infinite loop to keep getting inputs till termination
    while (1){
        //scanf the input to the input_buffer variable
        scanf("%s", input_buffer);
        
        //now validate the input and jump it to corresponding function
        head = jump_table(input_buffer, head);
    }
    
    //delete the entire list, free memory
    while ((head = d_end(head))){}
    
    return 0;
}
