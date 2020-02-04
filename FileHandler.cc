//
//  FileHandler.cpp
//  DBI P1
//
//  Created by Dhananjay Sarsonia on 2/1/20.
//  Copyright © 2020 Dhananjay Sarsonia and Arushi Singhvi All rights reserved.
//
#include <cstring>
#include <iostream>
#include "FileHandler.h"
#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Defs.h"
#include "Util.h"
//ToDo: change function names to start with capital cases. Don't follow java naming conventions!

FileHandler::FileHandler(){
    //ToDo: make all objects private and create getters and setters to access the objects
    file = new File();
    currentPage = new Page();
    
    //the flag is used to check two things, if file is already created and opened OR file is opened
    isFileOpenAndCreated = false;
}

FileHandler::~FileHandler()
{
    delete file;
    delete currentPage;
}

void FileHandler::moveFirst()
{
    emptyPageToFile();
    pIndex = 0;
    file->GetPage (currentPage, pIndex);
}

void FileHandler::initialiseFile(char *filepath)
{
    //first we set page index to zero
    pIndex = 0;
    //if there is any data in page refrerence we flush the page to memory before creating a new file
    emptyPageToFile();
    //starter code provides us the method to create file. if we pass 0 a new file be created if it doesn't exists or it will be overwritten and truncated
    //for now, we handled the case of an existing file as an error instead of overwriting
    file->Open(0, filepath);
    //we turn on this flag as a new file is created and opened here. our calling function is using this flag
    //ToDo: Put all the checks related to file inside this class
    isFileOpenAndCreated = true;
    
}

void FileHandler::openFileIfClosed(char *f_path){

    //set page index to 0 as we will be opening the file
    pIndex = 0;
    //turn on the flag as true indicating a file is opened
    isFileOpenAndCreated = true;
    //flush an dangling page to memory
    emptyPageToFile();
    //open the file with the starter code
    file->Open(1, f_path);
  
}


void FileHandler::loadFile(Schema &schema, const char *path)
{
    //first we load the file in read mode
    FILE *lFile = fopen(path, "r");
    //we there is no such file, the file object will point to null
    if(NULL == lFile)
    {
        
        //indicate an error that the file doesn't exists
        //ToDo: handle file error with exceptions instead of manually checking them
        cout<<"O! the file does not exist :(";
    
        //exit the code
        exit(0);
    }
    
    //The code will move here if file exists.
    //Create a record object.
    Record record;
    //set page index to 0
    pIndex = 0;
    //flush any previous page file to memory just in case
    emptyPageToFile();
    //such records from the file with the starter code provided
    while(record.SuckNextRecord(&schema, lFile)){
        //this method will create new pages if needed and flush them to memory
        addRecordToFile(record);
    }
    //when SuckNextRecord returns false, there will be page left which was never written to file and flushed
    //add page to file and add buffers if needed
    file->AddPage(currentPage, pIndex++);
    //flush the page to memory
    emptyPageToFile();
    //close the file to prevent memory leak
    fclose(lFile);
    
}

void FileHandler::closeFileIfOpen()
{
    //We might have opened a file, and might be processing records in a page
    //we will first check if there was a opened file, and page had some number of records
    if(isFileOpenAndCreated && isBufferPageNotEmpty())
    {
        // if a file was open and page had some records then we first process that page
        file->AddPage(currentPage, pIndex);
        //flush the page to memory
        emptyPageToFile();
        //turn down our flag as we will be closing the file now
        isFileOpenAndCreated = false;
    }
    //close the file
    file->Close();
    
}

void FileHandler::emptyPageToFile()
{
    //method used to flish pages to memory
    currentPage->EmptyItOut();
    
}

bool FileHandler::isBufferPageNotEmpty(){
    //boolean method used to check if buuger page is empty or not
    return currentPage->GetNumRecs()>0;
}



bool FileHandler::isFileOpen()
{
    //Future method, we will make every object private and get it through getters and setter for enhanced encapsulation of code
    return isFileOpenAndCreated;
    
}


void FileHandler::addRecordToFile(Record &record)
{
    //method used to add records to file
    //currentPage->Append returns false if the record could not be appended. This is possible when the page is full and new has to be created
    
    if(!currentPage->Append(&record))
    {
        //when the page we flush the page to memory and create a new page, and append record in that
        file->AddPage(currentPage, pIndex++);
        emptyPageToFile();
        currentPage->Append(&record);
        
    }
    
    
    
}

int FileHandler::getNextRecord(Record &record){
    //method used to get next record
    if (currentPage->GetFirst (&record)) {
        //returns true of a new record was fetched from the page
        return 1;
    } else {
        

        //if the new record was not fetched, pageindex is incremented and checked if it's still less than number of pages in the file
        //we proceed if there are new pages
        if (++pIndex < file->GetLength () - 1) {
            //we get page from the file
            file->GetPage (currentPage, pIndex);
            //we remove and return the first record from the page object
            currentPage->GetFirst (&record);
            //return true as we fetched a new record
            return 1;

        } else {
            //return false otherwise
            return 0;
            
        }
        
    }

    
    
}





