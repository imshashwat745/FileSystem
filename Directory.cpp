using namespace std;
#include "Directory.h"
#include<bits/stdc++.h>
#include "File.h"
// #include "Driver.h"


Directory::Directory(){
	parentDirectory=NULL;
	index=0;
}
Directory::Directory(string name,Directory* parent){
	this->directoryName=name;
	this->parentDirectory=parent;
	index=0;
}
void Directory::createFile(string name,string content){
	if(files.find(name)!=files.end()){
		string sameFileNamePrompt="ERROR There already exists a file with name\nEnter 1 to replace the old file\nEnter any other digit to cancel";
		int promptResult=Driver::generatePrompt(sameFileNamePrompt);
		if(promptResult==1){
			replaceFile(name,content);
		}else{
			return;
		}
	}else{
		File *newFile=new File(this,name,content);
		files[name]=newFile;
		string prompt="File created successfully";
		Driver::showContent(prompt);
	}
}
void Directory::listContents(){
	string content="Directories:\n";
	for(auto subDirectory:subDirectories){
		content+=subDirectory.first;
		content+="\n";
	}
	content+="Files:\n";
	for(auto file:files){
		content+=file.first;
		content+="\n";
	}
	Driver::showContent(content);
}
void Directory::replaceFile(string name,string content){
	if(files.find(name)==files.end()){
		string prompt="No such file exists";
		Driver::showContent(prompt);
		return;
	}
	File *file=files[name];
	file->replace(content);
	string prompt="Content updated successfully";
	Driver::showContent(prompt);
}
void Directory::createDirectory(string name){
	if(subDirectories.find(name)!=subDirectories.end()){
		string sameFolderNamePrompt="ERROR There already exists a folder with name, exitting this request,change the name to continue";
		Driver::showContent(sameFolderNamePrompt);
		return;
	}else{
		Directory *newDirectory=new Directory(name,this);
		subDirectories[name]=newDirectory;
		string prompt="Directory created successfully";
		Driver::showContent(prompt);
	}
}
Directory* Directory::getParentDirectory(){
	return this->parentDirectory;
}
Directory* Directory::changeDirectory(string name){
	if(subDirectories.find(name)==subDirectories.end()){
		return NULL;
	}
	return subDirectories[name];
}
string Directory::getName(){
	return this->directoryName;
}
pair<string,bool> Directory::getFileContent(string name){
	if(files.find(name)==files.end()){
		string prompt="No such file exists";
		Driver::showContent(prompt);
		return {"",false};
	}
	return {files[name]->getContent(),true};
}
void Directory:: rollbackFile(string name,int version){
	if(files.find(name)==files.end()){
		string prompt="No such file exists";
		Driver::showContent(prompt);
		return;
	}
	else if(files[name]->getVersion()<version){
		string prompt="ERROR current version running is "+to_string(files[name]->getVersion())+" and you are asking to rollback to version "+to_string(version);
		Driver::showContent(prompt);
	}
	files[name]->rollback(version);
	string prompt="File rolledback to version "+to_string(version)+" successfully";
	Driver::showContent(prompt);
}
void Directory::deleteFile(string name,bool askPrompt){
	if(files.find(name)==files.end()){
		string prompt="No such file exists";
		Driver::showContent(prompt);
		return;
	}
	if(askPrompt){
		string confirmationPrompt="Are you sure you want to delete this file, press 1 to delete, any other digit to cancel";
		int confirmation=Driver::generatePrompt(confirmationPrompt);
		if(confirmation!=1)return;
	}
	delete files[name];
	files.erase(name);
	if(askPrompt){
		string confirmationPrompt="File deleted successfully";
		Driver::showContent(confirmationPrompt);
	}
}
void Directory::deleteDirectoryHelper(Directory* currentDirectory){
	// Recursively deletes a directory and its sub directories and file
	for(auto file:currentDirectory->files){
		currentDirectory->deleteFile(file.first,false);
	}
	for(auto subDirectory:currentDirectory->subDirectories){
		deleteDirectoryHelper(subDirectory.second);
	}
	// When all its files and folders are deleted, delete it also
	delete currentDirectory;
	// Use this line to avoid invalid memory access
	currentDirectory=NULL;


}
void Directory::deleteDirectory(string name){
	if(subDirectories.find(name)==subDirectories.end()){
		string prompt="No such Directory exists";
		Driver::showContent(prompt);
		return;
	}
	string confirmationPrompt="Are you sure you want to delete this directory it may contain files and other directories, press 1 to delete, any other digit to cancel";
	int confirmation=Driver::generatePrompt(confirmationPrompt);
	if(confirmation!=1)return;
	
	deleteDirectoryHelper(subDirectories[name]);
	// Remove the directory entry from the map
	subDirectories.erase(name);
	confirmationPrompt="Directory deleted successfully";
	Driver::showContent(confirmationPrompt);
}
Directory* Directory::getDirectoryFromPath(string path){
	Directory *root=this;
	while(root->parentDirectory!=NULL)root=root->parentDirectory;
	Directory *curr=root;
	int i=0;
	string currentDirectoryName="";
	if(path.size()>0&&path[path.size()-1]!='/')path+='/';
	for(i=1;i<path.size();++i){
		if(path[i]=='/'){
			if(curr->subDirectories.find(currentDirectoryName)==curr->subDirectories.end()){
				// No such path exists
				return NULL;
			}
			curr=curr->subDirectories[currentDirectoryName];
			currentDirectoryName="";
		}
		else currentDirectoryName+=path[i];
	}
	return curr;
}


void Directory::moveDirectory(string name,string path){
	if(subDirectories.find(name)==subDirectories.end()){
		string prompt="No such Directory exists which you are asking to move, in current directory";
		Driver::showContent(prompt);
		return;
	}
	Directory *destinationDirectory=getDirectoryFromPath(path);
	if(destinationDirectory==NULL){
		string prompt="No such path exists to move the directory";
		Driver::showContent(prompt);
		return;
	}
	if(destinationDirectory==this){
		string prompt="The destination path is already the current path hence no change would be reflected";
		Driver::showContent(prompt);
		return;
	}
	if(destinationDirectory->subDirectories.find(name)!=destinationDirectory->subDirectories.end()){
		string prompt="The destination path already has a directory with the same name, could not move";
		Driver::showContent(prompt);
		return;
	}
	destinationDirectory->subDirectories[name]=this->subDirectories[name];
	this->subDirectories.erase(name);
	string prompt="Directory moved successfully";
	Driver::showContent(prompt);
}




void Directory::moveFile(string name,string path){
	if(files.find(name)==files.end()){
		string prompt="No such File exists which you are asking to move, in current directory";
		Driver::showContent(prompt);
		return;
	}
	Directory *destinationDirectory=getDirectoryFromPath(path);
	if(destinationDirectory==NULL){
		string prompt="No such path exists to move the directory";
		Driver::showContent(prompt);
		return;
	}
	if(destinationDirectory==this){
		string prompt="The destination path is already the current path hence no change would be reflected";
		Driver::showContent(prompt);
		return;
	}
	if(destinationDirectory->files.find(name)!=destinationDirectory->files.end()){
		string prompt="The destination path already has a file with the same name, could not move";
		Driver::showContent(prompt);
		return;
	}
	destinationDirectory->files[name]=this->files[name];
	this->files.erase(name);
	string prompt="File moved successfully";
	Driver::showContent(prompt);
}


void Directory::copyFile(string name,string path){
	if(files.find(name)==files.end()){
		string prompt="No such File exists which you are asking to copy, in current directory";
		Driver::showContent(prompt);
		return;
	}
	Directory *destinationDirectory=getDirectoryFromPath(path);
	if(destinationDirectory==NULL){
		string prompt="No such path exists to copy the file";
		Driver::showContent(prompt);
		return;
	}
	if(destinationDirectory==this){
		string prompt="The destination path is already the current path hence no change would be reflected";
		Driver::showContent(prompt);
		return;
	}
	if(destinationDirectory->files.find(name)!=destinationDirectory->files.end()){
		string prompt="The destination path already has a file with the same name, could not copy";
		Driver::showContent(prompt);
		return;
	}
	destinationDirectory->files[name]=this->files[name];
	string prompt="File copied successfully";
	Driver::showContent(prompt);
}