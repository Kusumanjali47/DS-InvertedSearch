#include <stdio.h>
#include <index.h>

/*Main Program*/
int main()
{
	char char_word[32], new_word[32], char_file[32], ch;

	int option;

	w_node **word_array;

	do
	{
		//read the option
		printf("Enter the option :\n1. Create Data Base\n2. Display\n3. Search word\n4. Delete word\n5. Edit word\n6. Exit\nChoose : ");
		scanf("%d", &option);

		switch (option)
		{
			case 1:
				
				//creating the data base
				word_array = create_hash_table();

				//reading the files
				read_file_names(word_array);
				
				break;

			case 2:
				
				printf("\nDATA BASE\n");

				printf("\n****************************************************************************\n");

				printf("%-15s%-15s%-15s\n", "WORD", "COUNT", "FILES");
				
				printf("\n****************************************************************************\n");

				//print
				print_hash_table(word_array);
				
				printf("****************************************************************************\n");

				break;

			case 3:

				//read the word
				printf("\nEnter the word to search :");
				scanf("%s", char_word);

				//searching the word
				search_hash_table(word_array, char_word);

				break;

			case 4:

				//read the word
				printf("\nEnter the word to delete:");
				scanf("%s", char_word);

				//read the file
				printf("\nEnter the file :");
				scanf("%s", char_file);

				//deleting the word
				delete_word_from_file(char_word, char_file);
				
				break;

			case 5:

				//read the word
				printf("\nEnter the word to edit :");
				scanf("%s", char_word);

				//read the word
				printf("\nEnter the new word :");
				scanf("%s", new_word);

				//read the file
				printf("\nEnter the file :");
				scanf("%s", char_file);

				//edit the word
				edit_word_from_file(char_word, new_word, char_file);

				break;

			case 6:

				/*exit*/
				return 0;

			default :

				printf("check the option :");

		}

		//read the continue option
		printf("Do you want to continue : (y/n)");
		scanf("\n%c", &ch);

	} while (ch == 'y');

	return 0;
}
