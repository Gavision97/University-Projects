JerryBoreeMain :
I used 5 data structures in the project:

1. JerryHash - HashTable that contains pointers to Jerries ids as keys and Jerries objects as values.
2. JerryID - LinkedList that contains pointers to Jerry id
3. JerryMVHT - MultiValueHashTable that contains pointers to physical characteristics and keys and 
LinkedList of pointers to Jerries ids as values.
4. PhyLinkedList - LinkedList of all of the physical charateristic that exist in the program in a given time.
5. planet_arr - Array of planets in shape of poiner to poiner, the array contain all of the planets from the configuration file. 
( No restrictions in the project to make ** array to the planets)

Notes: All of the free function and copy function at the data structures that contain *pointers* instead of real data does not
make any functionality. For example : in JerryID linked list which contain pointers to Jerries ids, the free function doesnot free the id,
it's just return, so the the real value doesn't got deleted (See JerryBoreeMain.c).

 - finishcript function gets also flag, the flag represent what data structes we want to destroy because at every other stage in the program
we have other data structures. For exapl, if the program crashes when we read the planets, we will destroy only the planets, thus flag = 1 
(not other data structure initiallize in that stage). At the end when we finish the program flag = 4 and the function knows to destroy ALL
of the data stuctures.

 - Few changes been made in Jerry.c - some Get function added to help in JerryBoreeMain.c 
