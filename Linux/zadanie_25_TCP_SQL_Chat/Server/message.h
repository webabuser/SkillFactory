#pragma once

#include <iostream>
#include <string>
#include "db.h"

class Message {
 public:
    Message() = default;
    ~Message() = default;
 
    Message(const std::string& from, const std::string& to, const std::string& text); 
    Message(const Message& mess);
    Message& operator=(const Message& mess);
  

    
    bool Create();
    bool CreateForAll();

    std::map<size_t, std::vector<std::string>> Read();
    std::map<size_t, std::vector<std::string>> ReadReceiver();
    
    bool Update();
    bool Delete();



    const std::string& getFrom() const;
    const std::string& getTo() const;
    const std::string& getText() const;
    
    void setFrom(const std::string& from);
    void setTo(const std::string& to);
    void setText(const std::string& text);
    
 private:
    Database * db_ptr_ =  Database::GetSinglton();  
    
    std::string from_;
    std::string to_;

    std::string text_;
    size_t sender_id_ = 0;
    size_t receiver_id_ = 0;
    std::string created_;
};

