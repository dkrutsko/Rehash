////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                           Exe Hash Changing Tool                           //
//                             v1.0 - Jan 28 2014                             //
//                                                                            //
//                        (C) 2013-2014  David Krutsko                        //
//                        See LICENSE.md for copyright                        //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



//----------------------------------------------------------------------------//
// Utility                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Returns whether the string ends with ".exe". </summary>

static unsigned int EndsWithExe (const char* s)
{
	if (s != NULL)
	{
		// Compute the string size
		size_t size = strlen (s);

		// Check if ends with .exe
		if (size >= 4 &&
			 s[size-4]       == '.' &&
			(s[size-3] | 32) == 'e' &&
			(s[size-2] | 32) == 'x' &&
			(s[size-1] | 32) == 'e')
			return 1;
	}

	return 0;
}



//----------------------------------------------------------------------------//
// Main                                                                       //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// <summary> Main execution point for this application. </summary>
/// <param name="argc"> Number of arguments in the command line. </param>
/// <param name="argv"> Arguments from the command line. </param>
/// <returns> Zero for success, error code for failure. </returns>

int main (int argc, const char **argv)
{
	int i= 0; FILE* file;
	char buf[16] = { 0 };

	if (argc < 2)
	{
		// Print documentation
		printf ("\nExe Hash Changing Tool\n"											);
		printf ("-------------------------------------\n"								);
		printf ("Copyright (C) 2013-2014 David Krutsko\n\n"								);

		printf ("This  application changes  the hash of any executable  without\n"		);
		printf ("affecting its functionality. It does this by appending a block\n"		);
		printf ("of sixteen bytes to the end of the file. The first byte of the\n"		);
		printf ("block is  always zero, followed by eight  randomized bytes and\n"		);
		printf ("finishing off with seven zero bytes. Files must end with \".exe\"\n"	);
		printf ("in order to be processed. Multiple file support is included.\n\n"		);

		printf ("Input:\n"																);
		printf ("  $ Rehash [Filename1] [...]\n\n"										);

		printf ("Output:\n"																);
		printf ("  0 - No errors occurred\n"											);
		printf ("  1 - No filename was passed\n"										);
		printf ("  2 - File is not compatible\n"										);
		printf ("  3 - File could not be opened\n\n"									);

		// Not enough arguments
		return 1;
	}

	// Seed the random number generator
	srand ((unsigned int) time (NULL));

	// Iterate file arguments
	for (i = 1; i < argc; ++i)
	{
		// Check if file ends with .exe
		if (EndsWithExe (argv[i]) == 0)
			return 2;

		// Attempt to open the file
		file = fopen (argv[i], "ab");

		// Could not open the file
		if (file == NULL) return 3;

		// Randomize the buffer data
		buf[1] = rand() % 128;
		buf[2] = rand() % 128;
		buf[3] = rand() % 128;
		buf[4] = rand() % 128;
		buf[5] = rand() % 128;
		buf[6] = rand() % 128;
		buf[7] = rand() % 128;
		buf[8] = rand() % 128;

		// Append buffer to the end
		fwrite (buf, 1, 16, file);
		fclose (file);
	}

	return 0;
}
