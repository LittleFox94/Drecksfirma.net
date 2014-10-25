#include "inc/datamanager.h"
#include "config.h"

#include <algorithm>
#include <exception>
#include <map>
#include <string>
#include <iostream>
#include <string.h>
#include <ham/hamsterdb.h>

using namespace std;

ham_env_t* DataManager::_hamEnvironment;

void DataManager::connect()
{
	ham_status_t status;

	bool connected = false;
	int retryCounter = 5;

	while(!connected && retryCounter > 0)
	{
		if((status = ham_env_open(&_hamEnvironment, DRECKSTOOL_DATABASE_FILE, 0, 0)) != HAM_SUCCESS)
		{
			if(status == HAM_FILE_NOT_FOUND || status == HAM_IO_ERROR)
			{
				ham_status_t innerStatus;
				if((innerStatus = ham_env_create(&_hamEnvironment, DRECKSTOOL_DATABASE_FILE, 0, 0644, 0)) != HAM_SUCCESS)
				{
					throw new exception();
				}

				ham_db_t* database;

				if((innerStatus = ham_env_create_db(_hamEnvironment, &database, DataManager::DatabaseCompanies, HAM_RECORD_NUMBER, 0)) != HAM_SUCCESS)
				{
					throw new exception();
				}

				ham_db_close(database, 0);

				if((innerStatus = ham_env_create_db(_hamEnvironment, &database, DataManager::DatabaseVotes, HAM_RECORD_NUMBER, 0)) != HAM_SUCCESS)
				{
					throw new exception();
				}

				ham_db_close(database, 0);

				connected = true;
			}
			else if(status == HAM_WOULD_BLOCK)
			{
			}
			else if(status == HAM_ENVIRONMENT_ALREADY_OPEN)
			{
				connected = true;
			}
			else
			{
				throw new exception();
			}
		}
		else
		{
			connected = true;
		}

		retryCounter--;
	}
}

void DataManager::disconnect()
{
	ham_env_close(_hamEnvironment, HAM_AUTO_CLEANUP);
}

void DataManager::getHighscore(unsigned long long* numEntries, HighscoreEntry** entries)
{
	ham_status_t status;

	ham_db_t* companyDB;
	if((status = ham_env_open_db(_hamEnvironment, &companyDB, DataManager::DatabaseCompanies, 0, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	ham_cursor_t* companyCursor;
	if((status = ham_cursor_create(&companyCursor, companyDB, 0, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	map<unsigned long long, HighscoreEntry> highscore;

	ham_key_t key;
	ham_record_t rec;

	memset(&key, 0, sizeof(key));
	memset(&rec, 0, sizeof(rec));

	if((status = ham_cursor_move(companyCursor, &key, &rec, HAM_CURSOR_FIRST)) != HAM_SUCCESS && status != HAM_KEY_NOT_FOUND)
	{
		throw new exception();
	}

	do
	{
		unsigned long long keyNum = *(unsigned long long*)key.data;
		highscore[keyNum].Key = keyNum;
		highscore[keyNum].Votes = 0;
		highscore[keyNum].CompanyName.assign((char*)rec.data, rec.size);

		if((status = ham_cursor_move(companyCursor, &key, &rec, HAM_CURSOR_NEXT)) != HAM_SUCCESS && status != HAM_KEY_NOT_FOUND)
		{
			throw new exception();
		}
	} while (status == 0);

	ham_cursor_close(companyCursor);
	ham_db_close(companyDB, 0);

	ham_db_t* voteDB;
	if((status = ham_env_open_db(_hamEnvironment, &voteDB, DataManager::DatabaseVotes, 0, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	ham_cursor_t* voteCursor;
	if((status = ham_cursor_create(&voteCursor, voteDB, 0, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	if((status = ham_cursor_move(voteCursor, &key, &rec, HAM_CURSOR_FIRST)) != HAM_SUCCESS && status != HAM_KEY_NOT_FOUND)
	{
		throw new exception();
	}

	do
	{
		unsigned long long companyKey = *(unsigned long long*)rec.data;

		// we don't want to create new entries with invalid votes
		if(highscore.count(companyKey) == 1)
		{
			highscore[companyKey].Votes++;
		}

		if((status = ham_cursor_move(voteCursor, &key, &rec, HAM_CURSOR_NEXT)) != HAM_SUCCESS && status != HAM_KEY_NOT_FOUND)
		{
			throw new exception();
		}
	} while (status == 0);

	ham_cursor_close(voteCursor);
	ham_db_close(voteDB, 0);

	*numEntries = highscore.size();
	*entries = new HighscoreEntry[*numEntries];

	int i = 0;
	for(map<unsigned long long, HighscoreEntry>::iterator it = highscore.begin(); it != highscore.end(); ++it)
	{
		(*entries)[i] = it->second;
		i++;
	}

	stable_sort(*entries, *entries + *numEntries, DataManager::highscoreEntryCompare);
}

void DataManager::insertVote(unsigned long long companyID)
{
	ham_status_t status;

	ham_db_t* voteDB;
	if((status = ham_env_open_db(_hamEnvironment, &voteDB, DataManager::DatabaseVotes, 0, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	ham_record_t rec;
	ham_key_t key;
	memset(&rec, 0, sizeof(rec));
	memset(&key, 0, sizeof(key));

	rec.size = sizeof(companyID);
	rec.data = &companyID;

	key.size = 0;
	key.data = NULL;

	if((status = ham_db_insert(voteDB, 0, &key, &rec, 0)) != HAM_SUCCESS)
	{
		cout << "X-Debug: Insert" << endl;
		throw new exception();
	}

	if((status = ham_db_close(voteDB, 0)) != HAM_SUCCESS)
	{
		cout << "X-Debug: Close" << endl;
		throw new exception();
	}
}

void DataManager::insertCompany(std::string name)
{
	ham_status_t status;

	ham_db_t* companyDB;
	if((status = ham_env_open_db(_hamEnvironment, &companyDB, DataManager::DatabaseCompanies, 0, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	ham_record_t rec;
	ham_key_t key;
	memset(&rec, 0, sizeof(rec));
	memset(&key, 0, sizeof(key));

	rec.size = name.length() + 1;
	char cname[name.length() + 1];
	strcpy(cname, name.c_str());
	rec.data = cname;

	key.size = 0;
	key.data = NULL;

	if((status = ham_db_insert(companyDB, 0, &key, &rec, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	if((status = ham_db_close(companyDB, 0)) != HAM_SUCCESS)
	{
		throw new exception();
	}

	insertVote(*(unsigned long long*)key.data);
}

bool DataManager::highscoreEntryCompare(HighscoreEntry entry1, HighscoreEntry entry2)
{
	return entry1.Votes > entry2.Votes;
}
