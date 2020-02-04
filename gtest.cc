#include "test/gtest.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "test.h"


class FilePath{
public:

    const char *dbfile_dir = "bin/";
    const char *tpch_dir ="tpch-dbgen/";
    const char *catalog_path = "catalog"; 
    const string fileName = "nation.bin";

};




TEST(CreateTesting, Create) {
    // scenario 1: Create a file

   
    FilePath filepath;
    const string dbFilePath = filepath.dbfile_dir + filepath.fileName;
    
    cout<<"I am in create";
    DBFile dbfile;

    ASSERT_EQ(1,dbfile.Create(dbFilePath.c_str(),heap,NULL));
    dbfile.Close();
}


TEST(CreateTesting, CreateExisting)
{
    FilePath filepath;
    
     const string dbFilePath = filepath.dbfile_dir + filepath.fileName;
     cout<<"I am in create";
     DBFile dbfile;
    // checking if existing file is opened
    ASSERT_EQ(0,dbfile.Create(dbFilePath.c_str(),heap,NULL));
}


TEST(OpenTesting, Open) {

    FilePath filepath;
    DBFile dbfile;
    const string existentPath = filepath.dbfile_dir + filepath.fileName;
    
    
    // open existing file
    ASSERT_EQ(1,dbfile.Open(existentPath.c_str()));




}


TEST(OpenTesting, openAlreadyOpen)
{
    
    FilePath filepath;
    DBFile dbfile;
    const string existentPath = filepath.dbfile_dir + filepath.fileName;
    
    ASSERT_EQ(1,dbfile.Open(existentPath.c_str()));
    dbfile.Close();
    
    
}

TEST(CloseTesting, Close) {
    // scenario 1: trying to close a file which is not open
    FilePath filepath;
    cout<<"I am in close";
    DBFile dbfile;

    const string completePath = filepath.dbfile_dir + filepath.fileName;

    dbfile.Open(completePath.c_str());
    ASSERT_EQ(1,dbfile.Close());
    cout<<"This was done here";
}

TEST(CloseTesting, CloseNotOpen)
{
      FilePath filepath;
      cout<<"I am in close";
      const string completePath = filepath.dbfile_dir + filepath.fileName;
      DBFile dbfile;
      ASSERT_EQ(0,dbfile.Close());
}



TEST(CloseTesting, CloseFileDoesnotExist)
{
      FilePath filepath;
      cout<<"I am in close";
    string doesnotexist = "xyx";
      const string completePath = filepath.dbfile_dir + doesnotexist;
      DBFile dbfile;
      ASSERT_EQ(0,dbfile.Close());
}






int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
