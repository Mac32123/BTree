#include<iostream>
#include <fstream>
#define d 5
#pragma once;

using namespace std;

struct response {
	int key;
	int address;
	int pointer;
};

class BDPage {

private:
	int pointers[(d * 2) + 1];
	int keys[d * 2];
	int addresses[d * 2];
	int myNum;
	int fill;
	bool isRoot;
	string fileName;

	response search(int key, int start, int end) {
		if (start == end) {
			response resp;
			resp.key = -1;
			resp.address = -1;
			return resp;
		}
		int index = (start + end) / 2;
		int value = keys[index];
		if (value == key) {
			response resp;
			resp.key = value;
			resp.address = addresses[index];
			return resp;
		}

	}

public:
	BDPage(string fileName, int pageNumber, bool create) {	//0 = read, 1 = create
		myNum = pageNumber;
		fill = 0;
		if (myNum == 0) isRoot = true;
		this->fileName = fileName;
			for (int i = 0; i < d * 2; i++) {
				keys[i] = -1;
				pointers[i] = -1;
				addresses[i] = -1;
			}
			pointers[d * 2] = -1;
		if(!create) {
			ifstream is(fileName, ifstream::binary);
			if(is.good()){
			int size = sizeof(int) * d * 4 + sizeof(int*) * (d * 2 + 1);
			is.seekg(0, is.end);
			int length = is.tellg();
			is.seekg(myNum * size);
			for (int i = 0; i < 2 * d; i++) {
				is.read((char*) &pointers[i], sizeof(int));
				is.read((char*)&keys[i], sizeof(int));
				is.read((char*)&addresses[i], sizeof(int));
				if (i*(3*sizeof(int)) == size) break;
			}
			is.read((char*)&pointers[2*d], sizeof(int));
			is.close();
			}
		}
	}
	void save() {
		ofstream wf;
		wf.open(fileName, ios::out | ios::binary);
		int size = sizeof(int) * d * 4 + sizeof(int) * (d * 2 + 1);
		int num = 5;
		wf.seekp(myNum * size);
		for (int i = 0; i < 2*d; i++) {
			//if (keys[i] == -1) {
			//	num = i;
			//	break;
			//}
			wf.write((char*)&pointers[i], sizeof(int));
			wf.write((char*)&keys[i], sizeof(int));
			wf.write((char*)&addresses[i], sizeof(int));
		}
		wf.write((char*)&pointers[num], sizeof(int));
		wf.close();
	}
	int getKey(int index) {
		return keys[index];
	}
	void setKey(int key, int index) {
		keys[index] = key;
	}
	int getPointer(int index) {
		return pointers[index];
	}
	void setPointer(int pointer, int index) {
		pointers[index] = pointer;
	}
	int getAddress(int index) {
		return addresses[index];
	}
	void setAddresses(int address, int index) {
		addresses[index] = address;
	}


	response search(int key) {
		//return search(key, 0, fill);
		for (int i = 0; i < 2 * d; i++) {
			if (key == keys[i]) {
				response resp;
				resp.address = addresses[i];
				resp.key = key;
				resp.pointer = -1;
				return resp;
			}
			else if(keys[i] > key) {
				response resp;
				resp.address = -1;
				resp.key = -1;
				resp.pointer = pointers[i];
				return resp;
			}
			else if (keys[i] == -1) {
				response resp;
				resp.address = -1;
				resp.key = -1;
				resp.pointer = pointers[i];
				return resp;
			}
		}
		response resp;
		resp.address = -1;
		resp.key = -1;
		resp.pointer = pointers[d*2];
		return resp;
	}

};
