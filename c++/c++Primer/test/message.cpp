#include <iostream>
#include <set>
#include <string>

using namespace std;

class Message;
class Folder {
public:
    Folder(){};
    ~Folder(){};

    void addMsg(Message *msg);
    void rmMsg(Message *msg);

private:
    bool isExists(Message *msg);

private:
    set<Message *> messages;
};

inline bool Folder::isExists(Message *msg)
{
    return (messages.find(msg) != messages.end());
}

void Folder::addMsg(Message *msg)
{
    if (isExists(msg)) throw logic_error("This msg already exists!");
    messages.insert(msg);
}

void Folder::rmMsg(Message *msg)
{
    if (!isExists(msg)) throw logic_error("This msg is not exists!");
    messages.erase(msg);
}

class Message {
    friend class Folder;

public:
    Message(const string cont = " ") : content(cont) {}
    Message(const Message &msg);
    Message &operator=(const Message &other);
    ~Message();

    void save(Folder *);
    void remove(Folder *);

private:
    void add_to_Folder(const set<Folder *> &folders);
    void rm_from_Folder();

private:
    string content;
    set<Folder *> folders;
};

void Message::add_to_Folder(const set<Folder *> &folders)
{
    for (auto folder : folders) {
	folder->addMsg(this);
    }
}

void Message::rm_from_Folder()
{
    for (auto folder : folders) {
	folder->rmMsg(this);
    }
}

Message::Message(const Message &msg)
    : content(msg.content), folders(msg.folders)
{
    add_to_Folder(folders);
}

Message &Message::operator=(const Message &other)
{
    content = other.content;
    rm_from_Folder();
    folders = other.folders;
    add_to_Folder(other.folders);
    return *this;
}

void Message::save(Folder *folder)
{
    folders.insert(folder);
    folder->addMsg(this);
}

void Message::remove(Folder *folder)
{
    folders.erase(folder);
    folder->rmMsg(this);
}

Message::~Message() { rm_from_Folder(); }

int main() { return 0; }
