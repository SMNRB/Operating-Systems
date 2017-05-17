/*-------------------------------------------------------------------------------------------------------------------------*/ 

 /* 
  *  	Research and analyze the POSIX alternatives for shared memory and semaphores. Describe the differences 
  *	between them and the System V mechanisms used in the previous tasks, and highlight advantages and 
  * 	disadvantages of both.
  */
  
/*-------------------------------------------------------------------------------------------------------------------------*/
	Differences:
/*-------------------------------------------------------------------------------------------------------------------------*/

	POSIX IPC is thread-safe.
	SysV IPC is NOT .
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	The semaphores, queues and shared memory for Posix have Ascii string names.
	while under System V these are given with integer number.

/*-------------------------------------------------------------------------------------------------------------------------*/

	There is no such thing for Posix.
	The System V semaphores allows to be automatically released if process dies (semop SEM_UNDO flag).
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	In System V you can control how much the semaphore count can be increased or decreased
	In POSIX, the semaphore count is increased and decreased by 1
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	It has been said that POSIX semaphore performance is better than System V-based semaphores.
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	System V semaphores, when creating a semaphore object, creates an array of semaphores whereas POSIX semaphores 
	create just one. Because of this feature, semaphore creation (memory footprint-wise) is costlier in System V 
	semaphores when compared to POSIX semaphores.
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	System V key hast to be a 16 bit unsigned integer and when the key gets removed the semeaphoron is destroyed
	In POSIX the key is arithmetic
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	System V is older
	Posix is newer and has some more features
	
/*-------------------------------------------------------------------------------------------------------------------------*/

	Alternative: TRON project https://en.wikipedia.org/wiki/TRON_project
	
