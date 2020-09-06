#include "cl_base.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

fstream& cl_base::get_stream() { return file; }

void cl_base::set_stream() { file.open("field.txt", ios_base::out); }

void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base* p_ob_hendler,TYPE_HANDLER p_hendler) {
    TYPE_SIGNAL p_key;
    o_sh* p_value;
    if (connects.size() > 0) {
        it_connects = connects.begin();
        while (it_connects != connects.end()) {
            p_key = it_connects->first;
            p_value = it_connects->second;
            if ((p_key) == p_signal && (p_value->p_cl_base) == p_ob_hendler &&
                (p_value->p_hendler) == p_hendler)
                return;
            it_connects++;
        }
    }
    p_value = new o_sh;
    p_value->p_cl_base = p_ob_hendler;
    p_value->p_hendler = p_hendler;
    connects.insert({ p_signal, p_value });
}
void cl_base::emit_signal(TYPE_SIGNAL p_signal, stringstream& s_command) {
    TYPE_HANDLER p_hendler;
    if (connects.empty())
        return;
    if (connects.count(p_signal) == 0)
        return;
    (p_signal)(s_command);
    it_connects = connects.begin();
    while (it_connects != connects.end()) {
        if ((it_connects->first) == p_signal) {
            p_hendler = it_connects->second->p_hendler;
            cl_base* obj = it_connects->second->p_cl_base;
            (obj->*p_hendler)(s_command);
        }
        it_connects++;
    }
}

string cl_base::get_item(string path, int level) {
    int start = 1, end, count = 1;
    while (start) {
        end = path.find('/', start);
        if (count == level)
            return path.substr(start, end - start);
        count++;
        start = end + 1;
    }
    return "";
}

cl_base* cl_base::get_root() {
    cl_base* head;
    if (object_name == "root")
        return this;
    head = p_parent;
    while (head->p_parent) {
        head = head->p_parent;
    }
    return head;
}

cl_base* cl_base::get_object_root() {
    cl_base* p_parent_previous; 
    if (object_name == "root")
        return this;
    p_parent_previous = p_parent;
    while (p_parent_previous->p_parent) {
        p_parent_previous = p_parent_previous->p_parent;
    }

    return p_parent_previous;
}
cl_base* cl_base::get_object(string path) {
    string item;
    cl_base* head, * child;
    int level = 2;
    head = get_root();
    item = get_item(path, 1);
    if (item != "root")
        return 0;
    item = get_item(path, level);
    while (!item.empty()) {
        child = head->get_child(item);
        if (child) {
            head = child;
            level++;
            item = get_item(path, level);
        }
        else
            return 0;
    }
    return head;
}

void cl_base::output(cl_base* ob_parent, int howfar) {
    if (ob_parent->get_object_name() != "root")
        cout << endl;

    for (int i = 0; i < howfar; i++) {
        cout << "    ";
    }

    cout << ob_parent->get_object_name();

    if (ob_parent->children.size() == 0)
        return;

    ob_parent->it_child = ob_parent->children.begin();

    howfar++;

    while (ob_parent->it_child != ob_parent->children.end()) {

        output(*(ob_parent->it_child), howfar);

        ob_parent->it_child++;
    }
}

cl_base::cl_base(cl_base* p_parent) {
    //-------------------------------------------------------------------------
    // Êîíñòðóêòîð
    //-------------------------------------------------------------------------

    set_object_name("cl_base");

    if (p_parent) {
        this->p_parent = p_parent;
        p_parent->add_child(this);
    }
    else {
        this->p_parent = 0;
    }
}

void cl_base::set_object_name(string s_object_name) {
    //-------------------------------------------------------------------------
    // Ïðèñâîèòü èìÿ îáúåêòó
    //-------------------------------------------------------------------------

    object_name = s_object_name;
}

string cl_base::get_object_name() {
    //-------------------------------------------------------------------------
    // Ïîëó÷èòü èìÿ îáúåêòà
    //-------------------------------------------------------------------------

    return object_name;
}

void cl_base::set_parent(cl_base* p_parent) {
    //-------------------------------------------------------------------------
    // Îïðåäåëåíèå ññûëêè íà ãîëîâíîé îáúåêò
    //-------------------------------------------------------------------------

    if (p_parent) {
        this->p_parent = p_parent;
        p_parent->children.push_back(this);
    }
}

void cl_base::add_child(cl_base* p_child) {
    //-------------------------------------------------------------------------
    // Äîáàâëåíèå íîâîãî îáúåêòà â ïåðå÷íå îáúåêòîâ-ïîòîìêîâ
    //-------------------------------------------------------------------------

    this->children.push_back(p_child);
}

void cl_base::delete_child(string s_object_name) {
    //-------------------------------------------------------------------------
    // Óäàëåíèå îáúåêòà èç ïåðå÷íÿ îáúåêòîâ-ïîòîìêîâ
    //-------------------------------------------------------------------------

    if (children.size() == 0)
        return;

    it_child = children.begin();

    while (it_child != children.end()) {

        if ((*it_child)->get_object_name() == s_object_name) {

            children.erase(it_child);
            return;
        }
        it_child++;
    }
}

cl_base* cl_base::take_child(string s_object_name) {
    //-------------------------------------------------------------------------
    // Óäàëèòü ïîä÷èíåíûé îáúåêò è âåðíóòü ññûëêó
    //-------------------------------------------------------------------------
    cl_base* ob_child;
    //-------------------------------------------------------------------------

    ob_child = get_child(s_object_name);

    if (ob_child == 0)
        return 0;

    delete_child(s_object_name);

    return ob_child;
}

cl_base* cl_base::get_child(string s_object_name) {
    //-------------------------------------------------------------------------
    // Ïîëó÷èòü ññûëêó íà îáúåêò ïîòîìîê ïî èìåíè îáúåêòà
    //-------------------------------------------------------------------------

    if (children.size() == 0)
        return 0;

    it_child = children.begin();

    while (it_child != children.end()) {

        if ((*it_child)->get_object_name() == s_object_name) {

            return (*it_child);
        }
        it_child++;
    }

    return 0;
}

void cl_base::set_state(int i_state) {
    //-------------------------------------------------------------------------
    // Îïðåäåëèòü ñîñòîÿíèå îáúåêòà
    //-------------------------------------------------------------------------

    this->i_state = i_state;
}

int cl_base::get_state() {
    //-------------------------------------------------------------------------
    // Ïîëó÷èòü ñîñòîÿíèå îáúåêòà
    //-------------------------------------------------------------------------

    return i_state;
}

void cl_base::show_object_state() { show_state_next((cl_base*)this); }

//     =====     private:     =====


void cl_base::show_state_next(cl_base* ob_parent) {
    //-------------------------------------------------------------------------
    // Âûâîä ãîòîâíîñòè (ñîñòîÿíèÿ) î÷åðåäíîãî îáúåêòà â öèêëå îáõîäà äåðåâà
    //-------------------------------------------------------------------------

    if (ob_parent->get_state() == 1) {

        cout << "The object " << ob_parent->get_object_name() << " is ready"
            << endl;
    }
    else {

        cout << "The object " << ob_parent->get_object_name() << " is not ready"
            << endl;
    }

    if (ob_parent->children.size() == 0)
        return;

    ob_parent->it_child = ob_parent->children.begin();

    while (ob_parent->it_child != ob_parent->children.end()) {

        show_state_next((*(ob_parent->it_child)));

        ob_parent->it_child++;
    }
}