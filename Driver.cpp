using namespace std;
#include<unordered_set>
#include<set>
// #include "File.h"
#include "Directory.h"
#include "Driver.h"
#include<string>
// class Directory;
Driver::Driver(){
	
	cout<<"----------------------------------You are currently in Root directory-----------------------------------------------"<<endl;
	rootDirectory=new Directory("Root",NULL);
	currentDirectory=rootDirectory;
}
void Driver::init(){
	bool continueLoop=true;
	while(continueLoop){
		cout<<"CHOOSE ONE OPTION\n1. List all files and folders in current directory\n2. Change directory to a sub-directory\n3. Go back to parent directory\n4. Create a new File\n5. Create a new Directory\n6. Show content of a file\n7. Rollback a file\n8. Update a file\n9. Delete a file\n10. Delete a directory\n11. Move a directory\n12. Move a File\n13. Copy a File\n14. Exit"<<endl;
		int choice;
		cin>>choice;
		cin.ignore();
		switch(choice){
			case 1:
				ls();
				break;
			case 2:
				cd();
				break;
			case 3:
				moveToParentDirectory();
				break;
			case 4:
				createFile();
				break;
			case 5:
				createDirectory();
				break;
			case 6:
				showFile();
				break;
			case 7:
				rollBackFile();
				break;
			case 8:
				updateFile();
				break;
			case 9:
				deleteFile();
				break;
			case 10:
				deleteDirectory();
				break;
			case 11:
				moveDirectory();
				break;
			case 12:
				moveFile();
				break;
			case 13:
				copyFile();
				break;
			case 14:
				continueLoop=false;
				break;
			default:
				cout<<"Invalid choice"<<endl;
				break;
		}
	}
}
int Driver::generatePrompt(string prompt){
	cout<<prompt<<endl;
	int choice;
	cin>>choice;
	cin.ignore();
	return choice;
}
void Driver::showFile(){
	string name;
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	pair<string,bool> result=currentDirectory->getFileContent(name);
	if(result.second==false){
		return;
	}
	cout<<"The content inside the file is:"<<endl<<result.first<<endl;

}
void Driver::showContent(string &content){
	cout<<content<<endl;
}
void Driver:: ls(){
	currentDirectory->listContents();
}
void Driver::moveToParentDirectory(){
	Directory* tempNewDir=currentDirectory->getParentDirectory();
	if(tempNewDir==NULL){
		cout<<"You are already in root directory"<<endl;
		return;
	}
	this->currentDirectory=tempNewDir;
	cout<<"----------------------------------You are currently in "<<currentDirectory->getName()<<" directory-----------------------------------------------"<<endl;
}
void Driver::cd(){
	cout<<"Enter directory name to change to"<<endl;
	string dirName;
	getline(cin,dirName);
	Directory* tempNewDir=currentDirectory->changeDirectory(dirName);
	if(tempNewDir==NULL){
		cout<<"No such directory exists"<<endl;
		return;
	}
	this->currentDirectory=tempNewDir;
	cout<<"----------------------------------You are currently in "<<currentDirectory->getName()<<" directory-----------------------------------------------"<<endl;
}
void Driver::createFile(){
	string name,content="";
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	cout<<"Enter file content"<<endl;
	getline(cin,content);
	currentDirectory->createFile(name,content);
}
void Driver::createDirectory(){
	string name;
	cout<<"Enter directory name"<<endl;
	getline(cin,name);
	currentDirectory->createDirectory(name);

}
void Driver::rollBackFile(){
	string name;
	int versionToRollback;
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	cout<<"Enter version to rollback"<<endl;
	cin>>versionToRollback;
	cin.ignore();
	currentDirectory->rollbackFile(name,versionToRollback);
}
void Driver::updateFile(){
	string name,content="";
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	cout<<"Enter file content"<<endl;
	getline(cin,content);
	currentDirectory->replaceFile(name,content);
}
void Driver::deleteFile(){
	string name;
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	currentDirectory->deleteFile(name);
}
void Driver::deleteDirectory(){
	string name;
	cout<<"Enter directory name"<<endl;
	getline(cin,name);
	currentDirectory->deleteDirectory(name);
}
void Driver::moveDirectory(){
	string name;
	cout<<"Enter directory name"<<endl;
	getline(cin,name);
	string path;
	cout<<"Enter full path you want to move this directory to"<<endl;
	getline(cin,path);
	currentDirectory->moveDirectory(name,path);
}


void Driver::moveFile(){
	string name;
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	string path;
	cout<<"Enter full path you want to move this file to"<<endl;
	getline(cin,path);
	currentDirectory->moveFile(name,path);
}

void Driver::copyFile(){
	string name;
	cout<<"Enter file name"<<endl;
	getline(cin,name);
	string path;
	cout<<"Enter full path you want to copy this file to"<<endl;
	getline(cin,path);
	currentDirectory->copyFile(name,path);
}