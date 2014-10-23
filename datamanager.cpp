#include "inc/datamanager.h"
#include "config.h"

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

	if((status = ham_env_open(&_hamEnvironment, DRECKSTOOL_DATABASE_FILE, 0, 0)) != HAM_SUCCESS)
	{
		if((status = ham_env_create(&_hamEnvironment, DRECKSTOOL_DATABASE_FILE, 0, 0644, 0)) != HAM_SUCCESS)
		{
			throw new exception();
		}
	}
}

void DataManager::getHighscore(unsigned long long* numEntries, HighscoreEntry** entries)
{
	ham_status_t status;

	ham_db_t* companyDB;
	if((status = ham_env_open_db(_hamEnvironment, &companyDB, DataManager::DatabaseCompanies, 0, 0)) != HAM_SUCCESS)
	{
		if((status = ham_env_create_db(_hamEnvironment, &companyDB, DataManager::DatabaseCompanies, HAM_RECORD_NUMBER, 0)) != HAM_SUCCESS)
		{
			throw new exception();
		}
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

	// TODO: load voting database

	*numEntries = highscore.size();
	*entries = new HighscoreEntry[*numEntries];

	int i = 0;
	for(map<unsigned long long, HighscoreEntry>::iterator it = highscore.begin(); it != highscore.end(); ++it)
	{
		(*entries)[i] = it->second;
		i++;
	}
}

void DataManager::insertCompany(std::string name)
{
	ham_status_t status;

	ham_db_t* companyDB;
	if((status = ham_env_open_db(_hamEnvironment, &companyDB, DataManager::DatabaseCompanies, 0, 0)) != HAM_SUCCESS)
	{
		if((status = ham_env_create_db(_hamEnvironment, &companyDB, DataManager::DatabaseCompanies, HAM_RECORD_NUMBER, 0)) != HAM_SUCCESS)
		{
			throw new exception();
		}
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
}
