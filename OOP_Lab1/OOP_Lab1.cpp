#include "SocialNetwork.h"
#include <iostream>
using namespace std;

int main() {
    SocialNetwork net;
    int choice;
    do {
        cout << "\n--- MENU ---\n1. Add user\n2. Add friendship\n3. Add subscription\n4. Send message\n5. Add post"
            << "\n6. Show info\n7. Update bio\n8. Set birthday\n9. Set phone\n10. Set gender"
            << "\n11. Update location\n12. Add follower\n13. Add following\n14. Change reputation\n15. Find common friends"
            << "\n16. Find close friends\n17. Find common subscriptions\n18. Find users nearby (same location)"
            << "\n0. Exit\nChoice: ";


        cin >> choice;
        switch (choice) {
        case 1: {
            int id; string name, email;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Email: "; cin >> email;
            net.addVertex(new User(id, name, email));
            break;
        }
        case 2: {
            int a, b; cout << "User1 ID: "; cin >> a; cout << "User2 ID: "; cin >> b;
            net.addEdge(new Friendship(a, b));
            break;
        }
        case 3: {
            int a, b; cout << "Follower ID: "; cin >> a; cout << "Followee ID: "; cin >> b;
            net.addEdge(new Subscription(a, b));
            break;
        }
        case 4: {
            int a, b; string msg;
            cout << "Sender ID: "; cin >> a;
            cout << "Receiver ID: "; cin >> b;
            cout << "Message: "; cin.ignore(); getline(cin, msg);
            net.addEdge(new Message(a, b, msg));
            User* sender = dynamic_cast<User*>(net.findUser(a));
            User* receiver = dynamic_cast<User*>(net.findUser(b));
            if (sender) sender->sendMessage();
            if (receiver) receiver->receiveMessage();
            break;
        }
        case 5: {
            int a; string text;
            cout << "Author ID: "; cin >> a;
            cout << "Post content: "; cin.ignore(); getline(cin, text);
            net.addEdge(new Post(a, text));
            User* author = dynamic_cast<User*>(net.findUser(a));
            if (author) author->addPost();
            break;
        }
        case 6: net.print(); break;

        case 7: { 
            int id; string bio;
            cout << "User ID: "; cin >> id;
            cout << "New bio: "; cin.ignore(); getline(cin, bio);
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->updateBio(bio);
            break;
        }
        case 8: { 
            int id; string bday;
            cout << "User ID: "; cin >> id;
            cout << "Birthday: "; cin >> bday;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->setBirthday(bday);
            break;
        }
        case 9: { 
            int id; string phone;
            cout << "User ID: "; cin >> id;
            cout << "Phone: "; cin >> phone;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->setPhone(phone);
            break;
        }
        case 10: { 
            int id; string g;
            cout << "User ID: "; cin >> id;
            cout << "Gender: "; cin >> g;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->setGender(g);
            break;
        }
        case 11: { 
            int id; string loc;
            cout << "User ID: "; cin >> id;
            cout << "Location: "; cin.ignore(); getline(cin, loc);
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->updateLocation(loc);
            break;
        }
        case 12: { 
            int id; cout << "User ID: "; cin >> id;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->addFollower();
            break;
        }
        case 13: { 
            int id; cout << "User ID: "; cin >> id;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->addFollowing();
            break;
        }
        case 14: { 
            int id, delta;
            cout << "User ID: "; cin >> id;
            cout << "Change reputation by: "; cin >> delta;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) u->changeReputation(delta);
            break;
        }
        case 15: 
        {
            int id1, id2;
            cout << "User 1 ID: "; cin >> id1;
            cout << "User 2 ID: "; cin >> id2;
            User* u1 = dynamic_cast<User*>(net.findUser(id1));
            User* u2 = dynamic_cast<User*>(net.findUser(id2));
            if (u1 && u2) {
                vector<User*> common = net.findCommonFriends(u1, u2);
                if (common.empty()) cout << "No common friends.\n";
                else for (auto& u : common) u->print();
            }
            else cout << "User(s) not found.\n";
            break;
        }

        case 16: 
        {
            int id; cout << "User ID: "; cin >> id;
            User* u = dynamic_cast<User*>(net.findUser(id));
            if (u) {
                vector<User*> close = net.findCloseFriends(u);
                if (close.empty()) cout << "No close friends.\n";
                else for (auto& c : close) c->print();
            }
            else cout << "User not found.\n";
            break;
        }

        case 17: 
        {
            int id1, id2;
            cout << "User 1 ID: "; cin >> id1;
            cout << "User 2 ID: "; cin >> id2;
            User* u1 = dynamic_cast<User*>(net.findUser(id1));
            User* u2 = dynamic_cast<User*>(net.findUser(id2));
            if (u1 && u2) {
                vector<User*> commonSubs = net.findCommonSubscriptions(u1, u2);
                if (commonSubs.empty()) cout << "No common subscriptions.\n";
                else for (auto& u : commonSubs) u->print();
            }
            else cout << "User(s) not found.\n";
            break;
        }

        case 18:
        {
            string loc;
            cout << "Location: "; cin.ignore(); getline(cin, loc);
            vector<User*> usersNearby = net.findUsersWithSameLocation(loc);
            if (usersNearby.empty()) cout << "No users found for this location.\n";
            else for (auto& u : usersNearby) u->print();
            break;
        }
        }
    } while (choice != 0);
}