#ifndef DBFILE_H
#define DBFILE_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "FileHandler.h"
#include "Util.h"
typedef enum {heap, sorted, tree} fType;

class DBFile {
protected:
	fType filetype;
    char filepath[50];
    FileHandler *fileHandler;

public:
	DBFile ();
	~DBFile ();

	int Create (const char *fpath, fType file_type, void *startup);
	int Open (const char *fpath);
	int Close();
	void Load (Schema &myschema, const char *loadpath);

	void MoveFirst ();
	void Add (Record &addme);
	int GetNext (Record &fetchme);
	int GetNext (Record &fetchme, CNF &cnf, Record &literal);

};
#endif
