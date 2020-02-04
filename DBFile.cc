//  Created by Dhananjay Sarsonia on 2/1/20.
//  Copyright © 2020 Dhananjay Sarsonia. All rights reserved.
//

#include <cstring>
#include <iostream>

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include "FileHandler.h"

DBFile::DBFile () {
	//file handler is a class which handles functions related to files and pages. To preserve the state of the databases...
    //...our plan is to serialize the object in an internal bin file later
    //we are still figuring out the best ways to preserve the file state so that processes can be resumed later
    fileHandler = new FileHandler();
}

DBFile::~DBFile () {
    
	delete fileHandler;
}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {
    //used to create file. First we check if the file already exists, if it does then we return an error
    if(Util::checkIfFileExists(f_path))
    {
        cout<<"File alreadt exists";
        return 0;
    }
    //our starter code accepts char instead of const char in some functions. A copy of path with char type is created.
    strcpy(filepath, f_path);
    //more types of file types will be introduced later. current requirement only wants us to create heap type. This switch chain will be extended later based on the requirements of file type
    switch (f_type) {
        case heap:
            //initialise file through our file handler
            fileHandler->initialiseFile(filepath);
            //create file and return success code
            return 1;
            break;        
        default:
            //do nothing
            break;
    }
    cout << "The functionality is not extended to this level yet";
	
	return 0;
	
}

void DBFile::Load (Schema &f_schema, const char *loadpath) {
   //our starter code accepts char instead of const char in some functions. A copy of path with char type is created.
    strcpy(filepath, loadpath);
    //load file from filehandler
    fileHandler->loadFile(f_schema, loadpath);

}

int DBFile::Open (const char *f_path) {
	
    //check if file is already open
    if(fileHandler->isFileOpen())
    {
        // throw an error if the file was already open
        //ToDo: throw an exception when handling files instead
        cout << "file already open!";
        return 1;
    }
    //our starter code accepts char instead of const char in some functions. A copy of path with char type is created.
    strcpy(filepath, f_path);
    fileHandler->openFileIfClosed(filepath);

	return 1;
}
void DBFile::MoveFirst () {
    //move to first record in the file
    fileHandler->moveFirst();
}



int DBFile::Close () {
    //check if file is closed
    if(!fileHandler->isFileOpen())
    {
    
        //give an error if file was already open
        //ToDo: throw an exception to handle files later
        cout << "File already closed!";
    
        return 0;
    }
    //close file
    fileHandler->closeFileIfOpen();
	

	return 1;
	
}

void DBFile::Add (Record &rec) {
    //add record
    fileHandler->addRecordToFile(rec);
}

int DBFile::GetNext (Record &fetchme) {
    //get next record
    return fileHandler->getNextRecord(fetchme);
	
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
	//comparison engine to fetch record according to the CNF. Code is referenced from the main class.
	ComparisonEngine compEngine;
	
	while (GetNext (fetchme)) {
		if (compEngine.Compare (&fetchme, &literal, &cnf)){
				return 1;
			
		}
		
	}
	
	return 0;
	
}
