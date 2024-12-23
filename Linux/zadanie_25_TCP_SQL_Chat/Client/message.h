#pragma once

#include <iostream>
#include <string>

class Message {
 public:
    Message() = default;
    ~Message() = default;
 
    Message(const std::string& from, const std::string& to, const std::string& text) 
        :from_(from), to_(to), text_(text){
    }
    Message(const Message& mess);
    Message& operator=(const Message& mess);
  
    const std::string& getFrom() const;
    const std::string& getTo() const;
    const std::string& getText() const;
    
    void setFrom(const std::string& from);
    void setTo(const std::string& to);
    void setText(const std::string& text);
    
 private:
    std::string from_;
    std::string to_;
    std::string text_;
};

