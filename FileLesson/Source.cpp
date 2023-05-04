#include<iostream>
using namespace std;


struct File {
	char* name;
	char* content;
};

struct HDD {
	int maxSize = 1024;// 1kb  
	int size = 0;
	File** files;
	int filecount = 0;
};


File* GetFile(const HDD& disc, const char* filename) {
	for (size_t i = 0; i < disc.filecount; i++)
	{
		if (strcmp(disc.files[i]->name, filename) == 0) {
			return disc.files[i];
		}
	}
	return nullptr;
}

int GetFileIndex(const HDD& disc, const char* filename) {
	for (size_t i = 0; i < disc.filecount; i++)
	{
		if (strcmp(disc.files[i]->name, filename) == 0) {
			return i;
		}
	}
	return -1;
}

void DeleteByIndex(HDD& disc, int index) {
	auto temp = new File * [disc.filecount - 1] {};
	for (size_t i = 0; i < index; i++)
	{
		temp[i] = disc.files[i];
	}
	for (size_t i = index; i < disc.filecount - 1; i++)
	{
		temp[i] = disc.files[i + 1];
	}
	disc.files = temp;
	temp = nullptr;
	disc.filecount--;
	cout << "File deleted successfully" << endl;
}

bool CheckFileCanAdded(const HDD& disc, const char* content) {
	auto currentSize = disc.size;
	auto total = currentSize + strlen(content);
	if (total <= disc.maxSize) {
		return true;
	}
	return false;
}
void AddFileToDisc(HDD& disc, char* filename, char* content) {
	File* newFile = new File{ filename,content };
	auto temp = new File * [disc.filecount + 1] {};
	for (size_t i = 0; i < disc.filecount; i++)
	{
		temp[i] = disc.files[i];
	}
	temp[disc.filecount] = newFile;
	disc.files = temp;
	disc.filecount += 1;
	disc.size += strlen(content);
	temp = nullptr;
}
void CreateFile(HDD& disc, char* filename, char* content) {
	if (strlen(filename) == 0) {
		cout << "Filename is empty" << endl;
		return;
	}
	if (strlen(filename) <= 4) {
		cout << "Filename should be more than 4 characters" << endl;
		return;
	}
	if (strlen(content) == 0) {
		cout << "Content is empty" << endl;
		return;
	}
	auto file = GetFile(disc, filename);
	if (file == nullptr) {
		auto canAdded = CheckFileCanAdded(disc, content);
		if (canAdded) {
			AddFileToDisc(disc, filename, content);
		}
		else {
			cout << "this content is huge for our disc capacity" << endl;
		}
	}
	else {
		cout << filename << " file is already exist" << endl;
	}
}
void ShowAllFiles(const HDD& disc) {
	cout << "DISC INFO" << endl;
	cout << "Maximum Size : " << disc.maxSize << " bytes" << endl;
	cout << "Current Size : " << disc.size << " bytes" << endl;
	cout << "Free : " << disc.maxSize - disc.size << " bytes" << endl;
	for (size_t i = 0; i < disc.filecount; i++)
	{
		cout << "\n\t\tFile Info" << endl;
		cout << "Filename : " << disc.files[i]->name << endl;
		cout << "Content : " << disc.files[i]->content << endl;
		cout << "Size : " << strlen(disc.files[i]->content) << " bytes" << endl;
	}cout << endl;
}


void RenameFile(HDD& disc, char* oldName, char* newName) {
	auto file = GetFile(disc, oldName);
	if (file == nullptr) {
		cout << oldName << " File not found" << endl;
		return;
	}
	if (strlen(newName) == 0) {
		cout << "New name is empty" << endl;
		return;
	}
	if (strlen(newName) <= 4) {
		cout << "New name should be more than 4 characters" << endl;
		return;
	}
	auto existFile = GetFile(disc, newName);
	if (existFile != nullptr) {
		cout << newName << " File already exists" << endl;
		return;
	}
	file->name = newName;
	cout << oldName << " File renamed to " << newName << endl;
}


void UbdateFileContent(HDD& disc, char* filename, char* newContent) {
	auto file = GetFile(disc, filename);
	if (file == nullptr) {
		cout << filename << " File not found" << endl;
		return;
	}
	if (strlen(newContent) == 0) {
		cout << "Content is empty" << endl;
		return;
	}
	auto contentLength = strlen(file->content);
	disc.size = disc.size - contentLength + strlen(newContent);
	file->content = new char[strlen(newContent) + 1];
	strcpy_s(file->content, strlen(newContent) + 1, newContent);
	cout << filename << " File content updated successfully" << endl;
}


void ShowMenu() {
	cout << "Show All Files      [1]" << endl;
	cout << "Add New File        [2]" << endl;
	cout << "Delete File         [3]" << endl;
	cout << "Rename File         [4]" << endl;
	cout << "Ubdate File Content [5]" << endl;
}

void main() {

	HDD disc;
	CreateFile(disc, new char[30] {"a.txt"},
		new char[30] {"Hello World"});
	CreateFile(disc, new char[30] {"b.txt"}, new char[30] {"Hello World"});

	while (true)
	{
		ShowMenu(); int select = 0;
		cin >> select;
		system("cls");
		if (select == 1)
		{
			ShowAllFiles(disc);
		}
		else if (select == 2) {
			cin.ignore();
			cin.clear();
			cout << "Enter of filename : " << endl;
			char* name = new char[50] {};
			cin.getline(name, 50);
			cout << "Enter of content : " << endl;
			char* content = new char[10000] {};
			cin.getline(content, 10000);
			CreateFile(disc, name, content);
		}
		else if (select == 3) {
			cin.ignore();
			cin.clear();
			ShowAllFiles(disc);
			cout << "Enter filename : " << endl;
			char* name = new char[50] {};
			cin.getline(name, 50);

			int index = GetFileIndex(disc, name);
			if (index == -1) {
				cout << name << " did not find" << endl;
			}
			else {
				DeleteByIndex(disc, index);
			}
		}
		else if (select == 4) {
			cin.ignore();
			cin.clear();
			ShowAllFiles(disc);
			cout << "Enter the old Filename : ";
			char* oldName = new char[20] {};
			cin.getline(oldName, 20);

			cout << "Enter the new Filename : ";
			char* newName = new char[20] {};
			cin.getline(newName, 20);
			RenameFile(disc, oldName, newName);
		}
		else if (select == 5) {
			cin.ignore();
			cin.clear();
			cout << "Enter the Filename : ";
			char* fileName = new char[20] {};
			cin.getline(fileName, 20);

			cout << "Enter the new content : ";
			char* newContent = new char[1000] {};
			cin.getline(newContent, 1000);
			UbdateFileContent(disc, fileName, newContent);
		}
	}
}

