//
// Created by sorer on 10/04/2022.
//

#include "Person.h"
Person::Person() {
    this->m_name = NULL;
    this->m_id = 0;
}
Person::Person(const char *name, int id) {
    this->m_name = strdup(name);
    this->m_id = id;
}
Person::Person(const Person &other) {
    this->m_name = strdup(other.m_name);
    this->m_id = other.m_id;
}
Person::~Person() = default;
void Person::SetId(int newId) { this->m_id = newId; }
void Person::SetName(const char* newName) {  this->m_name = strdup(newName); }
int Person::GetId() const { return this->m_id; }
char* Person::GetName() const { return this->m_name; }
