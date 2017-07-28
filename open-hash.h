/*******************************************************************************
 * NAME:	    open-hash.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Contains the public interface for the Open-Addressed Hash
 *		    API.
 *
 * CREATED:	    07/22/2017
 *
 * LAST EDITED:	    07/22/2017
 ***/

/**
 * \file open-hash.h
 * \author Ethan D. Twardy
 * \date 07/22/2017
 * \brief Public interface for API
 *
 * This file contains the public interface for use with the Open-Addressed
 * Hash C Library. Please \c #include this file in any source code file
 * to use the functions contained herein.
 */

#ifndef __ET_OPEN_HASH_H__
#define __ET_OPEN_HASH_H__

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

/**
 * \brief Returns the current size of the table.
 */
#define ohash_size(tbl) ((tbl)->size)

/**
 * \brief Returns 1 if the table is full, 0 otherwise.
 */
#define ohash_isfull(tbl) ((tbl)->size == (tbl)->positions ? 1 : 0)

/**
 * \brief Returns 1 if the table is empty, 0 otherwise.
 */
#define ohash_isempty(tbl) ((tbl)->size == 0 ? 1 : 0)

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

/**
 * \brief The hash table struct
 * \warning The user should directly interface with the struct members as
 * sparingly as possible. Also note that the vacant member is only for internal
 * use, and should NEVER be referred to by the user.
 */
typedef struct ohash_t {

  int positions;
  int size;

  /* This member is for internal use only. */
  int * vacant;
  /* */

  int (*h1)(const void *);
  int (*h2)(const void *);
  int (*match)(const void *, const void *);
  void (*destroy)(void *);
  
  void ** table;

} ohash_t;

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/**
 * \brief Initializes an ohash object.
 * \param positions Number of positions for the table to be initialized with
 * \param h1 User defined hash function. Refer to mainpage of documentation
 * \param h2 User defined hash function. Refer to mainpage of documentation
 * \param match User defined hash function to compare two keys.
 * \param destroy User defined function to free associated memory.
 * \return ohash_t* Pointer to a newly generated ohash_t object. The user should
 * check that this value is not \c NULL.
 * \warning \c destroy can be set to \c NULL. If this is the case, the memory
 * associated with the hash table is not destroyed when the user calls
 * ohash_destroy.
 */
ohash_t * ohash_init(int positions,
	       int (*h1)(const void *),
	       int (*h2)(const void *),
	       int (*match)(const void *, const void *),
	       void (*destroy)(void *)
	       );

/**
 * \brief Inserts a key into the hash table, if it does not already exist.
 * \param tbl The hash table to insert the value into
 * \param data The key to insert into the table.
 * \return int 0 on success, -1 if there was an error, and 1 if the key is
 * already contained within the table.
 */
int ohash_insert(ohash_t * tbl, const void * data);

/**
 * \brief Removes a key from the hash table, if it exists.
 * \param tbl The hash table to remove the value from.
 * \param data The data to look for. See warning below.
 * \return int 0 on success, -1 if there was an error.
 * \warning if \c data is set to \c NULL, removes the first element from the
 * hash table.
 */
int ohash_remove(ohash_t * tbl, void ** data);

/**
 * \brief Determines if a value exists within the hash table.
 * \param tbl The hash table to query.
 * \param data The data to look up.
 * \return int 0 on success, -1 if there was an error.
 * \warning if \c data is set to \c NULL, returns (but does not remove) the
 * first value in the table.
 */
int ohash_lookup(ohash_t * tbl, void ** data);

/**
 * \brief Destroys a hash table and all memory associated.
 * \param tbl The table to destroy.
 * \return void
 * \warning If \codetbl->destroy\endcode is set to \c NULL, the memory within
 * the table is not freed. If this is the case, the user is responsible for
 * managing all data associated with the table.
 */
void ohash_destroy(ohash_t * tbl);

#endif /* __ET_OPEN_HASH_H__ */

/******************************************************************************/
