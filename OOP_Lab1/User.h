#ifndef USER_H
#define USER_H

#include "Graph.h"
#include <string>
#include <ctime>

class User : public Vertex {
private:
    string name;
    string email;
    string biography;
    string location;
    string phone;
    string birthday;
    string gender;
    time_t lastLogin;
    int reputation; 
    int followers;
    int following;
    int postsCount;
    int messagesSent;
    int messagesReceived;
public:
    User(int id, const string n, const string e);

    void updateBio(const string& b);
    void setBirthday(const string& bday);
    void setPhone(const string& ph);
    void setGender(const string& g);
    void updateLocation(const string& loc);
    string getLocation() const { return location; }
    
    void addFollower();
    void addFollowing();
    void addPost();
    void sendMessage();
    void receiveMessage();
    void changeReputation(int delta);


    string getName() const { return name; }
    string getEmail() const { return email; }
    string getBio() const { return biography; }
    void print() const override;
};

class Friendship : public Edge {
public:
    Friendship(int f, int t); 
    void print() const override;
};

class Subscription : public Edge {
public:
    Subscription(int f, int t); 
    void print() const override;
};

class Message : public Edge {
    string text;
public:
    Message(int f, int t, string msg);
    void print() const override;
    const string& getText() const { return text; }
};

class Post : public Edge {
    string content;
public:
    Post(int f, string c);
    void print() const override;
    const string& getContent() const { return content; }
};

#endif // USER_H
 
