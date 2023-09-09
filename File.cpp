#include "File.h"
// #include "Directory.h"

File :: File(Directory* parent, string name,string content){
	this->fileName=name;
	this->fileContent=content;
	this->parentDirectory=parent;
	currentVersion=1;
	fileContentByVersion.push_back(content);
}
void File::replace(string content){
	if(this->fileContent==content)return;
	this->fileContent=content;
	++currentVersion;
	fileContentByVersion.push_back(content);
}
string File::getContent(){
	return this->fileContent;
}
void File::rollback(int version){
	if(version==0)return;
	while(fileContentByVersion.size()>version)fileContentByVersion.pop_back();
	this->currentVersion=fileContentByVersion.size();
	this->fileContent=fileContentByVersion[currentVersion-1];
}
int File::getVersion(){
	return this->currentVersion;
}


