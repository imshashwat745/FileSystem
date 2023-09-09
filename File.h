/*
 * File.h
 *
 *  Created on: 24-Aug-2023
 *      Author: sksco
 */

#ifndef FILE_H_
#define FILE_H_


using namespace std;
#include<iostream>
#include<vector>
#include<unordered_set>
#include<set>
#include<string>
#include "Directory.h"
class Directory;
class File{
private:
    string fileName;
    string fileContent;
    Directory* parentDirectory;
    vector<string> fileContentByVersion;
    int currentVersion;
public:
    File(Directory* parent, string name,string content);
    void replace(string content);
    string getContent();
    void rollback(int version);
    int getVersion();
};



#endif /* FILE_H_ */
