#define ROOT_PROCESS 0

#define ifRoot(currentRank, callback) if (currentRank == ROOT_PROCESS) callback