#include <string>
#include <iostream>

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

    Role               role()    const noexcept;
    const std::string& content() const noexcept;

private:
    Role        role_;
    std::string content_;
};