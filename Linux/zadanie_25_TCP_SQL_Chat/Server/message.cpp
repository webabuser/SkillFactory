#include "message.h"

Message::Message(const std::string& from, const std::string& to, const std::string& text) 
        :from_(from), to_(to), text_(text){
        
}


Message::Message(const Message& mess){
    //if(this == &mess) return;
    
    from_ = mess.from_;
    to_   = mess.to_;
    text_ = mess.text_;
}

Message& Message::operator=(const Message& mess){
     if(this == &mess) return *this;
     
    from_ = mess.from_;
    to_   = mess.to_;
    text_ = mess.text_;
    
    return *this;
}

const std::string& Message::getFrom() const {return from_; }
const std::string& Message::getTo() const {return to_; }
const std::string& Message::getText() const {return text_; }

void Message::setFrom(const std::string& from)
{
    from_ = from;

    std::string query = "SELECT id FROM users WHERE login = '" + from_ + "'";

    db_ptr_ -> DbQuery(query);
    std::map<size_t, std::vector<std::string>> result =  db_ptr_ -> GetResult();
    sender_id_ = std::stoi(result[0][0]);
}


void Message::setTo(const std::string& to)
{
    to_ = to;


    std::string query = "SELECT id FROM users WHERE login = '" + to_ + "'";

    db_ptr_ -> DbQuery(query);
    std::map<size_t, std::vector<std::string>> result =  db_ptr_ -> GetResult();
    receiver_id_ = std::stoi(result[0][0]);

};


void Message::setText(const std::string& text) { text_ = text; }

bool Message::Create()
{
    std::string query = "INSERT INTO messages \
                         SET \
                         sender_id = (SELECT id FROM users WHERE login = '" + from_ + "'), \
                         receiver_id = (SELECT id FROM users WHERE login = '" + to_ + "'), \
                         text = '" + text_ + "'";

    db_ptr_->DbQuery(query);
    if(db_ptr_->UDIresult()) return true;
    return false;
}    


bool Message::CreateForAll()
{
    std::string query = "INSERT INTO messages (sender_id, receiver_id, text) \
                         VALUES ('" + std::to_string(sender_id_) + "','" + std::to_string(receiver_id_) + "','" + text_ + "')";
    db_ptr_->DbQuery(query);
    if(db_ptr_->UDIresult()) return true;
    return false;
}


std::map<size_t, std::vector<std::string>> Message::Read()
{
    std::string query = "SELECT * FROM messages WHERE sender_id = (SELECT id FROM users WHERE login = '"+ from_ +"' ";
    
    db_ptr_ -> DbQuery(query);
    return db_ptr_->GetResult();
}


std::map<size_t, std::vector<std::string>> Message::ReadReceiver()
{
    std::string query = "SELECT * FROM messages WHERE receiver_id = '"+ std::to_string(receiver_id_) +"'";
    
    db_ptr_ -> DbQuery(query);
    return db_ptr_->GetResult();
}
