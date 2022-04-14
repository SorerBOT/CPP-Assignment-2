/*
* Name: Alon Filler
* ID: 216872374
* */
#include "Person.h"
// Person blank constructor.
Person::Person() {
    this->m_name = NULL;
    this->m_id = 0;
}
// Person constructor which generates a person using a given name and id.
Person::Person(const char *name, int id) {
    this->m_name = strdup(name);
    this->m_id = id;
}
// Person copy constructor.
Person::Person(const Person &other) {
    this->m_name = strdup(other.m_name);
    this->m_id = other.m_id;
}
// Person destructor.
Person::~Person() = default;
// Sets the m_id member of a Person.
void Person::SetId(int newId) { this->m_id = newId; }
// Sets the m_name member of a Person.
void Person::SetName(const char* newName) {  this->m_name = strdup(newName); }
// Returns a Person's m_id member.
int Person::GetId() const { return this->m_id; }
// Returns a Person's m_name member.
char* Person::GetName() const { return this->m_name; }
