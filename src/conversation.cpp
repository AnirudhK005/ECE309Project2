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

Conversation::Conversation(Conversation&& object) noexcept{
    data_ = object.data_;
    size_ = object.size_;
    capacity_ = object.capacity_;
    object.data_ = nullptr;
    object.size_ = 0;
    object.capacity_ = 0;
}

Conversation& Conversation::operator=(Conversation&& object) noexcept{
    if(this != &object){
        delete[] data_;
        data_ = object.data_;
        capacity_ = object.capacity_;
        size_ = object.size_;
        object.data_ = nullptr;
        object.capacity_ = 0;
        object.size_ = 0;
    }
    return *this;
}

void Conversation::append(Message m){
    if(size_ < capacity_){
        data_[size_] = m;
        size_++;
    } else {
        if(capacity_ == 0){
            capacity_ = 1;
        } else {
            capacity_ = capacity_ * 2;
        }
        Message* newArray = new Message[capacity_];
        for(int i = 0; i < size_; i++){
            newArray[i] = data_[i];
        }
        delete[] data_;
        data_ = newArray;
        data_[size_] = m;
        size_++;
    }
}

std::size_t Conversation::size() const noexcept {
    return size_;
}

const Message& Conversation::at(std::size_t i) const{
    if(i >= size()){
        throw std::out_of_range("Out of range");
    } else {
        return data_[i];
    }
}

const Message* Conversation::begin() const noexcept{
    return data_;
}

const Message* Conversation::end() const noexcept{
    return data_ + size_;
}

