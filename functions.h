#pragma once
#include "B+tree.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>

namespace fs = std::filesystem;

/*
	stream1:Store paths
	stream2:store names
	dirName:Name of directory to index
*/
int makeIndexFile(fstream& stream1, fstream& stream2, const char* dirName) {
	stream1.seekp(0, ios::beg);
	stream1.seekg(0, ios::beg);
	stream2.seekp(0, ios::beg);
	stream2.seekg(0, ios::beg);
	long long len1 = 0, len2 = 0;
	std::string name;
	try {
		for (const auto& entry : fs::recursive_directory_iterator(dirName)) {
			name = entry.path().filename().generic_string();
			auto find1 = name.find_last_of('.');
			auto find2 = name.find('.');
			if (find1 != 0&&find2!=0) {
				//name = name.substr(0, find1);
				if (fs::is_directory(entry.path()))
				 	stream1 << "D|" << entry.path() << "\n";
				else
					stream1 << "F|" << entry.path() << "\n";
				len1 = len2;
				len2 = stream1.tellp();
				stream2 << len1 << "|" << name << "\n";
			}
		}
	}
	catch (const std::exception & e) {
		std::cerr << e.what();
		return 1;
	}
	stream1.close();
	stream2.close();
	return 0;
}


int index(btree *b,ifstream& stream) {
	nodetype n;
	int count = 0;
	char* str=new char[200];
	if (stream) {

		try
		{
			while (stream.getline(str, 10, '|')) {
				n.loc = std::stoll(str, nullptr, 10);
				stream.getline(str, 200, '\n');
				int i = 0;
				while (str[i]) {
					str[i] = std::tolower(str[i]);
					i++;
				}
				std::string a(str);
				n.filename = a;
				b->insert(n);
				count++;
				cout << n.loc << n.filename;
			}
		}
		catch (const std::exception&)
		{
			//Error
		}
	}
	delete[] str;
	stream.close();
	return count;
}

char* search(btree* b, char* key)
{
	//Removing White Spaces and Converting to lowercase
	int j = 0;
	char* res = new char[2000];
	strcpy_s(res, 2000, "");
	for (int i = 0; key[i]; i++)
		if (key[i] != ' ')
			key[j++] = std::tolower(key[i]);
	key[j] = '\0';
	__int64 results[20];
	int n = b->search(key,results);
	char* buf = new char[100];
	if (n != 0) {
		ifstream stream("filepaths");
		if (!stream)
			return NULL;
		for (int i = 0; i < n; i++) {
			if (results[i] < 0)
				break;
			stream.seekg(results[i]);
			stream.getline(buf,100, '|');
			if (strcmp(buf, "F") == 0)
				strcat_s(res, 2000, "File:");
			else if (strcmp(buf, "D") == 0)
				strcat_s(res, 2000, "Directory:");
			else
				break;
			stream >> buf;
			//stream.getline(buf, 200);// , '\n');// '\n');
			//_itoa_s(result[i], buf, 10, 10);
			strcat_s(res, 2000, buf);
			strcat_s(res, 2000, "\r\n");
		}
		delete[] buf;
		stream.close();
		return res;
	}
	return "Nothing Found";
}


void writeToDisk(btree* b,ofstream *stream)
{
	b->traverseleaf(stream);
	stream->close();
}