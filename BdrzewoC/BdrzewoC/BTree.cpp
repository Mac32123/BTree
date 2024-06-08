#include <iostream>
#include "BDPage.cpp";
#pragma once;

using namespace std;


class BTree {
private:
    BDPage* actPage;
    string indexFile;
    string recordsFile;
public:

    BTree(string indexFile, string recordsFile, bool create) {
        indexFile = indexFile;
        recordsFile = recordsFile;
        if (create) {
            actPage = new BDPage(indexFile, 0, true);
            actPage->save();
        }
    }

    response search(int key) {
        delete actPage;
        response resp;
        actPage = new BDPage(indexFile, 0, false);          //actPage == root
        resp = actPage->search(key);
        if (resp.key != -1) return resp;
        else if (resp.pointer == -1) return resp;
        else {
            while (resp.pointer != -1) {
                delete actPage;
                actPage = new BDPage(indexFile, resp.pointer, false);
                resp = actPage->search(key);
                if (resp.key != -1) return resp;
            }
            return resp;
        }
    }

    ~BTree() {
        delete actPage;
    }

};