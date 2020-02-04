//
//  FileHandler.hpp
//  DBI P1
//
//  Created by Dhananjay Sarsonia on 2/1/20.
//  Copyright © 2020 Dhananjay Sarsonia and Arushi Singhvi All rights reserved.
//

#ifndef FileHandler_h
#define FileHandler_h



#include <stdio.h>

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"


class FileHandler{
    
public:
    //ToDo: make the objects private and get them from getters and setters later
    File *file;
    Page *currentPage;
    off_t pIndex;
    char path[50];
    bool isFileOpenAndCreated;
    
    
    //Filehandler constructor and distructor
    FileHandler(); 
    ~FileHandler();
    bool isFileOpen();
    bool isBufferPageNotEmpty();
    void loadFile(Schema &schema, const char *path);
    void initialiseFile(char *filepath);
    void closeFileIfOpen();
    void addRecordToFile(Record &record);
    void openFileIfClosed(char *f_path);
    void emptyPageToFile();
    void moveFirst();
    int getNextRecord(Record &record);
    
    
};

#endif /* FileHandler.h */
