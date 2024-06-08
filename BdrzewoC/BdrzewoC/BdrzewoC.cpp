#include <iostream>
#include <fstream>
#include "BDPage.cpp";
#include "BTree.cpp";
#define D 5;

using namespace std;

int main()
{
    //cout << "Hello World!\n";
    string plik = "index";
    ofstream wf(plik, ios::out | ios::binary);
    if (!wf) {
        return 1;
    }
    int pointers[(5 * 2) + 1] = {1, 2, 3, -1, -1, -1, -1, -1, -1, -1, -1};
    int keys[5 * 2] = { 5, 10, -1, -1, -1, -1, -1, -1, -1, -1};
    int addresses[5 * 2] = { 5, 10, -1, -1, -1, -1, -1, -1, -1, -1 };
    int pointers1[(5 * 2) + 1] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    int keys1[5 * 2] = { 1, 2 , 3, -1, -1, -1, -1, -1, -1, -1 };
    int addresses1[5 * 2] = { 1, 2, 3, -1, -1, -1, -1, -1, -1, -1 };
    int pointers2[(5 * 2) + 1] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    int keys2[5 * 2] = { 6, 8, 9, -1, -1, -1, -1, -1, -1, -1 };
    int addresses2[5 * 2] = { 5, 10, 12, -1, -1, -1, -1, -1, -1, -1 };
    int pointers3[(5 * 2) + 1] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    int keys3[5 * 2] = { 12, 14, 15, -1, -1, -1, -1, -1, -1, -1 };
    int addresses3[5 * 2] = { 5, 10, 51, -1, -1, -1, -1, -1, -1, -1 };

    BTree* tree = new BTree(plik, "", true);
    BDPage* page = new BDPage(plik, 0, false);
    BDPage* page1 = new BDPage(plik, 1, true);
    BDPage* page2 = new BDPage(plik, 2, true);
    BDPage* page3 = new BDPage(plik, 3, true);
    for (int i = 0; i < 5 * 2; i++) {
        page->setKey(keys[i], i);
        page->setAddresses(addresses[i], i);
        page->setPointer(pointers[i], i);
        page1->setKey(keys1[i], i);
        page1->setAddresses(addresses1[i], i);
        page1->setPointer(pointers1[i], i);
        page2->setKey(keys2[i], i);
        page2->setAddresses(addresses2[i], i);
        page2->setPointer(pointers2[i], i);
        page3->setKey(keys3[i], i);
        page3->setAddresses(addresses3[i], i);
        page3->setPointer(pointers3[i], i);
    }
    page->setPointer(-1, pointers[5 * 2]);
    page1->setPointer(-1, pointers[5 * 2]);
    page2->setPointer(-1, pointers[5 * 2]);
    page3->setPointer(-1, pointers[5 * 2]);

    page->save();
    page1->save();
    page2->save();
    page3->save();

    for (int i = 0; i < 5; i++) {
        keys[i] = 10 + i;
        addresses[i] = rand() % 10000;
    }


    for (int i = 0; i < 5 ; i++) {
        wf.write((char*)&pointers[i], sizeof(int*));
        wf.write((char*)&keys[i], sizeof(int));
        wf.write((char*)&addresses[i], sizeof(int));
    }
    wf.write((char*)&pointers[5], sizeof(int*));
    wf.close();
    //BDPage* page = new BDPage(plik, 0, false);
    //delete page;
    //page = new BDPage("mojaNazwa", 0, true);
    //page->setKey(0, 0);
    //page->setKey(1, 1);
    //page->setKey(2, 2);
    //page->save();
    //delete page;
    //page = new BDPage("mojaNazwa", 0, false);
    //delete page;
}
