#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
#include <ostream>
using namespace std;

class ItemInfo
{
    int curBid;
    int totalBids;
    int sucBids;
    int rejectBids;
public:
    ItemInfo(int StartBid = 0)
    {
        curBid = StartBid;
        totalBids = 0;
        sucBids = 0;
        rejectBids = 0;
    }
    ~ItemInfo() {}
    void placeBid(int bid)
    {
        if (bid > curBid)
        {
            curBid = bid;
            sucBids++;
        }
        else
        {
            rejectBids++;
        }
        totalBids++;
    }
    void setCurBid(int bid)
    {
        curBid = bid;
    }
    int getCurBid()
    {
        return curBid;
    }
    int getTotalBid()
    {
        return totalBids;
    }
    int getSuccessBid()
    {
        return sucBids;
    }
    int getRejectBid()
    {
        return rejectBids;
    }
    friend ostream& operator<<(ostream& os, const ItemInfo& item)
    {
        os << item.curBid;
        return os;
    }
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 1;
    }

    // TODO: Declare data structures to track bid statistics for each item
    // You need to track: total bids, successful bids, rejected bids for each item
    // Hint: You may use additional BSTs or other data structures
    // Start your code here
    ListBST<string, ItemInfo> auction;
    // End your code here

    int n;
    string itemID;
    int StartBid,Bid;
    int allBids = 0,allSucBids = 0,allRejBids = 0;

    in_file >> n;
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read initial items and their starting bids
        // Initialize statistics tracking for each item
        // Start your code here
        in_file >> itemID >> StartBid;
        if (auction.find(itemID) && auction.get(itemID).getCurBid() < StartBid)
        {
            ItemInfo temp = auction.get(itemID);
            temp.setCurBid(StartBid);
            auction.update(itemID, temp);
        }
        else
        {
            auction.insert(itemID, ItemInfo(StartBid));
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial auction state
    // Start your code here
    ofstream out_file("out2.txt");
    streambuf *old_buff = cout.rdbuf();
    cout.rdbuf(out_file.rdbuf());
    cout << "Initial auction items:" << endl;
    cout << "BST (In-order): ";
    auction.print('A');
    // End your code here
    cout << "\nAuction starts!\n\n";
    cout << "==============================\n";

    string operation;
    while (in_file >> operation)
    {
        // TODO: Implement the logic to process operations (ADD, BID, CHECK, STATS, REPORT) and print auction state after each operation
        // For BID operations: update statistics (total bids, successful/rejected counts)
        // For STATS operations: display statistics for the specified item
        // For REPORT operations: display comprehensive auction statistics
        // For other operations: print auction state using in-order traversal
        // Start your code here
        if (operation == "ADD")
        {
            in_file >> itemID >> StartBid;
            if (auction.find(itemID) && auction.get(itemID).getCurBid() < StartBid)
            {
                ItemInfo temp = auction.get(itemID);
                temp.setCurBid(StartBid);
                auction.update(itemID, temp);
            }
            else
            {
                auction.insert(itemID, ItemInfo(StartBid));
            }
            cout << "Item " << itemID << " added with starting bid " << auction.get(itemID).getCurBid() << endl;
            cout << "BST (In-order): ";
            auction.print('A');
            cout << endl;
        }
        else if (operation == "BID")
        {
            in_file >> itemID >> Bid;
            
            ItemInfo temp = auction.get(itemID);
            
            if(Bid > temp.getCurBid()){
                allSucBids++;
                cout << "Bid of " << Bid << " on " << itemID << " accepted. Current Bid: " << Bid << endl; 
            }
            else{
                allRejBids++;
                cout << "Bid of " << Bid << " on " << itemID << " rejected. Current Bid: " << temp.getCurBid() << endl;
            }

            temp.placeBid(Bid);
            auction.update(itemID, temp);
            allBids++;
            cout << "BST (In-order): ";
            auction.print('A');
            cout << endl;
        }
        else if (operation == "CHECK")
        {
            in_file >> itemID;

            ItemInfo temp = auction.get(itemID);
            cout << "Current bid for " << itemID << ": " << temp.getCurBid() << endl;
            cout << "BST (In-order): ";
            auction.print('A');
            cout << endl;
        }
        else if (operation == "STATS")
        {
            in_file >> itemID;

            ItemInfo temp = auction.get(itemID);

            cout << "Statistics for " << itemID << ":" << endl;
            //Current highest bid: 600
            //Total bids placed: 2
            //Successful bids: 1
            //Rejected bids: 1
            cout << "   Current highest bid: " << temp.getCurBid() << endl;
            cout << "   Total bids placed: " << temp.getTotalBid() << endl;
            cout << "   Successful bids: " << temp.getSuccessBid() << endl;
            cout << "   Rejected bids: " << temp.getRejectBid() << endl;
        }
        else if (operation == "REPORT")
        {
            cout << "Auction Report:" << endl;
            cout << "Total items: " << auction.size() << endl;
            cout << "Total bids placed: " << allBids << endl;
            cout << "Total successful bids: " << allSucBids << endl;
            cout << "Total rejected bids: " << allRejBids << endl;
            
            cout << endl;

            cout << "Item Statistics: " << endl;
            auction.print('R');
        }

        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    // TODO: Delete data structures you created
    // Start your code here
    cout.rdbuf(old_buff);
    out_file.close();
    // End your code here
    return 0;
}
