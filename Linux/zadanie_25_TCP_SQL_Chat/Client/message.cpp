#include "message.h"

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

void Message::setFrom(const std::string& from) { from_ = from; }
void Message::setTo(const std::string& to) { to_ = to; };
void Message::setText(const std::string& text) { text_ = text; }
