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
            << "\n19. Recommend users you may know\n20. Show most central users\n21. Check friendship cycles"
            << "\n22. Update last login time\n23. Generate random users"
            << "\n0. Exit\nChoice: ";

        cin >> choice;
        switch (choice) {
        case 1: {
            int id; string name, email;
            cout << "ID: "; cin >> id; cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Email: "; getline(cin, email);
            net.addUser(new User(id, name, email));
            break;
        }

        case 2: {
            int a, b; cout << "User1 ID: "; cin >> a; cout << "User2 ID: "; cin >> b;
            net.addFriendship(a, b);
            break;
        }

        case 3: {
            int a, b; cout << "Follower ID: "; cin >> a; cout << "Followee ID: "; cin >> b;
            net.addSubscription(a, b);
            break;
        }

        case 4: {
            int a, b; string msg;
            cout << "Sender ID: "; cin >> a;
            cout << "Receiver ID: "; cin >> b;
            cout << "Message: "; cin.ignore(); getline(cin, msg);
            net.sendMessage(a, b, msg);
            break;
        }

        case 5: {
            int a; string text;
            cout << "Author ID: "; cin >> a;
            cout << "Post content: "; cin.ignore(); getline(cin, text);
            net.addPost(a, text);
            break;
        }

        case 6: net.printNetwork(); break;

        case 7: { 
            int id; string bio;
            cout << "User ID: "; cin >> id; cin.ignore();
            cout << "New bio: "; getline(cin, bio);
            User* u = net.getUser(id);
            if (u) u->updateBio(bio);
            break;
        }

        case 8: { 
            int id; string bday;
            cout << "User ID: "; cin >> id;
            cout << "Birthday: "; cin >> bday;
            User* u = net.getUser(id);
            if (u) u->setBirthday(bday);
            break;
        }

        case 9: { 
            int id; string phone;
            cout << "User ID: "; cin >> id;
            cout << "Phone: "; cin >> phone;
            User* u = net.getUser(id);
            if (u) u->setPhone(phone);
            break;
        }

        case 10: { 
            int id; string g;
            cout << "User ID: "; cin >> id;
            cout << "Gender: "; cin >> g;
            User* u = net.getUser(id);
            if (u) u->setGender(g);
            break;
        }

        case 11: { 
            int id; string loc;
            cout << "User ID: "; cin >> id; cin.ignore();
            cout << "Location: "; getline(cin, loc);
            User* u = net.getUser(id);
            if (u) u->updateLocation(loc);
            break;
        }

        case 12: { 
            int id; cout << "User ID: "; cin >> id;
            User* u = net.getUser(id);
            if (u) u->addFollower();
            break;
        }

        case 13: { 
            int id; cout << "User ID: "; cin >> id;
            User* u = net.getUser(id);
            if (u) u->addFollowing();
            break;
        }

        case 14: { 
            int id, delta;
            cout << "User ID: "; cin >> id;
            cout << "Change reputation by: "; cin >> delta;
            User* u = net.getUser(id);
            if (u) u->changeReputation(delta);
            break;
        }

        case 15: 
        {
            int id1, id2;
            cout << "User 1 ID: "; cin >> id1;
            cout << "User 2 ID: "; cin >> id2;
            auto common = net.findMutualFriends(id1, id2);
            if (common.empty()) cout << "No common friends.\n";
            else for (auto& u : common) u->print();
            break;
        }

        case 16: 
        {
            int id; cout << "User ID: "; cin >> id;
            auto close = net.findCloseFriends(id);
            if (close.empty()) cout << "No close friends.\n";
            else for (auto& c : close) c->print();
            break;
        }

        case 17: 
        {
            int id1, id2;
            cout << "User 1 ID: "; cin >> id1;
            cout << "User 2 ID: "; cin >> id2;
            auto commonSubs = net.findCommonSubscriptions(id1, id2);
            if (commonSubs.empty()) cout << "No common subscriptions.\n";
            else for (auto& u : commonSubs) u->print();
            break;
        }

        case 18:
        {
            string loc;
            cout << "Location: "; cin.ignore(); getline(cin, loc);
            auto usersNearby = net.findUsersByLocation(loc);
            if (usersNearby.empty()) cout << "No users found for this location.\n";
            else for (auto& u : usersNearby) u->print();
            break;
        }

        case 19: { 
            int startId;
            cout << "Enter your user ID: ";
            cin >> startId;
            auto dist = net.shortestPathsFrom(startId);
            if (dist.empty()) {
                cout << "No recommendations found.\n";
            }
            else {
                cout << "Recommended users you may know\n";
                for (auto it = dist.begin(); it != dist.end(); ++it) {
                    cout << "User " << it->first << " connection distance: " << it->second << endl;
                }
            }
            break;
        }

        case 20: { 
            auto cent = net.userCentrality();
            if (cent.empty()) {
                cout << "No users found.\n";
            }
            else {
                cout << "User influence ranking\n";
                for (auto it = cent.begin(); it != cent.end(); ++it) {
                    cout << "User " << it->first << " → centrality score: " << it->second << endl;
                }
            }
            break;
        }

        case 21: { 
            auto cycles = net.detectFriendGroups();
            if (cycles.empty()) {
                cout << "No friend cycles found.\n";
            }
            else {
                cout << "Detected friend groups\n";
                for (size_t i = 0; i < cycles.size(); ++i) {
                    cout << "Group " << (i + 1) << ": (";
                    for (size_t j = 0; j < cycles[i].size(); ++j) {
                        cout << cycles[i][j];
                        if (j < cycles[i].size() - 1) cout << ", ";
                    }
                    cout << ")\n";
                }
            }
            break;
        }

        case 22: {
            int id;
            cout << "User ID: "; cin >> id;
            User* user = net.getUser(id);
            if (user) {
                char buffer[26];
                time_t lastLogin = user->getLastLogin();
                ctime_s(buffer, sizeof(buffer), &lastLogin);
                cout << "Last login: " << buffer;
            }
            else {
                cout << "User not found.\n";
            }
            break;
            }

        case 23: {
            int count;
            cout << "How many random users generate? ";
            cin >> count;
            net.generateRandomUsers(count);
            net.printNetwork();
            break;
        }
      }
    } while (choice != 0);

    return 0;
}