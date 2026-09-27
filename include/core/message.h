#include <string>
#include <iostream>
#pragma once

enum class Role { System, User, Assistant };

class Message {
public:
    Message(){
        role_ = Role::System;
        content_ = "";
    }

    Message(Role role, std::string content){
        role_ = role;
        content_ = content;
    }

    Role role() const noexcept{
        return this->role_;
    }

    const std::string& content() const noexcept {
        return this->content_;
    }

private:
    Role        role_;
    std::string content_;
};