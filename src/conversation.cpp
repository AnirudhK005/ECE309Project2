#include "core/conversation.h"

Conversation::Conversation(){
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

Conversation::~Conversation(){
    delete[] data_;
}

Conversation::Conversation(const Conversation& object){
    data_ = new Message[object.size_];
    size_ = object.size_;
    capacity_ = object.capacity_;
    for(int i = 0; i < size_; i++){
        data_[i] = object.data_[i];
    }
}

Conversation& Conversation::operator=(const Conversation& object){
    if(this != &object){
        delete[] data_;
        size_ = object.size_;
        capacity_ = object.capacity_;
        data_ = new Message[size_];
        for(int i = 0; i < size_; i++){
            data_[i] = object.data_[i];
        }
    }
    return *this;
}