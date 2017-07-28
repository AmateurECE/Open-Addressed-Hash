/*******************************************************************************
 * NAME:	    open-hash.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Contains the source code for the Open-Addressed Hash table
 *		    API, as well as source code for testing.
 *
 * CREATED:	    07/22/2017
 *
 * LAST EDITED:	    07/22/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include "open-hash.h"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int default_h1(const void *);
static int default_h2(const void *);
static int default_match(const void *, const void *);

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    ohash_init
 *
 * DESCRIPTION:	    Initializes an ohash_t object and returns a pointer to it.
 *
 * ARGUMENTS:	    positions: (int) -- the size of memory to initialize
 *		    h1: (int (*)(const void *) -- user defined hash function.
 *			See documentation.
 *		    h2: (int (*)(const void *) -- user defined hash function.
 *			See documentation.
 *		    match: (int (*)(const void *, const void *) -- user defined
 *			function for comparing keys. See documentation.
 *		    destroy: (void (*)(void *) -- user defined function for
 *			releasing allocated memory. See documentation.
 *
 * RETURN:	    ohash_t * -- pointer to an initialized ohash struct, or NULL
 *			if there was an error.
 *
 * NOTES:	    none.
 ***/
ohash_t * ohash_init(int positions,
	       int (*h1)(const void *),
	       int (*h2)(const void *),
	       int (*match)(const void *, const void *),
	       void (*destroy)(void *)
	       )
{

  ohash_t * struc = malloc(sizeof(ohash_t));
  if (struc == NULL)
    return NULL;

  *struc = (ohash_t){.positions = positions,
		     .h1 = h1 == NULL ? default_h1 : h1,
		     .h2 = h2 == NULL ? default_h2 : h2,
		     .match = match == NULL ? default_match : match,
		     .destroy = destroy,
		     .vacant = malloc(sizeof(int))
  };

  return struc;

}

/*******************************************************************************
 * FUNCTION:	    ohash_insert
 *
 * DESCRIPTION:	    Inserts an element into the ohash_t struct.
 *
 * ARGUMENTS:	    tbl: (ohash_t *) -- pointer to the struct.
 *		    data: (const void *) -- pointer to the data to insert.
 *
 * RETURN:	    int -- 0 on success, -1 if there was an error, or 1 if the
 *			element already exists in the hash.
 *
 * NOTES:	    none.
 ***/
int ohash_insert(ohash_t * tbl, const void * data)
{

  if (ohash_isfull(tbl))
    return -1;
  else if (!ohash_lookup(tbl, &data))
    return 1;

  int i = 0, index = tbl->h1(data) % tbl->positions;
  while (i < tbl->positions - 1 &&
	 tbl->table[index] != tbl->vacant &&
	 tbl->table[index] != NULL)
    int index = (tbl->h1(data) + (i * tbl->h2(k))) % tbl->positions;

  tbl->table[index] = data;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    ohash_remove
 *
 * DESCRIPTION:	    Removes an element from the list if it exists, or removes
 *		    the first element.
 *
 * ARGUMENTS:	    tbl: (ohash_t *) -- the table to query
 *		    data: (void **) -- the data to check for. If set to NULL,
 *			removes the first element.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    none.
 ***/
int ohash_remove(ohash_t * tbl, void ** data)
{

  if (data == NULL)
    return tbl->table[0];
  else if (*data == tbl->vacant || *data == NULL)
    return -1;

}

/*******************************************************************************
 * FUNCTION:	    ohash_lookup
 *
 * DESCRIPTION:	    Probes the table for an element. If the data is found,
 *		    returns it in *data. If *data is set to NULL, returns the
 *		    address of the first element.
 *
 * ARGUMENTS:	    tbl: (ohash_t *) -- the table to query.
 *		    data: (void **) -- the data to check for.
 *
 * RETURN:	    int -- 0 on success, -1 if there was a problem.
 *
 * NOTES:	    none.
 ***/
int ohash_lookup(ohash_t * tbl, void ** data)
{

  if (data == NULL && !ohash_isempty(tbl))) {
    for (int i = 0; i < tbl->positions; i++)
      if (tbl->table[i] != NULL && tbl->table[i] != tbl->vacant)
	return tbl->table[i];
} else if (*data == tbl->vacant || *data == NULL || ohash_isempty(tbl))
    return -1;

  for (int i = 0; i < tbl->positions; i++)
    if (tbl->match(*data, tbl->table[i]) && tbl->table[i] != NULL)
      return &tbl->table[i];

  return -1;
}

/*******************************************************************************
 * FUNCTION:	    ohash_destroy
 *
 * DESCRIPTION:	    Removes all elements from a hash table and frees memory
 *		    associated with it, if tbl->destroy is not set to NULL.
 *
 * ARGUMENTS:	    tbl: (ohash_t *) -- the table to destroy.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none.
 ***/
void ohash_destroy(ohash_t * tbl)
{

  if (tbl->destroy == NULL)
    goto free_struc;

  for (int i = 0; i < tbl->positions; i++)
    tbl->destroy(tbl->table[i]);

 free_struc:
  free(tbl);
}

/*******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_OPEN_HASH
int main(int argc, char * argv[])
{

  

}
#endif /* CONFIG_DEBUG_OPEN_HASH */

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    default_h1
 *
 * DESCRIPTION:	    The default hashing function, used in the case that
 *		    ohash_init is called with NULL as h1.
 *
 * ARGUMENTS:	    data: (const void *) -- the data to hash.
 *
 * RETURN:	    int -- the hashed value of the data, in the form of an int.
 *
 * NOTES:	    none.
 ***/
static int default_h1(const void * data)
{

  int key = (int)data;

}

/*******************************************************************************
 * FUNCTION:	    default_h2
 *
 * DESCRIPTION:	    The default hashing function, used in the case that
 *		    ohash_init is called with NULL as h2.
 *
 * ARGUMENTS:	    data: (const void *) -- the data to hash.
 *
 * RETURN:	    int -- the hashed value of the data, in the form of an int.
 *
 * NOTES:	    none.
 ***/
static int default_h2(const void *);

/*******************************************************************************
 * FUNCTION:	    default_match
 *
 * DESCRIPTION:	    The default hashing function, used in the case that
 *		    ohash_init is called with NULL as match.
 *
 * ARGUMENTS:	    data: (const void *) -- the data to hash.
 *
 * RETURN:	    int -- the hashed value of the data, in the form of an int.
 *
 * NOTES:	    none.
 ***/
static int default_match(const void *, const void *);

/******************************************************************************/
