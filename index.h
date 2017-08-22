#ifndef INDEX_H
#define INDEX_H

//structure for file node
typedef struct file_nodes
{
	char *file_name;

	int word_count;

	struct file_nodes *next;

}f_node;

//structure for word node
typedef struct word_nodes
{
	char *word_name;

	int file_count;

	struct file_nodes *file_head;
	
	struct word_nodes *next;

}w_node;

//creating the file node
f_node *create_file_node(char *file_name);

//creating the word node
w_node *create_word_node(char *word_name, char *file_name);

//insert first in the word list
void wl_insert_first(w_node **head, char *word_name, char *file_name);

//insert last in the word list
void wl_insert_last(w_node **head, char *word_name, char *file_name);

//insert last in the file list
void fl_insert_last(f_node **head, char *file_name);

//insert after in the word list
void wl_insert_after(w_node **head, char *word_name_1, char *word_name_2, char *file_name);

//printing the word list
void wl_print_list(w_node *head);

//printing the file list
void fl_print_list(f_node *head);

//insert sorted in the word list
void wl_insert_sorted(w_node **head, char *word_name, char *file_name);

//creating the hash table
w_node **create_hash_table(void);

//function for key
int get_index(char ch);

//creating the data base
void create_data_base(w_node **word_array, char *word_name, char *file_name);

//searching
void search_hash_table(w_node **word_array, char *word_name);

//printing the hash table
void print_hash_table(w_node **hash_array);

//reading the number files
char **read_no_files(int *limit);

//get word from the file
FILE *get_word_from_file(FILE *fptr, char *word_name);

//reading the files
void read_file_names(w_node **hash_array);

//deleting the word
void delete_word_from_file(char *word, char *file);

//editing the word
void edit_word_from_file(char *word, char *new_word, char *file);

//opening the files
FILE *file_open(char *file_name, char *mode);

#endif
