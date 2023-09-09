/*
 * Directory.h
 *
 *  Created on: 24-Aug-2023
 *      Author: sksco
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

using namespace std;
#include<bits/stdc++.h>
#include "File.h"
#include "Driver.h"

class File;

class Directory{
private:
    string directoryName;
    Directory *parentDirectory;
    map<string,Directory*> subDirectories;
    map<string,File*> files;
    int index;
    void deleteDirectoryHelper(Directory* currentDirectory);
    Directory* getDirectoryFromPath(string path);
public:
    Directory();
    Directory(string name,Directory* parent);
    string getName();
    pair<string,bool> getFileContent(string name);
    void createFile(string name,string content);
    void createDirectory(string name);
    void listContents();
    Directory* changeDirectory(string name);
    Directory* getParentDirectory();
    void rollbackFile(string name,int version);
    void replaceFile(string name,string content);
    void deleteFile(string name,bool askPrompt=true);
    void deleteDirectory(string name);
    void moveDirectory(string name,string path);
    void moveFile(string name,string path);
    void copyFile(string name,string path);
};


#endif /* DIRECTORY_H_ */
