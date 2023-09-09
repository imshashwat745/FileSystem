/*
 * Driver.h
 *
 *  Created on: 24-Aug-2023
 *      Author: sksco
 */

#ifndef DRIVER_H_
#define DRIVER_H_

using namespace std;

#include<bits/stdc++.h>
#include "Directory.h"
#include "File.h"
class Directory;
class Driver{
private:
    Directory* rootDirectory;
    Directory *currentDirectory;
public:
    Driver();
    void ls();
    void cd();
    void moveToParentDirectory();
    void createFile();
    void createDirectory();
    void showFile();
    void init();
    static int generatePrompt(string prompt);
    static void showContent(string &content);
    void rollBackFile();
    void updateFile();
    void deleteFile();
    void deleteDirectory();
    void moveDirectory();
    void moveFile();
    void copyFile();

};


#endif /* DRIVER_H_ */
