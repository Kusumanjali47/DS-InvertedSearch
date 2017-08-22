#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <index.h>

/*creating the hash table*/
w_node **create_hash_table(void)
{
	int i_index;

	/*allocating dynamic memory*/
	w_node **word_array = malloc(52 * sizeof (w_node *));

	for (i_index = 0; i_index < 52; i_index++)
	{
		word_array[i_index] = NULL;
	}
	return word_array;
}

/*key for the hash function*/
int get_index(char ch)
{
	int i_index;

	/*comparing the character in between A and Z*/
	if (ch >= 'A' && ch <= 'Z')
	{
		i_index = ch - 'A';
	}
	/*comparing the character in between a and z*/
	if (ch >= 'a' && ch <= 'z')
	{
		i_index = ch - 'a' + 26;
	}
	return i_index;
}

/*Function for creating the file node in the hash table*/
f_node *create_file_node(char *file_name)
{
	int length;

	//allocating the dynamic memory
	f_node *f_new = malloc(sizeof(f_node));

	//computing the length
	length = strlen(file_name);

	//allocating the memory for file name
	f_new->file_name = malloc(length + 1);

	//copying the file_name into structure file name
	strcpy(f_new->file_name, file_name);

	//terminating the file name with the null cahracter
	f_new->file_name[length] = '\0';

	//assigning word count to 1
	f_new->word_count = 1; 

	//storing next address as null
	f_new->next = NULL;

	return f_new;
}

/*Function for creating the word list in the hash table*/
w_node *create_word_node(char *word_name, char *file_name)
{
	int length;

	//allocating the dynamic memory
	w_node *w_new = malloc(sizeof(w_node));

	//computing the length
	length = strlen(word_name);

	//allocating the memory for the word name
	w_new->word_name = malloc(length + 1);

	//copying the word name into the structure word name
	strcpy(w_new->word_name, word_name);

	//terminating the word name with the null character
	w_new->word_name[length] = '\0';

	//assigning the file count as 1
	w_new->file_count = 1;

	//creating the file node in the word list
	w_new->file_head = create_file_node(file_name);

	//assigning the next address as null
	w_new->next = NULL;

	return w_new;
}

/*Function for insering first*/
void wl_insert_first(w_node **head, char *word_name, char *file_name)
{
	//checking if the list is present or not
	if (*head == NULL)
	{
		//if the list is not present then creating the node
		*head = create_word_node(word_name, file_name);
	}
	else
	{
		//creating the new node
		w_node *new = create_word_node(word_name, file_name);

		//assigning head address to the new node link
		new->next = *head;

		//updating the head
		*head = new;
	}
}
/*Function for insert last*/
void wl_insert_last(w_node **head, char *word_name, char *file_name)
{
	//checking if the list is present or not
	if (*head == NULL)
	{
		//if the list is not present then creating the node
		*head = create_word_node(word_name, file_name);
	}
	else
	{
		w_node *ptr;

		//storing head address to thr ptr
		ptr = *head;

		//traversing the list till last node
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		//creating the node
		ptr->next = create_word_node(word_name, file_name);
	}
}

/*Function for insert last in the file list*/
void fl_insert_last(f_node **head, char *file_name)
{
	//checking if the list is present or not
	if (*head == NULL)
	{
		//if the list is not present creating the node
		*head = create_file_node(file_name);
	}
	else
	{
		f_node *ptr;

		//assigning the head address to the ptr
		ptr = *head;

		//traversing the list till last node
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		//creating the node
		ptr->next = create_file_node(file_name);
	}
}

/*Function for insert after in the word list*/
void wl_insert_after(w_node **head, char *word_name_1, char *word_name_2, char *file_name)
{
	//checking if the list is present or not
	if (*head == NULL)
	{
		//print the message
		printf("There is no word list\n");
	}
	else
	{
		w_node *ptr;

		//storing the head address to the ptr
		ptr = *head;

		//traversing the list upto the word name is found
		while (ptr != NULL && strcmp(ptr->word_name, word_name_1) != 0)
		{
			ptr = ptr->next;
		}

		//if the ptr is null
		if (ptr == NULL)
		{
			//print the word is not present
			printf("Word is not present\n");
		}
		else
		{
			//creating the new node
			w_node *new = create_word_node(word_name_2, file_name);

			//stroing the ptr next element address to the new next
			new->next = ptr->next;

			//stroing new addrees to the ptr next
			ptr->next = new;
		}
	}
}

/*Function for insert sorted in the word list*/
void wl_insert_sorted(w_node **head, char *word_name, char *file_name)
{
	//checking if the list is present or not
	if (*head == NULL)
	{
		//if the list is not present then creating the node
		*head = create_word_node(word_name, file_name);
	}
	else
	{
		w_node *ptr1, *ptr2;

		//assigningg the head address to the ptr1 and ptr2
		ptr1 = *head;

		ptr2 = *head;

		//comparing the inserting word name and the word present in the hash table
		if (strcmp(ptr1->word_name, word_name) < 0)
		{
			//if the word is less than the inserting word name.then inserting first in the word list
			wl_insert_first(head, word_name, file_name);
		}
		else
		{
			//traversing the list till last node
			while (ptr2->next != NULL)
			{
				ptr2 = ptr2->next;

				//comparing the words
				if (strcmp(ptr1->word_name, word_name) < 0 && strcmp(ptr1->word_name, word_name) > 0)
				{
					//inserting after the word if the word is in between word names present in the hash table
					wl_insert_after(head, ptr1->word_name, word_name, file_name);

					break;
				}

				ptr1 = ptr1->next;
			}

			//if the ptr2 is null
			if (ptr2->next == NULL && strcmp(word_name, ptr2->word_name) > 0)
			{
				//then inserting the word at the last
				wl_insert_last(head, word_name, file_name);
			}
		}
	}
}

/* Function for creating the data base*/
void create_data_base(w_node **word_array, char *word_name, char *file_name)
{
	int i_index;

	w_node *ptr;

	//calculating the function key
	i_index = get_index(word_name[0]);

	//assigning the hash array address to the ptr
	ptr = word_array[i_index];

	//comparing the insertin word name and the word name already present in the hash table
	while (ptr != NULL && strcmp(ptr->word_name, word_name) != 0)

		ptr = ptr->next;

	//if the ptr is not null
	if (ptr != NULL)
	{
		//storing file head address to the file node ptr
		f_node *fptr = ptr->file_head;

		//comparing the file name present in the file node and inserted file name
		while (fptr != NULL && strcmp(fptr->file_name, file_name) != 0)

			fptr = fptr->next;

		//if the file node ptr not equal to null
		if (fptr != NULL)

			//counting the words present in the file
			fptr->word_count = fptr->word_count + 1;

		else
		{	
			//inserting file 
			fl_insert_last(&ptr->file_head, file_name);

			//counting the files
			ptr->file_count = ptr->file_count + 1;
		}
	}
	else
	{
		//if the word is not present invoking the insert sorted array
		wl_insert_sorted(&word_array[i_index], word_name, file_name);
	}
}

/*Function for printing hash table*/
void print_hash_table(w_node **hash_array)
{
	int i_index = 0;

	while (i_index < 52)
	{
		if (hash_array[i_index] != NULL)

			wl_print_list(hash_array[i_index]);

		i_index++;
	}
}

/*Function for print the word list*/
void wl_print_list(w_node *head)
{
	//if the list is not present
	if (head == NULL)
	{
		printf("There is no word list\n");
	}
	else
	{
		w_node *ptr;

		ptr = head;

		while (ptr != NULL)
		{
			printf("%-15s", ptr->word_name);

			printf("%-15d", ptr->file_count);

			//printing the file list
			if (ptr->file_head != NULL)
				fl_print_list(ptr->file_head);

			ptr = ptr->next;
		}
		printf("\n");
	}
}

//printing the file list
void fl_print_list(f_node *head)
{
	//checking if the list is present or not
	if (head == NULL)
	{
		printf("There is no file list\n");
	}
	else
	{
		//if the list is present
		f_node *ptr;

		ptr = head;

		while (ptr != NULL)
		{
			printf("%-15s", ptr->file_name);

			printf("%-15d", ptr->word_count);

			ptr = ptr->next;
		}
		printf("\n\n");
	}
}

/*Function for searching the word in the hash table*/
void search_hash_table(w_node **word_array, char *word_name)
{
	int i_index;

	w_node *ptr;

	//computing the get index
	i_index = get_index(word_name[0]);

	ptr = word_array[i_index];

	//comparing the word names
	while (ptr != NULL && strcmp(ptr->word_name, word_name) != 0)
	{
		ptr = ptr->next;
	}

	//if the ptr is not null
	if (ptr != NULL)
	{
		//printing the word and file count
		printf("\n%-15s%-15s\n", "WORD", ptr->word_name);
		printf("\n%-15s%-15d\n", "FILE COUNT", ptr->file_count);

		//print the file list
		fl_print_list(ptr->file_head);
	}
	else
	{
		printf("word is not found in the given files\n");
	}
}

/*Function for to read the files*/
char **read_no_files(int *limit)
{
	char char_buffer[32];

	int i_index, length;

	//reading the number of files
	printf("Enter the number of files :");
	scanf("%d", limit);

	char **array_files = malloc((*limit) * sizeof (char *));

	//reading the file names
	for (i_index = 0; i_index < *limit; i_index++)
	{
		printf("Enter the file name %d: ", i_index + 1);

		scanf("%s", char_buffer);

		length = strlen(char_buffer);

		array_files[i_index] = malloc(length + 1);

		strcpy(array_files[i_index], char_buffer);
	}

	return array_files;
}

/*Function for get word from the file*/
FILE *get_word_from_file(FILE *fptr, char *word_name)
{
	char char_ch;

	int i_index = 0;

	//if there are no words to read
	if (feof(fptr) != 0)
	{
		word_name[0] = '\0';

		return fptr;
	}

	//if there are words read
	while (feof(fptr) == 0)
	{
		//reading the word from the file
		fread(&char_ch, 1, 1, fptr);

		//checking the delimeters
		if (char_ch < 31 || char_ch == ' ' || char_ch == '\n' || char_ch == '\t' || char_ch == ',' || char_ch == '.')
		{
			if (char_ch == ',' || char_ch == '.')
			{
				//reading the char
				fread(&char_ch, 1, 1, fptr);

				if (char_ch != ' ')

					fseek(fptr, -1, SEEK_CUR);
			}

			//storing the null
			word_name[i_index] = '\0';

			break;
		}
		else
		{
			//if there is no delimeter store the word
			word_name[i_index++] = char_ch;
		}
	}

	return fptr;
}

/*Function for reading the file names*/
void read_file_names(w_node **hash_array)
{
	int file_size, i_index;

	char file_content[32];

	FILE *fptr;

	//calling the nnumber of files function
	char **no_files = read_no_files(&file_size);

	for (i_index = 0; i_index < file_size; i_index++)
	{
		//opening the file
		fptr = fopen(no_files[i_index], "r");

		if (fptr == NULL)
		{
			printf("Error while opening files\n");

			return;
		}
		while(1)
		{
			//reading the word
			fptr = get_word_from_file(fptr, file_content);

			if (strlen(file_content) == 0)
			{
				break;
			}

			if (file_content[0] >= 'A' && file_content[0] <= 'Z' || file_content[0] >= 'a' && file_content[0] <= 'z')

				//creating the data base
				create_data_base(hash_array, file_content, no_files[i_index]);
		}

		fclose(fptr);
	}
}

/* Function for opening the file*/
FILE *file_open(char *file_name, char *mode)
{
	//open the file
	FILE *fptr = fopen(file_name, mode);

	//sanity check
	if (fptr == NULL)
	{
		printf("Error...File couldn't be opened\n");
	}

	return fptr;
}


/*Function for delete word*/
void delete_word_from_file(char *word, char *file)
{
	int length = strlen(word), r_byte = 0, sflag = 1, flag = 0, dflag = 0, index;
	char buff[100], ch;

	//open the file in the read mode
	FILE *fptr = file_open(file, "r");
	if (fptr == NULL)
		return;

	//open the temp file in the write mode
	FILE *temp = file_open("temp.txt", "w");
	if (temp == NULL)
		return;

	//reading the bytes from the file
	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		//checking the char
		if (flag || sflag || dflag || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
		{
			//clearing the flags
			sflag = 0;

			dflag = 0;

			//setting the flags
			flag = 1;
		}

		else

			flag = 0;

		//if the ch is equal to word first char
		if (flag && ch == word[0])
		{
			index = 0;

			//storing into the buffer
			buff[index++] = ch;

			while (1)
			{
				//reading the from the source file
				fread(&ch, 1, 1, fptr);

				//checking the delimeters
				if ('!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
				{
					dflag = 1;

					buff[index] = '\0';

					break;
				}

				//storing the char
				buff[index++] = ch;
			}

			//coparing the word and buffer
			if (strcmp(word, buff) == 0)
			{
				//writing into the temp file
				fwrite(&ch, 1, 1, temp);

				continue;
			}

			else
			{
				//writing the contents except that word into the temp file
				fwrite(buff, strlen(buff), 1, temp);

				fwrite(&ch, 1, 1, temp);
			}
		}

		else

			fwrite(&ch, 1, 1, temp);
	}

	//closing the temp and fptr file
	fclose(fptr);
	fclose(temp);

	//opening the fptr in the write mode
	fptr = file_open(file, "w");
	if (fptr == NULL)
		return;

	//opening the temp file in the read mode
	temp = file_open("temp.txt", "r");
	if (temp == NULL)
		return;

	//writing the contents of temp file to fptr
	while (feof(temp) == 0)
	{
		//reading the bytes
		r_byte = fread(buff, 1, 100, temp);

		buff[r_byte] = '\0';

		//writing the bytes
		fwrite(buff, 1, r_byte, fptr);
	}
}

/*Function for editing the word from the file*/
void edit_word_from_file(char *word, char *new_word, char *file)
{
	int length = strlen(word), r_byte = 0, flag = 0, sflag = 1, dflag = 0, index;
	char buff[100], ch;

	//opening the file in the read mode
	FILE *fptr = file_open(file, "r");
	if (fptr == NULL)
		return;

	//opening the file in the write mode
	FILE *temp = file_open("temp.txt", "w");
	if (temp == NULL)
		return;

	//reading the bytes upto EOF
	while (feof(fptr) == 0)
	{
		fread(&ch, 1, 1, fptr);

		//checking the delimeters
		if (flag || sflag || dflag || '!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
		{
			//clearing the flags
			sflag = 0;
			dflag = 0;

			//setting the flags
			flag = 1;
		}

		else

			flag = 0;

		//if the ch and word first char are same
		if (flag && ch == word[0])
		{
			index = 0;

			//stroing into the buffer
			buff[index++] = ch;

			while (1)
			{
				fread(&ch, 1, 1, fptr);

				//checking for the delimeters
				if ('!' <= ch && ch <= '/' || ':' <= ch && ch <= '@' || ch == ' ' || ch == '\n' || ch == '\t')
				{
					dflag = 1;

					buff[index] = '\0';

					break;
				}

				//storing the cahr to buffer
				buff[index++] = ch;
			}

			//comparing the word and buffer
			if (strcmp(word, buff) == 0)
			{
				fwrite(new_word, strlen(new_word), 1, temp);
				fwrite(&ch, 1, 1, temp);

				continue;
			}

			else
			{
				//writing the all the content
				fwrite(buff, strlen(buff), 1, temp);

				fwrite(&ch, 1, 1, temp);
			}
		}

		else

			fwrite(&ch, 1, 1, temp);

	}

	//closing the files
	fclose(fptr);
	fclose(temp);

	//opening the file in the write mode
	fptr = file_open(file, "w");
	if (fptr == NULL)
		return;

	//opening the file in the read mode
	temp = file_open("temp.txt", "r");
	if (temp == NULL)
		return;

	//reading the bytes till EOF
	while (feof(temp) == 0)
	{
		//read the bytes and write into the fptr
		r_byte = fread(buff, 1, 100, temp);
		buff[r_byte] = '\0';
		fwrite(buff, 1, r_byte, fptr);
	}
}

