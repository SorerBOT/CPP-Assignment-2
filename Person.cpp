//
// Created by sorer on 10/04/2022.
//

#include "Person.h"
Person::Person() {
    this->m_name = NULL;
    this->m_id = 0;
}
Person::Person(const char *name, int id) {
    strcpy(this->m_name, name);
    this->m_id = id;
}
Person::Person(const Person &other) {
    strcpy(this->m_name, other.m_name);
    this->m_id = other.m_id;
}
