#ifndef _DATAMANAGER_H_INCLUDED
#define _DATAMANAGER_H_INCLUDED

#include <string>
#include <ham/hamsterdb.h>

typedef struct
{
	std::string CompanyName;
	int Votes;
	unsigned long long Key;
} HighscoreEntry;

class DataManager
{
	public:
		static void connect();
		static void getHighscore(unsigned long long* numEntries, HighscoreEntry** entries);
		static void insertCompany(std::string name);

	private:
		static ham_env_t* _hamEnvironment;

		static const int DatabaseCompanies = 1;
		static const int DatabaseVotings = 2;
		static const int DatabaseHallOfShame = 3;
};

#endif
