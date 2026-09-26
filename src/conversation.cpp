#include "core/conversation.h"

Conversation::Conversation(){
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

Conversation::~Conversation(){
    delete[] data_;
}