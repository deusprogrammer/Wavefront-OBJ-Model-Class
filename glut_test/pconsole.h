// Pretty Console.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void PrintTextBox(char border_x, char border_y, int size_x, int size_y, char *formatStr, ...) {
	va_list args;
	char* buffer;
	char* start;
	char** lines;
	int size;
	int nLines = 0;
	int line = 0;
	int padding_x, padding_y;

	lines = new char*[size_y];

	va_start(args, formatStr);

	//size = vsprintf(NULL, formatStr, args);
	buffer = new char[1024];
	vsprintf(buffer, formatStr, args);
	size = strlen(buffer);

	va_end(args);
	
	start = buffer;
	for(int i=0; i<=size; i++)
		if(buffer[i]=='\n' || buffer[i]==0)
		{
			buffer[i] = 0;
			lines[nLines] = new char[size_x];

			int curr_size = strlen(start);
			int curr_padding = size_x - curr_size;
			int pos = 0;
			
			curr_padding/=2;
			if(curr_padding<=0)
			{
				curr_padding = 0;
				curr_size = size_x;
			}

			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			for(int j=0; j<curr_size; j++)
				pos += sprintf(lines[nLines]+pos, "%c", start[j]);
			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			if(pos<size_x)
			{
				for(int j=pos; j<size_x; j++)
					pos += sprintf(lines[nLines]+pos, " ");
			}
			
			start = buffer+i+1;
			nLines++;
		}

	padding_y = size_y - nLines;

	if(padding_y<0)
	{
		padding_y = 0;
		nLines = size_y;
	}

	//printf("Size: %d\nSize X: %d\nSize Y: %d\nPadding Y: %d\nnLines: %d\n", size, size_x, size_y, padding_y/2, nLines);
	//getchar();

	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x);
	printf("\n");
	for(int i=0; i<size_y; i++)
	{
		printf("%c", border_y);
		if(i>=padding_y/2 && i<nLines+padding_y/2)
			printf("%s", lines[line++]);
		else
		{
			for(int j=0; j<size_x; j++)
				printf(" ");
		}
		printf("%c\n", border_y);
	}
	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x);
	printf("\n");
}

void PrintTextBox(char border_x_top, char border_y_left, char border_x_bottom, char border_y_right, int size_x, int size_y, char *formatStr, ...) {
	va_list args;
	char* buffer;
	char* start;
	char** lines;
	int size;
	int nLines = 0;
	int line = 0;
	int padding_x, padding_y;

	lines = new char*[size_y];

	va_start(args, formatStr);

	//size = vsprintf(NULL, formatStr, args);
	buffer = new char[1024];
	vsprintf(buffer, formatStr, args);
	size = strlen(buffer);

	va_end(args);
	
	start = buffer;
	for(int i=0; i<=size; i++)
		if(buffer[i]=='\n' || buffer[i]==0)
		{
			buffer[i] = 0;
			lines[nLines] = new char[size_x];

			int curr_size = strlen(start);
			int curr_padding = size_x - curr_size;
			int pos = 0;
			
			curr_padding/=2;
			if(curr_padding<=0)
			{
				curr_padding = 0;
				curr_size = size_x;
			}

			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			for(int j=0; j<curr_size; j++)
				pos += sprintf(lines[nLines]+pos, "%c", start[j]);
			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			if(pos<size_x)
			{
				for(int j=pos; j<size_x; j++)
					pos += sprintf(lines[nLines]+pos, " ");
			}
			
			start = buffer+i+1;
			nLines++;
		}

	padding_y = size_y - nLines;

	if(padding_y<0)
	{
		padding_y = 0;
		nLines = size_y;
	}

	//printf("Size: %d\nSize X: %d\nSize Y: %d\nPadding Y: %d\nnLines: %d\n", size, size_x, size_y, padding_y/2, nLines);
	//getchar();

	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x_top);
	printf("\n");
	for(int i=0; i<size_y; i++)
	{
		printf("%c", border_y_left);
		if(i>=padding_y/2 && i<nLines+padding_y/2)
			printf("%s", lines[line++]);
		else
		{
			for(int j=0; j<size_x; j++)
				printf(" ");
		}
		printf("%c\n", border_y_right);
	}
	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x_bottom);
	printf("\n");
}

void PrintTextBox(char border_x, char border_y, char* formatStr, ...)
{
	va_list args;
	char* buffer;
	char* start;
	char** lines;
	int size;
	int longestLine = 0;
	int nLines = 0;
	int lineCount = 0;
	int line = 0;
	int padding_x, padding_y;
	int size_x, size_y;

	va_start(args, formatStr);

	//size = vsprintf(NULL, formatStr, args);
	buffer = new char[1024];
	vsprintf(buffer, formatStr, args);
	size = strlen(buffer);

	start = buffer;
	for(int i=0; i<=size; i++)
	{
		if(buffer[i]=='\n' || buffer[i]==0)
		{
			buffer[i] = 0;
			int curr_size = strlen(start);
			if(curr_size>longestLine)
				longestLine = curr_size;
			lineCount++;
			start = buffer + i + 1;
		}
	}
	lines = new char*[lineCount];

	size_x = longestLine;
	size_y = lineCount;

	va_end(args);
	
	start = buffer;
	for(int i=0; i<=size; i++)
	{
		if(buffer[i]=='\n' || buffer[i]==0)
		{
			buffer[i] = 0;
			lines[nLines] = new char[1024];
			int curr_size = strlen(start);
			int curr_padding = size_x - curr_size;
			int pos = 0;
			
			curr_padding/=2;
			if(curr_padding<=0)
			{
				curr_padding = 0;
				curr_size = size_x;
			}

			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			for(int j=0; j<curr_size; j++)
				pos += sprintf(lines[nLines]+pos, "%c", start[j]);
			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			if(pos<size_x)
			{
				for(int j=pos; j<size_x; j++)
					pos += sprintf(lines[nLines]+pos, " ");
			}
			
			start = buffer+i+1;
			nLines++;
		}
	}

	padding_y = size_y - nLines;

	if(padding_y<0)
	{
		padding_y = 0;
		nLines = size_y;
	}

	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x);
	printf("\n");
	for(int i=0; i<size_y; i++)
	{
		printf("%c", border_y);
		if(i>=padding_y/2 && i<nLines+padding_y/2)
			printf("%s", lines[line++]);
		else
		{
			for(int j=0; j<size_x; j++)
				printf(" ");
		}
		printf("%c\n", border_y);
	}
	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x);
	printf("\n");
}

void PrintTextBox(char border_x_top, char border_y_left, char border_x_bottom, char border_y_right, char* formatStr, ...)
{
	va_list args;
	char* buffer;
	char* start;
	char** lines;
	int size;
	int longestLine = 0;
	int nLines = 0;
	int lineCount = 0;
	int line = 0;
	int padding_x, padding_y;
	int size_x, size_y;

	va_start(args, formatStr);

	//size = vsprintf(NULL, formatStr, args);
	buffer = new char[1024];
	vsprintf(buffer, formatStr, args);
	size = strlen(buffer);

	start = buffer;
	for(int i=0; i<=size; i++)
	{
		if(buffer[i]=='\n' || buffer[i]==0)
		{
			buffer[i] = 0;
			int curr_size = strlen(start);
			if(curr_size>longestLine)
				longestLine = curr_size;
			lineCount++;
			start = buffer + i + 1;
		}
	}
	lines = new char*[lineCount];

	size_x = longestLine;
	size_y = lineCount;

	va_end(args);
	
	start = buffer;
	for(int i=0; i<=size; i++)
	{
		if(buffer[i]=='\n' || buffer[i]==0)
		{
			buffer[i] = 0;
			lines[nLines] = new char[1024];
			int curr_size = strlen(start);
			int curr_padding = size_x - curr_size;
			int pos = 0;
			
			curr_padding/=2;
			if(curr_padding<=0)
			{
				curr_padding = 0;
				curr_size = size_x;
			}

			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			for(int j=0; j<curr_size; j++)
				pos += sprintf(lines[nLines]+pos, "%c", start[j]);
			for(int j=0; j<curr_padding; j++)
				pos += sprintf(lines[nLines]+pos, " ");
			if(pos<size_x)
			{
				for(int j=pos; j<size_x; j++)
					pos += sprintf(lines[nLines]+pos, " ");
			}
			
			start = buffer+i+1;
			nLines++;
		}
	}

	padding_y = size_y - nLines;

	if(padding_y<0)
	{
		padding_y = 0;
		nLines = size_y;
	}

	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x_top);
	printf("\n");
	for(int i=0; i<size_y; i++)
	{
		printf("%c", border_y_left);
		if(i>=padding_y/2 && i<nLines+padding_y/2)
			printf("%s", lines[line++]);
		else
		{
			for(int j=0; j<size_x; j++)
				printf(" ");
		}
		printf("%c\n", border_y_right);
	}
	for(int i=0; i<size_x+2; i++)
		printf("%c", border_x_bottom);
	printf("\n");
}